#include <stdio.h>
#include <ctype.h>
#include "backend.c"
#include <stdlib.h>

enum estado {NUMERO=0, PALABRA};
enum rta {ERROR, FINALIZO, LINEA};
#define MAXLINEA 80
#define CNTDATOSNUM 4
#define BLOQUE 10

int getLine(char **, int []);

int main(void){
	censoADT censo;
	censo = newCenso();
	add(censo, 22, 1, 2, 23, "villa carlos gardel");
	add(censo, 22, 1, 2, 23, "avilla carlos gardel");
	add(censo, 22, 1, 2, 23, "bvilla carlos gardel");
	add(censo, 22, 1, 2, 23, "bvilla carlos gardel");
	add(censo, 99, 0, 4, 21, "bvilla carlos gardel");
	add(censo, 99, 0, 9, 18, "bvilla carlos gardel");
	add(censo, 99, 1, 8, 17, "bvilla carlos gardel");
	add(censo, 99, 0, 8, 9, "bvilla carlos gardel");

	analfabetismoCsv(censo);
	provinciaCsv(censo);
    departamentoCsv(censo);
	imprimirProvincia(censo, 22);
	return 0;
}

int getLine(char ** s, int v[MAXLINEA]){
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
                if(isalpha(c) || isdigit(c)){
                    if(cantidad%BLOQUE==0)
                        *s=realloc(*s, cantidad+BLOQUE);
                    (*s)[cantidad]=c;
                    cantidad++;
                }
                else if(c==',' && cantidad>0){
                    (*s)[cantidad]='\0';
                    cantidad=0;
                    estado=NUMERO;
                }
                else
                    rta=1;
                break;
        }
    }while(c!=EOF && c!='\n' && rta!=ERROR && cantidad <= MAXLINEA);
    if ( cantidad > MAXLINEA)
        rta=ERROR;
    else if(c==EOF)
        rta=FINALIZO;
    return rta;
}
