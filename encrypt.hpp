/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Část pro šifrování
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#pragma once

#include <iostream>
#include <fstream>

#include "config.hpp"
#include "myLib.hpp"

using namespace std;

void encrypt (config * cnf);
char encryptChar  ( int keyA,int keyB,char character);
string encrtptMess(int keyA,int keyB,string text);
char encryptFunc(int keyA,int keyB,char character);