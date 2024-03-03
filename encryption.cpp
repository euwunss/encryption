#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>

// Stores all related to cryptography data
struct EncryptionParameters {
    std::string userMessage;
    int userKey;
    char userDirection;
};

// Function prototypes
int getUserChoice();
void displayMenu();
void getUserMessage(EncryptionParameters &encryption);
void encryptMessage(EncryptionParameters &encryption, const char *letters);
void decryptMessage(EncryptionParameters &encryption, const char *letters);
void convertToUpper(std::string &message);
void bruteForceMessage(EncryptionParameters &encryption, const char *letters);
void breakCode(EncryptionParameters &encryption, const char *letters);
int findCommonWords(std::string message);

int main() {
    const char letters[] = {'A', 'B', 'C', 'D','E', 'F', 'G', 'H','I', 'J', 'K', 'L','M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};

    displayMenu();
    EncryptionParameters encryption;
    std::string tempVal;

    switch(getUserChoice()) {
        case 1:
            getUserMessage(encryption);
            encryptMessage(encryption, letters);
            std::cout << "Encrypted message: " << encryption.userMessage << std::endl;
            break;
        case 2:
            getUserMessage(encryption);
            decryptMessage(encryption, letters);
            std::cout << "Decrypted message: " << encryption.userMessage << std::endl;
            break;
        case 3:
            std::cout << "Enter message: ";
            getline(std::cin, tempVal);
            getline(std::cin, encryption.userMessage);
            bruteForceMessage(encryption, letters);
            break;
        case 4:
            std::cout << "Enter message: ";
            getline(std::cin, tempVal);
            getline(std::cin, encryption.userMessage);
            breakCode(encryption, letters);
            break;
    }
    
    return 0;
}

// Displays main menu with options
void displayMenu() {
    std::cout << "1. Encrypt  message" << std::endl;
    std::cout << "2. Decrypt message" << std::endl;
    std::cout << "3. Show decrypted possibilities" << std::endl;
    std::cout << "4. Break code" << std::endl;
}

// Prompts user for an option between encryption, decryption, showing all possibilities, and breaking code
int getUserChoice() {
    int userChoice;

    do {
        std::cout << "Enter choice: ";
        std::cin >> userChoice;
    } while (userChoice < 1 || userChoice > 4);

    return userChoice;
}

// Prompts user for a shift key, forward or backward direction of encryption/decryption, and a message to encrypt/decrypt
void getUserMessage(EncryptionParameters &encryption) {
    std::string tempVal;

    std::cout << "Enter shift (1-26): ";
    std::cin >> encryption.userKey;
    std::cout << "Enter direction (f or b): ";
    std::cin >> encryption.userDirection;
    std::cout << "Enter message: ";
    getline(std::cin, tempVal);
    getline(std::cin, encryption.userMessage);
}

// Converts message to all uppercase letters
void convertToUpper(std::string &message) {
    for (int i = 0, len = message.size(); i < len; i++) {
        message[i] = toupper(message[i]);
    }
}

// Encrypts message in forward or backward 
void encryptMessage(EncryptionParameters &encryption, const char *letters) {
    int shiftValue = encryption.userKey % 27;
    convertToUpper(encryption.userMessage);

    for (int i = 0, len = encryption.userMessage.size(); i < len; i++) {
        if (isalpha(encryption.userMessage[i]) || isspace(encryption.userMessage[i])) {
            char tmpChar = (isspace(encryption.userMessage[i])) ? 26 : encryption.userMessage[i] - 'A'; // 26 - space value as a letter after Z
            int letterIndex = (tmpChar + shiftValue) % 27;
            encryption.userMessage[i] = letters[letterIndex];
            shiftValue = (shiftValue + tmpChar + encryption.userKey) % 27;
        }
    }

    if (encryption.userDirection == 'b') {
        reverse(encryption.userMessage.begin(), encryption.userMessage.end());
    }
}

// Decrypts message in forward or backward 
void decryptMessage(EncryptionParameters &encryption, const char *letters) {
    int shiftValue = encryption.userKey % 27;
    convertToUpper(encryption.userMessage);
    if (encryption.userDirection == 'b') {
        reverse(encryption.userMessage.begin(), encryption.userMessage.end());
    }

    for (int i = 0, len = encryption.userMessage.size(); i < len; i++) {
        if (isalpha(encryption.userMessage[i]) || isspace(encryption.userMessage[i])) {
            char tmpChar = (isspace(encryption.userMessage[i])) ? 26 : encryption.userMessage[i] - 'A'; // 26 - space value as a letter after Z
            int letterIndex = (tmpChar - shiftValue) % 27;
            letterIndex = (letterIndex < 0) ? (27 + letterIndex) : letterIndex;
            encryption.userMessage[i] = letters[letterIndex];
            shiftValue = (shiftValue + letterIndex + encryption.userKey) % 27;
        }
    }
}

void bruteForceMessage(EncryptionParameters &encryption, const char *letters) {
    std::string message = encryption.userMessage;
    int shiftKey = 1;
    int count = 1;

    while (shiftKey < 27) {
        // Forward decryption possibilities
        encryption.userKey = shiftKey;
        encryption.userDirection = 'f';
        std::cout << count << "f: ";
        decryptMessage(encryption, letters);
        std::cout << encryption.userMessage << std::endl;

        // Backward decryption possibilities
        encryption.userKey = shiftKey;
        encryption.userMessage = message;
        encryption.userDirection = 'b';
        std::cout << count << "b: ";
        decryptMessage(encryption, letters);
        std::cout << encryption.userMessage << std::endl;

        encryption.userMessage = message;
        shiftKey++;
        count++;
    }
}

void breakCode(EncryptionParameters &encryption, const char *letters) {
    std::string message = encryption.userMessage;
    int count = 1;
    int commonWords = 0;
    int maxCommonWords = 0;
    std::string output = "Unable to find a decrypted message.";

    for (int shiftKey = 1; shiftKey < 27; shiftKey++) {
        // Forward decryption possibilities
        encryption.userKey = shiftKey;
        encryption.userDirection = 'f';
        decryptMessage(encryption, letters);
        commonWords = findCommonWords(encryption.userMessage);
        if (commonWords > maxCommonWords) {
            maxCommonWords = commonWords;
            output = encryption.userMessage;
        }

        // Backward decryption possibilities
        encryption.userKey = shiftKey;
        encryption.userMessage = message;
        encryption.userDirection = 'b';
        decryptMessage(encryption, letters);

        commonWords = findCommonWords(encryption.userMessage);
        if (commonWords > maxCommonWords) {
            maxCommonWords = commonWords;
            output = encryption.userMessage;
        }

        encryption.userMessage = message;
        count++;
    }

    std::cout << output << std::endl;
}

int findCommonWords(std::string message) {
    std::stringstream messageStream(message);
    std::string word;
    std::vector<std::string> commonWords = {"THE", "BE", "TO", "OF", "AND", "A", "IN", "THAT", "HAVE", "I"};
    int count = 0;

    while (messageStream >> word) {
        for (std::string commonWord : commonWords) {
            count = (commonWord == word) ? ++count : count;
        }
    }

    return count;
}