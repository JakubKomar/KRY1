#pragma once
#include <iostream>
#include "config.hpp"
#include "myLib.hpp"
#include <fstream>

using namespace std;

void encrypt (config * cnf);
char encryptChar  (config * cnf,char character);