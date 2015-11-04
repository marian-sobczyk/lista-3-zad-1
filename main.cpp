#include <iostream>
#include "FileContent.h"
#include "AESCTREncryptor.h"
#include "KeyChain.h"


using namespace std;

enum EncodingType {
    ETUnknown = 0,
    ETCBC = 1,
    ETCTR = 2
};

enum EncodingEffect {
    EEUnknown = 0,
    EEEncoding = 1,
    EEDecoding = 2
};

EncodingType getEncodingType(char *encodingType);

EncodingEffect getEncodingEffect(char *effectASCII);

int main(int argc, char *argv[]) {
    if (argc < 6) {
        cout <<
        "Użycie: tryb szyfrowania | ścieżka do keystora | identyfikator klucza | plik do zaszyfrowania | 1 - szyfrowanie, 0 - deszyfrowanie\n";
        return -1;
    }

    EncodingType type = getEncodingType(argv[1]);
    if (type == ETUnknown) {
        cout << "Błędny tryb szyfrowania\n";
        return -1;
    }

    char *keystorePath = argv[2];

    int index = atoi(argv[3]);

    char *filePath = argv[4];

    EncodingEffect effect = getEncodingEffect(argv[5]);

    char *password = getpass("Podaj hasło: ");
    KeyChain *keyChain = new KeyChain((unsigned char *) keystorePath,
                                      (unsigned char *) password, index);
    unsigned char *key = keyChain->key;
    FileContent *inputContent = new FileContent(false);
    inputContent->readFromPath("/Users/marian/Desktop/ssl/test1.txt");
    AESEncryptor *encryptor = new AESCTREncryptor(key);
    FileContent *outputContent = encryptor->encryptData(inputContent);
//    outputContent->saveInPath("/Users/marian/Desktop/ssl/test2.txt");
    delete inputContent;
    inputContent = new FileContent(true);
    inputContent->readFromPath("/Users/marian/Desktop/ssl/test2.txt");
    delete encryptor;
    encryptor = new AESCTREncryptor(key);
    delete outputContent;
    outputContent = encryptor->decryptData(inputContent);
    outputContent->saveInPath("/Users/marian/Desktop/ssl/test3.txt");
    delete encryptor;
    delete outputContent;
    delete keyChain;
    return 0;
}

EncodingEffect getEncodingEffect(char *effectASCII) {
    int effect = atoi(effectASCII);

    switch (effect) {
        case 0:
            return EEEncoding;
        case 1:
            return EEDecoding;
        default:
            return EEUnknown;
    }
}

EncodingType getEncodingType(char *encodingType) {
    if (strcmp(encodingType, "CBC") == 0) {
        return ETCBC;
    } else if (strcmp(encodingType, "CTR") == 0) {
        return ETCTR;
    } else {
        return ETUnknown;
    }
}

