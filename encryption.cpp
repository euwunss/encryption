#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

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
            decryptMessage(encryption, letters); // FIXME: Finish decryptMessage()
            break;
        case 3:
            break;
        case 4:
            break;
    }
    
    return 0;
}

void displayMenu() {
    std::cout << "1. Encrypt  message" << std::endl;
    std::cout << "2. Decrypt message" << std::endl;
    std::cout << "3. Show decrypted possibilities" << std::endl;
    std::cout << "4. Break code" << std::endl;
}
int getUserChoice() {
    int userChoice;

    do {
        std::cout << "Enter choice: ";
        std::cin >> userChoice;
    } while (userChoice < 1 || userChoice > 4);

    return userChoice;
}
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
void encryptMessage(EncryptionParameters &encryption, const char *letters) {
    int shiftValue = encryption.userKey % 27;

    for (int i = 0, len = encryption.userMessage.size(); i < len; i++) {
        encryption.userMessage[i] = toupper(encryption.userMessage[i]);

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

void decryptMessage(EncryptionParameters &encryption, const char *letters) {
    std::cout << "FIXME: Finish decryptMessage()" << std::endl;
    return;
}