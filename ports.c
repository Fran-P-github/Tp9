#include"ports.h"

// Struct de puertos, usada a lo largo del programa
static union{
	uint16_t D;
	struct{
		uint8_t B; // B byte menos significativo de D, asumiendo arquitectura little-endian. Cambiar orden si es arquitectura big-endian
		uint8_t A;
	}A_B;
} ports;

// Retorna 0 para puerto y bit validos (ver BITS DE ERROR)
static int validBitAndPort(port_t port, unsigned bit);

// Enciende o apaga el bit especificado del puerto especificado. Si state==0 lo apaga, si no lo enciende
// Si el puerto o bit son invalidos, no cambia el bit y retorna algo distinto de cero (ver BITS DE ERROR)
static int bitChange(port_t port, unsigned bit, int state);

// Devuelve mascara a usar para el puerto especificado:
// *Si es el puerto D, la mascara no cambia
// *Si es el puerto A o B, la mascara conserva el byte correspondiente al puerto, moviendolo al LSB de la mascara, y el resto queda en cero
// No chequea errores (asume puerto valido)
static mask_t newMask(port_t port, mask_t mask);


// ************************************************************
// ******************* Funciones Publicas *********************
// ************************************************************

int bitSet(port_t port, unsigned bit){
	int err = bitChange(port, bit, 1);
	return err;
}

int bitClr(port_t port, unsigned bit){
	int err = bitChange(port, bit, 0);
	return err;
}

int bitToggle(port_t port, unsigned bit){
	int err = bitChange(port, bit, !bitGet(port, bit));
	return err;
}

int bitGet(port_t port, unsigned bit){
	int error = validBitAndPort(port, bit);
	if(error){
		return error;
	}

	// Tomamos el bit especificado del puerto especificado con shifteos
	int rta;
	if(port == PORT_D){
		rta = ( ports.D>>bit ) & 1;
	}else if(port == PORT_A){
		rta = ( ports.A_B.A>>bit ) & 1;
	}else{ // port == PORT_B
		rta = ( ports.A_B.B>>bit ) & 1;
	}
	return rta;
}


int maskOn(port_t port, mask_t mask){
	if(port!=PORT_A && port!=PORT_B && port!=PORT_D){
		return ERR_INVALID_PORT;
	}

	mask = newMask(port, mask);
	ports.D |= mask; // Set
	return 0;
}

int maskOff(port_t port, mask_t mask){
	if(port!=PORT_A && port!=PORT_B && port!=PORT_D){
		return ERR_INVALID_PORT;
	}

	mask = newMask(port, mask);
	ports.D &= ~mask; // Clear
	return 0;
}

int maskToggle(port_t port, mask_t mask){
	if(port!=PORT_A && port!=PORT_B && port!=PORT_D){
		return ERR_INVALID_PORT;
	}

	mask = newMask(port, mask);
	ports.D ^= mask; // Toggle
	return 0;
}

// ************************************************************
// ********************* Funciones Privadas *******************
// ************************************************************

static mask_t newMask(port_t port, mask_t mask){
	if(port != PORT_D){ // Hay que ignorar uno de los bytes
		mask = (port==PORT_B) ? (mask & 0x00FF) : 	// B usa el LSB
								(mask << 8);  		// A usa el MSB
	}
	// else: si port==PORT_D la mascara no cambia

	return mask;
}

static int bitChange(port_t port, unsigned bit, int state){
	int err = validBitAndPort(port, bit);
	if(err){
		return err;
	}

	if(state){ // Set bit
		if(port == PORT_D){
			ports.D |= 1<<bit;
		}else if(port == PORT_A){
			ports.A_B.A |= 1<<bit;
		}else{ // port == PORT_B
			ports.A_B.B |= 1<<bit;
		}
	}else{ // Clear bit
		if(port == PORT_D){
			ports.D &= ~(1<<bit);
		}else if(port == PORT_A){
			ports.A_B.A &= ~(1<<bit);
		}else{ // port == PORT_B
			ports.A_B.B &= ~(1<<bit);
		}
	}

	return 0;
}

static int validBitAndPort(port_t port, unsigned bit){
	int error = 0;
	if(bit >= 16){ // Bit invalido
		error |= ERR_INVALID_BIT;
	}
	if(port!=PORT_A && port!=PORT_B && port!=PORT_D){ // Puerto invalido
		error |= ERR_INVALID_PORT;
	}
	if(port!=PORT_D && bit>=8){ // Bit invalido para el puerto especificado
		error |= ERR_INVALID_BIT;
	}

	return error;
}
