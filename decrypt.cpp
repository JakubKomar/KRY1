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

    char encryptedChar=invertedKeyA *( character -cnf->klicB )%26;   //šifrovací funke
    if(encryptedChar<0)
        encryptedChar=encryptedChar+26;
    return deNormalize(encryptedChar);
}

void decrypt (config * cnf){
    cout<<decryptMess(cnf);
    cout<<"\n";
}

string decryptMess(config * cnf){
    string decMess="";
    int invertedKeyA= modInverse(cnf->klicA,26);

    for (long unsigned int i=0; i<(cnf->text.length());i++){
        decMess+=decryptChar(cnf,cnf->text[i], invertedKeyA);
    }
    return decMess;
}