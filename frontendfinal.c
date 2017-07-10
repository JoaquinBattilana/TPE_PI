#include "backendfinal.c"

int main(void){
	char * provincias[]={"Ciudad autonoma de Buenos Aires", "Buenos Aires", "Catamarca", "Cordoba", "Corrientes", "Chaco", "Chubut", "Entre Rios", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza",
	"Misiones", "Neuquen", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe", "Santiago del Estero", "Tucuman", "Tierra del Fuego"};
	char * viviendas[]={"Casa", "Rancho", "Casilla", "Departamento", "Pieza en Inquilinato", "Pieza en hotel familiar o pension", "Local no construido para habitacion", "Vivienda movil", 
	"Persona/s viviendo en la calle"};
	censoADT censo;
	censo=newCenso(9, viviendas, 24, provincias);
	printProvincias(censo);
	printViviendas(censo);
	return 0;
}