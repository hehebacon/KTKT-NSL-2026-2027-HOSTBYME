#include <Arduino.h>
#include <string.h>
#include <ctype.h>
#include "RobotConfig.h"

static RobotStatus status;
static char commandBuffer[48];
static size_t commandLength = 0;
static uint32_t lastCommandAt = 0;

static const char* stateName(RobotState state) {
  switch (state) {
    case RobotState::SAFE_STOP: return "SAFE_STOP";
    case RobotState::IDLE: return "IDLE";
    case RobotState::APPROACH_SIM: return "APPROACH_SIM";
    case RobotState::PICKUP_SIM: return "PICKUP_SIM";
    case RobotState::LIFT_SIM: return "LIFT_SIM";
    case RobotState::LOCK_LOAD_SIM: return "LOCK_LOAD_SIM";
    case RobotState::VERIFY_LOAD_SIM: return "VERIFY_LOAD_SIM";
    case RobotState::CARRY_SIM: return "CARRY_SIM";
    case RobotState::PLACE_SIM: return "PLACE_SIM";
    case RobotState::FAULT: return "FAULT";
  }
  return "UNKNOWN";
}

static const char* faultName(FaultCode fault) {
  switch (fault) {
    case FaultCode::NONE: return "NONE";
    case FaultCode::INVALID_TRANSITION: return "INVALID_TRANSITION";
    case FaultCode::COMMAND_TIMEOUT: return "COMMAND_TIMEOUT";
    case FaultCode::SENSOR_NOT_CONFIGURED: return "SENSOR_NOT_CONFIGURED";
    case FaultCode::LOAD_NOT_VERIFIED: return "LOAD_NOT_VERIFIED";
    case FaultCode::ESTOP_REQUESTED: return "ESTOP_REQUESTED";
  }
  return "UNKNOWN";
}

static void printStatus() {
  Serial.print("state="); Serial.println(stateName(status.state));
  Serial.print("fault="); Serial.println(faultName(status.fault));
  Serial.print("armed_logic="); Serial.println(status.armed ? "true" : "false");
  Serial.print("payload_sensor="); Serial.println(status.payloadPresent ? "simulated_true" : "not_verified");
  Serial.print("lock_sensor="); Serial.println(status.loadLockConfirmed ? "simulated_true" : "not_verified");
  Serial.println("hardware_outputs=DISABLED");
}

static void stopSafely(FaultCode fault = FaultCode::NONE) {
  status.armed = false;
  status.state = (fault == FaultCode::NONE) ? RobotState::SAFE_STOP : RobotState::FAULT;
  status.fault = fault;
  // Deliberately no servo/motor output code exists in this initial scaffold.
}

static void help() {
  Serial.println("Commands: help, status, selftest, arm, disarm, abort, demo");
  Serial.println("NOTE: simulation/diagnostics only; no motor or servo outputs.");
}

static void selfTest() {
  bool ok = true;
  ok = ok && (RobotConfig::TARGET_ENVELOPE_CM <= RobotConfig::MAX_ENVELOPE_CM);
  ok = ok && (RobotConfig::PAYLOAD_TARGET_G > 0.0f);
  ok = ok && (!RobotConfig::HARDWARE_OUTPUTS_ENABLED);
  Serial.println(ok ? "SELFTEST=PASS (logic only)" : "SELFTEST=FAIL");
  Serial.println("Not a hardware, balance, payload, or flight test.");
}

static bool canStartDemo() {
  return status.state == RobotState::IDLE || status.state == RobotState::SAFE_STOP;
}

static void runDemo() {
  if (!canStartDemo()) {
    Serial.println("ERR: disarm/abort and return to safe state first");
    return;
  }
  // Simulated transitions only. These are not sensor measurements.
  status.armed = true;
  status.state = RobotState::APPROACH_SIM; Serial.println("SIM: approach");
  status.state = RobotState::PICKUP_SIM; Serial.println("SIM: pickup request");
  status.state = RobotState::LIFT_SIM; Serial.println("SIM: lift request");
  status.state = RobotState::LOCK_LOAD_SIM; Serial.println("SIM: lock request");
  status.state = RobotState::VERIFY_LOAD_SIM; Serial.println("SIM: verification required; no physical sensor configured");
  status.payloadPresent = false;
  status.loadLockConfirmed = false;
  stopSafely(FaultCode::SENSOR_NOT_CONFIGURED);
  Serial.println("SIM ended safely: hardware and sensor verification are not implemented.");
}

static void handleCommand(char* cmd) {
  for (char* p = cmd; *p; ++p) *p = static_cast<char>(tolower(static_cast<unsigned char>(*p)));
  if (strcmp(cmd, "help") == 0) { help(); return; }
  if (strcmp(cmd, "status") == 0) { printStatus(); return; }
  if (strcmp(cmd, "selftest") == 0) { selfTest(); return; }
  if (strcmp(cmd, "abort") == 0) { stopSafely(FaultCode::ESTOP_REQUESTED); printStatus(); return; }
  if (strcmp(cmd, "disarm") == 0) { stopSafely(); printStatus(); return; }
  if (strcmp(cmd, "arm") == 0) {
    Serial.println("DENIED: hardware outputs are disabled in this scaffold.");
    return;
  }
  if (strcmp(cmd, "demo") == 0) { runDemo(); printStatus(); return; }
  Serial.println("ERR: unknown command; type help");
}

void setup() {
  Serial.begin(RobotConfig::SERIAL_BAUD);
  lastCommandAt = millis();
  status.state = RobotState::SAFE_STOP;
  status.armed = false;
  status.fault = FaultCode::NONE;
  Serial.println("\n500g Quadruped — diagnostic scaffold");
  Serial.println("SAFE DEFAULT: no motor/servo outputs; demo is simulation only.");
  help();
  printStatus();
}

void loop() {
  while (Serial.available() > 0) {
    const char c = static_cast<char>(Serial.read());
    lastCommandAt = millis();
    if (c == '\r' || c == '\n') {
      if (commandLength > 0) {
        commandBuffer[commandLength] = '\0';
        handleCommand(commandBuffer);
        commandLength = 0;
      }
    } else if (isprint(static_cast<unsigned char>(c))) {
      if (commandLength + 1 < sizeof(commandBuffer)) {
        commandBuffer[commandLength++] = c;
      } else {
        commandLength = 0;
        Serial.println("ERR: command too long; cleared");
      }
    }
  }

  // Watchdog for future command-driven test modes. It cannot move hardware.
  if (status.armed && (millis() - lastCommandAt > RobotConfig::COMMAND_TIMEOUT_MS)) {
    stopSafely(FaultCode::COMMAND_TIMEOUT);
  }
  delay(2);
}
