/*
 * w5500_socket.h
 *
 *  Created on: Jun 30, 2025
 *      Author: mnsan
 */

#ifndef INC_W5500_SOCKET_H_
#define INC_W5500_SOCKET_H_

#include "w5500.h"

void w5500_send(uint8_t socket, uint8_t* data, size_t len);
size_t w5500_recv(uint8_t socket, uint16_t* source_port, uint8_t* source_ip, uint8_t* data);
void w5500_close(uint8_t socket);
void w5500_socket_mode_status(uint8_t socket, uint8_t* status);
void w5500_socket_status(uint8_t socket, uint8_t* status);

#endif /* INC_W5500_SOCKET_H_ */
