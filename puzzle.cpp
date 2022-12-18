#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

//функция получения индекса буквы по ее символу
int index(char c) {
    if ((c <= 'я' && c >= 'а') || c == 'ё') {
        if (c == 'ё')   c = 'Ё';
        else            c -= 32;
    }
    
    if (c == 'Ё') return 33;
    if (c <= 'Я' && c >= 'А') {
        return c - 'А';
    }
    return -1;
}

//функция ввода слова с клавиатуры
string get_word(int i) {
    printf("Введите СЛОВО%d: ", i);
    string word;
    cin >> word;
    int ind;

    for (size_t i = 0; i < word.size(); ++i) {
        if ((ind = index(word[i])) == -1) {
            return "";
        }
        else {
            word[i] = (ind == 33 ? 'Ё' : 'А' + ind);
        }
    }

    return word;
}

//структура загадки
struct puzzle {
    vector<char> letters;       //набор различных букв
    int order[10];              //массив для всех возможных перестановок цифр

    puzzle() {
        letters = vector<char>();
        for (int i = 0; i < 10; ++i) {
            order[i] = i;
        }
    }

    int get_ind(char ch) {
        for (size_t i = 0; i < letters.size(); ++i) {
            if (letters[i] == ch) { return i; }
        }
        return -1;
    }

    int add(char ch) {
        if (get_ind(ch) == -1) {
            letters.push_back(ch);
        }
        return letters.size();
    }

    long long to_int(string str) {
        long long num = 0;
        for (char ch : str) {
            num = num * 10 + order[get_ind(ch)];
        }
        return num;
    }

    bool NextSet()
    {
        int n = 10;
        int m = letters.size();
        int j;
        do  // повторяем пока не будет найдено следующее размещение
        {
            j = n - 2;
            while (j != -1 && order[j] >= order[j + 1]) j--;
            if (j == -1)
                return false; // больше размещений нет
            int k = n - 1;
            while (order[j] >= order[k]) k--;
            swap(order[j], order[k]);
            int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
            while (l < r)
                swap(order[l++], order[r--]);
        } while (j > m - 1);
        return true;
    }

    void print() {
        for (int i = 0; i < letters.size(); ++i) {
            cout << letters[i] << " = " << order[i] << '\n';
        }
    }
};

void solve(string words[3]) {
    cout << "Поиск решений...\n";
    puzzle s;
    for (int i = 0; i < 3; ++i) {
        for (char ch : words[i]) {
            if (s.add(ch) > 10) {
                cout << "Ошибка: различных букв больше чем цифр.\n";
                return;
            }
        }
    }
    do {
        //cout << s.to_int(words[0]) << " + " << s.to_int(words[1]) << " = " << s.to_int(words[2]) << '\n';
        if (s.to_int(words[0]) + s.to_int(words[1]) == s.to_int(words[2])) {
            cout << "Найдено решение:\n";
            s.print();
            cout << s.to_int(words[0]) << " + " << s.to_int(words[1]) << " = " << s.to_int(words[2]) << '\n';
            return;
        }
    } while (s.NextSet());
    cout << "Решений не найдено\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

   
    string header = "Решение загадки СЛОВО1+СЛОВО2=СЛОВО3\n";
    cout << header;

    string words[3];
    for (int i = 0; i < 3; ++i) {
        while ((words[i] = get_word(i+1)) == "") {
      
            printf("%s: некорректный ввод!\n", words[i].c_str());
        }
    }

    solve(words);
 
    return 0;

}
