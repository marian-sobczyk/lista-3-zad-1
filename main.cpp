#include <iostream>
#include "FileContent.h"
#include "AESCTREncryptor.h"
#include "KeyChain.h"
#include "AESCBCEncryptor.h"


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
    if (effect == EEUnknown) {
        cout << "Błędna metoda szyfrowania\n";
        return -1;
    }

    char *password = getpass("Podaj hasło: ");
    KeyChain *keyChain = new KeyChain((unsigned char *) keystorePath,
                                      (unsigned char *) password, index);
    unsigned char *key = keyChain->key;

    FileContent *input = new FileContent(effect == EEDecoding);
    input->readFromPath(filePath);
    AESEncryptor *encryptor;
    if (type == ETCBC) {
        encryptor = new AESCBCEncryptor(256, key);
    } else {
        encryptor = new AESCTREncryptor(key);
    }

    FileContent *output;
    if (effect == EEEncoding) {
        output = encryptor->encryptData(input);
    } else {
        output = encryptor->decryptData(input);
    }

    string newPath = string(filePath);
    unsigned long found = newPath.find_last_of("/");
    newPath = newPath.substr(0, found + 1) + (effect == EEDecoding ? "decoded" : "encoded");
    const char *outputPath = newPath.c_str();

    output->saveInPath(outputPath);

    delete input;
    delete output;
    delete keyChain;
    delete encryptor;


    return 0;
}

EncodingEffect getEncodingEffect(char *effectASCII) {
    int effect = atoi(effectASCII);

    switch (effect) {
        case 0:
            return EEDecoding;
        case 1:
            return EEEncoding;
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

