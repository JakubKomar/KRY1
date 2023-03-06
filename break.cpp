#include "decrypt.hpp"

void breakEn (config * cnf){

    FILE* input_file = fopen(cnf->vstupniSoubor.c_str(), "r");
    if (input_file == nullptr) {
       throw invalid_argument("Nepodařilo se otevřít vstupní soubor");
    }

    FILE* outPut_file = fopen(cnf->vystupniSoubor.c_str(), "w");
    if (input_file == nullptr) {
       throw invalid_argument("Nepodařilo se otevřít vstupní soubor");
    }

    char character = 0;
    while ((character = fgetc(input_file)) != EOF) {
        //putchar(character);
        //fputc(codedChar, outPut_file);
    }
}