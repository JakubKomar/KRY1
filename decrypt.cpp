/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Část pro dešifrování
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#include "decrypt.hpp"

char decryptChar  (char character,int invertedKeyA,int keyB){
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

    char encryptedChar=decryptFunc(character,invertedKeyA,keyB);
    if(encryptedChar<0)
        encryptedChar=encryptedChar+26;
    return deNormalize(encryptedChar);
}

char decryptFunc(char character,int invertedKeyA,int keyB){
    return invertedKeyA *( character - keyB )%26;   //šifrovací funke
}

void decrypt (config * cnf){
    cout<<decryptMess(cnf->text,cnf->klicA,cnf->klicB);
    cout<<"\n";
}

string decryptMess(string message,int keyA, int keyB){
    string decMess="";
    int invertedKeyA= modInverse(keyA,26);

    for (long unsigned int i=0; i<(message.size());i++){
        decMess+=decryptChar(message[i], invertedKeyA,keyB);
    }
    return decMess;
}