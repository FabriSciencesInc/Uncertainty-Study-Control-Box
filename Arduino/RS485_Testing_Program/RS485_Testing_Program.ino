// PRECISION STUDY Shark/VFD listening function
/// this function reads and prints the messages sent between the VFD and Shark so
/// relivant messages can be analyzed and reproduced.

#include <SoftwareSerial.h>

// Define RS485 Module pins
#define RO_PIN 0       // Receiver Output from RS485 module
#define DI_PIN 1       // Driver Input to RS485 module
#define DE_RE_PIN 7   // Driver Enable and Receiver Enable combined pin

SoftwareSerial rs485Serial(RO_PIN, DI_PIN);  // RX, TX

void setup() {
  // Start the built-in serial port, used for debugging and viewing received data
  Serial.begin(9600);
  while (!Serial);  // Wait for Serial Monitor/terminal to open

  // Start the RS485 communication port
  rs485Serial.begin(9600);

  pinMode(DE_RE_PIN, OUTPUT);
  digitalWrite(DE_RE_PIN, LOW);  // Set module to listen
}

void loop() {
  // Read from RS485, send to Serial Monitor
  while (rs485Serial.available()) {
    char c = rs485Serial.read();
    Serial.print(c, HEX);  // Print in hexadecimal format
    Serial.print(" ");     // Add space for clarity
  }

  // // Optional: add delay to reduce loop frequency, if necessary
  // delay(10);
}