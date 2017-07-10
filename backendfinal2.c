#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "backendfinal.h"

#define MAX_PROV 24
#define MAX_VIVI 9

typedef struct censoCDT * censoADT;

typedef struct
{
	int habitantes;
	int alfa;
} vivienda;

typedef struct nodeCDT
{
	int habitantes;
	char* dpto;
	int alfa;
	struct nodeCDT * next;
} tLista;

typedef struct censoCDT
{
	char hogar[]={"Casa","Rancho","Casilla","Departamento","Pieza en inquilinato","Pieza en hotel familiar o pension","Local no construido para habitacion","Vivienda movil","Persona/s viviendo en la  calle"};
	char provincias[]={"Ciudad autonoma de Buenos Aires", "Buenos Aires", "Catamarca", "Cordoba", "Corrientes", "Chaco", "Chubut", "Entre Rios", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza",
	"Misiones", "Neuquen", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe", "Santiago del Estero", "Tucuman", "Tierra del Fuego"};
	tLista prov[MAX_PROV];
	vivienda viviendas[MAX_VIVI];
	long int edadxprov[MAX_PROV];
	int habxprov[MAX_PROV];
	int alfaxprov[MAX_PROV];
}censoCDT;

censoADT NewCenso(void)
{
	censoADT censo;
	censo=calloc(1,sizeof(*censo));
	int i;
	for(i=0;i<MAX_PROV;i++)
		{
			censo->prov[i]=NULL;
			censo->edadxprov[i]=0;
			censo->alfaxprov[i]=0;
		}
	return censo;
}

static tList addR(tList l,int alfa,char* dpto)
{
	int c;
	if(l==NULL || c=(strcmp(l->dpto,dpto))>0)
	{
		tList aux=calloc(1,sizeof(*aux));
		if(alfa==0)
		aux->alfa=1;
		else
		aux->alfa=0;
		aux->habitantes++;
		aux->dpto=malloc(strlen(dpto)+1);
		strcpy(aux->dpto,dpto);
		aux->next=l;
		return aux;
	}
	if(c==0)
	{
		l->habitantes++;
		if(alfa==0)
		aux->alfa++;
	}
	l->next=addR(l->next,alfa,dpto);
	return l;
}

void add(censoADT censo,int edad,int alfa,int vivienda, int provincia, char* dpto)
{
    provincia--;
    vivienda--;
    censo->prov[provincia] = addR(censo->prov[provincia],alfa,dpto);
    if(alfa==0) {
        censo->alfaxprov[provincia]++;
				censo->viviendas[vivienda].alfa++;
    }
    censo->habxprov[provincia]++;
		censo->edadxprov[provincia]+=edad;
		(censo->viviendas[vivienda].habitantes)++;
    return;
}


static double indiceDeAnalfabetismo(int analfabetos, int personas )
{   if (analfabetos==0)
	return 0;
	return ((double)analfabetos)/personas;
}

void analfabetismoCsv(censoADT censo)
{
    FILE* fp;
    int i;
    fp=fopen("./Analfabetismo.csv","w");
    for(i=0;i<MAX_VIVI;i++)
        fprintf(fp,"%d,%s,%d,%4.2f\n",i+1,censo->hogar[i],censo->viviendas[i].habitantes,indiceDeAnalfabetismo(censo->viviendas[i].alfa, censo->viviendas[i].habitantes));
    fclose(fp);
}


void provinciaCsv(censoADT censo)
{
    FILE* fp;
    int i;
    fp=fopen("Provincia.csv","w");
    for(i=0;i<MAX_PROV;i++)
        fprintf(fp,"%s,%d,%4.2f,%4.2f\n",censo->provincias[i],censo->habxprov[i],censo->edadxprov[i]/censo->habxprov[i],indiceDeAnalfabetismo(censo->alfaxprov[i], censo->habxprov[i]));
    fclose(fp);
}


void departamentoCsv(censoADT censo)
{
    FILE* fp;
    int i;
    fp=fopen("Departamentos.csv","w");
    for(i=0;i<MAX_PROV;i++)
    {
    	while(censo->prov[i]!=NULL)
				{
					fprintf(fp,"%s,%s,%d,%4.2f\n",censo->provincias[i],censo->prov[i].dpto,censo->prov[i].habitantes,indiceDeAnalfabetismo(censo->prov[i].alfa,censo.prov[i].habitantes));
					censo->prov[i]=censo->prov[i].next;
				}
    }
    fclose(fp);
}
