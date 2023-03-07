 * @project Implementace Afinitní šifry - KRY (1 projekt) 
 * @details Program pro šifrování/defšifrování pomocí afinitní šifry a její prolamování
 * @brief   Všeobecné pomocné funkce
 * @authors Bc. Jakub Komárek (xkomar33)

použití:
    ./kry [ [ -e | -d ] -a "klíč A" -b "klíč B" ] | -c -f "vstupní soubor"  -o "výstupní soubor" | -h
    
argumenty:
    -e – parametr označující šifrování
    -d – parametr označující dešifrování
    -c – parametr označující dešifrování bez znalosti klíče
    -a x – parametr označující klíč “a” (x označuje hodnotu například 3)
    -b y – parametr označující klíč “b” (x označuje hodnotu například 7)
    -f <název souboru> - parametr označující cestu k souboru.
    -o <název souboru> - parametr označující výstupní soubor s otevřeným textem

příklady použití:
    ./kry -e -a 3 -b 7 "TOTO JE TAJNA ZPRAVA"
    ./kry -d -a 3 -b 7 "MXMX IT MHIUH EAGHSH"
    ./kry -c -f "soubor.txt.enc" -o "soubor.txt"

