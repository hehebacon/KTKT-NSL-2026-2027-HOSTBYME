#pragma once

#include <stdint.h>

namespace RobotConfig {
constexpr float TARGET_ENVELOPE_CM = 28.0f;
constexpr float MAX_ENVELOPE_CM = 28.0f;
constexpr float PAYLOAD_TARGET_G = 500.0f;
constexpr bool HARDWARE_OUTPUTS_ENABLED = false;
constexpr uint32_t SERIAL_BAUD = 115200;
}

enum class RobotState : uint8_t {
  SAFE_STOP,
  APPROACH_SIM,
  PICKUP_SIM,
  LIFT_SIM,
  LOCK_LOAD_SIM,
  VERIFY_LOAD_SIM,
  FAULT
};

enum class FaultCode : uint8_t {
  NONE,
  SENSOR_NOT_CONFIGURED,
  ABORT_REQUESTED
};

struct RobotStatus {
  RobotState state = RobotState::SAFE_STOP;
  FaultCode fault = FaultCode::NONE;
  bool payloadPresent = false;
  bool loadLockConfirmed = false;
};
