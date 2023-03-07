/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Všeobecné pomocné funkce
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#pragma once

#include <iostream>
#include <fstream>

#include "config.hpp"

using namespace std;

char deNormalize(char character);
char normalize(char character);
bool isLetter(char character);