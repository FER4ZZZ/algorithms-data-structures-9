// Задание 1
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    // Открываем входной файл для чтения и выходной для записи
    ifstream in("input.txt");
    ofstream out("output.txt");
    
    // Фраза, буквы которой нужно удалить из текста
    string forbidden = "useragreement";
    
    // Массив-флаг: isForbidden[c] == true, если символ c нужно удалять
    // Размер 256 — покрывает все возможные значения типа unsigned char (ASCII)
    bool isForbidden[256] = {false};
    
    // Заполняем флаги для каждого символа фразы в обоих регистрах
    for (char c : forbidden) {
        isForbidden[(unsigned char)tolower(c)] = true;  // строчная буква
        isForbidden[(unsigned char)toupper(c)] = true;  // заглавная буква
    }
    
    // Читаем файл построчно (на случай нескольких строк)
    string line;
    while (getline(in, line)) {
        string result;  // сюда собираем "очищенную" строку
        
        // Проходим по каждому символу строки
        for (char c : line) {
            // Если символ НЕ запрещён — оставляем его
            if (!isForbidden[(unsigned char)c]) {
                result += c;
            }
        }
        
        // Записываем результат в выходной файл с переводом строки
        out << result << "\n";
    }
    
    // Закрываем файлы
    in.close();
    out.close();
    return 0;
}

//Задание 1.1
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cctype>
using namespace std;

int main() {
    // Открываем входной и выходной файлы
    ifstream in("input.txt");
    ofstream out("output.txt");
    
    // Множество запрещённых символов (в нижнем регистре)
    set<char> forbidden;
    
    // Заполняем множество буквами из фразы "user agreement"
    string phrase = "useragreement";
    for (char c : phrase) {
        forbidden.insert(c);  // все буквы во фразе уже строчные
    }
    
    // Читаем файл построчно
    string line;
    while (getline(in, line)) {
        string result;
        
        // Проходим по каждому символу строки
        for (char c : line) {
            // Приводим символ к нижнему регистру для проверки,
            // чтобы "U" и "u" считались одинаковыми
            char lower = (char)tolower((unsigned char)c);
            
            // Если символа нет в множестве запрещённых — оставляем его
            // (важно: добавляем ИСХОДНЫЙ символ c, а не lower,
            //  чтобы сохранить регистр разрешённых букв)
            if (forbidden.find(lower) == forbidden.end()) {
                result += c;
            }
        }
        
        out << result << "\n";
    }
    
    in.close();
    out.close();
    return 0;
}

// Задание 2
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // X — строка из монолога Карлина, Y — строка из стэндапа Продольного
    ifstream in1("input1.txt");
    ifstream in2("input2.txt");
    
    string X, Y;
    getline(in1, X);  // читаем первую строку целиком (с пробелами)
    getline(in2, Y);  // читаем вторую строку целиком
    
    // Убираем возможный '\r' в конце (перевод строки в формате Windows)
    if (!X.empty() && X.back() == '\r') X.pop_back();
    if (!Y.empty() && Y.back() == '\r') Y.pop_back();
    
    // Метод find ищет Y внутри X:
    //   - если нашёл, возвращает позицию первого вхождения;
    //   - если не нашёл, возвращает string::npos.
    if (X.find(Y) != string::npos)
        cout << "yes" << endl;  // Y является подстрокой X
    else
        cout << "no" << endl;   // Y не содержится в X
    
    in1.close();
    in2.close();
    return 0;
}

// Задание 3
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

// Функция перевода целого числа в двоичную строку
string toBinary(long long n) {
    if (n == 0) return "0";  // особый случай: ноль в двоичной = "0"
    
    string result;
    while (n > 0) {
        // Берём младший бит (остаток от деления на 2)
        // и ставим его В НАЧАЛО строки, чтобы получить правильный порядок
        result = char('0' + n % 2) + result;
        n /= 2;  // отбрасываем младший бит
    }
    return result;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    
    string s;
    getline(in, s);  // читаем всю строку целиком (может содержать пробелы/символы)
    
    string result;   // итоговая строка
    int i = 0;
    int n = s.size();
    
    // Проходим по строке вручную, чтобы "захватывать" целые числа
    while (i < n) {
        if (isdigit((unsigned char)s[i])) {
            // Началось число — собираем все цифры подряд
            long long num = 0;
            while (i < n && isdigit((unsigned char)s[i])) {
                num = num * 10 + (s[i] - '0');  // накопление числа
                i++;
            }
            // Преобразуем накопленное число в двоичную строку и дописываем
            result += toBinary(num);
        } else {
            // Обычный символ (не цифра) — копируем как есть
            result += s[i];
            i++;
        }
    }
    
    out << result;  // выводим результат в файл
    
    in.close();
    out.close();
    return 0;
}