#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getKey(char *cadena);
int index(char *cadena, int sizeTable);

int getKey(char *cadena){
	int coeficientes[20], i, num = 20, clave;
	for(i = 19; i >= 0; i--){
		coeficientes[i] = num;
		num--;
	}
	clave = 0;
	for(i = 0; i < strlen(cadena); i++){
		cadena[i] = tolower(cadena[i]);
		if(cadena[i] != ':') clave += (cadena[i] * coeficientes[i]);
	}
	return clave - 97;
}

int index(char *cadena, int sizeTable){
	return getKey(cadena) % sizeTable;
}