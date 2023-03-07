/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Struktura pro ukládání konfigurace
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#pragma once

#include <cstring>

using namespace std;

typedef struct config{
    bool sifrovani=false;
    bool desifrovani=false;
    bool desifrovaniBezKlice=false;
    int klicA=0;
    int klicB=0;
    string vstupniSoubor="";
    string vystupniSoubor="";
    string text="";
}config;
