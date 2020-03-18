#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX 20

int main()
{
    setlocale (LC_ALL, "");

    int qtd_simbolos;
    int qtd_estados;
    int estado_inicial;
    int qtd_estados_finais;
    int estados_finais;
    int estados[MAX];
    char m[MAX][MAX];

    printf("Quantos simbolos tem o automato?\n");
    scanf("%d", &qtd_simbolos);

    char simbolos[qtd_simbolos];

    int i,j,x;
    for(i = 0; i<qtd_simbolos; i++)
    {
        printf("Quai é o simbolo %d?\n", i);
        scanf("%s", &simbolos[i]);
    }


    printf("Qual a quantidade de estados?\n");
    scanf("%d", &qtd_estados);

    printf("Qual é o estado inicial?\n");
    scanf("%d", &estado_inicial);



    printf("Qual é a quantidade de estados finais?\n");
    scanf("%d", &qtd_estados_finais);

    int eFinais[qtd_estados_finais];

    if(qtd_estados_finais > 1)
    {
		for(i=0; i<qtd_estados_finais; i++)
		{
            printf("Insira o estado final %d\n", i);
            scanf("%d", &eFinais[i]);
		}
	}
	else
	{
    	printf("Insira o estado final\n");
    	scanf("%d", &estados_finais);
	}




    for (i = 0; i<qtd_estados; i++){
        for(j = 0; j<qtd_simbolos; j++){
            printf("Para o estado e%d e simbolo %c, qual o próximo estado?", i, simbolos[j] );
            scanf("%d", &m[i][j]);
        }
    }


    FILE *f = fopen("gerador.c", "w");

    int op = 0; // opção default para evitar lixo de memória

    printf("Qual o tipo de arquivo você quer que seja gerado? \n\n");
    printf("Digite 1 para ""FUNÇÃO"" e 2 para ""GOTO""\n\n");
    scanf("%d", &op); // opção de geração de arquivo escolhida pelo usuário


    if(f == NULL)
        printf("ERRO");
    else
        printf("Arquivo \"gerador.c criado\" com sucesso!");


    switch(op)
    {
//===========================================================UTILIZANDO A OPÇÃO DE FUÑÇÃO===============================================================
        case(1):
            fprintf(f, "#include <stdlib.h>\n");
            fprintf(f, "#include <stdio.h>\n");
            fprintf(f, "#include <conio.h>\n");
            fprintf(f, "\n\n");

            fprintf(f,"char string[30];\n"); // vetor de char utilizado como variavel global.
            fprintf(f,"int p = 0;\n"); // Váriavel auxiliar para controle dos if's

            for(i = 0; i<qtd_estados; i++)
            {
                fprintf(f, "void e%d();\n", i);
            }
            fprintf(f,"void aceita();\n");
            fprintf(f,"void rejeita();\n\n");
            fprintf(f,"int main()\n");
            fprintf(f,"{\n\n");


            fprintf(f,"    int i;\n");

            fprintf(f,"   printf(\" Digite a sentença: \");\n");
            fprintf(f,"   gets(string);\n");
            fprintf(f,"   e%d();\n", estado_inicial);

            fprintf(f,"\n");
            fprintf(f,"    return 0;\n");
            fprintf(f,"}\n");

            int aux = 0;

            for(i = 0; i<qtd_estados; i++)
            {

                fprintf(f, "void e%d()\n{", i);
                for(j = 0; j<qtd_simbolos; j++)
                {
                    if ( m[i][j] >= 0 )
                    {
                        if (aux == 0)
                        {
                            fprintf(f, " \n    if( string[p] == '%c')\n    { ", simbolos[j]);
                            fprintf(f, "     p++; \n");
                            fprintf(f, "\   e%d(); \ \n", m[i][j]);
                            fprintf(f, "\    } \n");

                            aux += 1;
                        }
                        else
                        {
                            fprintf(f, "    else if ( string[p] == '%c') \n    { ", simbolos[j]);
                            fprintf(f, "    p++; \n");
                            fprintf(f, "\    e%d(); \ \n", m[i][j]);
                            fprintf(f, "    } \n");

                        }

                    }

                }
                aux = 0;

                if(qtd_estados_finais == 1)
                {
					if(estados_finais == i)
					{
						fprintf(f, "	else if( string[p] == 0 )\n    {");
						fprintf(f, "\n");
						fprintf(f, "		aceita();\n");
						fprintf(f, "	}\n");
						fprintf(f, "\n");
					}
				}
				else if(qtd_estados_finais > 1 )
				{
					for(x=0; x<qtd_estados_finais; x++){
						if(eFinais[x] == i)
						{
							fprintf(f, "	else if( string[p] == 0 )\n{");
							fprintf(f, "		aceita();\n");
							fprintf(f, "}\n");
							fprintf(f, "\n");
						}
					}
				}
				fprintf(f, "    else\n    {");
				fprintf(f, "\n");
				fprintf(f, "    rejeita();\n");
				fprintf(f, "    }\n");
				fprintf(f, "}\n");
            }

            fprintf(f, "void aceita()\n{");
            fprintf(f, "	printf(\"=====================SENTENÇA ACEITA=======================\");\n");
            fprintf(f, "    getch();\n");
            fprintf(f, "    exit(0);\n");
            fprintf(f, "    }");
            fprintf(f, "    \n\n");

            fprintf(f, "void rejeita()\n{");
            fprintf(f, "	printf(\"=====================SENTENÇA REJEITADA=====================\");\n");
            fprintf(f, "    getch();\n");
            fprintf(f, "    exit(0);\n");
            fprintf(f, "    }");
            fprintf(f, "    \n\n");
            break;

        case(2):
//===========================================================UTILIZANDO A OPÇÃO PARA GOTO===========================================================
            fprintf(f, "#include <stdlib.h>\n");
            fprintf(f, "#include <stdio.h>\n");
            fprintf(f, "#include <conio.h>\n");
            fprintf(f, "\n\n");

            fprintf(f,"char string[30];\n"); // vetor de char utilizado como variavel global.
            fprintf(f,"int p = 0;\n"); // Váriavel auxiliar para controle dos if's
            fprintf(f,"int main()\n{");
            fprintf(f,"\n");

            fprintf(f,"   printf(\"Digite a sentença: \");\n");
            fprintf(f,"   gets(string);\n");
            fprintf(f,"   goto E%d;\n", estado_inicial);
            fprintf(f,"}");
            fprintf(f,"\n");

            aux = 0;

             for(i=0; i<qtd_estados; i++){
				fprintf(f,"	E%d:\n", i);

				for(j=0; j<qtd_simbolos; j++){
					if(m[i][j] >= 0){
						if(aux == 0)
						{
                            fprintf(f,"    if(string[p] == '%c')\n    {\n", simbolos[j]);
                            fprintf(f,"		p++;\n");
                            fprintf(f,"		GOTO E%d;\n", m[i][j]);
                            fprintf(f,"    }\n");
						}
						else
						{
							fprintf(f,"		else if(string[p] == '%c')\n    {\n", simbolos[j]);
							fprintf(f,"		p++;\n");
							fprintf(f,"		GOTO E%d;\n", m[i][j]);
							fprintf(f,"    }\n");
						}
						aux += 1;
					}
				}
				aux = 0;


                if(qtd_estados_finais == 1) // CONDIÇÃO PARA APENAS 1 ESTADO FINAL
                {
                    if(estados_finais == i)
                    {
						fprintf(f, "	else if( string[p] == 0 )\n");
						fprintf(f, "		GOTO ACEITA;\n");
						fprintf(f, "	\n");
						fprintf(f, "\n");
                    }
				}
				else if (qtd_estados_finais > 1 )
				{
					for(x=0; x<qtd_estados_finais; x++){
						if(eFinais[x] == i)
						{
							fprintf(f, "	else if( string[p] == 0 )\n{\n");
							fprintf(f, "		GOTO ACEITA;\n");
							fprintf(f, "}\n");
							fprintf(f, "\n");
						}
					}
				}

				fprintf(f, "    else\n    ");
				fprintf(f, "    GOTO REJEITA;\n");
				fprintf(f, "\n");
				fprintf(f, "    \n");
				//fprintf(f, "}\n");
            }

            fprintf(f, "void ACEITA()\n    {\n");
            fprintf(f, "	    printf(\"=====================SENTENÇA ACEITA=======================\");\n");
            fprintf(f, "        getch();\n");
            fprintf(f, "        exit(0);\n");
            fprintf(f, "    }");
            fprintf(f, "    \n\n");

            fprintf(f, "void REJEITA()\n    {\n");
            fprintf(f, "	    printf(\"=====================SENTENÇA REJEITADA=====================\");\n");
            fprintf(f, "        getch();\n");
            fprintf(f, "        exit(0);\n");
            fprintf(f, "    }");
            fprintf(f, "    \n\n");
            break;



        default:
            printf("Opção inválida!\n");
            break;

    }


    return 0;
}
