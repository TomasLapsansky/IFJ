#include <stdio.h>

void gener_fce()
{
	printf("jump main \n");
	printf("#-----Zacatek vestavenych funkci------ \n\n");
	printf("#telo funkce length() \n");
	printf("label lenght \n");
	printf("pushframe \n");
	printf("defvar Lf@$return\n");
	printf("strlen Lf@$return Lf@s\n");
	printf("popframe \n");
	printf("return \n");

	printf("\n\n#telo funkce asc() \n");
	printf("label asc \n");
	printf("pushframe \n");
	printf("defvar Lf@$return\n");
	printf("move Lf@$return int@0\n");
	printf("defvar Lf@bool\n");
	printf("defvar Lf@delka\n");
	printf("strlen Lf@delka Lf@s\n");
	printf("LT Lf@bool Lf@i Lf@delka\n");
	printf("jumpifeq $asc_end$ Lf@bool bool@false\n");
	printf("stri2int  Lf@$return Lf@s Lf@i \n");
	printf("label $asc_end$ \n");
	printf("popframe \n");
	printf("return \n");

	printf("\n\n#telo funkce chr() \n");
	printf("label chr \n");
	printf("pushframe \n");
	printf("defvar Lf@$return\n");
	printf("move Lf@$return string@ \n");
	printf("defvar Lf@bool\n");
	printf("defvar Lf@bool2\n");
	printf("LT Lf@bool Lf@i int@256\n");
	printf("GT Lf@bool2 Lf@i int@-1\n");
	printf("AND Lf@bool Lf@bool Lf@bool2 \n");
	printf("jumpifeq $chr_end$ Lf@bool bool@false\n");
	printf("int2char  Lf@$return Lf@i \n");
	printf("label $chr_end$ \n");
	printf("popframe \n");
	printf("return \n");


	printf("\n\n#telo funkce substr() \n");
	printf("label substr \n");
	printf("pushframe \n");
	printf("defvar Lf@$return\n");
	printf("defvar Lf@$delka \n");
	printf("defvar Lf@$pomoc \n");
	printf("defvar Lf@$retez \n");
	printf("defvar Lf@$bool \n");
	printf("move  Lf@$retez string@ \n");
	printf("defvar Lf@index \n");
	printf("move lf@index Lf@i \n");
	printf("sub lf@index lf@index int@1 \n");
	printf("strlen Lf@delka lf@s \n");
	printf("gt Lf@bool Lf@i Lf@delka \n");
	printf("jumpifeq $substr_end$ Lf@bool bool@true \n");
	printf("eq Lf@bool Lf@i int@0 \n");
	printf("jumpifeq $substr_end$ Lf@bool bool@true \n");
	printf("lt Lf@bool Lf@i int@0 \n");
	printf("jumpifeq $substr_end$ Lf@bool bool@true \n");
	printf("eq Lf@bool Lf@s string@ \n");
	printf("jumpifeq $substr_end$ Lf@bool bool@true \n");
	printf("lt lf@bool lf@n int@0 \n");
	printf("jumpifeq $substr_n$ Lf@bool bool@true \n");
	printf("sub lf@delka lf@delka lf@index \n");
	printf("gt lf@bool lf@n lf@delka \n");
	printf("strlen Lf@delka lf@s \n");
	printf("jumpifeq $substr_n$ Lf@bool bool@true \n");
	printf("jump $substr_n_end$ \n");
	printf("label $substr_n$ \n");
	printf("lt lf@bool lf@index lf@delka \n");
	printf("jumpifeq $substr_end$ Lf@bool bool@false \n");
	printf("getchar Lf@pomoc Lf@s Lf@index \n");
	printf("add Lf@index Lf@index int@1 \n");
	printf("concat Lf@retez Lf@retez Lf@pomoc \n");
	printf("jump $substr_n$ \n");
	printf("label $substr_n_end$ \n");
	printf("label $substr_while_start$ \n");
	printf("eq Lf@bool Lf@n int@0 \n");
	printf("jumpifeq $substr_while_end$ Lf@bool bool@true \n");
	printf("gt Lf@bool Lf@delka Lf@index  \n");
	printf("jumpifeq $substr_end$ Lf@bool bool@false \n");
	printf("getchar Lf@pomoc Lf@s Lf@index \n");
	printf("concat Lf@retez Lf@retez Lf@pomoc \n");
	printf("add Lf@index Lf@index int@1 \n");
	printf("sub Lf@n Lf@n int@1 \n");
	printf("jump $substr_while_start$ \n");
	printf("label $substr_while_end$ \n");
	printf("label $substr_end$ \n");
	printf("move Lf@$return Lf@$retez\n");
	printf("popframe \n");
	printf("return \n\n");
	printf("#-----Konec vestavenych funkci------ \n\n");

}
