#include <stdio.h>
#include <string.h>
#include <stdlib.h>
https://github.com/fermartin17/TPE.git
#define MAX_LEGHT 23

typedef TnodeCDT* Tlist;

struct CensoCDT
{
  Tlist prov[MAX_LEGHT];
  int hab[MAX_LEGHT];
  int alfaxprov[MAX_LEGHT];
};

struct TnodeCDT
{
  int edad;
  int alfa;
  int vivienda;
  char* partido;
  int prov;
  struct TnodeCDT* next;
};


Tlist Add(Tlist l,int edad,int alfa,int vivienda,char* partido,int prov)
{
  int c;
  if(l==NULL || c=strcmp(l->partido,partido)>0)
    {
      Tlist aux=calloc(1,sizeof(*aux));
      aux->edad=edad;
      aux->alfa=alfa;
      aux->vivienda;vivienda;
      aux->partido=calloc(strlen(partido)+1);
      strcpy(aux->partido,partido);
      aux->prov=prov;
      aux->next=l;
      return aux;
    }
  if(c==0)
    return l;
  l->next=Add(l->next,edad,alfa,vivienda,partido,prov);
  return l;
}
