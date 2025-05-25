#include"ports.h"
#include <stdio.h>

// Lectura de la entrada. Entrada esperada "x\n", con x un caracter
// Devuelve 0 si la entrada no es valida, si no devuelve el caracter x, correspondiente a la operacion a realizar, segun lo siguiente:
// *t: toggle bits port A
// *s: set bits port A
// *c: clear bits port A
// *q: salir del programa
// 0-7: bit de port A a setear
// default: ninguna operacion
char leerEntrada();

// Imprime el estado del port A
void printLEDs();

int main(){
	printf("Estado inicial de LEDs:\n");
	printLEDs();

	char entrada;
	while( (entrada = leerEntrada()) != 'q' ){
		switch(entrada){
		case 't': 	maskToggle(PORT_A, 0xFF);	printf("Alternando LEDs...\n");		break;
		case 'c': 	maskOff(PORT_A, 0xFF);		printf("Apagando LEDs...\n");		break;
		case 's': 	maskOn(PORT_A, 0xFF);		printf("Prendiendo LEDs...\n");		break;
		default:
			if(entrada>='0' && entrada<='7'){
				unsigned bitToSet = entrada - '0';
				bitSet(PORT_A, bitToSet);
			}else{
				printf("Entrada invalida u operacion no existente\n");
			}
			break;
		}

		printf("Estado actual de LEDs:\n");
		printLEDs();
	}

	return 0;
}

void printLEDs(){
	int i;

	for(i=7; i>=0; --i){
		printf("LED %d\t", i);
	}
	putchar('\n');

	for(i=7; i>=0; --i){
		printf(" [%c] \t", bitGet(PORT_A, i) ? '*' : ' ');
	}
	putchar('\n');
}

char leerEntrada(){
	char c;
	char nextChar = '\n'; // Inicializado así para contemplar caso en que la entrada es "\n"
	// Se obtiene el caracter actual y el siguiente (mientras que el primero no sea un '\n')
	if((c = getchar()) != '\n'){
		nextChar = getchar();
	}
	else{
		c = 0; // Invalida
	}
	// Si el siguiente caracter no es una nueva linea, la entrada no es valida.
	while(nextChar != '\n'){
		nextChar = getchar();
		c = 0; // Invalida
	}
	return c;
}
