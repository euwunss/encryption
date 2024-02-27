#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

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

int main() {
    const char letters[] = {'A', 'B', 'C', 'D','E', 'F', 'G', 'H','I', 'J', 'K', 'L','M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};

    displayMenu();
    EncryptionParameters encryption;

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
            break;
        case 4:
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
            char tmpChar = (isspace(encryption.userMessage[i])) ? (91 - 'A') : encryption.userMessage[i] - 'A';
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
            char tmpChar = (isspace(encryption.userMessage[i])) ? (91 - 'A') : encryption.userMessage[i] - 'A';
            int letterIndex = (tmpChar - shiftValue) % 27;
            letterIndex = (letterIndex < 0) ? (27 + letterIndex) : letterIndex;
            encryption.userMessage[i] = letters[letterIndex];
            shiftValue = (shiftValue + letterIndex + encryption.userKey) % 27;
        }
    }
}