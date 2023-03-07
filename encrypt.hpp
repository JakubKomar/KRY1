#pragma once
#include <iostream>
#include "config.hpp"
#include "myLib.hpp"
#include <fstream>

using namespace std;

void encrypt (config * cnf);
char encryptChar  ( int keyA,int keyB,char character);
string encrtptMess(int keyA,int keyB,string text);