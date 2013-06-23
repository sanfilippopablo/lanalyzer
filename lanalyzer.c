#include <stdio.h>
#include <stdlib.h>
#define ESTADOS_MAX 4
#define SIMBOLOS_MAX 5

// Estructuras de datos
// ====================
struct transicion {
	char estado_origen;
	char move[SIMBOLOS_MAX][2]; // move[i][0] representa el simbolo, move[i][1] representa el estado destino.
};

// Variables globales
// ==================
struct transicion tabla[ESTADOS_MAX];
char estado_inicial;
char estados_aceptacion[ESTADOS_MAX];


// Prototipos
// ==========
void cargar_tabla();
char move(char, char);
int match (char*);
char leer_char();
int donde_guardar_move(char, char);
int donde_guardar_transicion(char);


// Funciones	
// =========

char leer_char() {
	/* Devuelve un caracter leído por teclado.
	Limpia automáticamente el buffer. */
	char c;
	c = getchar();
	fflush(stdin);
	return c;
}

void cargar_tabla() {
	/* Procedimiento general de carga de datos sobre el AFD. */
	int i = 0, j = 0, indice_tabla = 0, indice_move;
	char estado, simbolo, estado_destino;
	
	// Llenar todos los campos de la tabla con un valor convención, '*'.
	for (i = 0; i < ESTADOS_MAX; i++) {
		tabla[i].estado_origen  = '*';
		for (j = 0; j < SIMBOLOS_MAX; j++){
			tabla[i].move[j][0] = '*';
			tabla[i].move[j][1] = '*';
		}
	}

	//Llenar con * también los campos del array estados_aceptación.
	for (i = 0; i < ESTADOS_MAX; ++i) {
		estados_aceptacion[i] = '*';
	}

	// Cargar los datos en la tabla.
	printf("Cargar datos del AFD.\n");
	while (1) {
		
		printf("Ingresar estado origen (Enter para terminar): ");
		estado = leer_char();
		if (estado == '\n') break;
		indice_tabla = donde_guardar_transicion(estado);

		printf("Ingresar simbolo: ");
		simbolo = leer_char();
		indice_move = donde_guardar_move(indice_tabla, simbolo);
		tabla[indice_tabla].move[indice_move][0] = simbolo;
		
		printf("Ingresar estado destino: ");
		tabla[indice_tabla].move[indice_move][1] = leer_char();
	}

	printf("Ingresar estado_inicial: ");
	estado_inicial = leer_char();

	i = 0;
	while (1) {
		printf("Ingresar estado de aceptación: \n");
		estado = leer_char();
		if (estado == '\n') break;
		estados_aceptacion[i] = estado;
	}
}

int donde_guardar_move(char estado, char simbolo) {
	/* Busca en el elemento transición determinado por el
	primer parámetro el símbolo indicado en el segundo.
	Si lo encuentra, devuelve su índice para que lo sobreescriba,
	si no devuelve, guarda el símbolo en el primer casillero libre
	y devuelve el índice. En cualquier caso siempre devuelve
	un índice con la posición de ese símbolo en el move. */
	int i = 0;
	while (tabla[estado].move[i][0] != '*' && i <= SIMBOLOS_MAX) {
		if (tabla[estado].move[i][0] == simbolo) {
			return i;
		}
		i++;
	}

	tabla[estado].move[i][0] = simbolo;
	return i;
}

int donde_guardar_transicion(char estado) {
	/* Busca en la tabla el estado dado. Si lo encuentra devuelve
	el índice. Sino, guarda ese estado en el primer casillero vacío
	y devuelve su índice. En cualquer caso siempre devuelve un
	índice con la posición de ese estado en la tabla. */
	int i = 0;
	while (tabla[i].estado_origen != '*' && i <= ESTADOS_MAX) {
    	if (tabla[i].estado_origen == estado) return i;
    	i++;
   }

	tabla[i].estado_origen = estado;
	return i;
}

char move(char estado, char simbolo) {
	/* Toma un estado y un símbolo y devuelve el estado
	al cual se llega desde ese estado a través de ese
	símbolo. Si esto no es posible, devuelve '*'. */
	int i_estado = 0, i_simbolo = 0, i = 0;
	while (tabla[i].estado_origen != '*' && i <= ESTADOS_MAX) {
    	if (tabla[i].estado_origen == estado) break;
    	i++;
   	}

	i_estado = i;
	while (tabla[i_estado].move[i_simbolo][0] != '*' && i <= SIMBOLOS_MAX) {
		if (tabla[i_estado].move[i_simbolo][0] == simbolo) {
			//Ya tengo el i_estado y i_simbolo, devolver estado destino.
			return tabla[i_estado].move[i_simbolo][1];
		}
		i++;
	}
	/* Se encontró el estado, pero a través de ese caracter no se
	llega a ningún lado. Devolver '*'. */
	return '*';

}

int match (char *cadena) { //Devuelve 1 si la cadena pasada coincide con el AFD.
	int i = 0;
	char estado_actual;
	estado_actual = move(estado_inicial, cadena [0]);
	if (estado_actual == '*') return 0; //El asterisco es una convención.
	for (i = 1; i < strlen(cadena); i++) {
		estado_actual = move(estado_actual, cadena[i]);
		if (estado_actual == '*') return 0;
	}

	//Chequear si el estado final está entre los estados de aceptación.
	i = 0;
	while (estados_aceptacion[i] != '*' && i <= ESTADOS_MAX) {
    	if (estados_aceptacion[i] == estado_actual) return 1;
    	i++;
   }
	return 0;
}


//  MAIN
//  ====
int main() {
	char cadena[100];
	cargar_tabla();
	while (1) {
		printf("Ingresar cadena a analizar (* para salir): ");
		scanf("%s", &cadena);
		if (cadena[0] == '*') return 0;
		if ( match(cadena) ) printf("La cadena %s coincide.\n", cadena);
		else printf("La cadena %s no coincide. \n", cadena);
	}
	return 0;
}
