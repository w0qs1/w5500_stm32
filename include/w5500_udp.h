/*
 * w5500_udp.h
 *
 *  Created on: Jun 30, 2025
 *      Author: mnsan
 */

#ifndef INC_W5500_UDP_H_
#define INC_W5500_UDP_H_

#include "w5500.h"
#include "w5500_socket.h"

void w5500_open_udp(uint8_t socket, uint8_t* dest_ip_address, uint16_t dest_port);
void w5500_open_udp_recv(uint8_t socket, uint16_t receive_port);

#endif /* INC_W5500_UDP_H_ */
