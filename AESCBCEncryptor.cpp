//
// Created by Marian Sobczyk on 01.11.2015.
//

#include <openssl/aes.h>
#include <string.h>
#include "AESCBCEncryptor.h"

FileContent *AESCBCEncryptor::encryptData(FileContent *data) {
    long outputLength = ((data->filesize + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    FileContent *outputData = new FileContent(outputLength);
    AES_cbc_encrypt(data->content, outputData->content, (const unsigned long) data->filesize,
                    &enc_key, initVector, AES_ENCRYPT);

    return outputData;
}

AESCBCEncryptor::AESCBCEncryptor(const unsigned char *const key, unsigned char *initVector) {
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_set_decrypt_key(key, 128, &dec_key);
    this->initVector = new unsigned char[AES_BLOCK_SIZE];
    memcpy(this->initVector, initVector, AES_BLOCK_SIZE);
}

FileContent *AESCBCEncryptor::decryptData(FileContent *data) {
    long outputLength = data->filesize;
    FileContent *outputData = new FileContent(outputLength);
    AES_cbc_encrypt(data->content, outputData->content, data->filesize, &dec_key, initVector,
                    AES_DECRYPT);
    return outputData;
}
