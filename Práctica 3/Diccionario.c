#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib\TADListaSL.h"
#include "lib\presentacion.h"
#include "lib\key.h"

int menu();
void imprimirCentrado(char *cadena, int Y);
void letreros();
void limpiarCadena(char *cadena, int tam);
void quitarEspacios(char *cadena, int tam);
void quitarMayusculas(char *cadena);
void iniciaDiccionario();
void cargarArchivo();
void agregarEntrada(char *palabra, char *definicion);
void consultarEntrada(char accion);
void actualizarEntrada();
void eliminarEntrada();

lista sublista[31];
elemento tabla[31];
elemento e1;
posicion aux = NULL;
int indiceMarcado[31];

int main(){
	int indice;
	char palabra[25], definicion[200];
	iniciaDiccionario(); //Inicializa el diccionario
	while(1){
		cleanScreen();
		switch(menu()){
			case 1:
				imprimirCentrado("Usted selecciono cargar un archivo", 18);
				cargarArchivo();
				break;
			case 2:
				printf("\n\tUsted selecciono agregar una nueva entrada en el diccionario");
				printf("\n\tIntroduzca la palabra: ");
				setbuf(stdin, NULL);
				gets(palabra);
				quitarMayusculas(palabra);
				setbuf(stdin, NULL);
				printf("\n\tIntroduzca la definicion: ");
				gets(definicion);
				agregarEntrada(palabra, definicion);
				break;
			case 3:
				printf("\n\tUsted selecciono buscar una palabra");
				consultarEntrada('c'); //Consulta de una entrada (sin remover o reemplazar definición)
				break;
			case 4:
				printf("\n\tUsted selecciono modificar una definicion");
				actualizarEntrada();
				break;
			case 5:
				printf("\n\tUsted selecciono eliminar una entrada");
				eliminarEntrada();
				break;
			case 6:
				exit(1);
		}
		setbuf(stdin, NULL);
		getchar();
	}
	return 0;
}

int menu(){
	int opcion;
	letreros();
	imprimirCentrado("MENU", 6);
	imprimirCentrado("Seleccione alguna opcion: ", 8);
	imprimirCentrado("1) Agregar un archivo de definiciones", 10);
	imprimirCentrado("2) Agregar una palabra y su definicion", 11);
	imprimirCentrado("3) Buscar palabra y ver su definicion", 12);
	imprimirCentrado("4) Modificar una definicion", 13);
	imprimirCentrado("5) Eliminar una palabra", 14);
	imprimirCentrado("6) Salir", 15);
	printf("\n\tIntroduzca su seleccion: ");
	scanf("%d", &opcion);
	if(opcion >= 1 && opcion <= 6) return opcion;

}

void imprimirCentrado(char *cadena, int Y){
	gotoxy((80 - strlen(cadena))/2, Y);
	puts(cadena);
}

void letreros(){
	imprimirCentrado("Instituto Politecnico Nacional", 1);
	imprimirCentrado("Escuela Superior de Computo", 2);
	imprimirCentrado("Practica 03: Diccionario", 4);
}

void limpiarCadena(char *cadena, int tam){
	int i;
	for(i = 0; i < tam; i++){
		cadena[i] = '\0';
	}
	quitarEspacios(cadena, tam);
	return;
}

void quitarEspacios(char *cadena, int tam){
	int i, j = 0;
	for(i = 0; i < tam; i++){
		if(cadena[i] != ' '){
			cadena[j] = cadena[i];
			j++;
		}
	}
}
/*
char otroProceso(){
	char sn;
	scanf("%c",&sn);
	return sn;
}
*/
void quitarMayusculas(char *cadena){
	int i;
	for(i = 0; i < strlen(cadena); i++){
		cadena[i] = tolower(cadena[i]);
	}
}

void animacion(){
	int i;
	for(i = 0; i < 5; i++){
		printf(".");
		delay_ms(100);
	}
}

void actualizarDefinicion(char *cadena){
	char definicion[200];
	printf("\n\tIntroduzca la nueva definicion: ");
	setbuf(stdin, NULL);
	gets(definicion);
	strcpy(e1.definicion, definicion);
	strcpy(e1.palabra, cadena);
}

void iniciaDiccionario(){
	int i;
	for(i = 0; i < 31; i++){
		indiceMarcado[i] = 0;
		Initialize(&sublista[i]); //Inicializa el array de listas
	}
}
void cargarArchivo(){
	//Variables locales 
	FILE *archivo;
	char nombreFichero[20], c;
	char palabra[25], definicion[200];
	int i = 0, indice;
	//Procedimientos
	archivo = fopen("definiciones.txt","r");
	if(archivo == NULL){
		printf("\n\tERROR: Archivo no valido");
		exit(1);
	}
	imprimirCentrado("Se extrajeron las siguientes palabras con sus definiciones: ", 20);
	do{
		limpiarCadena(palabra, 25);
		limpiarCadena(definicion, 200);
		i = 0;
		while(!feof(archivo)){
			c = fgetc(archivo);
			if(c == ':') break;
			else{
				if(c != 13) palabra[i] = c;
				i++;
			}
		}
		if(c != EOF) printf("%s", palabra);
		i = 0;
		while(!feof(archivo)){
			c = fgetc(archivo);
			if(c == 13 || c == '.') break;
			else{
				definicion[i] = c;
				i++;
			}
		}
		if(c != EOF){
			printf("%s\n", definicion);
			agregarEntrada(palabra, definicion);
		}
	}while(!feof(archivo));
 	fclose(archivo);
}

void agregarEntrada(char *palabra, char *definicion){
	int indice;
	strcpy(e1.palabra, palabra);
	strcpy(e1.definicion, definicion);
	indice = index(palabra, 31);
	printf("\n\t\tEl indice va a ser %d", indice);
	if(indiceMarcado[indice] == 0){
		tabla[indice] = e1;
		indiceMarcado[indice] = 1;
	}
	else{
		printf("\n\tSe dio una colision");
		printf("\n\tResolviendo colision");
		animacion();
		printf("\n\tColision resuelta, se agrego la entrada a la sublista[%d]", indice);
		Add(&sublista[indice], e1);
		indiceMarcado[indice]++;
	} 
	printf("\n\tAgregando entrada");
	animacion();
	printf("\n\tEntrada agregada");
	return;
}

void consultarEntrada(char accion){
	char palabra[25], definicion[200], sn;
	int indice, i;
	boolean reemplazado = FALSE;
	printf("\n\n\tIntroduzca la palabra: ");
	setbuf(stdin, NULL);
	gets(palabra);
	quitarMayusculas(palabra); //Para que no sea sensitivo a mayúsculas
	indice = index(palabra, 31);
	printf("\n\tEl indice hash es: %d", indice);
	if(indiceMarcado[indice] == 1){ //Si se consultó una palabra en una posición que no colisionó
		e1 = tabla[indice]; 
		if(strcmp(e1.palabra, palabra) == 0) printf("\n\tLa definicion es: %s", e1.definicion);
		else printf("\n\tPalabra NO encontrada");
		if(accion == 'a'){ //Si la acción es actualizar la definición
			actualizarDefinicion(palabra);
			tabla[indice] = e1;
			printf("\n\tActualizando definicion");
			animacion();
			printf("\n\tLa definicion se actualizo exitosamente");
			//reemplazado = TRUE;
		}
		else if(accion == 'r'){ //Si la acción es remover la entrada
			printf("\n\tLa entrada se eliminara");
			limpiarCadena(e1.palabra, 25);
			limpiarCadena(e1.definicion, 200);
			tabla[indice] = e1;
			indiceMarcado[indice] = 0;
			animacion();
			printf("\n\tEntrada eliminada exitosamente");
		}
	}
	else if(indiceMarcado[indice] > 1){ //Si se consulta en una posición que colisionó
		e1 = tabla[indice];
		if(strcmp(e1.palabra, palabra) != 0){ //Si la palabra no se encuentra en el indice explora la sublista
			strcpy(e1.palabra, palabra);
			aux = Search(&sublista[indice], e1); //Busca la posición en la que se encuentra la palabra
			if(accion == 'c') e1 = Position(&sublista[indice], aux); //Si sólo se desea consultar la definición
			else if(accion == 'a'){ //Si se desea actualizar la definición
				actualizarDefinicion(palabra);
				Replace(&sublista[indice], aux, e1); //Reemplaza la definición en la lista
				printf("\n\tActualizando definicion");
				animacion();
				printf("\n\tDefinicion actualizada con exito");
				reemplazado = TRUE;
			}
			if(accion == 'r'){ //Si se desea remover una entrada (palabra y definición)
				Remove(&sublista[indice], aux);
				indiceMarcado[indice]--; //Reduce en 1 el numero que habia en indiceMarcado
			}
		}
		else if(accion == 'a' && reemplazado == FALSE){
			printf("\n\tIntroduzca la nueva definicion: ");
			setbuf(stdin, NULL);
			gets(definicion);
			strcpy(e1.palabra, palabra);
			strcpy(e1.definicion, definicion);
			tabla[indice] = e1;
			printf("\n\tActualizando definicion");
			animacion();
			printf("\n\tDefinicion actualizada");
			}
			printf("\n\tLa definicion es: %s", e1.definicion);
			if(accion == 'r'){ //Si la acción es remover pero no dentro de la lista, sino en el arreglo
			printf("\n\tLa entrada se removera");
			limpiarCadena(e1.palabra, 25);
			limpiarCadena(e1.definicion, 200);
			tabla[indice] = e1;
			indiceMarcado[indice]--;
			animacion();
			printf("\n\tEntrada removida exitosamente");
		}
	}
	else{
		printf("\n\tERROR: Palabra no existe en el diccionario, ¿Desea agregarla?(s|n): ");
		scanf("%c", &sn);
		if(sn == 's'){
			printf("\n\tIntroduzca la definicion: ");
			setbuf(stdin, NULL);
			gets(definicion);
			agregarEntrada(palabra, definicion);
			printf("\n\tAgregando entrada");
			animacion();
			printf("\n\n\tEntrada agregada con exito");
		}
		else printf("\n\tPresione cualquier tecla para continuar");
	}
	return;
}

void actualizarEntrada(){
	consultarEntrada('a'); //Va a reemplazar la definición de la entrada (palabra) consultada
	return;
}

void eliminarEntrada(){
	consultarEntrada('r');

}