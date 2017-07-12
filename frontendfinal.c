#include <stdio.h>
#include "backendfinal.c"
#define CNTDATOSNUM 4
#define CNTPROV 24
#define CNTVIV 9
#define MAXLINEA 80

enum {NUMERO,PALABRA};

int main(void){
	char * provincias[]={"Ciudad autonoma de Buenos Aires", "Buenos Aires", "Catamarca", "Cordoba", "Corrientes", "Chaco", "Chubut", "Entre Rios", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza",
	"Misiones", "Neuquen", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe", "Santiago del Estero", "Tucuman", "Tierra del Fuego"};
	char * viviendas[]={"Casa", "Rancho", "Casilla", "Departamento", "Pieza en Inquilinato", "Pieza en hotel familiar o pension", "Local no construido para habitacion", "Vivienda movil", 
	"Persona/s viviendo en la calle"};
	censoADT censo;
	censo=newCenso(CNTVIV, viviendas, CNTPROV, provincias);
	int estado=NUMERO,k=0;
	int estadito=0;
	int i=0, numero=0;
	char c;
	int v[CNTDATOSNUM];
	char s[MAXLINEA];
	do{
		c=getchar();
		numero=c-'0';
		if(c!='\n' && c!=EOF){
			do{
				c=getchar();
				switch(estado){
				case NUMERO:
					if(c!=',' && c!='\n'){
						numero=numero*10+(c-'0');
					}
					else{
						v[i++]=numero;
						numero=0;
						if(i==3)
							estado=PALABRA;
					}
					break;
				case PALABRA:
					if(c!=',')
						s[k++]=c;
					else{
						estado=NUMERO;
						s[k]='\0';
						k=0;
					}
					break;
				}
			}while(c!='\n');
			add(censo,v[0],v[1],v[2],s,v[3]);
			i=0;
		}
	}while(c!=EOF);
	analfabetismoCsv(censo);
	provinciaCsv(censo);
	departamentoCsv(censo);
	return 0;
}

