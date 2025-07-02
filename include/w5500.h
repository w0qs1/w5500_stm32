/*
 * w5500.h
 *
 *  Created on: Jun 28, 2025
 *      Author: mnsan
 */

#ifndef INC_W5500_H_
#define INC_W5500_H_

#include <stdint.h>
#include "w5500_config.h"

#if defined(W5500_USE_STM32F0xx)
#include "stm32f0xx_hal.h"
#elif defined(W5500_USE_STM32F1xx)
#include "stm32f1xx_hal.h"
#endif

#define W5500_OK	0x00U
#define W5500_ERR	0x01U

// Control
#define READ						(0 << 2)
#define WRITE						(1 << 2)

// This library uses only Variable Data Mode (VDM)

// Block Select Bits (BSB)
#define W5500_COMMON_REGISTER		0x00

#define W5500_SOCKET_0_REGISTER		0x01
#define W5500_SOCKET_0_TX_BUFFER	0x02
#define W5500_SOCKET_0_RX_BUFFER	0x03

#define W5500_SOCKET_1_REGISTER		0x05
#define W5500_SOCKET_1_TX_BUFFER	0x06
#define W5500_SOCKET_1_RX_BUFFER	0x07

#define W5500_SOCKET_2_REGISTER		0x09
#define W5500_SOCKET_2_TX_BUFFER	0x0A
#define W5500_SOCKET_2_RX_BUFFER	0x0B

#define W5500_SOCKET_3_REGISTER		0x0D
#define W5500_SOCKET_3_TX_BUFFER	0x0E
#define W5500_SOCKET_3_RX_BUFFER	0x0F

#define W5500_SOCKET_4_REGISTER		0x11
#define W5500_SOCKET_4_TX_BUFFER	0x12
#define W5500_SOCKET_4_RX_BUFFER	0x13

#define W5500_SOCKET_5_REGISTER		0x15
#define W5500_SOCKET_5_TX_BUFFER	0x16
#define W5500_SOCKET_5_RX_BUFFER	0x17

#define W5500_SOCKET_6_REGISTER		0x19
#define W5500_SOCKET_6_TX_BUFFER	0x1A
#define W5500_SOCKET_6_RX_BUFFER	0x1B

#define W5500_SOCKET_7_REGISTER		0x1D
#define W5500_SOCKET_7_TX_BUFFER	0x1E
#define W5500_SOCKET_7_RX_BUFFER	0x1F

// Common Register Block
#define W5500_MODE						0x0000

#define W5500_GATEWAY_ADDR_0			0x0001
#define W5500_GATEWAY_ADDR_1			0x0002
#define W5500_GATEWAY_ADDR_2			0x0003
#define W5500_GATEWAY_ADDR_3			0x0004

#define W5500_SUBNET_MASK_ADDR_0		0x0005
#define W5500_SUBNET_MASK_ADDR_1		0x0006
#define W5500_SUBNET_MASK_ADDR_2		0x0007
#define W5500_SUBNET_MASK_ADDR_3		0x0008

#define W5500_SOURCE_HARDWARE_ADDR_0	0x0009
#define W5500_SOURCE_HARDWARE_ADDR_1	0x000A
#define W5500_SOURCE_HARDWARE_ADDR_2	0x000B
#define W5500_SOURCE_HARDWARE_ADDR_3	0x000C
#define W5500_SOURCE_HARDWARE_ADDR_4	0x000D
#define W5500_SOURCE_HARDWARE_ADDR_5	0x000E

#define W5500_SOURCE_IP_ADDR_0			0x000F
#define W5500_SOURCE_IP_ADDR_1			0x0010
#define W5500_SOURCE_IP_ADDR_2			0x0011
#define W5500_SOURCE_IP_ADDR_3			0x0012

#define W5500_INT_LOW_LEVEL_TIM_0		0x0013
#define W5500_INT_LOW_LEVEL_TIM_1		0x0014

#define W5500_INTERRUPT					0x0015

#define	W5500_INTERRUPT_MASK			0x0016

#define W5500_SOCKETS_INTERRUPT			0x0017

#define W5500_SOCKETS_INTERRUPT_MASK 	0x0018

#define W5500_RETRY_TIME_0				0x0019
#define W5500_RETRY_TIME_1				0x001A

#define W5500_RETRY_COUNT				0x001B

#define W5500_PPP_LCP_REQUEST_TIMER		0x001C

#define W5500_PPP_LCP_MAGIC_NUMBER		0x001D

#define W5500_DEST_MAC_ADDR_0			0x001E
#define W5500_DEST_MAC_ADDR_1			0x001F
#define W5500_DEST_MAC_ADDR_2			0x0020
#define W5500_DEST_MAC_ADDR_3			0x0021
#define W5500_DEST_MAC_ADDR_4			0x0022
#define W5500_DEST_MAC_ADDR_5			0x0023

#define W5500_PPP_SESSION_ID_0			0x0024
#define W5500_PPP_SESSION_ID_1			0x0025

#define W5500_PPP_MAX_SEG_SIZE_0		0x0026
#define W5500_PPP_MAX_SEG_SIZE_1		0x0026

#define W5500_UNREACHABLE_IP_ADDR_0		0x0028
#define W5500_UNREACHABLE_IP_ADDR_1		0x0029
#define W5500_UNREACHABLE_IP_ADDR_2		0x002A
#define W5500_UNREACHABLE_IP_ADDR_3		0x002B

#define W5500_UNREACHABLE_PORT_0		0x002C
#define W5500_UNREACHABLE_PORT_1		0x002D

#define W5500_PHY_CONFIGURATION			0x002E

#define W5500_CHIP_VERSION				0x0039

// Socket Register Block
#define W5500_SOCKET_MODE				0x0000

#define W5500_SOCKET_COMMAND			0x0001

#define W5500_SOCKET_INTERRUPT			0x0002

#define W5500_SOCKET_STATUS				0x0003

#define W5500_SOCKET_SOURCE_PORT_0		0x0004
#define W5500_SOCKET_SOURCE_PORT_1		0x0005

#define W5500_SOCKET_DEST_HW_ADDR_0		0x0006
#define W5500_SOCKET_DEST_HW_ADDR_1		0x0007
#define W5500_SOCKET_DEST_HW_ADDR_2		0x0008
#define W5500_SOCKET_DEST_HW_ADDR_3		0x0009
#define W5500_SOCKET_DEST_HW_ADDR_4		0x000A
#define W5500_SOCKET_DEST_HW_ADDR_5		0x000B

#define W5500_SOCKET_DEST_IP_ADDR_0		0x000C
#define W5500_SOCKET_DEST_IP_ADDR_1		0x000D
#define W5500_SOCKET_DEST_IP_ADDR_2		0x000E
#define W5500_SOCKET_DEST_IP_ADDR_3		0x000F

#define W5500_SOCKET_DEST_PORT_0		0x0010
#define W5500_SOCKET_DEST_PORT_1		0x0011

#define W5500_SOCKET_MAX_SEG_SIZE_0		0x0012
#define W5500_SOCKET_MAX_SEG_SIZE_1		0x0013

#define W5500_SOCKET_IP_TOS				0x0015
#define W5500_SOCKET_IP_TTL				0x0016

#define W5500_SOCKET_RX_BUF_SIZE		0x001E

#define W5500_SOCKET_TX_BUF_SIZE		0x001F

#define W5500_SOCKET_TX_FREE_SIZE_0		0x0020
#define W5500_SOCKET_TX_FREE_SIZE_1		0x0021

#define W5500_SOCKET_TX_READ_PTR_0		0x0022
#define W5500_SOCKET_TX_READ_PTR_1		0x0023

#define W5500_SOCKET_TX_WRITE_PTR_0		0x0024
#define W5500_SOCKET_TX_WRITE_PTR_1		0x0025

#define W5500_SOCKET_RX_RECV_SIZE_0		0x0026
#define W5500_SOCKET_RX_RECV_SIZE_1		0x0027

#define W5500_SOCKET_RX_READ_PTR_0		0x0028
#define W5500_SOCKET_RX_READ_PTR_1		0x0029

#define W5500_SOCKET_RX_WRITE_PTR_0		0x002A
#define W5500_SOCKET_RX_WRITE_PTR_1		0x002B

#define W5500_SOCKET_INTERRUPT_MASK		0x002C

#define W5500_SOCKET_FRAG_OFF_IP_0		0x002D
#define W5500_SOCKET_FRAG_OFF_IP_1		0x002E

#define W5500_SOCKET_KEEP_ALIVE_TIMER	0x002F

// Common Registers Bit positions
// Mode register
#define W5500_COMMON_MODE_RST			7
#define W5500_COMMON_MODE_WOL			5
#define W5500_COMMON_MODE_PB			4
#define W5500_COMMON_MODE_PPPOE			3
#define W5500_COMMON_MODE_FARP			1

// Interrupt Register
#define W5500_COMMON_IR_CONFLICT		7
#define W5500_COMMON_IR_UNREACH			6
#define W5500_COMMON_IR_PPPOE			5
#define W5500_COMMON_IR_MP				4

// Interrupt Mask Register
#define W5500_COMMON_IM_CONFLICT		7
#define W5500_COMMON_IM_UNREACH			6
#define W5500_COMMON_IM_PPPOE			5
#define W5500_COMMON_IM_MP				4

// Socket Interrupt Register
#define W5500_COMMON_SIR_S7				7
#define W5500_COMMON_SIR_S6				6
#define W5500_COMMON_SIR_S5				5
#define W5500_COMMON_SIR_S4				4
#define W5500_COMMON_SIR_S3				3
#define W5500_COMMON_SIR_S2				2
#define W5500_COMMON_SIR_S1				1
#define W5500_COMMON_SIR_S0				0

// Socket Interrupt Mask Register
#define W5500_COMMON_SIM_S7				7
#define W5500_COMMON_SIM_S6				6
#define W5500_COMMON_SIM_S5				5
#define W5500_COMMON_SIM_S4				4
#define W5500_COMMON_SIM_S3				3
#define W5500_COMMON_SIM_S2				2
#define W5500_COMMON_SIM_S1				1
#define W5500_COMMON_SIM_S0				0

// PHY Configuration Register
#define W5500_COMMON_PHY_CFG_RST		7
#define W5500_COMMON_PHY_CFG_OPMD		6
#define W5500_COMMON_PHY_CFG_OPMDC5		5
#define W5500_COMMON_PHY_CFG_OPMDC4		4
#define W5500_COMMON_PHY_CFG_OPMDC3		3
#define W5500_COMMON_PHY_CFG_DPX		2
#define W5500_COMMON_PHY_CFG_SPD		1
#define W5500_COMMON_PHY_CFG_LNK		0

// Socket Registers Bit positions
// Socket Mode Register
#define W5500_SOCKET_MODE_MULTIMFEN		7
#define W5500_SOCKET_MODE_BCASTB		6
#define W5500_SOCKET_MODE_NDMCMMB		5
#define W5500_SOCKET_MODE_UCASTBMIP6B	4
#define W5500_SOCKET_MODE_P3			3
#define W5500_SOCKET_MODE_P2			2
#define W5500_SOCKET_MODE_P1			1
#define W5500_SOCKET_MODE_P0			0

// Socket Interrupt Register
#define W5500_SOCKET_IR_SEND_OK			4
#define W5500_SOCKET_IR_TIMEOUT			3
#define W5500_SOCKET_IR_RECV			2
#define W5500_SOCKET_IR_DISCON			1
#define W5500_SOCKET_IR_CON				0

// Socket Interrupt Mask Register
#define W5500_SOCKET_IM_SEND_OK			4
#define W5500_SOCKET_IM_TIMEOUT			3
#define W5500_SOCKET_IM_RECV			2
#define W5500_SOCKET_IM_DISCON			1
#define W5500_SOCKET_IM_CON				0

// Status values:
// Socket Status Register
#define W5500_SOCKET_SR_SOCK_CLOSED		0x00
#define W5500_SOCKET_SR_SOCK_INIT		0x13
#define W5500_SOCKET_SR_SOCK_LISTEN		0x14
#define W5500_SOCKET_SR_SOCK_ESTD		0x17
#define W5500_SOCKET_SR_SOCK_CLOSE_WAIT	0x1C
#define W5500_SOCKET_SR_SOCK_UDP		0x22
#define W5500_SOCKET_SR_SOCK_MACRAW		0x42

#define W5500_SOCKET_SR_SOCK_SYNSENT	0x15
#define W5500_SOCKET_SR_SOCK_SYNRECV	0x16
#define W5500_SOCKET_SR_SOCK_FIN_WAIT	0x18
#define W5500_SOCKET_SR_SOCK_CLOSING	0x1A
#define W5500_SOCKET_SR_SOCK_TIME_WAIT	0x1B
#define W5500_SOCKET_SR_SOCK_LAST_ACK	0x1D

// Commands:
// Socket Command Register
#define W5500_SOCKET_COMMAND_OPEN		0x01
#define W5500_SOCKET_COMMAND_LISTEN		0x02
#define W5500_SOCKET_COMMAND_CONNECT	0x04
#define W5500_SOCKET_COMMAND_DISCON		0x08
#define W5500_SOCKET_COMMAND_CLOSE		0x10
#define W5500_SOCKET_COMMAND_SEND		0x20
#define W5500_SOCKET_COMMAND_SEND_MAC	0x21
#define W5500_SOCKET_COMMAND_SEND_KEEP	0x22
#define W5500_SOCKET_COMMAND_RECV		0x40

typedef union {
	uint16_t u16;
	struct {
		uint8_t lsb, msb;	// Order is important here. Little endian is used here
	} u8;
} uint16_be_t;

void w5500_srand(uint32_t arg_seed);
uint32_t w5500_rand(void);

void w5500_reg_read(uint16_t offset_address, uint8_t bsb, uint8_t* data);
void w5500_reg_write(uint16_t offset_address, uint8_t bsb, uint8_t data);

void w5500_buf_read(uint16_t offset_address, uint8_t bsb, uint8_t* data, size_t len);
void w5500_buf_write(uint16_t offset_address, uint8_t bsb, uint8_t* data, size_t len);

void w5500_gpio_init(GPIO_TypeDef *In_CS_PORT, uint16_t In_CS_PIN, SPI_HandleTypeDef* In_SPI_Handle, GPIO_TypeDef *In_W5500_RESET_PORT, uint16_t In_W5500_RESET_PIN);
void w5500_reset();
uint8_t w5500_setup(uint8_t* mac_address);

void w5500_static_ip(uint8_t* source_ip_address, uint8_t *gateway_ip_address, uint8_t* subnet_mask);

void w5500_link_status(uint8_t* status);
#endif /* INC_W5500_H_ */
