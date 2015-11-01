#include <iostream>
#include <openssl/aes.h>
#include "FileContent.h"
#include <openssl/rand.h>


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


    AES_KEY enc_key, dec_key;

    unsigned char iv_enc[AES_BLOCK_SIZE], iv_dec[AES_BLOCK_SIZE];
    RAND_bytes(iv_enc, AES_BLOCK_SIZE);

    memcpy(iv_dec, iv_enc, AES_BLOCK_SIZE);

    long outputsLenght = ((inputContent->filesize + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    FileContent *outputContent = new FileContent(outputsLenght);

    AES_set_encrypt_key(key, 128, &enc_key);
    AES_cbc_encrypt(inputContent->content, outputContent->content, (const unsigned long) inputContent->filesize,
                    &enc_key, iv_enc, AES_ENCRYPT);

    outputContent->saveInPath("/Users/marian/Desktop/ssl/test2.txt");

    FileContent *output2Content = new FileContent(inputContent->filesize);

    AES_set_decrypt_key(key, 128, &dec_key);
    AES_cbc_encrypt(outputContent->content, output2Content->content, (const unsigned long) output2Content->filesize,
                    &dec_key, iv_dec, AES_DECRYPT);

    output2Content->saveInPath("/Users/marian/Desktop/ssl/test3.txt");

    delete inputContent;
    delete outputContent;
    delete output2Content;

    return 0;
}

