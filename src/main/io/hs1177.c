/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 Created by Craig J Perry

 HS1177 cameras have an OSD for configuring their settings. It's driven by
 an external joystick which pulls the camera's OSD pin to GND through
 various resistor values.

 Due to a pullup resistor internal to the hs1177 on the OSD pin, a voltage
 divider is created when any of the joystick directions or button are clicked.

 An alternative method of driving that circuit would be with the use of a DAC
 peripheral on the flight controller. The DAC could be configured for an unused
 output pin.

 This would allow a user to make the following wiring connections:

   --------------------\            /--------------
    flight     GND     |<---------->| GND    hs1177
   Controller  MOTOR X |<---------->| OSD
   --------------------/            \--------------

  With this electrical connectivity in place, we can drive the hs1177 OSD
  from the flight controller. Dedicated stick commands will be used:

                      Throttle    Yaw    Pitch    Roll
                    --------------------------------------
         Open OSD =    CENTRE    LEFT    CENTRE    DOWN
    Exit OSD Mode =    CENTRE    LEFT    CENTRE   CENTRE   (hold 2 seconds)
               Up =    CENTRE   CENTRE     UP     CENTRE
             Down =    CENTRE   CENTRE    DOWN    CENTRE
             Left =    CENTRE   CENTRE   CENTRE    LEFT
            Right =    CENTRE   CENTRE   CENTRE    RIGHT
            Click =    CENTRE    RIGHT   CENTRE   CENTRE

 */

#ifdef HS1177

typedef enum {
  INVALID_CAMERA = 0,
  GENERIC_HS1177
} cameraType_e;

// Different cameras may require different DAC outputs
static const buttonAdcValues_t[] = {
                   //    up  down  left  right  click
  [INVALID_CAMERA] = {    0,    0,    0,     0,     0 },
  [GENERIC_HS1177] = {   45,   27,   15,     7,     0 }
};

typedef enum {
  HS1177_STATUS_OSD_UNKNOWN = 0,
  HS1177_STATUS_OSD_CLOSED,
  HS1177_STATUS_OSD_ONSCREEN
} hs1177Status_e;

hs1177Status_e hs1177Status = HS1177_STATUS_OSD_UNKNOWN;

void hs1177Init() {
  hs1177Status = HS1177_STATUS_OSD_CLOSED;
  // read camera type from config parameters
  // configure dac peripheral
}

void hs1177Process(timeUs_t currentTimeUs) {
  // if we're not disarmed then return immediately

  // if there's a button press in progress
    // unset DAC output if we've satisfied the required button press time
    // return

  // if hs1177 is initialised
    // look for a valid stick command being present
      // If OSD is closed then the only valid command is "open osd"
      // if OSD is open then look for: up, down, left, right, click or exit
    // debounce stick command based on currentTimeUs
    // if there's a command to process
      // set DAC output and note starting time of button press
}

#endif
