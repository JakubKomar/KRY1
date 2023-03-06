
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
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

int main(int argc, char *argv[]);
config parseArgs(int argc, char *argv[]);
void cheackConf(config * cnf);

