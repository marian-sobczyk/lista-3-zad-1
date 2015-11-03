//
// Created by Marian Sobczyk on 01.11.2015.
//

#include <stdio.h>
#include "FileContent.h"

void FileContent::readFromPath(const char *path) {
    FILE *input = fopen(path, "rb");
    if (input == NULL) {
        return;
    }
    fseek(input, 0L, SEEK_END);
    filesize = ftell(input);
    fseek(input, 0L, SEEK_SET);
    content = new unsigned char[filesize];
    unsigned char character;
    for (int i = 0; i < filesize; i++) {
        fread(&character, 1, 1, input);
        content[i] = character;
    }
    fclose(input);
}

void FileContent::saveInPath(const char *path) {
    FILE *output = fopen(path, "wb");
    if (output == NULL) {
        return;
    }
    for (int i = 0; i < filesize; i++) {
        fwrite(&content[i], 1, 1, output);
    }

    fclose(output);
}

FileContent::FileContent(long size) {
    filesize = (unsigned long) size;
    content = new unsigned char[size];
}

FileContent::FileContent() {

}
