#include"ports.h"
#include <stdio.h>

char leerEntrada(void);

void printLEDs();

int main(){
	printf("Estado inicial de LEDs:\n");
	printLEDs();

	char entrada;
	while( (entrada = leerEntrada()) != 'q' ){
		switch(entrada){
		case 't': 	maskToggle(PORT_A, 0xFFFF);	printf("Alternando LEDs...\n");		break;
		case 'c': 	maskOff(PORT_A, 0xFFFF);	printf("Apagando LEDs...\n");		break;
		case 's': 	maskOn(PORT_A, 0xFFFF);		printf("Prendiendo LEDs...\n");		break;
		default:
			if(entrada>='0' && entrada<='7'){
				unsigned bitToSet = entrada - '0';
				bitSet(PORT_A, bitToSet);
			}else{
				printf("Entrada invalida\n");
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

// Devuelve 0 si entrada no es valida, sino devuelve el caracter c
char leerEntrada(void){
	char c;
	char nextChar;
	// Se obtiene el caracter actual (mientras que no sea un '\n') y el siguiente.
	if((c = getchar()) != '\n'){
		nextChar = getchar();
	}
	else{
		c = 0;
	}
	// Si el siguiente caracter no es una nueva linea, la entrada no es valida.
	while(nextChar != '\n'){
		nextChar = getchar();
		c = 0;
	}
	return c;
}
