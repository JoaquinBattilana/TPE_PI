#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEGHT 23

typedef TnodeCDT* Tlist;

struct CensoCDT
{
  Tlist prov[MAX_LEGHT];
  int hab[MAX_LEGHT];
  int alfaxprov[MAX_LEGHT];
};

struct DatosCDT
{
  int edad;
  int alfa;
  int vivienda;
  char* partido;
  int prov;
}

struct TnodeCDT
{
  struct DatosCDT* datos;
  struct TnodeCDT* next;
};


Tlist Add(Tlist l,int edad,int alfa,int vivienda,char* partido,int prov,int* hab,int* alfaxprov)
{
  int c;
  if(l==NULL || c=strcmp(l->partido,partido)>0)
    {
      Tlist aux=calloc(1,sizeof(*aux));
      aux->datos=calloc(1,sizeof(*(aux->datos)));
      aux->datos.edad=edad;
      aux->datos.alfa=alfa;
      aux->datos.vivienda;vivienda;
      aux->datos.partido=calloc(strlen(partido)+1);
      strcpy(aux->datos.partido,partido);
      aux->datos.prov=prov;
      aux->next=l;
      (*hab)++;
      if(alfa==1)
        (*alfaxprov)++;
      return aux;
    }
  if(c==0)
    return l;
  l->next=Add(l->next,edad,alfa,vivienda,partido,prov);
  return l;
}
