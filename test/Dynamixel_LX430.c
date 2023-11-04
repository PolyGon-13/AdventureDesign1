#include <DynamixelShield.h>

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
#include <SoftwareSerial.h>
SoftwareSerial soft_serial(10, 11); // DYNAMIXELShield UART RX/TX
#define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
#define DEBUG_SERIAL SerialUSB
#else
#define DEBUG_SERIAL Serial
#endif


const uint8_t DXL_ID1 = 0;
const uint8_t DXL_ID2 = 1;
const uint8_t DXL_ID3 = 3;
const uint8_t DXL_ID4 = 4;
const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl_1;
DynamixelShield dxl_2;
DynamixelShield dxl_3;
DynamixelShield dxl_4;

void setup() {
  DEBUG_SERIAL.begin(115200);
  dxl_1.begin(57600);
  dxl_2.begin(57600);
  dxl_3.begin(57600);
  dxl_4.begin(57600);

  dxl_1.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl_2.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl_3.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl_4.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  dxl_1.ping(DXL_ID1);
  dxl_2.ping(DXL_ID2);
  dxl_3.ping(DXL_ID3);
  dxl_4.ping(DXL_ID4);

  dxl_1.torqueOff(DXL_ID1);
  dxl_1.setOperatingMode(DXL_ID1, OP_VELOCITY);
  dxl_1.torqueOn(DXL_ID1);

  dxl_2.torqueOff(DXL_ID2);
  dxl_2.setOperatingMode(DXL_ID2, OP_VELOCITY);
  dxl_2.torqueOn(DXL_ID2);

  dxl_3.torqueOff(DXL_ID3);
  dxl_3.setOperatingMode(DXL_ID3, OP_VELOCITY);
  dxl_3.torqueOn(DXL_ID3);

  dxl_4.torqueOff(DXL_ID4);
  dxl_4.setOperatingMode(DXL_ID4, OP_VELOCITY);
  dxl_4.torqueOn(DXL_ID4);
}

void loop() {
  dxl_1.setGoalVelocity(DXL_ID1, 100);
  dxl_2.setGoalVelocity(DXL_ID2, 100);
  dxl_3.setGoalVelocity(DXL_ID3, 100);
  dxl_4.setGoalVelocity(DXL_ID4, 100);

  delay(10000);

  dxl_1.setGoalVelocity(DXL_ID1, 0);
  dxl_2.setGoalVelocity(DXL_ID2, 0);
  dxl_3.setGoalVelocity(DXL_ID3, 0);
  dxl_4.setGoalVelocity(DXL_ID4, 0);

  delay(1000);
}
