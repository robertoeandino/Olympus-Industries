#pragma once

#include <SPI.h>

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;

#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

#define CHARGER_STATS_MSG_ID          (0x18FF50E5)
#define CHARGER_CONTROL_MSG_ID        (0x1806E5F4)

// Does not exist yet
#define INVERTER_STATS_MSG_ID         (0xFFFFFFFF)

#define CHARGER_CONTROL_TX_MS	      (1000)

typedef charger_stats_struct {
	float output_voltage;
	float output_current;
	char status_flag;
	int temp;
} charger_stats_t;

typedef inverter_stats_struct {
	float motor_voltage;
	float motor_temp;
	float motor_current;
} motor_stats_t;


typedef can_packet_struct {
	uint8_t data[8];
	uint8_t len;
	uint32_t id;
} can_packet_t;


void can_tx(can_packet_t packet);
void can_rx();
can_packet_t form_charger_control_packet(
					float output_voltage,
					float output_current,
					bool enabled,
					bool charging
					);

