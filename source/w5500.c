/*
 * w5500.c
 *
 *  Created on: Jun 28, 2025
 *      Author: mnsan
 */

#include "w5500.h"

// SPI Stuff below:
GPIO_TypeDef* 		CS_PORT;
uint16_t			CS_PIN;
SPI_HandleTypeDef* 	SPI_Handle;

// Reset Pin below:
GPIO_TypeDef*		W5500_RESET_PORT;
uint16_t			W5500_RESET_PIN;

// Seed for PRNG
static uint32_t seed = 0x12345678;

void w5500_srand(uint32_t arg_seed) {
	seed = arg_seed;

	return;
}

uint32_t w5500_rand(void) {
	seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;

	return seed;
}

void w5500_reg_read(uint16_t offset_address, uint8_t bsb, uint8_t* data) {
	uint8_t packet[3] = {(offset_address & 0xFF00) >> 8, offset_address & 0xFF, (bsb << 3) | READ};

	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);

	// transmit address and control
	HAL_SPI_Transmit(SPI_Handle, packet, 3, HAL_MAX_DELAY);

	HAL_SPI_Receive(SPI_Handle, data, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);

	return;
}

void w5500_reg_write(uint16_t offset_address, uint8_t bsb, uint8_t data) {
	uint8_t packet[4] = {(offset_address & 0xFF00) >> 8, offset_address & 0xFF, (bsb << 3) | WRITE, data};

	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);

	HAL_SPI_Transmit(SPI_Handle, packet, 4, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);

	return;
}

void w5500_buf_read(uint16_t offset_address, uint8_t bsb, uint8_t* data, size_t len) {
	uint8_t packet[3] = {(offset_address & 0xFF00) >> 8, offset_address & 0xFF, (bsb << 3) | READ};

	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);

	HAL_SPI_Transmit(SPI_Handle, packet, 3, HAL_MAX_DELAY);

	HAL_SPI_Receive(SPI_Handle, data, len, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);

	return;
}

void w5500_buf_write(uint16_t offset_address, uint8_t bsb, uint8_t* data, size_t len) {
	uint8_t packet[3] = {(offset_address & 0xFF00) >> 8, offset_address & 0xFF, (bsb << 3) | WRITE};

	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);

	HAL_SPI_Transmit(SPI_Handle, packet, 3, HAL_MAX_DELAY);

	HAL_SPI_Transmit(SPI_Handle, data, len, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);

	return;
}

void w5500_gpio_init(GPIO_TypeDef* In_CS_PORT, uint16_t In_CS_PIN, SPI_HandleTypeDef* In_SPI_Handle, GPIO_TypeDef* In_W5500_RESET_PORT, uint16_t In_W5500_RESET_PIN) {
	CS_PORT 			= In_CS_PORT;
	CS_PIN 				= In_CS_PIN;
	SPI_Handle			= In_SPI_Handle;
	W5500_RESET_PORT	= In_W5500_RESET_PORT;
	W5500_RESET_PIN		= In_W5500_RESET_PIN;

	return;
}

void w5500_reset() {
	HAL_GPIO_WritePin(W5500_RESET_PORT, W5500_RESET_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(W5500_RESET_PORT, W5500_RESET_PIN, GPIO_PIN_SET);

	// Wait for 2ms after reset
	HAL_Delay(2);

	return;
}

uint8_t w5500_setup(uint8_t* mac_address) {

	// Read CHIP version
	uint8_t data;
	w5500_reg_read(W5500_CHIP_VERSION, W5500_COMMON_REGISTER, &data);

	// If Chip version is not 0x04, it indicates some issue with the chip or with the connections
	if (data != 0x04) {
		return W5500_ERR;
	}

	// Write MAC Address
	w5500_reg_write(W5500_SOURCE_HARDWARE_ADDR_0, W5500_COMMON_REGISTER, *(mac_address + 0));
	w5500_reg_write(W5500_SOURCE_HARDWARE_ADDR_1, W5500_COMMON_REGISTER, *(mac_address + 1));
	w5500_reg_write(W5500_SOURCE_HARDWARE_ADDR_2, W5500_COMMON_REGISTER, *(mac_address + 2));
	w5500_reg_write(W5500_SOURCE_HARDWARE_ADDR_3, W5500_COMMON_REGISTER, *(mac_address + 3));
	w5500_reg_write(W5500_SOURCE_HARDWARE_ADDR_4, W5500_COMMON_REGISTER, *(mac_address + 4));
	w5500_reg_write(W5500_SOURCE_HARDWARE_ADDR_5, W5500_COMMON_REGISTER, *(mac_address + 5));

	w5500_srand(HAL_GetUIDw0() ^ HAL_GetUIDw1() ^ HAL_GetUIDw2());

	return W5500_OK;
}

void w5500_static_ip(uint8_t* source_ip_address, uint8_t *gateway_ip_address, uint8_t* subnet_mask) {
	// Write Source IP Address
	w5500_reg_write(W5500_SOURCE_IP_ADDR_0, W5500_COMMON_REGISTER, *(source_ip_address + 0));
	w5500_reg_write(W5500_SOURCE_IP_ADDR_1, W5500_COMMON_REGISTER, *(source_ip_address + 1));
	w5500_reg_write(W5500_SOURCE_IP_ADDR_2, W5500_COMMON_REGISTER, *(source_ip_address + 2));
	w5500_reg_write(W5500_SOURCE_IP_ADDR_3, W5500_COMMON_REGISTER, *(source_ip_address + 3));

	// Write Gateway IP Address
	w5500_reg_write(W5500_GATEWAY_ADDR_0, W5500_COMMON_REGISTER, *(gateway_ip_address + 0));
	w5500_reg_write(W5500_GATEWAY_ADDR_1, W5500_COMMON_REGISTER, *(gateway_ip_address + 1));
	w5500_reg_write(W5500_GATEWAY_ADDR_2, W5500_COMMON_REGISTER, *(gateway_ip_address + 2));
	w5500_reg_write(W5500_GATEWAY_ADDR_3, W5500_COMMON_REGISTER, *(gateway_ip_address + 3));

	// Write Subnet Mask
	w5500_reg_write(W5500_SUBNET_MASK_ADDR_0, W5500_COMMON_REGISTER, *(subnet_mask + 0));
	w5500_reg_write(W5500_SUBNET_MASK_ADDR_1, W5500_COMMON_REGISTER, *(subnet_mask + 1));
	w5500_reg_write(W5500_SUBNET_MASK_ADDR_2, W5500_COMMON_REGISTER, *(subnet_mask + 2));
	w5500_reg_write(W5500_SUBNET_MASK_ADDR_3, W5500_COMMON_REGISTER, *(subnet_mask + 3));

	return;
}

void w5500_link_status(uint8_t* status) {
	w5500_reg_read(W5500_PHY_CONFIGURATION, W5500_COMMON_REGISTER, status);
}
