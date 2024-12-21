#include <SCServo.h>

// Servo setup
SMS_STS st;
#define S_RXD 18  // RX pin for servo communication
#define S_TXD 19  // TX pin for servo communication

void setup() {
  Serial.begin(115200);
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
  st.pSerial = &Serial1;

  Serial.println("Scanning for Servo IDs...");
  
  for (int id = 1; id <= 254; id++) { // Scan possible IDs
    int position = st.ReadPos(id); // Try to read position
    if (position != -1) { // If the servo responds
      Serial.print("Servo detected at ID: ");
      Serial.println(id);
    }
  }

  Serial.println("Scan complete.");
}

void loop() {
  // Do nothing
}
