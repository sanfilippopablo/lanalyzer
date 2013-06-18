#include <stdio.h>
#define ESTADOS_MAX 20
#define SIMBOLOS_MAX 30
//
//Estructuras de datos
//
struct transicion {
	char estado_origen;
	char move[SIMBOLOS_MAX][2]; // move[ i ][0] representa el simbolo, move[ i ][1] representa el estado destino.
}
struct transicion tabla[ESTADOS_MAX];
//
//Prototipos
//
int existe_estado(char estado); //Devuelve 1 si el estado ya existe en la tabla, else 0.
void cargar_tabla;
char move(char estado, char caracter);
int match (char *cadena);
//
//Funciones	
//
void cargar_tabla() {
	//Llenar todos los campos de la tabla con un valor convención, tipo ‘*’. Va a servir.
	int i=0, j =0;
	for (i=0;i<=ESTADOS_MAX; i++){
		tabla[i].estado_origen  = '*';
		for (j=0;j<=SIMBOLOS_MAX;j++){
			tabla[i].move[j][0]= '*';
			tabla[i].move[j][1]= '*';
		}
	}
	//Ahora si, a cargar la tabla
	while (1) {
		Leer estado
		if (estado == Enter key) break;
		if ( ! existe_estado(estado) ) agregarlo;
		Leer simbolo
		Leer estado_destino.
	}
	Leer estado_inicial, estados_aceptacion[ ] //Validando que pertenezcan a la tabla.
}

char move(estado, caracter) {
	buscar estado en la tabla;
	devolver estado al que se llega mediante ese caracter;
}

int match (char *cadena) { //Devuelve 0 si la cadena pasada coincide con el AFD.
	char estado_actual;
	estado_actual = move(estado_inicial, cadena [0];
	if estado_actual == ‘*’ return 0; //El asterisco es una convención.
	for (i = 1; i < len(cadena) - 1; i++) {
		estado_actual = move(estado_actual, cadena[i]);
		if estado_actual == ‘*’ return 0;
	}
	return 1;
}

//Luego el main que carga los datos y pregunta por cadenas, las analiza y devuelve el resultado.

