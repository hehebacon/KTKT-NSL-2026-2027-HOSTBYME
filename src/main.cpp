#include <Arduino.h>
#include <ctype.h>
#include <string.h>

#include "RobotConfig.h"

namespace {

RobotStatus robot;
char commandBuffer[48];
size_t commandLength = 0;
bool discardCommand = false;

const char* stateName(RobotState state) {
  switch (state) {
    case RobotState::SAFE_STOP: return "SAFE_STOP";
    case RobotState::APPROACH_SIM: return "APPROACH_SIM";
    case RobotState::PICKUP_SIM: return "PICKUP_SIM";
    case RobotState::LIFT_SIM: return "LIFT_SIM";
    case RobotState::LOCK_LOAD_SIM: return "LOCK_LOAD_SIM";
    case RobotState::VERIFY_LOAD_SIM: return "VERIFY_LOAD_SIM";
    case RobotState::FAULT: return "FAULT";
  }
  return "UNKNOWN";
}

const char* faultName(FaultCode fault) {
  switch (fault) {
    case FaultCode::NONE: return "NONE";
    case FaultCode::SENSOR_NOT_CONFIGURED: return "SENSOR_NOT_CONFIGURED";
    case FaultCode::ABORT_REQUESTED: return "ABORT_REQUESTED";
  }
  return "UNKNOWN";
}

void printStatus() {
  Serial.print("state=");
  Serial.println(stateName(robot.state));

  Serial.print("fault=");
  Serial.println(faultName(robot.fault));

  Serial.print("payload=");
  Serial.println(robot.payloadPresent ? "notional_only" : "not_verified");

  Serial.print("load_lock=");
  Serial.println(robot.loadLockConfirmed ? "notional_only" : "not_verified");

  Serial.println("hardware_outputs=DISABLED");
}

void stopSafely(FaultCode fault = FaultCode::NONE) {
  robot.state = fault == FaultCode::NONE
                    ? RobotState::SAFE_STOP
                    : RobotState::FAULT;
  robot.fault = fault;
  robot.payloadPresent = false;
  robot.loadLockConfirmed = false;
  // This scaffold has no motor, servo, or physical emergency-stop driver.
}

void printHelp() {
  Serial.println("Commands: help, status, selftest, disarm, abort, demo");
  Serial.println("Simulation only. Motor and servo outputs are not implemented.");
}

void runSelfTest() {
  const bool sizeIsValid =
      RobotConfig::TARGET_ENVELOPE_CM <= RobotConfig::MAX_ENVELOPE_CM;
  const bool payloadIsValid = RobotConfig::PAYLOAD_TARGET_G > 0.0f;
  const bool outputsAreDisabled = !RobotConfig::HARDWARE_OUTPUTS_ENABLED;

  if (sizeIsValid && payloadIsValid && outputsAreDisabled) {
    Serial.println("SELFTEST=PASS (configuration checks only)");
  } else {
    Serial.println("SELFTEST=FAIL");
  }

  Serial.println("No hardware, balance, pickup, or payload test was performed.");
}

bool normalizeCommand(char* command) {
  char* start = command;
  while (*start && isspace(static_cast<unsigned char>(*start))) {
    ++start;
  }

  char* end = start + strlen(start);
  while (end > start && isspace(static_cast<unsigned char>(end[-1]))) {
    --end;
  }
  *end = '\0';

  if (start != command) {
    memmove(command, start, static_cast<size_t>(end - start) + 1);
  }

  for (char* p = command; *p; ++p) {
    *p = static_cast<char>(tolower(static_cast<unsigned char>(*p)));
  }
  return command[0] != '\0';
}

void runDemo() {
  // Only demonstrate the task sequence. These are not sensor readings.
  robot.state = RobotState::APPROACH_SIM;
  Serial.println("SIM: approach");

  robot.state = RobotState::PICKUP_SIM;
  Serial.println("SIM: pickup requested");

  robot.state = RobotState::LIFT_SIM;
  Serial.println("SIM: lift requested");

  robot.state = RobotState::LOCK_LOAD_SIM;
  Serial.println("SIM: load lock requested");

  robot.state = RobotState::VERIFY_LOAD_SIM;
  Serial.println("SIM: cannot verify load; no physical sensors are configured");

  stopSafely(FaultCode::SENSOR_NOT_CONFIGURED);
  Serial.println("SIM ended in FAULT. No physical pickup was attempted.");
}

void handleCommand(char* command) {
  if (!normalizeCommand(command)) {
    return;
  }

  if (strcmp(command, "help") == 0) {
    printHelp();
  } else if (strcmp(command, "status") == 0) {
    printStatus();
  } else if (strcmp(command, "selftest") == 0) {
    runSelfTest();
  } else if (strcmp(command, "disarm") == 0) {
    stopSafely();
    printStatus();
  } else if (strcmp(command, "abort") == 0) {
    stopSafely(FaultCode::ABORT_REQUESTED);
    Serial.println("Abort recorded in software; this is not a physical emergency stop.");
    printStatus();
  } else if (strcmp(command, "demo") == 0) {
    runDemo();
    printStatus();
  } else {
    Serial.println("ERR: unknown command; type help");
  }
}

void readSerialCommands() {
  while (Serial.available() > 0) {
    const char input = static_cast<char>(Serial.read());

    if (input == '\r' || input == '\n') {
      if (discardCommand) {
        Serial.println("ERR: overlong command discarded");
      } else if (commandLength > 0) {
        commandBuffer[commandLength] = '\0';
        handleCommand(commandBuffer);
      }

      commandLength = 0;
      discardCommand = false;
      continue;
    }

    if (discardCommand) {
      continue;
    }

    if (!isprint(static_cast<unsigned char>(input))) {
      continue;
    }

    if (commandLength >= sizeof(commandBuffer) - 1) {
      commandLength = 0;
      discardCommand = true;
      continue;
    }

    commandBuffer[commandLength++] = input;
  }
}

}  // namespace

void setup() {
  Serial.begin(RobotConfig::SERIAL_BAUD);
  robot.state = RobotState::SAFE_STOP;
  robot.fault = FaultCode::NONE;

  Serial.println();
  Serial.println("500 g quadruped - diagnostic scaffold");
  Serial.println("Safe default: physical outputs are disabled.");
  printHelp();
  printStatus();
}

void loop() {
  readSerialCommands();
  delay(2);
}
