#pragma once

#include "esphome.h"

class SmartBOBComponent : public Component, public UARTDevice {
 public:
  SmartBOBComponent(UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override {
    // Inicjalizacja, jeśli potrzebna
  }

  void loop() override {
    if (available()) {
      std::string data = read_str();
      process_data(data);
    }
  }

  void process_data(const std::string &data) {
    int DevID = 0;
    int SensorID = 0;
    float SensorValue = 0;

    if (sscanf(data.c_str(), "%d:%d:%f", &DevID, &SensorID, &SensorValue) == 3) {
      publish_state(DevID, SensorID, SensorValue == 1);
    }
  }

  void publish_state(int DevID, int SensorID, bool state) {
    // Implementacja logiki publikacji stanu
    // np. id(sensor_1_1).publish_state(state); itd.
  }
};
