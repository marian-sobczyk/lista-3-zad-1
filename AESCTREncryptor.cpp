//
// Created by Marian Sobczyk on 02.11.2015.
//

#include <string.h>
#include <openssl/aes.h>
#include "AESCTREncryptor.h"

AESCTREncryptor::AESCTREncryptor(unsigned char *key, unsigned char *initVector) {
    this->key = new unsigned char[128 / 8];
    memcpy(this->key, key, 128 / 8);
    this->initVector = new unsigned char[AES_BLOCK_SIZE];
    memcpy(this->initVector, initVector, AES_BLOCK_SIZE);
}

void AESCTREncryptor::initCtr() {
    num = 0;
    ecount = new unsigned char[AES_BLOCK_SIZE];
    memset(ecount, 0, AES_BLOCK_SIZE);
    ivec = new unsigned char[AES_BLOCK_SIZE];
    memset(ivec + 8, 0, 8);
    memcpy(ivec, initVector, 8);
}

FileContent *AESCTREncryptor::encryptData(FileContent *data) {
    initCtr();
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    FileContent *outputData = new FileContent(data->filesize);
    AES_ctr128_encrypt(data->content, outputData->content, data->filesize, &enc_key, ivec, ecount, &num);
    return outputData;
}

FileContent *AESCTREncryptor::decryptData(FileContent *data) {
    initCtr();
    AES_KEY dec_key;
    AES_set_encrypt_key(key, 128, &dec_key);
    FileContent *outputData = new FileContent(data->filesize);
    AES_ctr128_encrypt(data->content, outputData->content, data->filesize, &dec_key, ivec, ecount, &num);
    return outputData;
}
