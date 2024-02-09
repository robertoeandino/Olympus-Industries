#include <SPI.h>

#include "CAN.h"

float charger_output_voltage;
float charger_temperature;

void setup() {
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_250KBPS)) {             // init can bus : baudrate = 250k
        Serial.println("CAN init fail, retry...");
        delay(100);
    }
    Serial.println("CAN init ok!");
}


void loop() {
	int last_charger_CAN_tx_ms = 0;

	bool charger_enabled = true;

	if (CAN_MSGAVAIL == CAN.checkReceive()) {         // check if data coming
		can_rx();
	}

	if (millis() > last_charger_CAN_tx_ms + CHARGER_CONTROL_TX_MS) {
		can_tx(form_charger_control_packet(
					126,
					50,
					charger_enabled,
					true);
		last_charger_CAN_tx_ms = millis();
	}
    
	if (charger_output_voltage >= MAX_CHARGER_OUTPUT_VOLTAGE ||
		charger_temperature >= MAX_CHARGER_TEMPERATURE) {
		charger_enabled = false;
	}

}

/*********************************************************************************************************
    END FILE
*********************************************************************************************************/qq
