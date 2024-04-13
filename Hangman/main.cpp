#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

class HangmanGame {
private:
    vector<string> words; // Вектор для хранения слов
    string secretWord; // Загаданное слово
    string guessedWord; // Угаданное слово
    int attempts; // Количество попыток
    const int maxAttempts = 5; // Максимальное количество попыток
    time_t startTime; // Время начала игры

public:
    // Конструктор класса
    HangmanGame() {
        loadWordsFromFile("words.txt"); // Загрузка слов из зашифрованного файла
        srand(static_cast<unsigned int>(time(nullptr)));
        startTime = time(nullptr);
        attempts = 0;
        selectSecretWord(); // Выбор загаданного слова
        initializeGuessedWord(); // Инициализация угаданного слова
    }

    // Метод для загрузки слов из файла
    void loadWordsFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string word;
            while (getline(file, word)) {
                words.push_back(decrypt(word)); // Расшифровка слова и добавление его в список слов
            }
            file.close();
        }
        else {
            cerr << "Unable to open file " << filename << endl;
        }
    }

    // Метод для расшифровки слова
    string decrypt(const string& word) {
        string decryptedWord = "";
        int shift = 7; // Сдвиг для расшифровки шифра Цезаря
        for (char c : word) {
            if (isalpha(c)) {
                char decryptedChar;
                if (islower(c)) {
                    decryptedChar = 'a' + ((c - 'a' - shift + 26) % 26); // Расшифровка символов в нижнем регистре
                }
                else {
                    decryptedChar = 'A' + ((c - 'A' - shift + 26) % 26); // Расшифровка символов в верхнем регистре
                }
                decryptedWord += decryptedChar;
            }
            else {
                decryptedWord += c; // Неалфавитные символы остаются неизменными
            }
        }
        return decryptedWord;
    }

    // Метод для выбора загаданного слова
    void selectSecretWord() {
        int index = rand() % words.size();
        secretWord = words[index];
    }

    // Метод для инициализации угаданного слова
    void initializeGuessedWord() {
        guessedWord = string(secretWord.length(), '_');
    }

    // Метод для отображения угаданного слова
    void displayGuessedWord() {
        cout << "Guessed word: " << guessedWord << endl;
    }

    // Метод для рисования виселицы
    void drawHangman() {
        switch (attempts) {
        case 1:
            cout << "  __" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << "__|___" << endl;
            break;
        case 2:
            cout << "  __" << endl;
            cout << " |  |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << "__|___" << endl;
            break;
        case 3:
            cout << "  __" << endl;
            cout << " |  |" << endl;
            cout << " |  O" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << "__|___" << endl;
            break;
        case 4:
            cout << "  __" << endl;
            cout << " |  |" << endl;
            cout << " |  O" << endl;
            cout << " |  |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << "__|___" << endl;
            break;
        case 5:
            cout << "  __" << endl;
            cout << " |  |" << endl;
            cout << " |  O" << endl;
            cout << " | /|\\" << endl;
            cout << " | / \\" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << "__|___" << endl;
            break;
        default:
            break;
        }
    }

    // Метод для угадывания буквы
    void guessLetter(char letter) {
        bool found = false;
        char uppercaseLetter = toupper(letter); // Преобразуем введенную букву в верхний регистр
        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (secretWord[i] == uppercaseLetter || secretWord[i] == letter) { // Проверяем обе версии буквы: верхний и нижний регистр
                guessedWord[i] = secretWord[i]; // Присваиваем правильную букву угаданному слову
                found = true;
            }
        }
        if (!found) {
            ++attempts;
            drawHangman();
            if (attempts >= maxAttempts) {
                cout << "You've exceeded the maximum number of attempts. Game over!" << endl;
                displayStatistics();
                exit(0); // Завершаем игру
            }
        }
    }

    // Метод для проверки угадано ли слово полностью
    bool isWordGuessed() const {
        return secretWord == guessedWord;
    }

    // Метод для отображения статистики игры
    void displayStatistics() {
        cout << "Game statistics:" << endl;
        cout << "Time taken: " << difftime(time(nullptr), startTime) << " seconds" << endl;
        cout << "Number of attempts: " << attempts << endl;
        cout << "Searched word: " << secretWord << endl;
        cout << "Player letters: " << guessedWord << endl;
    }

    // Метод для запуска игры
    void play() {
        char letter;
        while (!isWordGuessed()) {
            cout << "Enter a letter: ";
            cin >> letter;
            guessLetter(letter);
            displayGuessedWord();
        }
        displayStatistics();
    }
};

int main() {
    HangmanGame game; // Создаем объект игры
    game.play(); // Запускаем игру
    return 0;
}
