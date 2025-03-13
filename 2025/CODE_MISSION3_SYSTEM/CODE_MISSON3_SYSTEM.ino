#include "BLEDevice.h"
#include <ESP32Servo.h>

#define LED_PIN 8
#define RECEIVE_LAZE1 2
#define RECEIVE_LAZE2 1
#define RECEIVE_LAZE3 0
#define BUZZ_PIN 6
#define SERVO1_PIN 7
#define SERVO2_PIN 3
#define SERVO3_PIN 4

Servo servo1, servo2, servo3;
Servo servos[] = {servo1, servo2, servo3};
int lazePins[] = {RECEIVE_LAZE1, RECEIVE_LAZE2, RECEIVE_LAZE3};
int check = 0;

static BLEUUID serviceUUID("0000ffe0-0000-1000-8000-00805f9b34fb");
static BLEUUID characteristicUUID("0000ffe1-0000-1000-8000-00805f9b34fb");

static boolean doConnect = false;
static boolean connected = false;

static BLEAddress *pServerAddress;
static BLERemoteCharacteristic* pRemoteCharacteristic;
BLEClient* pClient;

class MyClientCallback : public BLEClientCallbacks {
public:
  void onConnect(BLEClient* pClient) override {
    Serial.println("Connected to server");
  }
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
  if (!pRemoteService) {
    Serial.println("Failed to find service UUID");
    return false;
  }

  pRemoteCharacteristic = pRemoteService->getCharacteristic(characteristicUUID);
  if (!pRemoteCharacteristic) {
    Serial.println("Failed to find characteristic UUID");
    return false;
  }
  
  Serial.println("Found characteristic");
  pRemoteCharacteristic->registerForNotify(notifyCallback);
  return true;
}

static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  String receivedData = "";
  for (size_t i = 0; i < length; i++) receivedData += (char)pData[i];
  receivedData.trim();

  Serial.print("Received data: ");
  Serial.println(receivedData);

  if (receivedData == "shoot" && check < 3) {
    check++;
    Serial.println(check);

    for (int i = 0; i < 3; i++) {
      if (checkLaze(lazePins[i])) {
        Serial.printf("shoot target %d completed\n", i + 1);
        turnServo(servos[i], 80);
        buzz();
        return;
      }
    }
    Serial.println("shoot failed");
  }
}

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {
      advertisedDevice.getScan()->stop();
      pServerAddress = new BLEAddress(advertisedDevice.getAddress());
      doConnect = true;
      Serial.println("Device found. Connecting!");
    }
  }
};

bool checkLaze(int pin) {
  return digitalRead(pin) == 0;
}

void turnServo(Servo &servo, int angle) {
  for (int pos = 0; pos <= angle; pos += 5) {
    servo.write(pos);
    delay(20);
  }
}

void buzz() {
  digitalWrite(BUZZ_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZ_PIN, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  pinMode(RECEIVE_LAZE1, INPUT);
  pinMode(RECEIVE_LAZE2, INPUT);
  pinMode(RECEIVE_LAZE3, INPUT);
  pinMode(BUZZ_PIN, OUTPUT);

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);

  turnServo(servo1, 0);
  turnServo(servo2, 0);
  turnServo(servo3, 0);

  Serial.println("Starting BLE Client application...");
  BLEDevice::init("");

  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5);
}

void loop() {
  if (doConnect) {
    if (connectToServer(*pServerAddress)) {
      Serial.println("We are now connected to the BLE Server.");
      connected = true;
    } else {
      Serial.println("Failed to connect to the server.");
    }
  }
  digitalWrite(LED_PIN, connected ? LOW : HIGH);
}
