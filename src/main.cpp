#include <Arduino.h>

#include <ArduinoBLE.h>

const char* UUID = "02401BCD-38A9-4218-AB87-128397ED1C3B";
BLEService service(UUID);
BLEStringCharacteristic characteristic(UUID, BLEWrite, 512);

void setup() {
  // general setup
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // bluetooth setup
  while (!BLE.begin()) {
    Serial.println("BLE init failure");
    delay(1000);
  }

  service.addCharacteristic(characteristic);
  BLE.addService(service);
  BLE.setAdvertisedService(service);

  // doesn't work
  // BLE.setLocalName("Arduino Nano 33 BLE (Peripheral) - LED");

  BLE.advertise();
}

void loop() {
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("Received connection: ");
    Serial.println(central.address());
    while (central.connected()) {
      if (characteristic.written()) {
        String receivedValue = characteristic.value();
        if (receivedValue == "yes") {
          digitalWrite(LED_BUILTIN, HIGH);
        } else {
          digitalWrite(LED_BUILTIN, LOW);
        }
      }
    }
    Serial.println("disconnected");
  }
}
