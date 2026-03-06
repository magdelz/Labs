#include <iostream>
#include <cstring>

// Функция для извлечения слов
char** extract_words(const char* str) {
    if (!str) return nullptr;

    // 1. Подсчет количества слов
    int word_count = 0;
    bool in_word = false;
    for (int i = 0; str[i] != '\0'; ++i) {
        // Считаем разделителями пробел, табуляцию и перенос строки
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            if (!in_word) {
                word_count++;
                in_word = true;
            }
        } else {
            in_word = false;
        }
    }

    // 2. Создание динамического массива указателей (плюс 1 для NULL-ограничителя)
    char** words_array = new char*[word_count + 1];

    // 3. Выделение памяти под каждое слово и копирование символов
    int current_word = 0;
    in_word = false;
    int start_idx = 0;

    for (int i = 0; ; ++i) {
        bool is_separator = (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\0');

        if (!is_separator) {
            if (!in_word) {
                start_idx = i; // Запоминаем начало слова
                in_word = true;
            }
        } else {
            if (in_word) {
                int len = i - start_idx;
                // Выделяем память под конкретное слово (+1 для нуль-терминатора '\0')
                words_array[current_word] = new char[len + 1]; 
                
                // Копируем символы слова
                for (int j = 0; j < len; ++j) {
                    words_array[current_word][j] = str[start_idx + j];
                }
                words_array[current_word][len] = '\0'; // Закрываем строку
                current_word++;
                in_word = false;
            }
        }

        if (str[i] == '\0') break; // Конец исходной строки
    }

    // Ограничитель массива указателей
    words_array[word_count] = nullptr; 

    return words_array;
}

int main() {
    const char* text = "Массивы указателей - это простейшая структура данных";
    
    char** words = extract_words(text);
    
    if (words) {
        std::cout << "Извлеченные слова:" << std::endl;
        
        // Выводим слова до тех пор, пока не встретим nullptr
        for (int i = 0; words[i] != nullptr; ++i) {
            std::cout << "Слово " << i + 1 << ": " << words[i] << std::endl;
        }
        
        std::cout << "---" << std::endl;
        
        // Очистка памяти: сначала уничтожаются динамические массивы-строки, а затем сам массив указателей
        for (int i = 0; words[i] != nullptr; ++i) {
            delete[] words[i];
        }
        delete[] words; 
        std::cout << "Память успешно очищена." << std::endl;
    }
    
    return 0;
}