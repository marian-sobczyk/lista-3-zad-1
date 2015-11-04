#include <iostream>
#include "FileContent.h"
#include "AESCTREncryptor.h"
#include "KeyChain.h"


using namespace std;

int main() {
    char *password = getpass("Podaj hasło: ");
    KeyChain *keyChain = new KeyChain((unsigned char *) "/Users/marian/Desktop/ssl/keyChain.kc",
                                      (unsigned char *) password, 0);
    unsigned char *key = keyChain->key;
    FileContent *inputContent = new FileContent(false);
    inputContent->readFromPath("/Users/marian/Desktop/ssl/test1.txt");
    AESCTREncryptor *encryptor = new AESCTREncryptor(key);
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

