#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
A=1

echo ---01 Basic Testy---

vstup=code1.txt
../prg < ./01_basic_tests/${vstup}


A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  prazdny scope =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  prazdny scope !=0 =$A ${NC}
fi

vstup=code2.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  testovanie komentarov =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  testovanie komentarov !=0 =$A ${NC}
fi

vstup=code3.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} - Program 1: Vypocet faktorialu =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} - Program 1: Vypocet faktorialu !=0 =$A ${NC}
fi

vstup=code4.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Program 2: Vypocet faktorialu rekurzivne =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Program 2: Vypocet faktorialu rekurzivne !=0 =$A ${NC}
fi

vstup=code5.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Program 3: Prace s retezci a vestavenymi funkcemi =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Program 3: Prace s retezci a vestavenymi funkcemi !=0 =$A ${NC}
fi

vstup=code6.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  IF =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  IF !=0 =$A ${NC}
fi

vstup=code7.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} -  IF =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  IF !=2 =$A ${NC}
fi

vstup=code8.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  while =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  while !=0 =$A ${NC}
fi

vstup=code9.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} -  while =2 = $? ${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  while !=2 =$A ${NC}
fi

vstup=code10.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  priradenie =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  priradenie !=0 =$A ${NC}
fi

vstup=code11.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  priradenie =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  priradenie !=3 =$A ${NC}
fi

vstup=code12.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  input =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  input !=0 =$A ${NC}
fi

vstup=code13.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A != 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  input !=0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  input =0 !=0 ${NC}
fi

vstup=code14.txt

../prg < ./01_basic_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} - print =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} - print !=0 =$A ${NC}
fi

vstup=code15.txt

../prg < ./01_basic_tests/${vstup}


A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} - print =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} - print !=2 =$A ${NC}
fi

vstup=code16.txt

../prg < ./01_basic_tests/${vstup}


A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} - double vyraz =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} - double vyraz !=0 =$A ${NC}
fi

vstup=code17.txt

../prg < ./01_basic_tests/${vstup}


A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} - vstavane funkcie =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} - vstavane funkcie !=0 =$A ${NC}
fi

vstup=code18.txt

../prg < ./01_basic_tests/${vstup}


A=$?
if [  $A = 4 ]
then
echo -e ${GREEN}OK  - ${vstup} - typova konverzia =4${NC}
else
echo -e ${RED}FAIL  - ${vstup} - typova konverzia !=4 =$A ${NC}
fi

vstup=code19.txt

../prg < ./01_basic_tests/${vstup}


A=$?
if [  $A = 4 ]
then
echo -e ${GREEN}OK  - ${vstup} - typova konverzia =4${NC}
else
echo -e ${RED}FAIL  - ${vstup} - typova konverzia !=4 =$A ${NC}
fi

vstup=code20.txt

../prg < ./01_basic_tests/${vstup}


A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} - typova konverzia =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} - typova konverzia !=0 =$A ${NC}
fi


echo ---02 Lex Testy---

vstup=code1.txt
../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} -  blokovy komentar =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  blokovy komentar !=1 =$A ${NC}
fi

vstup=code2.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} -  blokovy komentar =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  blokovy komentar !=1 =$A ${NC}
fi

vstup=code3.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} - blokovy komentar =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} - blokovy komentar !=1 =$A ${NC}
fi

vstup=code4.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Vnoreny blokovy komentar =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Vnoreny blokovy komentar !=1 =$A ${NC}
fi

vstup=code5.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Viacriadkovy blokovy komentar =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Viacriadkovy blokovy komentar !=0 =$A ${NC}
fi

vstup=code6.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  riadkovy komentar =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  riadkovy komentar !=0 =$A ${NC}
fi

vstup=code7.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  correct string =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  correct string !=0 =$A ${NC}
fi

vstup=code8.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} -  wrong string =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  wrong string !=1 =$A ${NC}
fi

vstup=code9.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} -  wrong string =1 ${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  wrong string !=1 =$A ${NC}
fi

vstup=code10.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} -  wrong string =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  wrong string !=1 =$A ${NC}
fi

vstup=code11.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} -  wrong string =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  wrong string !=2 =$A ${NC}
fi

vstup=code12.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  retazce =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  retazce !=0 =$A ${NC}
fi

vstup=code13.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} -  chyba retazca =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  chyba retazca !=1 !=$A ${NC}
fi

vstup=code14.txt

../prg < ./02_lex_tests/${vstup}

A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} -  chyba retazca =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  chyba retazca !=1 !=$A ${NC}
fi

vstup=code15.txt

../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} - krajny pripad retazca =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} - krajny pripad retazca !=0 =$A ${NC}
fi

vstup=code16.txt

../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} -  chyba retazca, krajny pripad =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  chyba retazca, krajny pripad !=1 !=$A ${NC}
fi

vstup=code17.txt

../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} - double =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} - double !=0 =$A ${NC}
fi

vstup=code18.txt

../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} - double krajne pripady =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} - double krajne pripady !=0 =$A ${NC}
fi

vstup=code19.txt

../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} - double 2.0.0 =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} - double 2.0.0 !=1 =$A ${NC}
fi

vstup=code20.txt

../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} - double -2.0.0 =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} - double -2.0.0 !=1 =$A ${NC}
fi

vstup=code21.txt

../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} - zaporny double -5.5e10 =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} - zaporny double -5.5e10 !=1 =$A ${NC}
fi

vstup=code22.txt

../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} - 5e+10.5 =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} - 5e+10.5 !=1 =$A ${NC}
fi

vstup=code23.txt

../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} - 5ee+10 =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} - 5ee+10 !=1 =$A ${NC}
fi

vstup=code24.txt

../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} - 5e+10e =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} - 5e+10e !=1 =$A ${NC}
fi

vstup=code25.txt

../prg < ./02_lex_tests/${vstup}


A=$?
if [  $A = 1 ]
then
echo -e ${GREEN}OK  - ${vstup} - zaporne cislo, int =1${NC}
else
echo -e ${RED}FAIL  - ${vstup} - zaporne cislo, int !=1 =$A ${NC}
fi


echo ---03 Syn Testy---

vstup=code1.txt
../prg < ./03_syn_tests/${vstup}


A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  DIM test =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  DIM test !=0 =$A ${NC}
fi

vstup=code2.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} -  DIM test =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  DIM test !=2 =$A ${NC}
fi

vstup=code3.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} - priradenie =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} - priradenie !=0 =$A ${NC}
fi

vstup=code4.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} -  priradenie =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  priradenie !=2 =$A ${NC}
fi

vstup=code5.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  INPUT =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  INPUT !=0 =$A ${NC}
fi

vstup=code6.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} -  INPUT =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  INPUT !=2 =$A ${NC}
fi

vstup=code7.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  PRINT =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  PRINT !=0 =$A ${NC}
fi

vstup=code8.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} -  PRINT =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  PRINT !=2 =$A ${NC}
fi

vstup=code9.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  IF =0 ${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  IF !=0 =$A ${NC}
fi

vstup=code10.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} -  IF =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  IF !=2 =$A ${NC}
fi

vstup=code11.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  DO WHILE =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  DO WHILE !=0 =$A ${NC}
fi

vstup=code12.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} -  DO WHILE =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  DO WHILE !=2 =$A ${NC}
fi

vstup=code13.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Priradenie f =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Priradenie f !=0 !=$A ${NC}
fi

vstup=code14.txt

../prg < ./03_syn_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Chybne volanie f =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Chybne volanie f !=3 =$A ${NC}
fi

vstup=code15.txt

../prg < ./03_syn_tests/${vstup}


A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} - Vyraz =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} - Vyraz !=0 =$A ${NC}
fi

vstup=code16.txt

../prg < ./03_syn_tests/${vstup}


A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Vyraz =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Vyraz !=2 !=$A ${NC}
fi

vstup=code17.txt

../prg < ./03_syn_tests/${vstup}


A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} - Vyraz s relaciou =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} - Vyraz s relaciou !=2 =$A ${NC}
fi

vstup=code18.txt

../prg < ./03_syn_tests/${vstup}


A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} - Vyraz s relaciou =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} - Vyraz s relaciou !=0 =$A ${NC}
fi

vstup=code19.txt

../prg < ./03_syn_tests/${vstup}


A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} - Vyraz uzatvorkovanie =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} - Vyraz uzatvorkovanie !=2 =$A ${NC}
fi

vstup=code20.txt

../prg < ./03_syn_tests/${vstup}


A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} - Vyraz blizkost operatorov =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} - Vyraz blizkost operatorov !=2 =$A ${NC}
fi

echo ---04 Sem Testy---

vstup=code1.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Function test =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Function test !=0 =$A ${NC}
fi

vstup=code2.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Function test bez deklaracie =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Function test bez deklaracie !=0 =$A ${NC}
fi

vstup=code3.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Function test bez definicie =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Function test bez definicie !=3 =$A ${NC}
fi

vstup=code4.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Function test dvojita deklaracia =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Function test dvojita deklaracia !=3 =$A ${NC}
fi

vstup=code5.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Function test dvojita definicia =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Function test dvojita definicia !=3 =$A ${NC}
fi

vstup=code6.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Function test nezhodnost deklaracie a definicie =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Function test nezhodnost deklaracie a definicie !=3 =$A ${NC}
fi

vstup=code7.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Overenie presuvania medzi TS =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Overenie presuvania medzi TS !=3 =$A ${NC}
fi

vstup=code8.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Overenie presuvania medzi TS =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Overenie presuvania medzi TS !=0 =$A ${NC}
fi

vstup=code9.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Overenie presuvania medzi TS =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Overenie presuvania medzi TS !=3 =$A ${NC}
fi

vstup=code10.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Vzajomne volanie funkcii =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Vzajomne volanie funkcii !=0 =$A ${NC}
fi

vstup=code11.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Chybna scope deklaracia =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Chybna scope deklaracia !=3 =$A ${NC}
fi

vstup=code12.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Volanie funkcie double = integer =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Volanie funkcie double = integer !=0 =$A ${NC}
fi

vstup=code13.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 4 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Volanie funkcie string = integer =4${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Volanie funkcie string = integer !=4 =$A ${NC}
fi

vstup=code14.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Volanie funkcie integer = double =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Volanie funkcie integer = double !=0 =$A ${NC}
fi

vstup=code15.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Nezhodnost parametrov definicie a deklaracie =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Nezhodnost parametrov definicie a deklaracie !=3 =$A ${NC}
fi

vstup=code16.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Nezhodnost parametrov definicie a deklaracie =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Nezhodnost parametrov definicie a deklaracie !=3 =$A ${NC}
fi

vstup=code17.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Redeklaracia premennej, rovnaky typ =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Redeklaracia premennej, rovnaky typ !=3 =$A ${NC}
fi

vstup=code18.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Redeklaracia premennej, rozny typ =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Redeklaracia premennej, rozny typ !=3 =$A ${NC}
fi

vstup=code19.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Return konverzia double = int= =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Return konverzia double = int !=0 =$A ${NC}
fi

vstup=code20.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Relacny vyraz =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Relacny vyraz !=0 =$A ${NC}
fi

vstup=code21.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Relacny vyraz + aritmetika =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Relacny vyraz + aritmetika !=0 =$A ${NC}
fi

vstup=code22.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 4 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Integer = boolean relacia =4${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Integer = boolean relacia !=4 =$A ${NC}
fi

vstup=code23.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 2 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Chybne volanie funkcie =2${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Chybne volanie funkcie !=2 =$A ${NC}
fi

vstup=code24.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 3 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Chybne volanie funkcie =3${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Chybne volanie funkcie !=3 =$A ${NC}
fi

vstup=code25.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Vkladanie presneho vyrazu int to int =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Vkladanie presneho vyrazu int to int !=0 =$A ${NC}
fi

vstup=code26.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Vkladanie presneho vyrazu double to double =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Vkladanie presneho vyrazu double to double !=0 =$A ${NC}
fi

vstup=code27.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Vkladanie presneho vyrazu double to int =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Vkladanie presneho vyrazu double to int !=0 =$A ${NC}
fi

vstup=code28.txt
../prg < ./04_sem_tests/${vstup}

A=$?
if [  $A = 0 ]
then
echo -e ${GREEN}OK  - ${vstup} -  Chybne volanie funkcie int to double =0${NC}
else
echo -e ${RED}FAIL  - ${vstup} -  Chybne volanie funkcie int to double !=0 =$A ${NC}
fi
