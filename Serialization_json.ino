#include <HardwareSerial.h>
#include <ArduinoJson.h>
#define UART_RX_PIN 16
#define UART_TX_PIN 17
#define BAUD_RATE 115200

HardwareSerial SerialUART(1);// UART object
//Declaration

String readString;
//int startTime = 0;
String id;
String Station;
String Distance;
String Speed ;
int ind1;
int ind2;
int ind3;
int ind4;

void setup() {
  Serial.begin(115200); // Set the baud rate for the serial monitor
  //SerialUART.begin(BAUD_RATE, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN); // Initialize UART with specified baud rate and pins
}

void loop() {
  if (Serial.available()) {
    String receivedData = Serial.readString();
    Serial.println("Received Data : " + receivedData);
    // receive data will split
    ind1 = receivedData.indexOf(',');
    id = receivedData.substring(0, ind1);
    ind2 = receivedData.indexOf(',', ind1 + 1); //finds location of second ,
    Station = receivedData.substring(ind1 + 1, ind2 + 1);
    ind3 = receivedData.indexOf(',', ind2 + 1);
    Distance = receivedData.substring(ind2 + 1, ind3 + 1);
    ind4 = receivedData.indexOf(',', ind3 + 1);
    Speed = receivedData.substring(ind3 + 1); //captures remain part of data after last ,
    Serial.println("id:" + id );
    Serial.println("station:" + Station);
    Serial.println("Distance in cm:" + Distance);
    Serial.println("Speed per secs:" + Speed);

    readString = ""; // string empty
  }

  // Serialization
  StaticJsonDocument<200> outputJson;
  outputJson["id"] = id.toInt();
  outputJson["Station"] = Station.toInt(); // data convert string ro int
  outputJson["Distance in cm"] = Distance.toInt();
  outputJson["Speed per secs"] = Speed.toInt();

  // like this will print
  // {
  //   "Pod id": 1,
  //   "Speed": 100
  // }
  
  char op [128]; // op = output
  int b = serializeJson(outputJson, op);
  Serial.println(op); 
  Serial.print("bytes = ");
  Serial.println(b, DEC);// to calculate the bytes will put in the[]

  delay(4000);
}
