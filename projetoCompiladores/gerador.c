#include <stdlib.h>
#include <stdio.h>
#include <conio.h>


char string[30];
int p = 0;
int main()
{
   printf("Digite a sentença: ");
   gets(string);
   goto E0;
}
	E0:
    if(string[p] == 'a')
    {
		p++;
		GOTO E1;
    }
		else if(string[p] == 'b')
    {
		p++;
		GOTO E0;
    }
    else
        GOTO REJEITA;

    
	E1:
    if(string[p] == 'a')
    {
		p++;
		GOTO E0;
    }
		else if(string[p] == 'b')
    {
		p++;
		GOTO E1;
    }
	else if( string[p] == 0 )
		GOTO ACEITA;
	

    else
        GOTO REJEITA;

    
void ACEITA()
    {
	    printf("=====================SENTENÇA ACEITA=======================");
        getch();
        exit(0);
    }    

void REJEITA()
    {
	    printf("=====================SENTENÇA REJEITADA=====================");
        getch();
        exit(0);
    }    

