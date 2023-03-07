#include "encrypt.hpp"


char encryptChar  (int keyA,int keyB,char character){

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

    char encryptedChar= (keyA * character +keyB )%26;   //šifrovací funke
    return deNormalize(encryptedChar);
}

string encrtptMess(int keyA,int keyB,string text){
    string encMess="";

    for (long unsigned int i=0; i<(text.length());i++){
        encMess+=encryptChar(keyA,keyB, text[i]);
    }
    return encMess;
}


void encrypt (config * cnf){
    for (long unsigned int i=0; i<(cnf->text.length());i++){
        cout<<encryptChar(cnf->klicA,cnf->klicB,cnf->text[i]);
    }
    cout<<"\n";
}