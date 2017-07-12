#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct censoCDT * censoADT;

censoADT newCenso(int , char **, int, char **);
void printProvincias(censoADT);
void printViviendas(censoADT);
static struct node * addR(struct node *, int, char *);
static void printProvinciaR(struct node *);
static double edadPromedio(int, int);

typedef struct datos{
	char * nombre;
	int habitantes;
	int analfabetos;
	long int sumaEdades;
} datos;

typedef struct tLista{
	datos datosProv;
	struct node * dptos;
}tLista;

typedef struct censoCDT{
	tLista * listaProv;
	datos * viviendas;
	int cntprov;
	int cntviv;
}censoCDT;


typedef struct node{
	datos datosDpto;
	struct node * next;
}node;

censoADT newCenso(int cntviv, char ** viviendas, int cntprov, char ** provincias){
	censoADT aux = calloc(1, sizeof(censoCDT));
	aux->cntprov=cntprov;
	aux->cntviv=cntviv;
	aux->listaProv=calloc(cntprov, sizeof(tLista));
	for(int i=0; i<cntprov; i++){
		aux->listaProv[i].datosProv.nombre=malloc(strlen(provincias[i]));
		strcpy(aux->listaProv[i].datosProv.nombre,provincias[i]);
		aux->listaProv[i].dptos=NULL;
	}
	aux->viviendas=calloc(cntviv, sizeof(datos));
	for(int i=0; i<cntviv; i++){
		aux->viviendas[i].nombre=malloc(strlen(viviendas[i]));
		strcpy(aux->viviendas[i].nombre,viviendas[i]);
	}
	return aux;
}

void printProvincias(censoADT censo){
	int i;
	for(i=0; i<censo->cntprov;i++){
		printf("%s\n", censo->listaProv[i].datosProv.nombre);
	}
}

void printViviendas(censoADT censo){
	int i;
	for(i=0; i<censo->cntviv;i++){
		printf("%s\n", censo->viviendas[i].nombre);
	}
}

void add(censoADT censo, int edad, int alfa, int vivienda, char * dpto, int provincia){
	provincia--;
	vivienda--;
	censo->viviendas[vivienda].habitantes++;
	censo->listaProv[provincia].datosProv.habitantes++;
	censo->listaProv[provincia].datosProv.sumaEdades+=edad;
	if(alfa==1){
		censo->listaProv[provincia].datosProv.analfabetos++;
		censo->viviendas[vivienda].analfabetos++;
	}
	censo->listaProv[provincia].dptos=addR(censo->listaProv[provincia].dptos, alfa, dpto);
	return;
}

static node * addR(struct node * nodo, int alfa, char * dpto){
	if(nodo==NULL || strcmp(nodo->datosDpto.nombre,dpto)>0)
	    {
	        node * aux=calloc(1,sizeof(*aux));
	        aux->datosDpto.habitantes=1;
	        if(alfa==1)
				aux->datosDpto.analfabetos=1;
	        aux->datosDpto.nombre=malloc(strlen(dpto)+1);
	        strcpy(aux->datosDpto.nombre,dpto);
	        aux->next=nodo;
	        return aux;
	    }
	else if(strcmp(nodo->datosDpto.nombre,dpto)==0){
		if(alfa==1)
			nodo->datosDpto.analfabetos++;
		nodo->datosDpto.habitantes++;
		return nodo;
	}
	nodo->next=addR(nodo->next,alfa,dpto);
	return nodo;
}


void printProvincia(censoADT censo, int provincia){
	provincia--;
	printf("Habitantes de la provincia y analfabetos:\n%d\n%d\n", censo->listaProv[provincia].datosProv.habitantes, censo->listaProv[provincia].datosProv.analfabetos);
	printProvinciaR(censo->listaProv[provincia].dptos);
}

static void printProvinciaR(struct node * nodo){
	if (nodo==NULL)
		return;
	printf("Habitantes del dpto: %s y analfabetos:\n%d\n%d\n", nodo->datosDpto.nombre, nodo->datosDpto.habitantes, nodo->datosDpto.analfabetos);
	printProvinciaR(nodo->next);
}


static double indiceDeAnalfabetismo(int analfabetos, int personas)
{   if (analfabetos==0)
	return 0;
	return ((double)analfabetos)/personas;
}

void analfabetismoCsv(censoADT censo)
{
    FILE* fp;
    int i;
    fp=fopen("./Analfabetismo.csv","w");
    for(i=0;i<censo->cntviv;i++){
        fprintf(fp,"%d,%s,%d,%4.2f\n",i+1,censo->viviendas[i].nombre,censo->viviendas[i].habitantes,indiceDeAnalfabetismo(censo->viviendas[i].analfabetos, censo->viviendas[i].habitantes));
    }
    fclose(fp);
}

void provinciaCsv(censoADT censo)
{
    FILE* fp;
    int i;
    fp=fopen("Provincia.csv","w");
    for(i=0;i<censo->cntprov;i++){
        fprintf(fp,"%s,%d,%4.2f,%4.2f\n",censo->listaProv[i].datosProv.nombre,censo->listaProv[i].datosProv.habitantes,edadPromedio(censo->listaProv[i].datosProv.sumaEdades, censo->listaProv[i].datosProv.habitantes)
        	,indiceDeAnalfabetismo(censo->listaProv[i].datosProv.analfabetos, censo->listaProv[i].datosProv.habitantes));
    }
    fclose(fp);
}

static double edadPromedio(int sumaEdades, int habitantes){
	if (sumaEdades==0)
		return 0;
	return ((double)sumaEdades)/habitantes;
}


void departamentoCsv(censoADT censo)
{
    FILE* fp;
    int i;
    fp=fopen("Departamentos.csv","w");
    for(i=0;i<censo->cntprov;i++)
    {
    	struct node * aux=censo->listaProv[i].dptos;
    	while(aux!=NULL)
				{
					fprintf(fp,"%s,%s,%d,%4.2f\n",censo->listaProv[i].datosProv.nombre,aux->datosDpto.nombre,aux->datosDpto.habitantes,
						indiceDeAnalfabetismo(aux->datosDpto.analfabetos,aux->datosDpto.habitantes));
					aux=aux->next;
				}
    }
    fclose(fp);
}
