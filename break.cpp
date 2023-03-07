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

    vector <int> counter(26, 0);
    int sum=0;

    for (long unsigned int i=0; i<(cnf->text.length());i++){
        if (isLetter(cnf->text[i])){
            int index=int(normalize(cnf->text[i]));
            if(!(index>=0&&index<=25))
                throw invalid_argument("Blbě");
            counter[index]++;
            sum++;
        }
    }   
    
    vector <bool> mask(26, true);
    vector <int> vyskyt;
    
    for (long unsigned int j=0;j<13;j++){
        int maximumIndex=-1;
        int maximum=-1;
        for (long unsigned int i = 0; i < counter.size(); ++i){
            if((maximum<counter.at(i))&&mask.at(i)){
                maximumIndex=i;
                maximum=counter.at(i);               
            }
        }
        mask[maximumIndex]=false;
        vyskyt.push_back(maximumIndex);
    }

    vector <int> vaha{8,7,7,6,5,5,5,4,3,1,1,1,1};

    vector <int> nejcastejsi{f('E'),f('O'),f('A'),f('I'),
    f('N'),f('S'),f('T'),f('R'),f('V'),f('D'),f('P'),f('M'),f('U')};
    vector <int> strata{8, 7, 7,6,5,5,5,4,3,1,1,1,1};

    map <string,int> storage;
    int cnt=0;

    vector <int> keyA_Var={1,3,5,7,9,11,15,17,19,21,23,25};

    for (long unsigned int i=0;i<keyA_Var.size();i++){
        for (int j = 0; j <= 25; j++){
            for (long unsigned int mostrLeter=0;mostrLeter<vyskyt.size();mostrLeter++){
                for (long unsigned int guestLeter=0;guestLeter<nejcastejsi.size();guestLeter++){   
                    cnt++;
                    if(vyskyt[guestLeter]==(keyA_Var[i]*nejcastejsi[mostrLeter]+j)%26) {
                        string key=to_string(keyA_Var[i])+","+to_string(j);
                        if(storage.find(key)== storage.end()){
                            storage[key]=8- abs((vaha[mostrLeter] -strata[guestLeter]));
                        }
                        else{
                            storage[key]+=8- abs((vaha[mostrLeter] -strata[guestLeter]));
                        }
                    }   
                }               
            }
        }
    }
    std::multimap<int, string> dst = flip_map(storage);

    if(dst.empty()){
        cerr<<"něco je špatně\n";
        exit(-1);
    }

    auto it=dst.end();
    it--;

    int keyA,keyB;
    sscanf(it->second.c_str(),"%d,%d",&keyA,&keyB);  

    cnf->klicA=keyA;
    cnf->klicB=keyB;
    cout<< "a=" <<keyA <<",b="<< keyB <<"\n";
    cerr<<"metrika: "<< it->first<<"\n";
    cerr<<"porovnání: "<< cnt<<"\n";
    
    int lastN=5;
    it--;
    cerr<<"\n";
    cerr<<"Další pravděpodobné klíče:\n";
    while (it!=dst.begin()){
        sscanf(it->second.c_str(),"%d,%d",&keyA,&keyB);  
        cerr<< "a=" <<keyA <<",b="<< keyB <<"(M:"<<it->first<<"); ";
        lastN--;
        it--;
        if(lastN==0)
            break;
    }
    cerr<<"\n";
}