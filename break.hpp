/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Část pro prolamování šífry pomocí frekvenční analýzy
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include "config.hpp"
#include "myLib.hpp"
#include "decrypt.hpp"
#include "encrypt.hpp"

using namespace std;

void breakEn (config * cnf);
void leaterAnalysys(config * cnf);