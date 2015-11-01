#include <iostream>
#include <openssl/aes.h>
#include "FileContent.h"

using namespace std;

static const unsigned char key[] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
};

int main() {
    FileContent *inputContent = new FileContent();
    inputContent->readFromPath("/Users/marian/Desktop/ssl/test1.txt");

    FileContent *outputContent = new FileContent(inputContent->filesize);

    AES_KEY enc_key, dec_key;

    AES_set_encrypt_key(key, 128, &enc_key);
    AES_encrypt(inputContent->content, outputContent->content, &enc_key);
    outputContent->saveInPath("/Users/marian/Desktop/ssl/test2.txt");

    FileContent *output2Content = new FileContent(inputContent->filesize);

    AES_set_decrypt_key(key, 128, &dec_key);
    AES_decrypt(outputContent->content, output2Content->content, &dec_key);

    output2Content->saveInPath("/Users/marian/Desktop/ssl/test3.txt");

    delete inputContent;
    delete outputContent;
    delete output2Content;

    return 0;
}

