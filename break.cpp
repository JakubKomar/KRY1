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

    out<< decryptMess(cnf);

}

int f(char a){
    return int(a)-65;
}

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                   flip_pair<A,B>);
    return dst;
}

void leaterAnalysys(config * cnf){  
    //vector <double> cetnostCeskyJazyk={8.4548,1.5582,2.5557,3.6241,10.6751,0.2732,0.2729,1.2712,1.1709,7.6227,2.1194,3.7367,3.8424,3.2267,6.6167,8.6977,3.4127,0.0013,4.9136,5.3212,5.7694,3.9422,4.6616,0.0088,0.0755,2.9814,3.1939,};
    vector <double> cetnostCeskyJazyk={8.82,1.665,2.6,3.62,10.5,0.394,0.343,1.296,1.007,7.673,1.983,3.752,4.097,3.662,6.73,8.3,3.454,0.006,5.163,5.437,5.59,3.845,4.378,0.072,0.092,2.7,3.145};
    
    vector <double> cetnostText(26, 0);
    int sum=0;
    char prevChar=' ';

    map <string,int> bigramy;

    for (long unsigned int i=0; i<(cnf->text.length());i++){
        if (isLetter(cnf->text[i])){
            int index=int(normalize(cnf->text[i]));
            cetnostText[index]++;
            sum++;

            if(prevChar!=' '){
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
   /*
    for ( map<string, int>::const_iterator it = bigramy.begin(); it != bigramy.end(); it++) {
        cout << it->first <<":"<< it->second<< "; ";
    }
    cout << "\n";*/

    std::multimap<int, string> sortedBigramy = flip_map(bigramy);
    
    vector <string>gratestBigrams;
    #define pocetBigramu 50
    int grCnt=pocetBigramu;
    for ( multimap<int, string>::const_iterator it = sortedBigramy.end(); it != sortedBigramy.begin(); ) {
        it--;
        //cout << it->first <<":"<< it->second<< "; ";
        if(grCnt<0)
            break;
        gratestBigrams.push_back( it->second);
        grCnt--;
    }
    //cout <<"\n";

    for(long unsigned int i=0; i<(cetnostText.size());i++){
        cetnostText[i]=(cetnostText[i]/sum)*100;
    }
    
   vector <string> bigramyCeskyJazyk={"ST","NI","PO","OV","RO","EN","NA","JE","PR","TE","LE","KO","NE","OD","RA","TO","OU","NO","LA","LI"
   ,"HO","DO","OS","SE","TA","AL","ED","AN","CE","VA","PR","AT","RE","ER","TI","EM","IN","SK","LO","NE"};


    map <string,int> storage;
    int cnt=0;
    int cnt2=0;
    vector <int> keyA_Var={1,3,5,7,9,11,15,17,19,21,23,25};

    for (long unsigned int i=0;i<keyA_Var.size();i++){
        for (int j = 0; j <= 25; j++){  //všechny klíče
            string key=to_string(keyA_Var[i])+","+to_string(j);
            storage[key]=0;
            for (int leterIndex=0;leterIndex<26;leterIndex++){    //všechna písmena
                int substitedLet=(keyA_Var[i]*leterIndex+j)%26  ;
                storage[key]+= pow( abs(cetnostCeskyJazyk[leterIndex] - cetnostText[substitedLet]),2);                                 
            }
            int toFind=pocetBigramu;
            for (long unsigned int x=0;x<bigramyCeskyJazyk.size();x++){ 
                string bigramDe= encrtptMess(keyA_Var[i],j,bigramyCeskyJazyk[x]);
                if(find(gratestBigrams.begin(), gratestBigrams.end(), bigramDe) != gratestBigrams.end()){
                   toFind--;
                }


            }
            storage[key]+=(600/pocetBigramu)*toFind;
            
        }
    }

    std::multimap<int, string> dst = flip_map(storage);
    
    /*for ( multimap<int, string>::const_iterator it = dst.begin(); it != dst.end(); it++) {
        cout << it->first <<":"<< it->second<< "; ";
    }
    cout << "\n";*/
    if(dst.empty()){
        cerr<<"něco je špatně\n";
        exit(-1);
    }

    auto it=dst.begin();

    int keyA,keyB;
    sscanf(it->second.c_str(),"%d,%d",&keyA,&keyB);  

    cnf->klicA=keyA;
    cnf->klicB=keyB;
    cout<< "a=" <<keyA <<",b="<< keyB <<"\n";
    cerr<<"metrika: "<< it->first<<"\n";
    cerr<<"porovnání: "<< cnt2<<"\n";
    
    int lastN=10;
    cerr<<"\n";
    cerr<<"Další pravděpodobné klíče:\n";
    while (it!=dst.end()){
        it++;
        sscanf(it->second.c_str(),"%d,%d",&keyA,&keyB);  
        cerr<< "a=" <<keyA <<",b="<< keyB <<"(M:"<<it->first<<"); ";
        lastN--;
        if(lastN==0)
            break;
    }
    cerr<<"\n";
}