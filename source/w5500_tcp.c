/*
 * w5500_tcp.c
 *
 *  Created on: Jun 30, 2025
 *      Author: mnsan
 */

#include "w5500_tcp.h"

/**
 * @brief  Open a socket as a TCP Client
 * @note   
 * @param  socket: Socket number
 * @param  ip_address: IP Address of TCP server
 * @param  port: Port of TCP server
 * @retval None
 */
 */
void w5500_open_tcp_client(uint8_t socket, uint8_t* ip_address, uint16_t port) {
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

	// Write the IP
	w5500_reg_write(W5500_SOCKET_DEST_IP_ADDR_0, SOCKET_ADDRESS, *(ip_address + 0));
	w5500_reg_write(W5500_SOCKET_DEST_IP_ADDR_1, SOCKET_ADDRESS, *(ip_address + 2));
	w5500_reg_write(W5500_SOCKET_DEST_IP_ADDR_2, SOCKET_ADDRESS, *(ip_address + 2));
	w5500_reg_write(W5500_SOCKET_DEST_IP_ADDR_3, SOCKET_ADDRESS, *(ip_address + 3));

	// Write the port
	w5500_reg_write(W5500_SOCKET_DEST_PORT_0, SOCKET_ADDRESS, port_be.u8.msb);
	w5500_reg_write(W5500_SOCKET_DEST_PORT_1, SOCKET_ADDRESS, port_be.u8.lsb);

	// Generate the source port and write it
	port_be.u16 = 50000 + (w5500_rand() % 64);
	w5500_reg_write(W5500_SOCKET_SOURCE_PORT_0, SOCKET_ADDRESS, port_be.u8.msb);
	w5500_reg_write(W5500_SOCKET_SOURCE_PORT_1, SOCKET_ADDRESS, port_be.u8.lsb);

	// Set TCP protocol in the socket mode register
	w5500_reg_write(W5500_SOCKET_MODE, SOCKET_ADDRESS, 0x01);

	// Open Socket
	w5500_reg_write(W5500_SOCKET_COMMAND, SOCKET_ADDRESS, W5500_SOCKET_COMMAND_OPEN);

	return;
}

/**
 * @brief  Connect socket as a TCP client
 * @note   Call after w5500_open_tcp_client()
 * @param  socket: Socket number
 * @retval 
 */
 */
uint8_t w5500_connect_tcp_client(uint8_t socket) {
	uint8_t SOCKET_ADDRESS = W5500_SOCKET_0_REGISTER + (socket << 2);

	// Connect to server
	w5500_reg_write(W5500_SOCKET_COMMAND, SOCKET_ADDRESS, W5500_SOCKET_COMMAND_CONNECT);

	uint8_t status;
	for(uint8_t i = 0; i < RETRY_STATUS_COUNT; i++) {
		HAL_Delay(TCP_COOLDOWN_TIME);
		w5500_reg_read(W5500_SOCKET_STATUS, SOCKET_ADDRESS, &status);

		if(status == W5500_SOCKET_SR_SOCK_ESTD) {
			return W5500_TCP_CLIENT_OK;
		}
	}

	return W5500_TCP_CLIENT_ERR;
}

/**
 * @brief  Open a socket as TCP server
 * @note   
 * @param  socket: Socket number
 * @param  port: Port of the TCP server
 * @retval None
 */
 */
void w5500_open_tcp_server(uint8_t socket, uint16_t port) {
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

	// Write the port
	w5500_reg_write(W5500_SOCKET_SOURCE_PORT_0, SOCKET_ADDRESS, port_be.u8.msb);
	w5500_reg_write(W5500_SOCKET_SOURCE_PORT_1, SOCKET_ADDRESS, port_be.u8.lsb);

	// Set TCP protocol in the socket mode register
	w5500_reg_write(W5500_SOCKET_MODE, SOCKET_ADDRESS, 0x01);

	// Open Socket
	w5500_reg_write(W5500_SOCKET_COMMAND, SOCKET_ADDRESS, W5500_SOCKET_COMMAND_OPEN);

	return;
}

/**
 * @brief  Listen(wait) for client to connect
 * @note   Handles only 1 client at any given time. This is a blocking function; returns only after a client connects
 * @param  socket: Socket number
 * @retval None
 */
 */
void w5500_listen_tcp_server(uint8_t socket) {
	uint8_t SOCKET_ADDRESS = W5500_SOCKET_0_REGISTER + (socket << 2);

	uint8_t status;

	do {
		w5500_reg_read(W5500_SOCKET_STATUS, SOCKET_ADDRESS, &status);
		HAL_Delay(SOCKET_CLOSE_COOLDOWN);
	} while(status != W5500_SOCKET_SR_SOCK_INIT);

	// Set mode to listen mode
	w5500_reg_write(W5500_SOCKET_COMMAND, SOCKET_ADDRESS, W5500_SOCKET_COMMAND_LISTEN);

	do {
		w5500_reg_read(W5500_SOCKET_STATUS, SOCKET_ADDRESS, &status);
		HAL_Delay(SOCKET_CLOSE_COOLDOWN);
	} while(status != W5500_SOCKET_SR_SOCK_ESTD);
}

/**
 * @brief  Disconnect a TCP connection
 * @note   Both Active and Passive disconnects
 * @param  socket: Socket number
 * @retval 
 */
 */
uint8_t w5500_discon_tcp(uint8_t socket) {
	uint8_t SOCKET_ADDRESS = W5500_SOCKET_0_REGISTER + (socket << 2);

	// Disconnect
	w5500_reg_write(W5500_SOCKET_COMMAND, SOCKET_ADDRESS, W5500_SOCKET_COMMAND_DISCON);

	uint8_t status;
	for(uint8_t i = 0; i < RETRY_STATUS_COUNT; i++) {
		HAL_Delay(TCP_COOLDOWN_TIME);
		w5500_reg_read(W5500_SOCKET_STATUS, SOCKET_ADDRESS, &status);

		if(status == W5500_SOCKET_SR_SOCK_CLOSED) {
			return W5500_TCP_CLIENT_OK;
		}
	}

	return W5500_TCP_CLIENT_ERR;
}
