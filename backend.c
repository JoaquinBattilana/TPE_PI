#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "backend.h"

#define MAX_LEGHT 24
#define MAX_HOGAR 9

typedef enum{CABA=0,Buenos Aires,Catamarca,Cordoba,Corrientes,Chaco,Chubut,Entre Rios,Formosa,Jujuy,La Pampa,La Rioja,Mendoza,Misiones,Neuquen,Rio Negro,Salta,San Juan,San Luis,Santa Cruz,Santa Fe,Santiago del Estero,Tucuman,Tierra del Fuego}
Tprovincia;

typedef TnodeCDT* Tlist;

struct CensoCDT
{
  Tlist prov[MAX_LEGHT];
  int habxprov[MAX_LEGHT];
  int alfaxprov[MAX_LEGHT];
  int habxhogar[MAX_HOGAR];
  int alfaxhogar[MAX_HOGAR];
  char* hogar={"Casa","Rancho","Casilla","Departamento","Pieza en inquilinato","Pieza en hotel familiar o pension","Local no construido para habitacion","Vivienda movil","Persona/s viviendo en la  calle"};
  Tprovincia provincia;
};

struct DatosCDT
{
  int edad;
  int alfa;
  int vivienda;
  char* partido;
}

struct TnodeCDT
{
  struct DatosCDT datos;
  struct TnodeCDT* last;
  struct TnodeCDT* next;
};

CensoADT New(void)
{
  CensoADT censo=malloc(sizeof(*censo));
  return censo;
}

static int VerifAlfa(Tlist l,char* partido)
{
  int c;
  if(c=strcmp(l->datos.partido,partido)<0)
    return 0;
  if(c==0)
    {
      return l->datos.alfa + VerifAlfa(l->next,partido);
    }
  return VerifAlfa(l->next,partido);
}

static void ToBegin(Tlist l)
{
  l->last=l;
}

static void ChangeLast(Tlist l)
{
  int c;
  if(l==NULL)
    {
      l->last=l;
      return;
    }
  if(strcmp(l->datos.partido,l->next->datos.partido)!=0)
    {
      l->last=l->next;
      return;
    }
  ChangeLast(l->next);
}


Tlist Add(list l,int edad,int alfa,int vivienda,char* partido,int* habxprov,int* alfaxprov,int* habxhogar,int* alfaxhogar)
{
  int c;
  if(l==NULL || c=strcmp(l->datos.partido,partido)<0)
    {
      Tlist aux=calloc(1,sizeof(*aux));
      aux->datos=calloc(1,sizeof(*(aux->datos)));
      aux->datos.edad=edad;
      aux->datos.alfa=alfa;
      aux->datos.vivienda;vivienda;
      aux->datos.partido=calloc(strlen(partido)+1);
      strcpy(aux->datos.partido,partido);
      aux->next=l;
      (*habxprov)++;
      (*habxhogar)++;
      if(alfa==1)
        {
          (*alfaxprov)++;
          (*alfaxhogar)++;
        }
      return aux;
    }
  l->next=Add(l->next,edad,alfa,vivienda,partido,prov);
  return l;
}

static int HabPartido(Tlist l,char* partido) //para la departamento
{
  if(l==NULL || (c=strcmp(l->datos.partido,partido)<0))
    return 0;
  if(c>0)
    return HabPartido(l->next,partido);
  return HabPartido(l->next,partido) +1;
}

static double IndiceDeAnal(int anlafabetas,int personasT)
{
  return analfabetas / personasT;
}

void Analfabetismo(CensoADT censo)
{
  FILE* fp;
  int i;
  fp=fopen("Analfabetismo.csv","r");
  for(i=0;i<MAX_HOGAR;i++)
    {
      fprintf(fp,"%d,%s,%d,%4.2f\n",i+1,censo->hogar[i],censo->habxhogar[i],IndiceDeAnal(censo->habxhogar[i]-censo->alfaxhogar,censo->habxhogar[i]));
    }
  fclose(fp);
}

void Departamento(CensoADT censo)
{
  FILE* fp;
  int i,c;
  fp=fopen("Departamentos.csv","r");
  for(i=0;i<MAX_LEGHT;i++)
    {
      ToBegin(censo->prov[i]);
      while(censo->prov[i]->last==NULL)
        {
            censo->provincia=i;
            fprintf(fp,"%s,%s,%d,%4.2f\n",censo->provincia,censo->prov->last.partido,c=HabPartido(censo->prov[i]->last,censo->prov[i]->last->datos.partido,IndiceDeAnal(c - VerifAlfa(censo->prov[i]->last,censo->prov[i]->last->datos.partido),c)));
        }
      ChangeLast(censo->prov[i]->last);
    }
  fclose(fp);
}

static int Edad(Tlist l)
{
  if(l==NULL)
    return 0;
  return l->datos.edad + Edad(l->next);
}

void Provincia(CensoADT censo)
{
  FILE* fp;
  int i,c;
  fp=fopen("Provincia.csv","r");
  for(i=0;i<MAX_LEGHT;i++)
    {
      censo->provincia=i;
      fprintf(fp,"%s,%d,%4.2f,%4.2f\n",censo->provincia,censo->habxprov[i],Edad(censo->prov[i])/censo->habxprov[i],IndiceDeAnal(censo->habxprov[i]-censo->alfaxprov[i],censo_>habxprov[i]));
    }
  fclose(fp);
}
