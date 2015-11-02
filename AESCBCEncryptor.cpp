//
// Created by Marian Sobczyk on 01.11.2015.
//

#include <openssl/aes.h>
#include <string.h>
#include "AESCBCEncryptor.h"

FileContent *AESCBCEncryptor::encryptData(FileContent *data) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, keyLength * 8, &enc_key);
    long outputLength = ((data->filesize + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    FileContent *outputData = new FileContent(outputLength);
    AES_cbc_encrypt(data->content, outputData->content, (const unsigned long) data->filesize,
                    &enc_key, initVector, AES_ENCRYPT);

    return outputData;
}

FileContent *AESCBCEncryptor::decryptData(FileContent *data) {
    AES_KEY dec_key;
    AES_set_decrypt_key(key, keyLength * 8, &dec_key);
    long outputLength = data->filesize;
    FileContent *outputData = new FileContent(outputLength);
    AES_cbc_encrypt(data->content, outputData->content, (const unsigned long) data->filesize, &dec_key, initVector,
                    AES_DECRYPT);
    return outputData;
}

AESCBCEncryptor::AESCBCEncryptor(int keyLength, unsigned char *key, unsigned char *initVector) {
    this->keyLength = keyLength / 8;
    this->key = new unsigned char[this->keyLength];
    memcpy(this->key, key, (size_t) this->keyLength);
    this->initVector = new unsigned char[AES_BLOCK_SIZE];
    memcpy(this->initVector, initVector, AES_BLOCK_SIZE);
}
