#include <stdlib.h>
#include <stdio.h>
#include <conio.h>


char string[30];
int p = 0;
int main()
{
   printf("Digite a senten�a: ");
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
	    printf("=====================SENTEN�A ACEITA=======================");
        getch();
        exit(0);
    }    

void REJEITA()
    {
	    printf("=====================SENTEN�A REJEITADA=====================");
        getch();
        exit(0);
    }    

