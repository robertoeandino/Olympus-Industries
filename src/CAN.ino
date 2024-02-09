#include "CAN.h"
#include "stdint.h"

charger_stats_t decode_charger_stats_msg(can_packet_t packet)
{
	charger_stats_t stats;
	stats.output_current = ((float)((int)packet.data[2] << 8 | packet.data[3])) * 0.1;
	stats.output_voltage = ((float)(packet.data[0] << 8 | packet.data[1])) * 0.1;
	stats.status_flag = packet.data[4];
	stats.temp = packet.data[5] - 100;

	return stats;
}

void can_rx()
{	
	static can_packet_t packet;
	
        CAN.readMsgBuf(&packet.len, packet.buf);
	packet.id = CAN.getCanId();


	switch (canId) {
		case CHARGER_STATS_MSG_ID:
			charger_stats_t charger_stats = decode_charger_stats_msg(packet);
			Serial.println("Output current: %f\n", charger_stats.output_current);
			//Serial.println("Output current: %f\n", charger_stats.output_current);

			charger_output_voltage = charger_stats.output_voltage;	
			charger_temperature = charger_stats.temp;
			//check_charger_status(charger_stats.status_flag); // checks status flag, alerts user if any errors
			break;
		case INVERTER_STATS_MSG_ID:
			// decode it
			break;
		default:
			Serial.println("Unknown CAN ID: 0x%X\n", canId);
	}

        Serial.println("-----------------------------");
        Serial.print("Get data from ID: 0x");
        Serial.println(canId, HEX);

        for (int i = 0; i < len; i++) { // print the data
            Serial.print(buf[i], HEX);
            Serial.print("\t");
        }
        Serial.println();
}

can_packet_t form_charger_control_packet(
					float output_voltage,
					float output_current,
					bool enabled,
					bool charging
					)
{
	can_packet_t packet;
	packet.len = 8;
	packet.id = CHARGER_CONTROL_MSG_ID;
	
	output_voltage *= 10;
	int output_voltage = (int)output_voltage;
	packet.data[0] = output_voltage >> 8;
	packet.data[1] = output_voltage & 0xFF;

	output_current*= 10;
	int output_current = (int)output_current;
	packet.data[2] = output_current >> 8;
	packet.data[3] = output_current & 0xFF;

	packet.data[4] = !enabled;
	packet.data[5] = !charging;

	return packet;
}

void can_tx(can_packet_t packet)
{
	CAN.sendMsgBuf(packet.id, 0, packet.len, packet.data);
}
