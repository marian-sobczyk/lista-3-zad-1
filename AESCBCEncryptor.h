//
// Created by Marian Sobczyk on 01.11.2015.
//

#ifndef LISTA_3_ZAD_1_AESCBCENCRYPTOR_H
#define LISTA_3_ZAD_1_AESCBCENCRYPTOR_H


#include "FileContent.h"
#include <openssl/aes.h>

class AESCBCEncryptor {

public:
    AESCBCEncryptor(int keyLength, unsigned char *key, unsigned char *initVector);

    FileContent *encryptData(FileContent *fileContent);

    FileContent *decryptData(FileContent *data);

private:
    unsigned char *initVector;
    int keyLength;
    unsigned char *key;
};


#endif //LISTA_3_ZAD_1_AESCBCENCRYPTOR_H
