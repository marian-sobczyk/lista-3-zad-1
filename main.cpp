﻿#include <iostream>
#include "FileContent.h"
#include "AESCTREncryptor.h"
#include "KeyChain.h"


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
    AESCTREncryptor *encryptor = new AESCTREncryptor((unsigned char *) key);
    FileContent *outputContent = encryptor->encryptData(inputContent);
    outputContent->saveInPath("/Users/marian/Desktop/ssl/test2.txt");
    delete inputContent;
    inputContent = new FileContent(true);
    inputContent->readFromPath("/Users/marian/Desktop/ssl/test2.txt");
    delete encryptor;
    encryptor = new AESCTREncryptor((unsigned char *) key);
    delete outputContent;
    outputContent = encryptor->decryptData(inputContent);
    outputContent->saveInPath("/Users/marian/Desktop/ssl/test3.txt");
    delete encryptor;
    delete outputContent;

    unsigned char *password = (unsigned char *) "Marian";

    KeyChain *keyChain = new KeyChain((unsigned char *) "/Users/marian/Desktop/ssl/keyChain.kc", password, 0);


    delete keyChain;
    return 0;
}

