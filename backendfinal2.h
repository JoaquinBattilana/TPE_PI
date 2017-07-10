#ifndef BACKEND_H
#define BACKEND_H

typedef struct censoCDT * censoADT;

censoADT NewCenso(void);
void add(censoADT censo,int edad,int alfa,int vivienda, int provincia, char* dpto);
void analfabetismoCsv(censoADT censo);
void provinciaCsv(censoADT censo);
void departamentoCsv(censoADT censo);

#endif
