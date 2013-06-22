#include <stdio.h>
#define ESTADOS_MAX 20
#define SIMBOLOS_MAX 30

// Estructuras de datos
// ====================
struct transicion {
	char estado_origen;
	char move[SIMBOLOS_MAX][2]; // move[i][0] representa el simbolo, move[i][1] representa el estado destino.
};

struct transicion tabla[ESTADOS_MAX]; // La variable tabla es global.


// Prototipos
// ==========
int existe_estado(char estado); //Devuelve 1 si el estado ya existe en la tabla, else 0.
int existe_simbolo (char simbolo);//Devuelve 1 si el simbolo ya existe en la tabla, else 0.
void cargar_tabla();
char move(char estado, char caracter);
int match (char *cadena);
char leerchar();
int donde_guardar_move(char estado, char simbolo);
int donde_guardar_transicion(char estado);


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
	int i=0, j =0, indice_tabla=0;
	char estado,simbolo,estado_destino;
	
	//Llenar todos los campos de la tabla con un valor convención, tipo '*'. Va a servir.
	for (i=0;i<=ESTADOS_MAX; i++){
		tabla[i].estado_origen  = '*';
		for (j=0;j<=SIMBOLOS_MAX;j++){
			tabla[i].move[j][0]= '*';
			tabla[i].move[j][1]= '*';
		}
	}
	//Ahora si, a cargar la tabla
	while (1) {
		
		printf("Ingresar estado origen: ");
		estado = leerchar();
		if (estado == 13) break;
		indice_tabla = donde_guardar_transicion(estado);
		
		printf("Ingresar simbolo: ");
		simbolo = leerchar();
		indice_move = donde_guardar_move(estado, simbolo);
		tabla[indice_tabla].move[indice_move][0] = simbolo;
		
		printf("Ingresar estado destino: ");
		tabla[indice_tabla].move[indice_move][0] = leerchar();
	}
	Leer estado_inicial, estados_aceptacion[ ] //Validando que pertenezcan a la tabla.
}
	
int existe_estado (estado) {//Devuelve 1 si el estado ya existe en la tabla, else 0.
   int i = 0;
   while (tabla[i].estado_origen != '*' && i <= ESTADOS_MAX) {
      if (tabla[i].estado_origen == estado) return 1;
      i++;
   }
   return 0;
}

int donde_guardar_move(char estado, char simbolo) {
	/* Busca en el elemento transición determinado por el
	primer parámetro el símbolo indicado en el segundo.
	Si lo encuentra, devuelve su índice para que lo sobreescriba,
	si no devuelve, guarda el símbolo en el primer casillero libre
	y devuelve el índice. En cualquier caso siempre devuelve
	un índice con la posición de ese símbolo en el move. */
	int i = 0:
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
	tabla[estado].move[--i][0] = simbolo;
	return i;
}

int donde_guardar_transicion(char estado) {
	/* Busca en la tabla el estado dado. Si lo encuentra devuelve
	el índice. Sino, guarda ese estado en el primer casillero vacío
	y devuelve su índice. En cualquer caso siempre devuelve un
	índice con la posición de ese estado en la tabla. */
}

char move(estado, caracter) {
	buscar estado en la tabla;
	devolver estado al que se llega mediante ese caracter;
}

int match (char *cadena) { //Devuelve 1 si la cadena pasada coincide con el AFD.
	char estado_actual;
	estado_actual = move(estado_inicial, cadena [0];
	if estado_actual == '*' return 0; //El asterisco es una convención.
	for (i = 1; i < len(cadena) - 1; i++) {
		estado_actual = move(estado_actual, cadena[i]);
		if estado_actual == '*' return 0;
	}
	return 1;
}


//  MAIN
//  ====
int main() {
	char cadena[100];
	cargar_tabla();
	while (1) {
		printf("Ingresar cadena a analizar: ");
		scanf("%s", &cadena);
		if (cadena[0] == 13) return 0;
		if ( match(cadena) ) printf("La cadena %s coincide.\n", cadena);
		else printf("La cadena %s no coincide. \n", cadena);
	}
	return 0;
}
