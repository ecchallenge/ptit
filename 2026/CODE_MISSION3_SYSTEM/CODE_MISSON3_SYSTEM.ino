#include "BLEDevice.h"
#include <ESP32Servo.h>

#define LED_PIN 8
#define RECEIVE_LAZE1 20
#define RECEIVE_LAZE2 6
#define RECEIVE_LAZE3 1
#define SERVO1_PIN 21
#define SERVO2_PIN 5
#define SERVO3_PIN 0
Servo servo1;
Servo servo2;
Servo servo3;
int check = 0;
int read1;
int read2;
int read3;
int read4;
int read5;
int read6;

static BLEUUID serviceUUID("0000ffe0-0000-1000-8000-00805f9b34fb");
static BLEUUID characteristicUUID("0000ffe1-0000-1000-8000-00805f9b34fb");

static boolean doConnect = false;
static boolean connected = false;

static BLEAddress *pServerAddress;
static BLERemoteCharacteristic* pRemoteCharacteristic;
BLEClient* pClient;

class MyClientCallback : public BLEClientCallbacks {
public:
  // Override phương thức onConnect nếu nó là pure virtual trong lớp BLEClientCallbacks
  void onConnect(BLEClient* pClient) override {
    Serial.println("Connected to server");
  }

  // Override phương thức onDisconnect như đã có
  void onDisconnect(BLEClient* pClient) override {
    Serial.println("Disconnected from server");
    connected = false;
    doConnect = false;
  }
};

bool connectToServer(BLEAddress pAddress) {
  pClient = BLEDevice::createClient();
  pClient->setClientCallbacks(new MyClientCallback());

  pClient->connect(pAddress);
  
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    return false;
  }

  pRemoteCharacteristic = pRemoteService->getCharacteristic(characteristicUUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.print("Failed to find our characteristic UUID");
    return false;
  }
  Serial.println("Found our characteristic");

  pRemoteCharacteristic->registerForNotify(notifyCallback);
  return true;
}

bool checkLaze1(){
  read1 = digitalRead(20);
  delay(90);
  read2 = digitalRead(20);
  if(read1 == 0 && read2 == 0){
    return true;
  }
  else{
    return false;
  }
}

bool checkLaze2(){
  read3 = digitalRead(6);
  delay(90);
  read4 = digitalRead(6);
  if(read3 == 0 && read4 == 0){
    return true;
  }
  else{
    return false;
  }
}

bool checkLaze3(){
  read5 = digitalRead(1);
  delay(90);
  read6 = digitalRead(1);
  if(read5 == 0 && read6 == 0){
    return true;
  }
  else{
    return false;
  }
}


// void turnServo1(int angle){
//   for(int posDegrees = 0; posDegrees <= angle; posDegrees+=10) {
//     servo1.write(posDegrees);
//     delay(5);
//   }
// }
// void turnServo2(int angle){
//   for(int posDegrees = 180; posDegrees >= angle; posDegrees-=10) {
//     servo2.write(posDegrees);
//     delay(5);
//   }
// }
// void turnServo3(int angle){
//   for(int posDegrees = 180; posDegrees >= angle; posDegrees-=10) {
//     servo3.write(posDegrees);
//     delay(5);
//   }
// }

static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  String receivedData = "";
  
  for (size_t i = 0; i < length; i++) {  // Không bỏ ký tự cuối cùng
    receivedData += (char)pData[i];
  }

  receivedData.trim(); // Loại bỏ khoảng trắng và ký tự xuống dòng nếu có

  Serial.print("Received data: ");
  Serial.println(receivedData);
  delay(500);

  if (receivedData == "shoot") {
    check++;
    Serial.println(check);
    
    if (checkLaze1()  && check <= 15){
      Serial.println("shoot target 1 completed");
      // turnServo1(80);
      servo1.write(100);
    }if (checkLaze2()  && check <= 15){
      Serial.println("shoot target 2 completed");
      // turnServo2(105);
      servo2.write(100);
    }if (checkLaze3()  && check <= 15){
      Serial.println("shoot target 3 completed");
      // turnServo3(105);
      servo3.write(80);
    }
    
    else{
      Serial.println("shoot failed");
    }
  }
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {
      advertisedDevice.getScan()->stop();
      pServerAddress = new BLEAddress(advertisedDevice.getAddress());
      doConnect = true;
      Serial.println("Device found. Connecting!");
    }
  }
};

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  pinMode(RECEIVE_LAZE1, INPUT);
  pinMode(RECEIVE_LAZE2, INPUT);
  pinMode(RECEIVE_LAZE3, INPUT);
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo1.write(180);
  servo2.write(180);
  servo3.write(0);
  // turnServo1(0);
  // turnServo2(180);
  // turnServo3(180);

  Serial.println("Starting BLE Client application...");
  BLEDevice::init("");

  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);
}

void loop() {
  if (doConnect){
    if (connectToServer(*pServerAddress)){
      Serial.println("We are now connected to the BLE Server.");
      connected = true;
    } else{
      Serial.println("Failed to connect to the server.");
    }
  }
  else{
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->start(30);
  }
  if (connected) digitalWrite(LED_PIN, LOW);
  else           digitalWrite(LED_PIN, HIGH);
}