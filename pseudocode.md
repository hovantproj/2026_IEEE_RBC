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

### State Machine
**State 0:**
- starts in the box
- all IR's on
- roughly facing correct direction
- wait 5s then move straight forward

state 0 -> state 1: until not 3 IR's detected

**State 1:** line following algorithm
- follow line following algorithm
- every 50ms

state 1 -> state 2: all 3 IR's detected (probably in black box)

**State 2:** verify it's actually in black box
- do 2 cycles of moving forward like 2cm to verify it's in the black box
- while polling ultrasonic between moves to ensure it's not gna hit the ball

>[!caution] Make sure this process doesn't hit the ball
>Combine with US to make sure it's not hitting anything??

state 2 -> state 3: finished verification
state 2 -> state 3: ball close enough or smth

**State 3:** find ball
- turn left slowly looking for ball (roughly 30 degrees)
- turn right slowly looking for ball (roughly 60 degrees)

what happens if it doesn't find ball when it's in the end region?
- maybe restart state 3 but with a bigger range of motion and slower movement + increase max distance

state 3 -> state 4: ball found
state 3 -> state 3b: didn't find the ball

**State 4:** capturing ball
if ball found by US:
- move forward slowly until within 7 cm
- toggle close on servo
- verify the ball has been captured (US < 7cm or whatever)
- lock servo arms (no more opening)

if ball not captured successfully
- stop for 3s
- go to state 3

state 4 -> state 5: ball captured
state 4 -> state 3: ball not captured properly

**State 5:** navigating to border
- drive straight until at least 1 IR turns off
- drive straight until it turns back on (line detected)

state 5 -> state 6: found line

**State 6:** line following algorithm pt2
- follow lines back home (until all 3 IR's triggered)

state 6 -> state 7: all 3 IR's triggered

**State 7:** verify it's actually in (starting) black box
- do 2 cycles of moving forward like 2cm to verify it's in the black box

state 7 -> state 6: not in black box
state 7 -> state 8: in starting black box

**State 8:** END
- stop