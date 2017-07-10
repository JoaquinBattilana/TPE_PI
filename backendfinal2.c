#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct censoCDT * censoADT;

censoADT newCenso(int , char **, int, char **);
void printProvincias(censoADT);
void printViviendas(censoADT);

typedef struct{
	char * nombre;
	int habitantes;
	int analfabetos;
} vivienda;

typedef struct{
	char * provincia;
	int habitantes;
	int analfabetos;
	int sumaEdades;
	struct node * dptos;
} tLista;

typedef struct censoCDT{
	tLista * listaProv;
	vivienda * viviendas;
	int cntprov;
	int cntviv;
}censoCDT;


typedef struct{
	char * dpto;
	int habitantes;
	int analfabetos;
	struct node * nodo;
} node;

censoADT newCenso(int cntviv, char ** viviendas, int cntprov, char ** provincias){
	censoADT aux = calloc(1, sizeof(censoCDT));
	aux->cntprov=cntprov;
	aux->cntviv=cntviv;
	aux->listaProv=calloc(cntprov, sizeof(tLista));
	for(int i=0; i<cntprov; i++){
		aux->listaProv[i].provincia=malloc(strlen(provincias[i]));
		strcpy(aux->listaProv[i].provincia,provincias[i]);
		aux->listaProv[i].dptos=NULL;
	}
	aux->viviendas=calloc(cntviv, sizeof(vivienda));
	for(int i=0; i<cntviv; i++){
		aux->viviendas[i].nombre=malloc(strlen(viviendas[i]));
		strcpy(aux->viviendas[i].nombre,viviendas[i]);
	}
	return aux;
}

void printProvincias(censoADT censo){
	int i;
	for(i=0; i<censo->cntprov;i++){
		printf("%s\n", censo->listaProv[i].provincia);
	}
}

void printViviendas(censoADT censo){
	int i;
	for(i=0; i<censo->cntviv;i++){
		printf("%s\n", censo->viviendas[i].nombre);
	}
}