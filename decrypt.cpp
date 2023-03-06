#include "decrypt.hpp"


char decryptChar  (config * cnf,char character){
    if(character>=65&&character<=90) // normalizace A-Z
        character-=65;
    else if (character>=97&&character<=122)//normalizace a-z
        character-=97;
    else if (character==' ')    //mezery a odřádkování neřešíme
        return ' ';   
    else if (character=='\n')  //mezery a odřádkování neřešíme
        return '\n';   
    else
        return '_'; 

    char encryptedChar= (1/cnf->klicA) *( character -cnf->klicB )%26;   //šifrovací funke
    return encryptedChar+65;
}

void decrypt (config * cnf){
    cout<<"decrypting ...\n";

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
        char codedChar =decryptChar(cnf,character);
        fputc(codedChar, outPut_file);
    }

    fclose(input_file);
    fclose(outPut_file);
}