#include"ports.h"

static union{
	uint16_t D;
	struct{
		uint8_t B; // B byte menos significativo
		uint8_t A;
	}A_B;
} ports;

static int validBitAndPort(port_t port, unsigned bit);
static int bitChange(port_t port, unsigned bit, int state);

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
	if(bit >= 16){
		return ERR_INVALID_BIT;
	}else if(port!=PORT_A && port!=PORT_B && port!=PORT_D){
		return ERR_INVALID_PORT;
	}else if(port!=PORT_D && bit>=8){
		return ERR_INVALID_BIT;
	}

	return 0;
}
