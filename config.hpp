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
}config;
