# Source audit — 2026-10-22

## Scope
Reviewed the tracked firmware source, configuration, PlatformIO environment, workflow and test documentation in this repository.

## Findings and changes
- The firmware currently depends only on the Arduino framework supplied by the PlatformIO ESP32 platform; there were no third-party C++ libraries to remove.
- Removed unused state/fault definitions and the inactive timeout/watchdog fields. The previous timeout path could not fire because hardware arming is intentionally absent.
- Removed the `arm` command from the user interface: it was always denied and did not test a real actuator interlock.
- Kept fixed-size command storage; no dynamic `String`, heap allocation, or extra parsing library.
- Fixed overlong-line handling so the rest of that line is discarded until newline rather than accidentally being parsed as another command.
- Normalized command case and surrounding whitespace.
- Made status and abort output explicit that the program has no physical actuator driver or emergency-stop circuit.
- Kept the simulated task sequence deliberately limited: `demo` ends in `SENSOR_NOT_CONFIGURED`, never reports a successful pickup.
- Corrected the documented dimensional acceptance criterion to 28 × 28 × 28 cm.

## Current limits
- `platformio.ini` uses a provisional `esp32dev` environment only to check compilation; the actual controller board is not selected.
- No servo, motor, sensor, balance controller, inverse kinematics, battery monitoring or pickup mechanism driver is implemented.
- A passing build validates compilation only. It does not prove gait stability, pickup, safe power behavior or the 500 g payload target.
- Do not add a library until the selected hardware and a concrete requirement justify it.

## Verification record
The GitHub Actions workflow passed on the prior documentation-only commit. The source cleanup commit will trigger a new run; its result must be checked separately before claiming the revised source builds.
