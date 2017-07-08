#include <stdio.h>
#include <ctype.h>
#include "backend.c"
#include <stdlib.h>

enum estado {NUMERO=0, PALABRA};
enum rta {ERROR=0, FINALIZO, LINEA};
#define MAXLINEA 80
#define CNTDATOSNUM 4
#define BLOQUE 10

int getLine(char **, int []);

int main(void){
    int i=0;
	int c;
	int finalizo=0;
	char * s;
	int v[CNTDATOSNUM];
	censoADT censo;
	censo = newCenso();
	while((c=getLine(&s, v))!=ERROR && c!=FINALIZO){
		add(censo, v[0], v[1], v[2], v[3], s);
        printf("%d \n", i++);
	}
	if(c==ERROR)
		printf("ERROR EN EL FORMATO \n");
	else{
		analfabetismoCsv(censo);
		provinciaCsv(censo);
		departamentoCsv(censo);
	}
	return 0;
}

int getLine(char ** s, int v[CNTDATOSNUM]){
    *s=NULL;
    int estado=NUMERO;
    int i=0,rta=LINEA;
    char c;
    int numero=0;
    int cantidad=0;
    int total=0;
    do{
        c=getchar();
        total++;
        if(c==EOF)
            rta=FINALIZO;
        else{
        switch(estado){
            case NUMERO:
                if(isdigit(c)) {
                    numero = numero * 10 + (c - '0');
                    cantidad++;
                }
                else if((c==',' || c=='\n' || c==EOF) && cantidad>0 && i<CNTDATOSNUM){
                    cantidad=0;
                    v[i++]=numero;
                    numero=0;
                    if(i==(CNTDATOSNUM-1))
                        estado=PALABRA;
                }
                else
                    rta=ERROR;
                break;
            case PALABRA:
                if(c==',' && cantidad>0){
                    (*s)[cantidad]='\0';
                    cantidad=0;
                    estado=NUMERO;
                }
                else if(c!='\n' && c!=EOF){
                    if(cantidad%BLOQUE==0)
                        *s=realloc(*s, cantidad+BLOQUE);
                    (*s)[cantidad]=c;
                    cantidad++;
                }
                else
                    rta=ERROR;
                break;
        }
    }
    }while(c!=EOF && c!='\n' && rta!=ERROR && cantidad <= MAXLINEA);
    if ( cantidad > MAXLINEA)
        rta=ERROR;
    else if(c==EOF)
        rta=FINALIZO;
    return rta;
}
