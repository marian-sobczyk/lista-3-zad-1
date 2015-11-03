#include <iostream>
#include "FileContent.h"
#include "AESCTREncryptor.h"


using namespace std;

static const unsigned char key[] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0
};

static const unsigned char initVector[] = {'U', 0xe1, 0xb8, 0xb2, 0xe9, '~', 0xac, 'i', 0x95, 0x93, 0x81, '^', 'C', 'L',
                                           0xef, 0x93};

int main() {
    FileContent *inputContent = new FileContent();
    inputContent->readFromPath("/Users/marian/Desktop/ssl/test1.txt");
    AESCTREncryptor *encryptor = new AESCTREncryptor((unsigned char *) key, (unsigned char *) initVector);
    FileContent *outputContent = encryptor->encryptData(inputContent);
    outputContent->saveInPath("/Users/marian/Desktop/ssl/test2.txt");
    delete inputContent;
    inputContent = new FileContent();
    inputContent->readFromPath("/Users/marian/Desktop/ssl/test2.txt");
    delete encryptor;
    encryptor = new AESCTREncryptor((unsigned char *) key, (unsigned char *) initVector);
    delete outputContent;
    outputContent = encryptor->decryptData(inputContent);
    outputContent->saveInPath("/Users/marian/Desktop/ssl/test3.txt");
    delete encryptor;
    delete outputContent;

    return 0;
}

