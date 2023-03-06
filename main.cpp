/**
 * @brief Pop3 klient s podporu tsl/ssl
 * @details klient pro stahování emailů z POP3 serveru
 * @authors Jakub Komárek (xkomar33)
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
    for(int i=1;i<argc;i++)
	{
        if(!strcmp(argv[i],"-h"))
		{
			cout<<"napoveda\n";		
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
		else
			throw invalid_argument("Argument nebyl rozpoznán");
	}
    return conf;
}

void cheackConf(config *cnf){
    int cnt=0;
    if (cnf->desifrovani) cnt++;
    if (cnf->sifrovani) cnt++;
    if (cnf->desifrovaniBezKlice)cnt ++;
    if (cnt!=1) throw invalid_argument("Musíte vybrat právě jeden mód běhu programu.");

    if((cnf->desifrovani ||cnf->sifrovani) && cnf->vystupniSoubor=="")throw invalid_argument("nebyl zadán výstupní soubor");
    if((cnf->desifrovani ||cnf->sifrovani) && cnf->vstupniSoubor=="")throw invalid_argument("nebyl zadán vstupní soubor");
    if((cnf->desifrovani ||cnf->sifrovani) && cnf->klicA==0)throw invalid_argument("nebyl zadán klič A");
    if((cnf->desifrovani ||cnf->sifrovani)){
        if(! (cnf->klicA==1||cnf->klicA==3||cnf->klicA==5||cnf->klicA==7||cnf->klicA==9||cnf->klicA==11||
            cnf->klicA==15||cnf->klicA==17||cnf->klicA==19||cnf->klicA==21||cnf->klicA==23||cnf->klicA==25))
            throw invalid_argument("Nebyl zadán validní klíč A - vyberte číslo ze seznamu: 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23 a 25.");
    }
    if((cnf->desifrovani ||cnf->sifrovani) && cnf->klicB==0)throw invalid_argument("nebyl zadán klič B");
}