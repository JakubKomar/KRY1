/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Část pro dešifrování
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#pragma once

#include <iostream>

#include "config.hpp"
#include "myLib.hpp"
#include "externalCode.hpp"

using namespace std;

void decrypt (config * cnf);
char decryptChar (char character,int invertedKeyA,int keyB);
char decryptFunc(char character,int invertedKeyA,int keyB);
string decryptMess(string message,int keyA, int keyB);