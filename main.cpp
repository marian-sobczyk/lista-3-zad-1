﻿#include <iostream>
#include "FileContent.h"
#include "AESCBCEncryptor.h"


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

int main() {
    FileContent *inputContent = new FileContent(false);
    inputContent->readFromPath("/Users/marian/Desktop/ssl/test1.txt");
    AESCBCEncryptor *encryptor = new AESCBCEncryptor(128, (unsigned char *) key);
    FileContent *outputContent = encryptor->encryptData(inputContent);
    outputContent->saveInPath("/Users/marian/Desktop/ssl/test2.txt");
    delete inputContent;
    inputContent = new FileContent(true);
    inputContent->readFromPath("/Users/marian/Desktop/ssl/test2.txt");
    delete encryptor;
    encryptor = new AESCBCEncryptor(128, (unsigned char *) key);
    delete outputContent;
    outputContent = encryptor->decryptData(inputContent);
    outputContent->saveInPath("/Users/marian/Desktop/ssl/test3.txt");
    delete encryptor;
    delete outputContent;

    return 0;
}

