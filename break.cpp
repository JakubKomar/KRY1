/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Část pro prolamování šífry pomocí frekvenční analýzy
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#include "break.hpp"

void breakEn (config * cnf){
    FILE* input_file = fopen(cnf->vstupniSoubor.c_str(), "r");
    if (input_file == nullptr) {
       throw invalid_argument("Nepodařilo se otevřít vstupní soubor");
    }
    ofstream out(cnf->vystupniSoubor);

    char character = 0;
    while ((character = fgetc(input_file)) != EOF) {
        cnf->text+=character;
    }

    leaterAnalysys(cnf);

    out<< decryptMess(cnf->text,cnf->klicA,cnf->klicB);
}

#define pocetBigramu 50
void leaterAnalysys(config * cnf){  
    //předpokládaná četnost ze https://nlp.fi.muni.cz/cs/FrekvenceSlovLemmat
    //vector <double> cetnostCeskyJazyk={8.4548,1.5582,2.5557,3.6241,10.6751,0.2732,0.2729,1.2712,1.1709,7.6227,2.1194,3.7367,3.8424,3.2267,6.6167,8.6977,3.4127,0.0013,4.9136,5.3212,5.7694,3.9422,4.6616,0.0088,0.0755,2.9814,3.1939,};
    //předpokládaná četnost ze https://algoritmy.net/article/40/Cetnost-znaku-CJ
    vector <double> cetnostCeskyJazyk={8.82,1.665,2.6,3.62,10.5,0.394,0.343,1.296,1.007,7.673,1.983,3.752,4.097,3.662,6.73,8.3,3.454,0.006,5.163,5.437,5.59,3.845,4.378,0.072,0.092,2.7,3.145};
    vector <double> cetnostText(26, 0);
    int sum=0;
    char prevChar=' ';

    map <string,int> bigramy;

    for (long unsigned int i=0; i<(cnf->text.length());i++){
        if (isLetter(cnf->text[i])){
            int index=int(normalize(cnf->text[i]));
            cetnostText[index]++;       //počítadlo jednotlivých znaků
            sum++;  

            if(prevChar!=' '){  //počítadlo bigramů
                if(bigramy.find(string(1,prevChar)+cnf->text[i])== bigramy.end())
                    bigramy[string(1,prevChar)+cnf->text[i]] =1;
                else
                    bigramy[string(1,prevChar)+cnf->text[i]]++;
            }

            prevChar=cnf->text[i];
        }
        else{
            prevChar=' ';
        }
    }   

    std::multimap<int, string> sortedBigramy = flip_map(bigramy);   //seřazení bigramů
    
    vector <string>gratestBigrams;

    int grCnt=pocetBigramu;
    for ( multimap<int, string>::const_iterator it = sortedBigramy.end(); it != sortedBigramy.begin(); ) {  //výběr nejčastějších n bigramý
        it--;
        if(grCnt<0)
            break;
        gratestBigrams.push_back( it->second);
        grCnt--;
    }

    for(long unsigned int i=0; i<(cetnostText.size());i++){
        cetnostText[i]=(cetnostText[i]/sum)*100;    //normalizace a převod na procenta četnosti jednotlivých znaků
    }
    
    // nejčastější české bigramy ze https://nlp.fi.muni.cz/cs/FrekvenceSlovLemmat
    const vector <string> bigramyCeskyJazyk={"ST","NI","PO","OV","RO","EN","NA","JE","PR","TE","LE","KO","NE","OD","RA","TO","OU","NO","LA","LI","HO","DO","OS","SE","TA","AL","ED","AN","CE","VA","PR","AT","RE","ER","TI","EM","IN","SK","LO","NE"};

    const vector <int> keyA_Var={1,3,5,7,9,11,15,17,19,21,23,25};

    map <string,int> storage;

    for (long unsigned int i=0;i<keyA_Var.size();i++){
        for (int j = 0; j <= 25; j++){  //všechny klíče
            string key=to_string(keyA_Var[i])+","+to_string(j);
            storage[key]=0;
            for (int leterIndex=0;leterIndex<26;leterIndex++){    //ohodnocení páru klíčů  na základě frekvence písmen
                int substitedLet=(keyA_Var[i]*leterIndex+j)%26  ;
                // maximální/nejhorší ohodnocení se pohybuje okolo hodnoty 600 
                storage[key]+= pow( abs(cetnostCeskyJazyk[leterIndex] - cetnostText[substitedLet]),2);                                
            }

            int toFind=pocetBigramu;
            for (long unsigned int x=0;x<bigramyCeskyJazyk.size();x++){ //ohodnocení páru klíčů  na základě frekvence bigramů
                string bigramDe= encrtptMess(keyA_Var[i],j,bigramyCeskyJazyk[x]);
                if(find(gratestBigrams.begin(), gratestBigrams.end(), bigramDe) != gratestBigrams.end()){
                   toFind--;
                }
            }
            // v případě nenalezení bigramu z textu mezi nejčastějšími bigramy je udělena penalta, maximální penalta v případě nenalezení žádného je 600 
            storage[key]+=(600/pocetBigramu)*toFind;         
        }
    }

    std::multimap<int, string> dst = flip_map(storage); //sort podle nejmenšího skóre
    
    if(dst.empty()){
        cerr<<"něco je špatně\n";
        exit(-1);
    }

    // --------------- výpis výsledků  -----------------------
    auto it=dst.begin();

    int keyA,keyB;
    sscanf(it->second.c_str(),"%d,%d",&keyA,&keyB);  

    cnf->klicA=keyA;
    cnf->klicB=keyB;
    cout<< "a=" <<keyA <<",b="<< keyB <<"\n";


    cerr<<"\033[1;36m------------------------------------\n";
    cerr<<"metrika: "<< it->first<<"\n";
    
    int lastN=10;
    cerr<<"\n";
    cerr<<"Další pravděpodobné klíče:\n";
    while (it!=dst.end()){
        it++;
        sscanf(it->second.c_str(),"%d,%d",&keyA,&keyB);  
        cerr<< "a=" <<keyA <<",b="<< keyB <<" (M:"<<it->first<<"); ";
        lastN--;
        if(lastN==0)
            break;
    }
    cerr<<"\033[1;39m\n";
}