/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Převzaté kódy
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

int modInverse(int A, int M);

// sort funkce pro map podle hodnoty
// převzato ze https://stackoverflow.com/a/5056797
template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

// sort funkce pro map podle hodnoty
// převzato ze https://stackoverflow.com/a/5056797
template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                   flip_pair<A,B>);
    return dst;
}
 