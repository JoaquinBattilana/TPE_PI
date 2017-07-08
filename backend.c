#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "backend.h"

#define CNTPROV 24
#define MAX_VIVIENDA 9

/*
typedef enum{CABA=1,BUENOSAIRES,CATAMARCA,CORDOBA,CORRIENTES,CHACO,CHUBUT,ENTRERIOS,FORMOSA,JUJUY,LAPAMPA,LARIOJA,MENDOZA,MISIONES,NEUQUEN
    ,RIONEGRO,SALTA,SANJUAN,SANLUIS,SANTACRUZ,SANTAFE,SANTIAGODELESTERO,TUCUMAN,TIERRADELFUEGO};
typedef enum{CASA=1,RANCHO,CASILLA,DEPARTAMENTO,PIEZAENINQUILINATO,PENSION,LOCAL,VIVIENDAMOVIL,CALLE};
*/

char * provincias[]={"Ciudad autonoma de Buenos Aires", "Buenos Aires", "Catamarca", "Cordoba", "Corrientes", "Chaco", "Chubut", "Entre Rios", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza",
"Misiones", "Neuquen", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe", "Santiago del Estero", "Tucuman", "Tierra del Fuego"};
char * viviendas[]={"Casa", "Rancho", "Casilla", "Departamento", "Pieza en Inquilinato", "Pieza en hotel familiar o pension", "Local no construido para habitacion", "Vivienda movil", 
"Persona/s viviendo en la calle"};

typedef struct node * tList;

static tList addR(tList,int,int,int, char*);
static void imprimirProvinciaR(tLista);
static double indiceDeAnalfabetismo(int, int );
static int sumaEdades(tList);
static double edadesProm(tList, int);
static int sumaEdades(tList);

struct censoCDT
{
    tList listaProv[CNTPROV];
    int habxprov[CNTPROV];
    int alfaxprov[CNTPROV];
    int habxviv[MAX_VIVIENDA];
    int alfaxviv[MAX_VIVIENDA];
};

typedef struct {
    int edad;
    int alfa;
    int vivienda;
    char *dpto;
}tDato;

typedef struct node
{
    tDato datos;
    struct node * next;
}tNode;

typedef struct censoCDT * censoADT;

censoADT newCenso(void)
{
    censoADT censo=calloc(1,sizeof(*censo));
    for(int i=0; i<CNTPROV; i++)
        censo->listaProv[i]=NULL;
    return censo;
}

void add(censoADT censo,int edad,int alfa,int vivienda, int provincia, char* dpto){
    provincia--;
    vivienda--;
    censo->listaProv[provincia] = addR(censo->listaProv[provincia],edad,alfa,vivienda,dpto);
    if(alfa==1) {
        censo->alfaxprov[provincia]++;
        censo->alfaxviv[vivienda]++;
    }
    censo->habxprov[provincia]++;
    censo->habxviv[vivienda]++;
    return;
}

static tList addR(tList l,int edad,int alfa,int vivienda, char* dpto)
{
    if(l==NULL || strcmp(l->datos.dpto,dpto)>0)
    {
        tList aux=calloc(1,sizeof(*aux));
        aux->datos.edad=edad;
        aux->datos.alfa=alfa;
        aux->datos.vivienda=vivienda;
        aux->datos.dpto=malloc(strlen(dpto)+1);
        strcpy(aux->datos.dpto,dpto);
        aux->next=l;
        return aux;
    }
    l->next=addR(l->next,edad,alfa,vivienda,dpto);
    return l;
}

void imprimirProvincia(censoADT censo,int provincia){
    imprimirProvinciaR(censo->listaProv[provincia]);
}

static void imprimirProvinciaR(tList l){
    if(l==NULL)
        return; 
    printf("edad: %d, dpto: %s, alfabetismo: %d, vivienda: %d \n",
        l->datos.edad, l->datos.dpto, l->datos.alfa, l->datos.vivienda);
    imprimirProvinciaR(l->next);
    return;
}

void analfabetismoCsv(censoADT censo)
{
    FILE* fp;
    int i;
    fp=fopen("./Analfabetismo.csv","w");
    for(i=0;i<MAX_VIVIENDA;i++)
        fprintf(fp,"%d,%s,%d,%4.2f\n",i+1,viviendas[i],censo->habxviv[i],indiceDeAnalfabetismo(censo->alfaxviv[i], censo->habxviv[i]));
    fclose(fp);
}

static double indiceDeAnalfabetismo(int analfabetos, int personas )
{   if (analfabetos==0)
        return 0;
    return ((double)analfabetos)/personas;
}

void provinciaCsv(censoADT censo)
{
    FILE* fp;
    int i;
    fp=fopen("Provincia.csv","w");
    for(i=0;i<CNTPROV;i++)
        fprintf(fp,"%s,%d,%4.2f,%4.2f\n",provincias[i],censo->habxprov[i],edadesProm(censo->listaProv[i],censo->habxprov[i]),indiceDeAnalfabetismo(censo->alfaxprov[i], censo->habxprov[i]));
    fclose(fp);
}

static double edadesProm(tList l, int habitantes){
    if (habitantes == 0)
        return 0;
    int suma=sumaEdades(l);
    return (double)suma/habitantes;
}

static int sumaEdades(tList l)
{
    if(l==NULL)
        return 0;
    return l->datos.edad + sumaEdades(l->next);
}

void departamentoCsv(censoADT censo)
{
    FILE* fp;
    int i,c;
    fp=fopen("Departamentos.csv","w");
    for(i=0;i<CNTPROV;i++)
    {
    	if(censo->listaProv[i]!=NULL){
    		tList aux=censo->listaProv[i];
    		int sumaAlfa=0;
    		int habitantes=0;
    		while(aux->next!=NULL){
    			sumaAlfa+=aux->datos.alfa;
    			habitantes++;
    			if(strcmp(aux->datos.dpto,aux->next->datos.dpto)!=0){
 	   				fprintf(fp,"%s,%s,%d,%4.2f\n",provincias[i], aux->datos.dpto, habitantes, indiceDeAnalfabetismo(sumaAlfa, habitantes));
 	   				habitantes=0;
 	   				sumaAlfa=0;
    			}
 	   			aux=aux->next;
 	   		}
 	   		sumaAlfa+=aux->datos.alfa;
    		habitantes++;
    		fprintf(fp,"%s,%s,%d,%4.2f\n",provincias[i], aux->datos.dpto, habitantes, indiceDeAnalfabetismo(sumaAlfa, habitantes));

    	}
    }
    fclose(fp);	
}

