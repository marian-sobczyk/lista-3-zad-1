cmake_minimum_required(VERSION 3.3)
project(lista_3_zad_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FileContent.cpp FileContent.h AESCBCEncryptor.cpp AESCBCEncryptor.h AESCTREncryptor.cpp AESCTREncryptor.h)

link_libraries("-lssl -lcrypto")

add_executable(lista_3_zad_1 ${SOURCE_FILES})