#include <stdio.h>
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
int existe_estado(char estado); //Devuelve 1 si el estado ya existe en la tabla, else 0.
int existe_simbolo (char simbolo);//Devuelve 1 si el simbolo ya existe en la tabla, else 0.
void cargar_tabla();
char move(char, char);
int match (char *cadena);
char leer_char();
int donde_guardar_move(char estado, char simbolo);
int donde_guardar_transicion(char estado);


// Funciones	
// =========

void print_tabla() {
	int i, j;
	printf("Printing tabla.\n");
	printf("======================\n");
	for (i = 0; i < ESTADOS_MAX; ++i)
	{
		for (j = 0; j < SIMBOLOS_MAX; ++j)
		{
			printf("De %c a %c a través de %c.\n", tabla[i].estado_origen, tabla[i].move[j][1], tabla[i].move[j][0]);
		}
	}
	printf("======================\n");
}

char leer_char() {
	/* Devuelve un caracter leído por teclado.
	Limpia automáticamente el buffer. */
	char c;
	c = getchar();
	fflush(stdin);
	return c;
}

void cargar_tabla() {
	int i = 0, j = 0, indice_tabla = 0, indice_move;
	char estado,simbolo,estado_destino;
	
	//Llenar todos los campos de la tabla con un valor convención, tipo '*'. Va a servir.
	for (i=0;i<ESTADOS_MAX; i++){
		tabla[i].estado_origen  = '*';
		for (j=0;j<SIMBOLOS_MAX;j++){
			tabla[i].move[j][0]= '*';
			tabla[i].move[j][1]= '*';
		}
	}
	for (i = 0; i < ESTADOS_MAX; ++i) {
		estados_aceptacion[i] = '*';
	}

	print_tabla();
	//Ahora si, a cargar la tabla
	while (1) {
		
		printf("Ingresar estado origen: ");
		estado = leer_char();
		if (estado == '\n') break;
		indice_tabla = donde_guardar_transicion(estado);
		
		print_tabla();

		printf("Ingresar simbolo: ");
		simbolo = leer_char();
		indice_move = donde_guardar_move(indice_tabla, simbolo);
		tabla[indice_tabla].move[indice_move][0] = simbolo;

		print_tabla();
		
		printf("Ingresar estado destino: ");
		tabla[indice_tabla].move[indice_move][1] = leer_char();

		print_tabla();
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
	if (i > SIMBOLOS_MAX) {
		/* No hay lugar para más símbolos. */
		exit(1);
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
   if (i > ESTADOS_MAX) {
		/* No hay lugar para más estados. */
		exit(1);
	}
	tabla[i].estado_origen = estado;
	return i;
}

char move(char estado, char simbolo) {
	/* Toma un estado y un símbolo y devuelve el estado
	al cual se llega desde ese estado a través de ese
	símbolo. Si esto no es posible, devuelve '*'. */
	printf("[DEBUG] Buscando en la tabla el estado %c.\n", estado);
	int i_estado = 0, i_simbolo = 0, i = 0;
	while (tabla[i].estado_origen != '*' && i <= ESTADOS_MAX) {
    	if (tabla[i].estado_origen == estado) break;
    	i++;
   	}
	if (i > ESTADOS_MAX || tabla[i].estado_origen == '*') {
		/* Error, ese estado no existe. */
		exit(1);
	}
	i_estado = i;
	printf("[DEBUG] Encontrado. %d.\n", i_estado);
	printf("[DEBUG] Buscando en esa transicion el simbolo %c.\n", simbolo);
	while (tabla[i_estado].move[i_simbolo][0] != '*' && i <= SIMBOLOS_MAX) {
		if (tabla[i_estado].move[i_simbolo][0] == simbolo) {
			//Ya tengo el i_estado y i_simbolo, devolver estado destino.
			printf("[DEBUG] Encontrado. %d.\n", i_simbolo);
			return tabla[i_estado].move[i_simbolo][1];
		}
		i++;
	}
	/* Se encontró el estado, pero a través de ese caracter no se
	llega a ningún lado. Devolver '*'. */
	return '*';

}

int match (char *cadena) { //Devuelve 1 si la cadena pasada coincide con el AFD.
	printf("[DEBUG] Iniciando match.\n");
	int i = 0;
	char estado_actual;
	printf("[DEBUG] estado_inicial = %c.\n", estado_inicial);
	printf("[DEBUG] Intentando transicion a través del simbolo %c.\n", cadena[0]);
	estado_actual = move(estado_inicial, cadena [0]);
	if (estado_actual == '*') return 0; //El asterisco es una convención.
	for (i = 1; i < strlen(cadena); i++) {
		printf("[DEBUG] estado_actual = %c.\n", estado_actual);
		printf("[DEBUG] Intentando transicion a través del simbolo %c.\n", cadena[i]);
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
		printf("Ingresar cadena a analizar: ");
		scanf("%s", &cadena);
		if (cadena[0] == '\0') return 0;
		if ( match(cadena) ) printf("La cadena %s coincide.\n", cadena);
		else printf("La cadena %s no coincide. \n", cadena);
	}
	return 0;
}
