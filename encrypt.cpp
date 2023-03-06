#include "encrypt.hpp"


char encryptChar  (config * cnf,char character){

    if (isLetter(character))
        character=normalize(character);
    else if (character==' ')    //mezery a odřádkování neřešíme
        return ' ';   
    else if (character=='\n')  //mezery a odřádkování neřešíme
        return '\n';   
    else {
        //cerr<<"tento znak nelze šifrovat/dešifrovat: '"<<character<<"'!\n";
        return character;
    }

    char encryptedChar= (cnf->klicA * character +cnf->klicB )%26;   //šifrovací funke
    return deNormalize(encryptedChar);
}

void encrypt (config * cnf){
    for (long unsigned int i=0; i<(cnf->text.length());i++){
        cout<<encryptChar(cnf,cnf->text[i]);
    }
    cout<<"\n";
}