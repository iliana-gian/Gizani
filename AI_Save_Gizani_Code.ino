/*Ανοίγουμε την εφαρμογή "SERIAL BLUETOOTH TERMINAL" για να μπορέσουμε να στείλουμε μηνύματα.
  Όταν εντοπιστεί ψάρι, εχθρικό προς το Γκιζάνι, γίνεται αποστολή του μηνύματος "HELP" στην συσκευή που έχουμε συνδέσει μέσω Bluetooth.
*/

//#include <DFRobot_HuskyLens.h>
//#include <HUSKYLENS.h>
//#include <HUSKYLENSMindPlus.h>
//#include <HuskyLensProtocolCore.h>


#include "HUSKYLENS.h"
#include "Arduino.h"                //BLUETOOTH
#include "SoftwareSerial.h"        //BLUETOOTH
#include "Wire.h"

HUSKYLENS huskylens;
///////////////////////////////////////////////////////////////////

const byte rxPin = 9;                     //BLUETOOTH
const byte txPin = 8;                     //BLUETOOTH
SoftwareSerial BTSerial(rxPin, txPin);    // RX TX BLUETOOTH

String messageBuffer = "";                //BLUETOOTH
String message = "";                      //BLUETOOTH
char data = ' ';                          //BLUETOOTH

// Main program

void setup() {
    Serial.begin(9600);
    
    Wire.begin();
      //BLUETOOTH
  // define pin modes for tx, rx:
    pinMode(rxPin, INPUT);                 
    pinMode(txPin, OUTPUT);
    BTSerial.begin(9600);                 
 
    // Initialize HuskyLens
    while (!huskylens.begin(Wire)) {
        Serial.println("Begin failed!");
        delay(100);
    }
}

void loop() {

    // Request data from HuskyLens
    
    if (!huskylens.request()) {
        Serial.println("Fail to request data!");
    } else {
        // Check if object is learned and available
        if (huskylens.isLearned()) {
            for (int i = 0; i < huskylens.countBlocks(); i++) {
                HUSKYLENSResult result = huskylens.getBlock(i);
               
                // If the object ID is 1, send HELP
                if (result.ID == 1) {
                    BTSerial.write(" ΚΥΠΡΙΝΟΣ ");                  
                 
                } 
            }
        }
    }
    delay(100); 
}

