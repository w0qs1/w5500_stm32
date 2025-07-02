/*
 * w5500_udp.c
 *
 *  Created on: Jun 28, 2025
 *      Author: mnsan
 */

#include "w5500_udp.h"

/**
 * @brief  Open a UDP connection for sending data
 * @note   can also be used with w5500_open_udp_recv(). A random port (50000 - 50063) is used for sending data
 * @param  socket: Socket number
 * @param  dest_ip_address: Destination IP Address
 * @param  port: Destination Port
 * @retval None
 */
 */
void w5500_open_udp(uint8_t socket, uint8_t* dest_ip_address, uint16_t port) {
	uint16_be_t port_be;
	port_be.u16 = port;

	uint8_t SOCKET_ADDRESS = W5500_SOCKET_0_REGISTER + (socket << 2);

	uint8_t status;

	w5500_reg_read(W5500_SOCKET_STATUS, SOCKET_ADDRESS, &status);

	// Close if the socket is not closed
	while(status != W5500_SOCKET_SR_SOCK_CLOSED) {
		w5500_close(socket);
		w5500_reg_read(W5500_SOCKET_STATUS, SOCKET_ADDRESS, &status);
		HAL_Delay(SOCKET_CLOSE_COOLDOWN);
	}

	// Write the destination IP
	w5500_reg_write(W5500_SOCKET_DEST_IP_ADDR_0, SOCKET_ADDRESS, *(dest_ip_address + 0));
	w5500_reg_write(W5500_SOCKET_DEST_IP_ADDR_1, SOCKET_ADDRESS, *(dest_ip_address + 1));
	w5500_reg_write(W5500_SOCKET_DEST_IP_ADDR_2, SOCKET_ADDRESS, *(dest_ip_address + 2));
	w5500_reg_write(W5500_SOCKET_DEST_IP_ADDR_3, SOCKET_ADDRESS, *(dest_ip_address + 3));

	// Write the destination port
	w5500_reg_write(W5500_SOCKET_DEST_PORT_0, SOCKET_ADDRESS, port_be.u8.msb);
	w5500_reg_write(W5500_SOCKET_DEST_PORT_1, SOCKET_ADDRESS, port_be.u8.lsb);

	// Generate the source port and write it
	port_be.u16 = 50000 + (w5500_rand() % 64);
	w5500_reg_write(W5500_SOCKET_SOURCE_PORT_0, SOCKET_ADDRESS, port_be.u8.msb);
	w5500_reg_write(W5500_SOCKET_SOURCE_PORT_1, SOCKET_ADDRESS, port_be.u8.lsb);

	// Set UDP protocol in socket mode register
	w5500_reg_write(W5500_SOCKET_MODE, SOCKET_ADDRESS, 0x02);

	// Open Socket
	w5500_reg_write(W5500_SOCKET_COMMAND, SOCKET_ADDRESS, W5500_SOCKET_COMMAND_OPEN);

	return;
}

/**
 * @brief  Open UDP for receiving data
 * @note   can also be used with w5500_open_udp()
 * @param  socket: Socket number
 * @param  receive_port: Port to receive data on
 * @retval None
 */
 */
void w5500_open_udp_recv(uint8_t socket, uint16_t receive_port) {
	uint16_be_t port_be;
	port_be.u16 = receive_port;

	uint8_t SOCKET_ADDRESS = W5500_SOCKET_0_REGISTER + (socket << 2);

	uint8_t status;

	w5500_reg_read(W5500_SOCKET_STATUS, SOCKET_ADDRESS, &status);

	// Close if the socket is not closed
	while(status != W5500_SOCKET_SR_SOCK_CLOSED) {
		w5500_close(socket);
		w5500_reg_read(W5500_SOCKET_STATUS, SOCKET_ADDRESS, &status);
		HAL_Delay(SOCKET_CLOSE_COOLDOWN);
	}

	// Set the receive port
	w5500_reg_write(W5500_SOCKET_SOURCE_PORT_0, SOCKET_ADDRESS, port_be.u8.msb);
	w5500_reg_write(W5500_SOCKET_SOURCE_PORT_1, SOCKET_ADDRESS, port_be.u8.lsb);

	// Set UDP protocol in socket mode register
	w5500_reg_write(W5500_SOCKET_MODE, SOCKET_ADDRESS, 0x02);

	// Open Socket
	w5500_reg_write(W5500_SOCKET_COMMAND, SOCKET_ADDRESS, W5500_SOCKET_COMMAND_OPEN);

	return;
}
