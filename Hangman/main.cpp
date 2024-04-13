#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

class HangmanGame {
private:
    vector<string> words; // ������ ��� �������� ����
    string secretWord; // ���������� �����
    string guessedWord; // ��������� �����
    int attempts; // ���������� �������
    const int maxAttempts = 5; // ������������ ���������� �������
    time_t startTime; // ����� ������ ����

public:
    // ����������� ������
    HangmanGame() {
        loadWordsFromFile("words.txt"); // �������� ���� �� �������������� �����
        srand(static_cast<unsigned int>(time(nullptr)));
        startTime = time(nullptr);
        attempts = 0;
        selectSecretWord(); // ����� ����������� �����
        initializeGuessedWord(); // ������������� ���������� �����
    }

    // ����� ��� �������� ���� �� �����
    void loadWordsFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string word;
            while (getline(file, word)) {
                words.push_back(decrypt(word)); // ����������� ����� � ���������� ��� � ������ ����
            }
            file.close();
        }
        else {
            cerr << "Unable to open file " << filename << endl;
        }
    }

    // ����� ��� ����������� �����
    string decrypt(const string& word) {
        string decryptedWord = "";
        int shift = 7; // ����� ��� ����������� ����� ������
        for (char c : word) {
            if (isalpha(c)) {
                char decryptedChar;
                if (islower(c)) {
                    decryptedChar = 'a' + ((c - 'a' - shift + 26) % 26); // ����������� �������� � ������ ��������
                }
                else {
                    decryptedChar = 'A' + ((c - 'A' - shift + 26) % 26); // ����������� �������� � ������� ��������
                }
                decryptedWord += decryptedChar;
            }
            else {
                decryptedWord += c; // ������������ ������� �������� �����������
            }
        }
        return decryptedWord;
    }

    // ����� ��� ������ ����������� �����
    void selectSecretWord() {
        int index = rand() % words.size();
        secretWord = words[index];
    }

    // ����� ��� ������������� ���������� �����
    void initializeGuessedWord() {
        guessedWord = string(secretWord.length(), '_');
    }

    // ����� ��� ����������� ���������� �����
    void displayGuessedWord() {
        cout << "Guessed word: " << guessedWord << endl;
    }

    // ����� ��� ��������� ��������
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

    // ����� ��� ���������� �����
    void guessLetter(char letter) {
        bool found = false;
        char uppercaseLetter = toupper(letter); // ����������� ��������� ����� � ������� �������
        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (secretWord[i] == uppercaseLetter || secretWord[i] == letter) { // ��������� ��� ������ �����: ������� � ������ �������
                guessedWord[i] = secretWord[i]; // ����������� ���������� ����� ���������� �����
                found = true;
            }
        }
        if (!found) {
            ++attempts;
            drawHangman();
            if (attempts >= maxAttempts) {
                cout << "You've exceeded the maximum number of attempts. Game over!" << endl;
                displayStatistics();
                exit(0); // ��������� ����
            }
        }
    }

    // ����� ��� �������� ������� �� ����� ���������
    bool isWordGuessed() const {
        return secretWord == guessedWord;
    }

    // ����� ��� ����������� ���������� ����
    void displayStatistics() {
        cout << "Game statistics:" << endl;
        cout << "Time taken: " << difftime(time(nullptr), startTime) << " seconds" << endl;
        cout << "Number of attempts: " << attempts << endl;
        cout << "Searched word: " << secretWord << endl;
        cout << "Player letters: " << guessedWord << endl;
    }

    // ����� ��� ������� ����
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
    HangmanGame game; // ������� ������ ����
    game.play(); // ��������� ����
    return 0;
}
