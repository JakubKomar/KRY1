/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Main - parsování argumentů a volání hlavních funkcí
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

#include "break.hpp"
#include "config.hpp"
#include "encrypt.hpp"
#include "decrypt.hpp"

using namespace std;

int main(int argc, char *argv[]);
config parseArgs(int argc, char *argv[]);
void cheackConf(config * cnf);

