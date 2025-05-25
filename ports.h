#ifndef PORTS_H_
#define PORTS_H_
#include<stdint.h>

// BITS DE ERROR
// Ninguno puede ser el bit menos significativo, por la implementacion de bitGet
#define ERR_INVALID_BIT 1<<1
#define ERR_INVALID_PORT 1<<2
#if ERR_INVALID_BIT==1 || ERR_INVALID_PORT==1
#error los bits de error no pueden ser el menos significativo
#endif

// PUERTOS
typedef int port_t;
#define PORT_A 1
#define PORT_B 2
#define PORT_D 3

// MASCARAS
typedef uint16_t mask_t;

// Enciende el bit especificado del puerto especificado
// Si el puerto o bit son invalidos, no cambia el bit y retorna algo distinto de cero (ver BITS DE ERROR)
int bitSet(port_t port, unsigned bit);

// Apaga el bit especificado del puerto especificado
// Si el puerto o bit son invalidos, no cambia el bit y retorna algo distinto de cero (ver BITS DE ERROR)
int bitClr(port_t port, unsigned bit);

// Alterna el bit especificado del puerto especificado
// Si el puerto o bit son invalidos, no cambia el bit y retorna algo distinto de cero (ver BITS DE ERROR)
int bitToggle(port_t port, unsigned bit);

// Devuelve el estado del bit especificado del puerto especificado
// Si el puerto o bit son invalidos, no cambia el bit y retorna algo distinto de cero (ver BITS DE ERROR)
int bitGet(port_t port, unsigned bit);

// Enciende los bits especificados por la mascara correspondientes al puerto especificado
// mask es de 16bits. Si se especifica puerto A o B, se ignora el MSB de la mascara
int maskOn(port_t port, mask_t mask);

// Apaga los bits especificados por la mascara correspondientes al puerto especificado
// mask es de 16bits. Si se especifica puerto A o B, se ignora el MSB de la mascara
int maskOff(port_t port, mask_t mask);

// Alterna los bits especificados por la mascara correspondientes al puerto especificado
// mask es de 16bits. Si se especifica puerto A o B, se ignora el MSB de la mascara
int maskToggle(port_t port, mask_t mask);

#endif /* PORTS_H_ */
