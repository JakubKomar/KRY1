#pragma once
#include <iostream>
#include "config.hpp"
#include "myLib.hpp"

using namespace std;

void decrypt (config * cnf);
char decryptChar (config * cnf,char character,int invertedKeyA);
string decryptMess(config * cnf);