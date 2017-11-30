#!/bin/bash 

echo ---ZACATEK TESTOVANI---

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

vstup=code1.txt
../prg < ./vstupy/code1.txt

if [  $? = 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  prazdny scope s komentari${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  prazdny scope s komentari${NC}
fi

vstup=code2.txt

../prg < ./vstupy/${vstup}

if [  $? = 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  deklarace promenych${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  deklarace promenych${NC}
fi

vstup=code3.txt

../prg < ./vstupy/${vstup}

if [  $? = 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} - prirazeni promenych ${NC}
else 
echo -e ${RED}FAIL  - ${vstup} - prirazeni promenych ${NC}
fi

vstup=code4.txt

../prg < ./vstupy/${vstup}

if [  $? != 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  nalezena chyba prirazeni !=0${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  nelezena chyba prirazeni !=0${NC}
fi

vstup=code5.txt

../prg < ./vstupy/${vstup}

if [  $? = 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  scitani a konvertovani typu ${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  scitani a konvertovani typu ${NC}
fi

vstup=code6.txt

../prg < ./vstupy/${vstup}

if [  $? = 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  print${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  print${NC}
fi

vstup=code7.txt

../prg < ./vstupy/${vstup}

if [  $? = 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  casesensitiv + too long double${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  casesensitiv + too long double${NC}
fi

vstup=code8.txt

../prg < ./vstupy/${vstup}

if [  $? = 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  prazdne telo fce${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  prazdne telo fce${NC}
fi

vstup=code9.txt

../prg < ./vstupy/${vstup}

if [  $? != 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  stejny nazev promene a funkce !=0${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  stejny nazev promene a funkce !=0${NC}
fi

vstup=code10.txt

../prg < ./vstupy/${vstup}

if [  $? = 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  vestavene funkce${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  vestavene funkce${NC}
fi

vstup=code11.txt

../prg < ./vstupy/${vstup}

if [  $? = 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  3 funkce jeden parametr${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  3 funkce jeden parametr${NC}
fi

vstup=code12.txt

../prg < ./vstupy/${vstup}

if [  $? = 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  zadani 2 faktorial${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  zadani 2 faktorial${NC}
fi

vstup=code13.txt

../prg < ./vstupy/${vstup}

if [  $? = 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} -  zadani 3 retezce a vestavene funkcemi${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  zadani 3 retezce a vestavene funkcemi${NC}
fi

vstup=code14.txt

../prg < ./vstupy/${vstup}



if [  $? != 0 ] 
then 
echo -e ${GREEN}OK  - ${vstup} - retur n uvnitr scope  !=0${NC}
else 
echo -e ${RED}FAIL  - ${vstup} -  retur n uvnitr scope !=0${NC}
fi

