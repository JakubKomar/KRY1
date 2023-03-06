#include "encrypt.hpp"


char encryptChar  (config * cnf,char character){
    if(character>=65&&character<=90)
        character-=65;
    else if (character>=97&&character<=122)
        character-=97;
    else if (character==32)
        return 32;   
    else if (character=='\n')
        return '\n';   
    cout << int (character)<<";";
    char encryptedChar= (cnf->klicA * character +cnf->klicB )%26;
    return encryptedChar+65;
}

void encrypt (config * cnf){
    cout<<"encrypting ...\n";

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
        char codedChar =encryptChar(cnf,character);
        fputc(codedChar, outPut_file); ;
    }

    fclose(input_file);
    fclose(outPut_file);
}