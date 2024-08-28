#include "smartbob_component.h"

namespace esphome {
  namespace smartbob {

    void SmartBOBBinarySensor::setup() {
      // Inicjalizacja, jeśli jest potrzebna
    }

    void SmartBOBBinarySensor::dump_config() {
      ESP_LOGCONFIG(TAG, "SmartBOB Binary Sensor:");
      ESP_LOGCONFIG(TAG, "  Sensor ID: %d", this->sensor_id_);
    }

    void SmartBOBComponent::setup() {
      // Inicjalizacja UART lub inne operacje setup
    }

    void SmartBOBComponent::loop() {
      if (this->uart_->available()) {
        std::string data = this->uart_->read_str();
        process_data(data);
      }
    }

    void SmartBOBComponent::process_data(const std::string &data) {
      int DevID = 0;
      int SensorID = 0;
      float SensorValue = 0;

      if (sscanf(data.c_str(), "%d:%d:%f", &DevID, &SensorID, &SensorValue) == 3) {
        publish_state(DevID, SensorID, SensorValue == 1);
      }
    }

    void SmartBOBComponent::publish_state(int DevID, int SensorID, bool state) {
      std::string sensor_id = "binary_sensor_" + std::to_string(DevID) + "_" + std::to_string(SensorID);
      auto sensor = App.get_binary_sensor(sensor_id);
      if (sensor) {
        sensor->publish_state(state);
      }
    }

    void SmartBOBComponent::dump_config() {
      ESP_LOGCONFIG(TAG, "SmartBOB Component:");
      // Dodatkowe informacje konfiguracyjne, jeśli są potrzebne
    }

  }
}
