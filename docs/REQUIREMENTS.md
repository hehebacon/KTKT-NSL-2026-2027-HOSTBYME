# Requirements and verification gates

## Confirmed project constraints
- Form factor: four-legged ground robot.
- Target envelope: about 28 cm; hard project limit 30 × 30 × 30 cm.
- Useful payload goal: 500 g.
- Functional goal: approach an object, pick it up from the ground, lift it onto the back, mechanically retain it, then carry it.
- Balance/stability is a required capability, not yet demonstrated.
- Object shape and dimensions are not yet specified.

## Design decisions still open
- Exact controller board and servo/control architecture.
- Leg geometry, actuator count and torque margin.
- Pickup mechanism geometry and allowable object dimensions.
- Sensors for ground clearance, object presence, lift end stops, lock state and body attitude.
- Power system, runtime target, mass budget and safe power isolation.
- Competition rulebook and exact scoring rubric.

## Verification gates
1. **G0 — requirements:** confirm rules, object envelope, floor/surface and scoring criteria with teacher/organizer.
2. **G1 — software logic:** build and test state machine without connecting actuators.
3. **G2 — mechanical review:** verify envelope, center of mass, pinch points, retention and service access.
4. **G3 — bench integration:** adult/teacher-supervised test with robot restrained and actuator power isolated until checks pass.
5. **G4 — unloaded movement:** demonstrate stable standing and slow movement before adding payload.
6. **G5 — payload ladder:** increase test mass gradually under supervision; 500 g is only accepted after repeatable measured tests.
7. **G6 — competition rehearsal:** test the exact task course, battery condition and failure recovery.

## Pass criteria to define before testing
- Fits within 30 × 30 × 30 cm in every required configuration.
- Payload remains secured during the defined movement test.
- No unexpected reset, loose part, overheating or uncontrolled movement.
- A fault/abort request returns the software to a non-actuating safe state.
- Record test date, configuration, mass, result and any failures.

Never treat a simulated state, estimated torque, or successful compile as proof that the physical robot can balance or carry 500 g.
