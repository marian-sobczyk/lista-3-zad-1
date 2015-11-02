//
// Created by Marian Sobczyk on 01.11.2015.
//

#ifndef LISTA_3_ZAD_1_AESCBCENCRYPTOR_H
#define LISTA_3_ZAD_1_AESCBCENCRYPTOR_H


#include "FileContent.h"
#include <openssl/aes.h>

class AESCBCEncryptor {

public:
    AESCBCEncryptor(const unsigned char key[16], unsigned char *initVector);

    FileContent *encryptData(FileContent *fileContent);

    FileContent *decryptData(FileContent *data);

private:
    AES_KEY enc_key;

    unsigned char *initVector;
    AES_KEY dec_key;
};


#endif //LISTA_3_ZAD_1_AESCBCENCRYPTOR_H
