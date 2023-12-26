
# CAN Bus Tutorial and Resources

This repository contains information and tutorials for working with the CAN bus using Arduino, along with a datasheet for a 3.3KW charger.

## Tutorials and Documentation

- [Arduino CAN Bus Tutorial](https://docs.arduino.cc/tutorials/uno-r4-minima/can)
- [GitHub Shield Library](https://seeeddoc.github.io/CAN-BUS_Shield/)
- [CAN Bus Shield Tutorial on Instructables](https://www.instructables.com/Seeed-Studio-CAN-BUS-V20-Hacking-Getting-Started/)

## Charger Datasheet

- [3.3KW Charger Overview](https://www.longrunobc.com/obc-q2-3-3kw-dc48-440v-10-42a-broad-voltage-with-can-stackable-smart-charger-product/)
- [3.3KW Charger Datasheet (PDF)](https://www.longrunobc.com/uploads/DCNE-Q2-3.3-6.6kw-charger-manual0510.pdf)

![Protocol](img/chart.png)

When the data is retrieved it will dump it into the following HEX format.
ID, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7, BIT8
The ID usually represents a Node within your vehicle.
Let's make a simple example. (The below is made up and not real, just an example)
Air Conditioning Node ID= 0x402
TURN AIRCON OFF = 13
TURN AIRCON ON = 14
SET AIRCON BLOWER TO LOW = 7C
SET AIRCON BLOWER TO MEDIUM 8C
SET AIRCON BLOWER TO HIGH 9C
So if we turn on the Aircon and set it on medium the message will look like this
0x402, 13, 8C
the same goes for other nodes, example Central Locking
Central Locking ID= 0x503
LOCK all doors = 14
So if you press the button to lock all doors the message will look like this
0x502, 14
You can try the following messages. Load the send examples from the Arduino examples menu and change were relevant.
Engage Rear Locker.: CAN.sendMsgBuf(0x2B0, 0, 4 ,stmp);
Left Blinker On: CAN.sendMsgBuf(0x2A8, 0, 6 ,stmp);
Right Blinker On: CAN.sendMsgBuf(0x2A8, 0, 6 ,stmp);
ESP On/OFF: CAN.sendMsgBuf(0x2B0, 0, 4 ,stmp);
