# Pseudocode

conceptualise autonomous behaviour as a bi-layered finite state machine

diversify movement from ball extraction

stage 1: implement line following behaviour
- If ONLY left IR sensor detects line, turn left
- If ONLY right IR sensor detects line, turn right
- if ONLY main IR sensor detects line, straight
- If no line is detected, straight

- [ ] configure brightness of IR with screw (low = black, high = white)
	- [x] IR sensors need to be digital read pins
	- [x] nvm using AnalogRead now



stage 2: ???
- 