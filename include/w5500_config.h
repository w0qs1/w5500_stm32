/*
 * w5500_config.h
 *
 *  Created on: Jun 28, 2025
 *      Author: mnsan
 */

#ifndef INC_W5500_CONFIG_H_
#define INC_W5500_CONFIG_H_

// STM32 HAL Related config
#define W5500_USE_STM32F0xx
//#define W5500_USE_STM32F1xx

// TCP config
// This is used as the number of retries taken to verify CONNECT, DISCONNECT, LISTEN in TCP mode from the socket status register
#define RETRY_STATUS_COUNT 		10
// This is the time taken (in ms) before reading the socket status register
#define TCP_COOLDOWN_TIME		1

// Socket config
// This is used as a cooldown time (in ms) before trying to close the socket again
#define SOCKET_CLOSE_COOLDOWN 	1

#endif /* INC_W5500_CONFIG_H_ */
