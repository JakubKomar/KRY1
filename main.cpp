/**
 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Main - parsování argumentů a volání hlavních funkcí
 * @authors Bc. Jakub Komárek (xkomar33)
 */
#include "main.hpp"

int main(int argc, char *argv[]) 
{
    config conf = parseArgs(argc,argv);
    cheackConf(&conf);

    if (conf.sifrovani)
        encrypt(&conf);
    else if (conf.desifrovani)
        decrypt(&conf);
    else if (conf.desifrovaniBezKlice)
        breakEn(&conf);

    return 0;
}

config parseArgs(int argc, char *argv[]){
    config conf;
    bool textEntered=false;

    for(int i=1;i<argc;i++)
	{
        if(!strcmp(argv[i],"-h"))
		{
			cout<<
R""""(Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
Author: Bc. Jakub Komárek (xkomar33)
Použití:
    ./kry [ [ -e | -d ] -a "klíč A" -b "klíč B" ] | -c -f "vstupní soubor"  -o "výstupní soubor" | -h

Argumenty:
    -e – parametr označující šifrování
    -d – parametr označující dešifrování
    -c – parametr označující dešifrování bez znalosti klíče
    -a x – parametr označující klíč “a” (x označuje hodnotu například 3)
    -b y – parametr označující klíč “b” (x označuje hodnotu například 7)
    -f <název souboru> - parametr označující cestu k souboru.
    -o <název souboru> - parametr označující výstupní soubor s otevřeným textem

Příklady použití:
    ./kry -e -a 3 -b 7 "TOTO JE TAJNA ZPRAVA"
    ./kry -d -a 3 -b 7 "MXMX IT MHIUH EAGHSH"
    ./kry -c -f "soubor.txt.enc" -o "soubor.txt"
)"""";		
            exit(0);
		}	
		else if(!strcmp(argv[i],"-e"))
		{
			conf.sifrovani=true;
			
		}	
		else if(!strcmp(argv[i],"-d"))
		{
            conf.desifrovani=true;
        }
		else if(!strcmp(argv[i],"-c"))
		{
            conf.desifrovaniBezKlice=true;
        }
        else if(!strcmp(argv[i],"-a"))
		{
            (++i)<argc? conf.klicA=atoi(argv[i]):throw invalid_argument("Chybí hodnota za argumentem -a");
        }
        else if(!strcmp(argv[i],"-b"))
		{
             (++i)<argc? conf.klicB=atoi(argv[i]):throw invalid_argument("Chybí hodnota za argumentem -b");
        }
        else if(!strcmp(argv[i],"-f"))
		{
            (++i)<argc? conf.vstupniSoubor=argv[i]:throw invalid_argument("Chybí hodnota za argumentem -f");
        }
        else if(!strcmp(argv[i],"-o"))
		{
            (++i)<argc? conf.vystupniSoubor=argv[i]:throw invalid_argument("Chybí hodnota za argumentem -o");
        } 
        else if(!textEntered){
            conf.text=argv[i];
            textEntered=true;
        }
		else
			throw invalid_argument("Argument nebyl rozpoznán, zkuste parametr -h");
	}
    return conf;
}

void cheackConf(config *cnf){
    int cnt=0;
    if (cnf->desifrovani) cnt++;
    if (cnf->sifrovani) cnt++;
    if (cnf->desifrovaniBezKlice)cnt ++;
    if (cnt!=1) throw invalid_argument("Musíte vybrat právě jeden mód běhu programu.");

    if((cnf->desifrovaniBezKlice) && cnf->vystupniSoubor=="")throw invalid_argument("nebyl zadán výstupní soubor");
    if((cnf->desifrovaniBezKlice) && cnf->vstupniSoubor=="")throw invalid_argument("nebyl zadán vstupní soubor");

    if((cnf->desifrovani ||cnf->sifrovani) && cnf->klicA==0)throw invalid_argument("nebyl zadán klič A");
    if((cnf->desifrovani ||cnf->sifrovani)){
        if(! (cnf->klicA==1||cnf->klicA==3||cnf->klicA==5||cnf->klicA==7||cnf->klicA==9||cnf->klicA==11||
            cnf->klicA==15||cnf->klicA==17||cnf->klicA==19||cnf->klicA==21||cnf->klicA==23||cnf->klicA==25))
            throw invalid_argument("Nebyl zadán validní klíč A - vyberte číslo ze seznamu: 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23 a 25.");
    }
    if((cnf->desifrovani ||cnf->sifrovani) && cnf->klicB==0)throw invalid_argument("nebyl zadán klič B");
    if((cnf->desifrovani ||cnf->sifrovani) && cnf->text=="")throw invalid_argument("nebyl zadán text pro šifrování/defšifrování");
}