/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Všeobecné pomocné funkce
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#include "myLib.hpp"

char normalize(char character){
    if(character>=65&&character<=90) // normalizace A-Z
        character-=65;
    else if (character>=97&&character<=122)//normalizace a-z
        character-=97;

    return character;
}

bool isLetter(char character){
    return (character>=65&&character<=90) ||(character>=97&&character<=122);
}

char deNormalize(char character){
    return character + 65;
}