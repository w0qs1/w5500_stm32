/*
 * w5500_socket.c
 *
 *  Created on: Jun 30, 2025
 *      Author: mnsan
 */

#include "w5500_socket.h"

/**
 * @brief  Send data through a socket
 * @note   Setup UDP/TCP before calling this
 * @param  socket: Socket to send data through
 * @param  data: Pointer to data
 * @param  len: Number of bytes to send
 * @retval None
 */
 */
void w5500_send(uint8_t socket, uint8_t* data, size_t len) {
	uint8_t SOCKET_ADDRESS = W5500_SOCKET_0_REGISTER + (socket << 2);
	uint8_t TX_BUFFER_ADDRESS = SOCKET_ADDRESS + 1;

	// Fetch the current write_pointer
	uint16_be_t write_pointer;
	w5500_reg_read(W5500_SOCKET_TX_WRITE_PTR_0, SOCKET_ADDRESS, &write_pointer.u8.msb);
	w5500_reg_read(W5500_SOCKET_TX_WRITE_PTR_1, SOCKET_ADDRESS, &write_pointer.u8.lsb);

	// Transfer data to buffer
	w5500_buf_write(write_pointer.u16, TX_BUFFER_ADDRESS, data, len);

	write_pointer.u16 += len;

	// Update size of data transferred to TX buffer
	w5500_reg_write(W5500_SOCKET_TX_WRITE_PTR_0, SOCKET_ADDRESS, write_pointer.u8.msb);
	w5500_reg_write(W5500_SOCKET_TX_WRITE_PTR_1, SOCKET_ADDRESS, write_pointer.u8.lsb);

	// Write command to SEND the packet
	w5500_reg_write(W5500_SOCKET_COMMAND, SOCKET_ADDRESS, W5500_SOCKET_COMMAND_SEND);

	return;
}

/**
 * @brief  Receive data from a socket
 * @note   Only for UDP, the source_port and source_ip are set
 * @param  socket: Socket to receive data from
 * @param  source_port: Port address of the sender (UDP)
 * @param  source_ip: IP address of the sender (UDP)
 * @param  data: Pointer to data
 * @retval Returns the size of data received
 */
 */
size_t w5500_recv(uint8_t socket, uint16_t* source_port, uint8_t* source_ip, uint8_t* data) {
	uint8_t SOCKET_ADDRESS = W5500_SOCKET_0_REGISTER + (socket << 2);
	uint8_t RX_BUFFER_ADDRESS = SOCKET_ADDRESS + 2;

	uint16_be_t rx_size;
	w5500_reg_read(W5500_SOCKET_RX_RECV_SIZE_0, SOCKET_ADDRESS, &rx_size.u8.msb);
	w5500_reg_read(W5500_SOCKET_RX_RECV_SIZE_1, SOCKET_ADDRESS, &rx_size.u8.lsb);

	uint8_t status;
	// Get mode of socket (UDP or TCP)
	w5500_reg_read(W5500_SOCKET_MODE, SOCKET_ADDRESS, &status);
	status &= 0x0F;

	// If no UDP header is present in UDP mode, no data is present
	if(rx_size.u16 < 8 && (status == 0x02)) {
		return 0;
	} else if (rx_size.u16 == 0 && (status == 0x01)) {
		// No data in TCP mode
		return 0;
	} else if (status == 0x00){
		// Return if socket is closed
		return 0;
	}

	uint16_be_t read_pointer;
	w5500_reg_read(W5500_SOCKET_RX_READ_PTR_0, SOCKET_ADDRESS, &read_pointer.u8.msb);
	w5500_reg_read(W5500_SOCKET_RX_READ_PTR_1, SOCKET_ADDRESS, &read_pointer.u8.lsb);

	uint16_t data_length;

	if (status == 0x02) {
		// If UDP is used
		uint8_t header[8];
		// Read first 8 bytes to get the header
		w5500_buf_read(read_pointer.u16, RX_BUFFER_ADDRESS, header, 8);

		source_ip[0] = header[0];
		source_ip[1] = header[1];
		source_ip[2] = header[2];
		source_ip[3] = header[3];
		*source_port = (header[4] << 8) | header[5];
		data_length = (header[6] << 8) | header[7];

		w5500_buf_read(read_pointer.u16 + 8, RX_BUFFER_ADDRESS, data, data_length);

		// Increment read pointer and update it
		read_pointer.u16 += (8 + data_length);
	} else if (status == 0x01) {
		// If TCP is used
		// Read rx_size bytes
		w5500_buf_read(read_pointer.u16, RX_BUFFER_ADDRESS, data, rx_size.u16);

		data_length = rx_size.u16;
		// Increment read pointer and update it
		read_pointer.u16 += rx_size.u16;
	}

	w5500_reg_write(W5500_SOCKET_RX_READ_PTR_0, SOCKET_ADDRESS, read_pointer.u8.msb);
	w5500_reg_write(W5500_SOCKET_RX_READ_PTR_1, SOCKET_ADDRESS, read_pointer.u8.lsb);

	// Send command that data has been received
	w5500_reg_write(W5500_SOCKET_COMMAND, SOCKET_ADDRESS, W5500_SOCKET_COMMAND_RECV);

	return (size_t) data_length;
}

/**
 * @brief  Close a socket
 * @note   
 * @param  socket: Socket to close
 * @retval None
 */
 */
void w5500_close(uint8_t socket) {
	uint8_t SOCKET_ADDRESS = W5500_SOCKET_0_REGISTER + (socket << 2);

	// Close the socket
	w5500_reg_write(W5500_SOCKET_COMMAND, SOCKET_ADDRESS, W5500_SOCKET_COMMAND_CLOSE);

	return;
}

/**
 * @brief  Read the Socket Mode register
 * @note   
 * @param  socket: Socket number
 * @param  status: Pointer to status
 * @retval None
 */
 */
void w5500_socket_mode_status(uint8_t socket, uint8_t* status) {
	uint8_t SOCKET_ADDRESS = W5500_SOCKET_0_REGISTER + (socket << 2);

	w5500_reg_read(W5500_SOCKET_MODE, SOCKET_ADDRESS, status);

	return;
}

/**
 * @brief  Read the Socket Status register
 * @note   
 * @param  socket: Socket number
 * @param  status: Pointer to status
 * @retval None
 */
 */
void w5500_socket_status(uint8_t socket, uint8_t* status) {
	uint8_t SOCKET_ADDRESS = W5500_SOCKET_0_REGISTER + (socket << 2);

	w5500_reg_read(W5500_SOCKET_STATUS, SOCKET_ADDRESS, status);

	return;
}
