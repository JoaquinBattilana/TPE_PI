
#ifndef BACKEND_H
#define BACKEND_H


typedef struct censoCDT * censoADT;

void departamentoCsv(censoADT);
void provinciaCsv(censoADT);
void analfabetismoCsv(censoADT);
void add(censoADT,int,int,int, int, char*);
void imprimirProvincia(censoADT, int);
censoADT newCenso();

#endif
