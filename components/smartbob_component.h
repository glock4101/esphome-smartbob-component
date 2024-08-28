#pragma once

#include "esphome.h"

#define TAG "smartbob.component"

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
  namespace smartbob {

    class SmartBOBBinarySensor : public Component, public binary_sensor::BinarySensor {
    public:
      void set_target_relay_controller_addr(uint8_t addr) { this->target_relay_controller_addr_ = addr; }
      uint8_t get_target_relay_controller_addr() { return this->target_relay_controller_addr_; }
      void set_sensor_id(uint8_t sensor_id) { this->sensor_id_ = sensor_id; }
      uint8_t get_sensor_id() { return this->sensor_id_; }
      void setup() override;
      void dump_config() override;

    protected:
      uint8_t target_relay_controller_addr_;
      uint8_t sensor_id_;
    };

    class SmartBOBComponent : public Component, public uart::UARTDevice {
    public:
      SmartBOBComponent(uart::UARTComponent *uartComponent) : UARTDevice(uartComponent) {
        this->uart_ = uartComponent;
      }
      void register_binary_sensor(smartbob::SmartBOBBinarySensor *obj) { this->binary_sensors_.push_back(obj); }
      void setup() override;
      void loop() override;
      void dump_config() override;

    protected:
      uart::UARTComponent *uart_;
      std::vector<smartbob::SmartBOBBinarySensor *> binary_sensors_;
    };

  }
}
