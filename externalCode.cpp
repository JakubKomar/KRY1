/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Převzaté kódy
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#include "externalCode.hpp"

// modulární inverze
// vykradeno z https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
int modInverse(int A, int M)
{
    for (int X = 1; X < M; X++)
        if (((A % M) * (X % M)) % M == 1)
            return X;
    throw invalid_argument("blbě");
    return -1;
}

