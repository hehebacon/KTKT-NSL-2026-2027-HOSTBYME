#pragma once

#include <stdint.h>

namespace RobotConfig {
constexpr float TARGET_ENVELOPE_CM = 28.0f;
constexpr float MAX_ENVELOPE_CM = 28.0f;
constexpr float PAYLOAD_TARGET_G = 500.0f;
constexpr bool HARDWARE_OUTPUTS_ENABLED = false;
constexpr uint32_t SERIAL_BAUD = 115200;
constexpr uint32_t COMMAND_TIMEOUT_MS = 1500;
}

enum class RobotState : uint8_t {
  SAFE_STOP,
  IDLE,
  APPROACH_SIM,
  PICKUP_SIM,
  LIFT_SIM,
  LOCK_LOAD_SIM,
  VERIFY_LOAD_SIM,
  CARRY_SIM,
  PLACE_SIM,
  FAULT
};

enum class FaultCode : uint8_t {
  NONE,
  INVALID_TRANSITION,
  COMMAND_TIMEOUT,
  SENSOR_NOT_CONFIGURED,
  LOAD_NOT_VERIFIED,
  ESTOP_REQUESTED
};

struct RobotStatus {
  RobotState state = RobotState::SAFE_STOP;
  FaultCode fault = FaultCode::NONE;
  bool armed = false;
  bool payloadPresent = false;
  bool loadLockConfirmed = false;
  bool hardwareOutputsEnabled = RobotConfig::HARDWARE_OUTPUTS_ENABLED;
};
