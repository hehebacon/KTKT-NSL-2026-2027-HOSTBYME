# Pickup and carry state sequence

This is a software/behavior specification, not a validated mechanical design.

1. **SAFE_STOP** — actuator commands disabled; wait for deliberate reset.
2. **IDLE** — check configured sensors and fault status.
3. **APPROACH** — approach slowly; stop if attitude, distance or obstacle data are invalid.
4. **PICKUP** — align the pickup tool with the object; do not assume the object is captured.
5. **LIFT** — lift within a limited range; stop on end-stop, current/torque limit, or timeout.
6. **LOCK_LOAD** — engage a positive retention mechanism; do not rely only on friction.
7. **VERIFY_LOAD** — require independent evidence of object presence and lock engagement.
8. **CARRY** — permit movement only after verification and a stability check.
9. **PLACE** — stop body motion, release deliberately, verify the object has been released.
10. **FAULT** — disable movement requests and report the fault; require a deliberate recovery procedure.

## Mandatory interlocks
- No transition to CARRY unless both payload-present and lock-confirmed signals are valid.
- Unknown or disconnected sensor values count as failure, not success.
- Timeout, unexpected body tilt, overload indication or abort request stops the sequence.
- The current code uses simulated transitions only. It does not read real sensors or actuate the mechanism.
