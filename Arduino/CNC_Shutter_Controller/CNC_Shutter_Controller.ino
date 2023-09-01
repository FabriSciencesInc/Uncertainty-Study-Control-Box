// PRECISION STUDY iPhone/Shark Compatability Module
/// this module converts the output signal of the Shark HD520 control box to an iPhone-readable AUX signal for photo capture.
/// the below code is deployed in the first Wound^3 precision study. 

void setup() {
  
  // arduino and VFD default baud rate for serial communication
  Serial.begin(9600);
  
  //DE,RE Controling pin of RS-485
  pinMode(7, OUTPUT);
  //DE,RE = 0, set RS485 module to listening mode
  digitalWrite(7,LOW);
  
  //pin 8 set as output for relay
  pinMode(8, OUTPUT);
  //pin 12 set as output for LED
  pinMode(12, OUTPUT);

}

void loop() {

    // This example will listen for messages and try to extract spindle speed
    // The exact parsing depends on the protocol/format used by the HD520 for VFD control.

    if (Serial.available()) {
        String message = Serial.readString();  // Read the incoming data as a string

        // Here, you would parse the message to extract the spindle speed command
        // The specifics of this parsing depend on the exact message format
        if (message.indexOf("SPEED_COMMAND_IDENTIFIER") >= 0) {  // Replace SPEED_COMMAND_IDENTIFIER with the actual identifier or pattern for speed commands
            
            // Fire relay and output LED
            Serial.println("Firing relay...")
            digitalWrite(8, HIGH);
            digitalWrite(12, HIGH);
            
            // Pause to let photo capture commence
            delay(200);

            // Close relay and turn off LED
            Serial.println("Closing relay...")
            digitalWrite(8, LOW);
            digitalWrite(12, LOW);

        }
    }

}