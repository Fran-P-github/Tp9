#include"ports.h"
#include <stdio.h>

int main(){
	// Todo de testeo ejercicio 5

	maskOn(PORT_B, 0xFFFF);
	maskOn(PORT_A, 0xFFFF);
	maskOff(PORT_B, 0xFFFF);
	maskToggle(PORT_B, 0xFFFF);
	bitClr(PORT_D, 8);
	bitSet(PORT_D, 8);

	int i;
	for(i=0; i<16; ++i){
		printf("%d:\t%d\n", i, bitGet(PORT_D, i));
	}

	return 0;
}
