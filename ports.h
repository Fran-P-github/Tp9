#ifndef PORTS_H_
#define PORTS_H_
#include<stdint.h>

// CODIGOS DE ERROR
#define ERR_INVALID_BIT 1
#define ERR_INVALID_PORT 2

// PUERTOS
typedef int port_t;
#define PORT_A 1
#define PORT_B 2
#define PORT_D 3

// MASCARAS
typedef uint16_t mask_t;

int bitSet(port_t port, unsigned bit);
int bitClr(port_t port, unsigned bit);
int bitGet(port_t port, unsigned bit);
int bitToggle(port_t port, unsigned bit);
int maskOn(port_t port, mask_t mask);
int maskOff(port_t port, mask_t mask);
int maskToggle(port_t port, mask_t mask);

#endif /* PORTS_H_ */
