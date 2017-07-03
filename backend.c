#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEGHT 23

typedef TnodeCDT* Tlist;

struct CensoCDT
{
  Tlist prov[MAX_LEGHT];
  int habxprov[MAX_LEGHT];
  int alfaxprov[MAX_LEGHT];
  int habxhogar[8];
  char* hogar={"Casa","Rancho","Casilla","Departamento","Pieza en inquilinato","Pieza en hotel familiar o pension","Local no construido para habitacion","Vivienda movil","Persona/s viviendo en la  calle"};
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
  struct TnodeCDT* next;
};


Tlist Add(Tlist l,int edad,int alfa,int vivienda,char* partido,int prov,int* hab,int* alfaxprov,int* habxhogar)
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
      aux->next=l;
      (*hab)++;
      (*habxhogar)++;
      if(alfa==1)
        (*alfaxprov)++;
      return aux;
    }
  if(c==0)
    return l;
  l->next=Add(l->next,edad,alfa,vivienda,partido,prov);
  return l;
}
