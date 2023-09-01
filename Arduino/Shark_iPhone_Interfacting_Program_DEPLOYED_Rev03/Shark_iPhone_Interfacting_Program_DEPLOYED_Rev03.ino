
// Message 2 is the only message that should actually be read to fire the machine.
// Message 1 is coded to prevent the CNC error checking from preventing the CNC spindle speed changing
// twice in a row. In other words, Message 1 flips the mode in a state-machine like architecture. 

// Message 1 is S17000
// Message 2 is S18000
const uint8_t MESSAGE1[] = {0x3A, 0x30, 0x31, 0x30, 0x35, 0x30, 0x32, 0x36, 0x45, 0x41, 0x45, 0x44, 0x43};
const uint8_t MESSAGE2[] = {0x3A, 0x30, 0x31, 0x30, 0x35, 0x30, 0x32, 0x37, 0x35, 0x33, 0x31, 0x35, 0x32};

// Mode 'false' is ready to capture a photo
// Mode 'true' is currently capturing photo
bool mode = false;

#define BUFFER_SIZE sizeof(MESSAGE1)
uint8_t buffer[BUFFER_SIZE];
uint8_t bufferIndex = 0;

void setup() {
  Serial.begin(9600);

  pinMode(7, OUTPUT);  // DE,RE Control pin of RS-485
  digitalWrite(7, LOW);  // Set RS485 module to listening mode

  pinMode(8, OUTPUT);  // Pin for relay
  pinMode(12, OUTPUT); // Pin for LED

}

void loop() {
  while (Serial.available()) {
    uint8_t byteRead = Serial.read();

    // Shift the buffer and add the new byte to the end
    for(uint8_t i = 0; i < BUFFER_SIZE - 1; i++) {
      buffer[i] = buffer[i + 1];
    }
    buffer[BUFFER_SIZE - 1] = byteRead;

    // Check the buffer for the message to fire
    if(memcmp(buffer, MESSAGE2, BUFFER_SIZE) == 0 && !mode) {

      // Change the mode to firing photo capture
      mode = true;

      // Illuminate LED
      digitalWrite(12, HIGH);
      
      // Fire caputre command 3 times for redundancy
      digitalWrite(8, HIGH);
      delay(33);
      digitalWrite(8, LOW);
      delay(170);
      digitalWrite(8, HIGH);
      delay(33);
      digitalWrite(8, LOW);
      delay(170);
      digitalWrite(8, HIGH);
      delay(33);
      digitalWrite(8, LOW);
 
      // Dim LED
      digitalWrite(12, LOW);

    }

    // Check the buffer for the reset message
    if(memcmp(buffer, MESSAGE1, BUFFER_SIZE) == 0 && mode) {
      
      // Change the mode to awaiting photo capture
      mode = false;

    }

  }
}