/*
 * w5500_tcp.h
 *
 *  Created on: Jun 30, 2025
 *      Author: mnsan
 */

#ifndef INC_W5500_TCP_H_
#define INC_W5500_TCP_H_

#include "w5500.h"
#include "w5500_socket.h"

#define W5500_TCP_CLIENT_OK		0x00U
#define W5500_TCP_CLIENT_ERR	0x01U

void w5500_open_tcp_client(uint8_t socket, uint8_t* ip_address, uint16_t port);
uint8_t w5500_connect_tcp_client(uint8_t socket);
void w5500_open_tcp_server(uint8_t socket, uint16_t port);
void w5500_listen_tcp_server(uint8_t socket);
uint8_t w5500_discon_tcp(uint8_t socket);

#endif /* INC_W5500_TCP_H_ */
