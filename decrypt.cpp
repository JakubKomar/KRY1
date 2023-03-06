#include "decrypt.hpp"

// vykradeno z https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
int modInverse(int A, int M)
{
    for (int X = 1; X < M; X++)
        if (((A % M) * (X % M)) % M == 1)
            return X;
    throw invalid_argument("blbě");
    return -1;
}
// konec vykradené části
 

char decryptChar  (config * cnf,char character,int invertedKeyA){
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

    char encryptedChar=invertedKeyA *( character -cnf->klicB )%26;   //šifrovací funke
    if(encryptedChar<0)
        encryptedChar=encryptedChar+26;
    //cout << int(encryptedChar)<< "\n";
    return encryptedChar+65;
}

void decrypt (config * cnf){
    FILE* input_file = fopen(cnf->vstupniSoubor.c_str(), "r");
    if (input_file == nullptr) {
       throw invalid_argument("Nepodařilo se otevřít vstupní soubor");
    }

    FILE* outPut_file = fopen(cnf->vystupniSoubor.c_str(), "w");
    if (input_file == nullptr) {
       throw invalid_argument("Nepodařilo se otevřít vstupní soubor");
    }

    int invertedKeyA= modInverse(cnf->klicA,26);

    char character = 0;
    while ((character = fgetc(input_file)) != EOF) {
        //putchar(character);
        char codedChar =decryptChar(cnf,character, invertedKeyA);
        fputc(codedChar, outPut_file);
    }

    fclose(input_file);
    fclose(outPut_file);
}