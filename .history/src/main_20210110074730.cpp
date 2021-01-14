#include <Arduino.h>
//#include <SPI.h>
#include <IonDB.h>
// #include <ir_Lego_PF_BitStreamEncoder.h>

// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>

// Define sensor pin
const int RECV_PIN = 4;

// how much serial data we expect before a newline
const unsigned int MAX_INPUT = 50;

// Create IR Send Object
IRsend irsend;

// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);

enum remote_control_codes
{
  /* names for main remote control buttons */
  left,
  right,
  up,
  down,
  enter,
  home,
  volume_up,
  volume_dow,
  red,
  blue,
  green,
  yellow
};

enum device_mode{
  CONFIGURING,
  RELAYING 
};

device_mode active_device_mode = RELAYING;

//Device list
const int FOXTEL_DEVICE = 1;
const int GOOGLE_DEVICE = 2;
const int SAMSUNG_DEVICE = 3;
const int SONY_DEVICE = 4;

int activeDevice = FOXTEL_DEVICE;

void setup() {

  // Serial Monitor @ 9600 baud
  Serial.begin(9600);
  // Enable the IR Receiver
  irrecv.enableIRIn();
  //irrecv.blink13(true);
}
Dictionary<String, unsigned long> *sender = new SkipList<String, unsigned long>(-1, key_type_numeric_signed, sizeof(int), sizeof(int), 7);


// here to process incoming serial data after a terminator received
void process_data (const char * data)
  {
  // for now just display it
  // (but you could compare it to some value, convert to an integer, etc.)
  Serial.println (data);
  }  // end of process_data
  

// Define variable to store last code received
unsigned long lastCode;

void displayConfigurationOptions(){
  Serial.println("0 - display configuration options");
  Serial.println("1 - create a remote");
  Serial.println("2 - select source remote");
  Serial.println("3 - select source remote");
}
void processConfig(String command){
  if(command.equals("1")){
    displayConfigurationOptions();
  }
}
String getSerialCommand(){
  String str = Serial.readString();
  str.replace("\n","");
  return str;
}


void printDecodeSignal(decode_results decodeResults) {
  //Serial.println(decodeResults);
  Serial.print("Decode Type ");
  Serial.print(decodeResults.decode_type);
  Serial.print(" ");
  Serial.print(decodeResults.value, HEX);
  Serial.print(" (");
  Serial.print(decodeResults.bits, DEC);
  Serial.println(" bits)");
}

void sendCode(int activeDevice, unsigned long hex_code) {
  String log = "Sending '";
  switch (activeDevice) {

    case FOXTEL_DEVICE:
      log = log + "FOXTEL_DEVICE ";
      irsend.sendNEC(hex_code, 32);
      break;

    case GOOGLE_DEVICE:
      log = log + "GOOGLE_DEVICE ";
      Serial.println( log + activeDevice + "'not mapped");
      break;

    case SAMSUNG_DEVICE:
      log = log + "SAMSUNG_DEVICE ";
      irsend.sendSAMSUNG(hex_code, 32);
      break;
    case SONY_DEVICE:
      log = log + "SONY_DEVICE ";
      irsend.sendSony(hex_code, 15);
      break;
  }
  Serial.println( log + "- active device: " + activeDevice + "' code:" + String(hex_code, HEX));

}
void sendCommand(){
  decode_results results;

  if (irrecv.decode(&results)) {

    if (results.value == 0xFFFFFFFF)
    {
      // If Repeat then use last code received
      results.value = lastCode;
    }

    printDecodeSignal(results);
    switch (results.value) {

      // codes

      //shutdown
//      case 0x540C:
//       case 0x99805850:
//      case 0x5B2B1241:
      case 0xFFA25D: // remote arduino
        sendCode(SAMSUNG_DEVICE, 0xE0E040BF);
        sendCode(SONY_DEVICE, 0x540C);
        sendCode(FOXTEL_DEVICE, 0x6804847B);
        break;

      case 0xFF18E7: //up arrow button
        Serial.println(" up arrow button");
        sendCode(activeDevice, 0x6804A857);
        break;

      case 0xFF4AB5:
        Serial.println("down arrow button");
        lastCode = results.value;
        sendCode(activeDevice, 0x68046897);
        break;

      case 0xFF10EF:
        Serial.println(" left arrow button");
        lastCode = results.value;
        sendCode(activeDevice, 0x6804E817);
        break;

      case 0xFF5AA5:
        Serial.println(" rigth arrow button");
        lastCode = results.value;
        sendCode(activeDevice, 0x680418E7);
        break;

      case 0xFF38C7:
        Serial.println("center button");
        lastCode = results.value;
        sendCode(activeDevice, 0x68049867);
        break;

      case 0x1FF52AD:
        Serial.println(" home button");
        lastCode = results.value;
        sendCode(activeDevice, 0x6804E21D);
        break;

      case 0xFF42BD:
        Serial.println(" retunr button");
        lastCode = results.value;
        sendCode(activeDevice, 0x680412ED);
        break;


      //devices
      case 0x600D:
      case 0x77C8F32F:
        activeDevice = FOXTEL_DEVICE;
        break;
      case 0x5F0C:
      case 0x60992C36:
        activeDevice = GOOGLE_DEVICE;
        break;

    }

    irrecv.enableIRIn();
    // Add a small delay before repeating
    delay(200);
  }
}
 
void loop() {
  //String log = "loop: ";
  //log.concat(active_device_mode);
  // Serial.println(log);

  if(active_device_mode == RELAYING){
    sendCommand();
  }else if(active_device_mode == CONFIGURING){
    String str = getSerialCommand();
    processConfig(str);
  }
  while (Serial.available () > 0){
    String str = getSerialCommand();
    Serial.print("Entering mode: ");
    Serial.println(str);    
    if(str.equals("CONFIGURING")){
      Serial.print("Entering mode CONFIGURING");
      active_device_mode = CONFIGURING;
      displayConfigurationOptions();
    }
  }

  delay(1000);

}