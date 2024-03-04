#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>

// Stores all related to cryptography data
struct Encryption {
    std::string userMessage;
    int userKey;
    char userDirection;
};

// Functions prototypes
int getUserChoice();
void displayMenu();
void getEncryptionDetails(Encryption &encryption);
void getUserMessage(Encryption &encryption);
void encryptMessage(Encryption &encryption, const char *letters);
void decryptMessage(Encryption &encryption, const char *letters);
void convertToUpper(std::string &message);
void bruteForceMessage(Encryption &encryption, const char *letters);
void breakCode(Encryption &encryption, const char *letters);
int findCommonWords(std::string message);
bool isCommonWord(const std::vector<std::string> &words, std::string target);

int main() {
    const char letters[] = {'A', 'B', 'C', 'D','E', 'F', 'G', 'H','I', 'J', 'K', 'L','M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};

    displayMenu();
    Encryption userEncryption;

    // Perform encryption operation based on user choice
    switch(getUserChoice()) {
        // Encrypt a message
        case 1:
            getEncryptionDetails(userEncryption);
            getUserMessage(userEncryption);
            encryptMessage(userEncryption, letters);
            std::cout << "Encrypted message: " << userEncryption.userMessage << std::endl;
            break;
        // Decrypt a message
        case 2:
            getEncryptionDetails(userEncryption);
            getUserMessage(userEncryption);
            decryptMessage(userEncryption, letters);
            std::cout << "Decrypted message: " << userEncryption.userMessage << std::endl;
            break;
        // Brute force the message
        case 3:
            getUserMessage(userEncryption);
            bruteForceMessage(userEncryption, letters);
            break;
        // Break the code
        case 4:
            getUserMessage(userEncryption);
            breakCode(userEncryption, letters);
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

// Prompts user to choose between encryption, decryption, showing all possibilities, or breaking code
int getUserChoice() {
    int userChoice;
    do {
        std::cout << "Enter choice: ";
        std::cin >> userChoice;
    } while (userChoice < 1 || userChoice > 4);

    return userChoice;
}

// Prompts user for a shift key and the forward or backward direction of encryption/decryption
void getEncryptionDetails(Encryption &encryption) {
    std::cout << "Enter shift (1-26): ";
    std::cin >> encryption.userKey;
    std::cout << "Enter direction (f or b): ";
    std::cin >> encryption.userDirection;
}

// Prompts user for a message to encrypt/decrypt
void getUserMessage(Encryption &encryption) {
    std::cout << "Enter message: ";
    getline(std::cin, encryption.userMessage); // Get rid of a newline character in a buffer
    getline(std::cin, encryption.userMessage);
}

// Converts message to all uppercase letters
void convertToUpper(std::string &message) {
    for (int i = 0, len = message.size(); i < len; i++) {
        message[i] = toupper(message[i]);
    }
}

// Encrypts message in the forward or backward direction
// encryption is an Encryption data type variable that contains all necessary for encryption data
// letters is an array that contains all alphabetic uppercase characters + space treated as a letter after Z
void encryptMessage(Encryption &encryption, const char *letters) {
    int shiftValue = encryption.userKey % 27;
    convertToUpper(encryption.userMessage);

    for (int i = 0, len = encryption.userMessage.size(); i < len; i++) {
        if (isalpha(encryption.userMessage[i]) || isspace(encryption.userMessage[i])) { // Encrypts only alphabetic characters and spaces, leaving punctuation the same
            int tmpIndexVal = (isspace(encryption.userMessage[i])) ? 26 : encryption.userMessage[i] - 'A'; // 26 - space value treated as a letter after Z
            int letterIndex = (tmpIndexVal + shiftValue) % 27;
            encryption.userMessage[i] = letters[letterIndex];
            shiftValue = (shiftValue + tmpIndexVal + encryption.userKey) % 27;
        }
    }

    if (encryption.userDirection == 'b') {
        reverse(encryption.userMessage.begin(), encryption.userMessage.end());
    }
}

// Decrypts message in the forward or backward direction
// encryption is an Encryption data type variable that contains all necessary for decryption data
// letters is an array that contains all alphabetic uppercase characters + space treated as a letter after Z
void decryptMessage(Encryption &encryption, const char *letters) {
    int shiftValue = encryption.userKey % 27;
    convertToUpper(encryption.userMessage);
    if (encryption.userDirection == 'b') {
        reverse(encryption.userMessage.begin(), encryption.userMessage.end());
    }

    for (int i = 0, len = encryption.userMessage.size(); i < len; i++) { 
        if (isalpha(encryption.userMessage[i]) || isspace(encryption.userMessage[i])) { // Decrypts only alphabetic characters and spaces, leaving punctuation the same
            int tmpIndexVal = (isspace(encryption.userMessage[i])) ? 26 : encryption.userMessage[i] - 'A'; // 26 - space value treated as a letter after Z
            int letterIndex = (tmpIndexVal - shiftValue) % 27;
            letterIndex = (letterIndex < 0) ? (27 + letterIndex) : letterIndex;
            encryption.userMessage[i] = letters[letterIndex];
            shiftValue = (shiftValue + letterIndex + encryption.userKey) % 27;
        }
    }
}

// Attempts all 52 possible key-direction combinations to decrypt a message
// encryption is an Encryption data type variable that contains all necessary for decryption data
// letters is an array that contains all alphabetic uppercase characters + space treated as a letter after Z
void bruteForceMessage(Encryption &encryption, const char *letters) {
    std::string message = encryption.userMessage;
    int count = 1;

    for (int shiftKey = 1; shiftKey < 27; shiftKey++) {
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
        count++;
    }
}

// Attempts all 52 possible key-direction combinations to decrypt a message and outputs the one that contains the most of the 10 common words in English language
// encryption is an Encryption data type variable that contains all necessary for decryption data
// letters is an array that contains all alphabetic uppercase characters + space treated as a letter after Z
void breakCode(Encryption &encryption, const char *letters) {
    std::string message = encryption.userMessage;
    int count = 1;
    int numCommonWords = 0;
    int maxCommonWords = 0;
    std::string outputMessage = "Unable to find a decrypted message.";

    for (int shiftKey = 1; shiftKey < 27; shiftKey++) {
        // Forward decryption possibilities
        encryption.userKey = shiftKey;
        encryption.userDirection = 'f';
        decryptMessage(encryption, letters);
        numCommonWords = findCommonWords(encryption.userMessage);
        if (numCommonWords > maxCommonWords) {
            maxCommonWords = numCommonWords;
            outputMessage = encryption.userMessage;
        }

        // Backward decryption possibilities
        encryption.userKey = shiftKey;
        encryption.userMessage = message;
        encryption.userDirection = 'b';
        decryptMessage(encryption, letters);

        numCommonWords = findCommonWords(encryption.userMessage);
        if (numCommonWords > maxCommonWords) {
            maxCommonWords = numCommonWords;
            outputMessage = encryption.userMessage;
        }

        encryption.userMessage = message;
        count++;
    }

    std::cout << "Decrypted message is: " << outputMessage << std::endl;
}

// Finds the number of the 10 most common words in English language
int findCommonWords(std::string message) {
    std::stringstream messageStream(message);
    std::string word;
    std::vector<std::string> commonWords = {"A", "AND", "BE", "HAVE", "I", "IN", "OF", "THAT", "THE", "TO"};
    int count = 0;

    while (messageStream >> word) {
        count = (isCommonWord(commonWords,word)) ? ++count : count;
    }

    return count;
}

// Uses binary search to detect if the target word is in the list of most common words
// words is a vector containing the most common words in English language
// target is a word being searched for in a vector of most common words
bool isCommonWord(const std::vector<std::string> &words, std::string target) {
    int start = 0;
    int end = words.size() - 1;
    int mid;

    while (start <= end) {
        mid = (start + end) / 2;
        if (target == words.at(mid)) {
            return true;
        }
        else if (target < words.at(mid)) {
            end--;
        }
        else {
            start++;
        }
    }

    return false;
}