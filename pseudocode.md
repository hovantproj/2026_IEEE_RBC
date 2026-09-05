# Pseudocode

conceptualise autonomous behaviour as a bi-layered finite state machine

diversify movement from ball extraction

stage 1: implement line following behaviour
- If ONLY left IR sensor detects line, turn left
- If ONLY right IR sensor detects line, turn right
- if ONLY main IR sensor detects line, straight
- If no line is detected, straight

- [x] figure out what is "black" to the IR sensor using analog (19-20 = black, 0 = white)

stage 2: ???

procedure
- navigate to end region
- find and pickup ball in end region
- turn around (or do we just go in reverse??)
- navigate back to the start

state 0: navigating to end region
state 1: in end region, find ball
state 2: attempt to pickup ball
state 3: got ball, turn around
state 4: navigate back to start
state 5: stop

we could do a thing where if it stops for any reason (e.g. attempt to grab ball but it's not in there) it opens its claws and stops until we move our hand in front of the US