#ifndef PORTS_H_
#define PORTS_H_

typedef unsigned port_t;
#define PORT_A 1
#define PORT_B 2
#define PORT_D 3

void bitSet(port_t port, unsigned bit);
void bitClr(port_t port, unsigned bit);
int bitGet(port_t port, unsigned bit);
int bitToggle(port_t port, unsigned bit);

#endif /* PORTS_H_ */
