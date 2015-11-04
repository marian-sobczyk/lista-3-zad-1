//
// Created by Marian Sobczyk on 02.11.2015.
//

#ifndef LISTA_3_ZAD_1_AESCTRENCRYPTOR_H
#define LISTA_3_ZAD_1_AESCTRENCRYPTOR_H


#include "FileContent.h"
#include "AESEncryptor.h"

class AESCTREncryptor : public AESEncryptor {

public:

    AESCTREncryptor(unsigned char *key);

    virtual FileContent *encryptData(FileContent *data);

    virtual FileContent *decryptData(FileContent *data);

private:
    unsigned char *key;

    void initCtr();

    unsigned int num;
    unsigned char *ecount;
    unsigned char *ivec;

    unsigned char *initVector;
};


#endif //LISTA_3_ZAD_1_AESCTRENCRYPTOR_H
