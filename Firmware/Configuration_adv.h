#ifndef CONFIGURATION_ADV_H
#define CONFIGURATION_ADV_H

//===========================================================================
//=============================Thermal Settings  ============================
//===========================================================================

#ifdef BED_LIMIT_SWITCHING
  #define BED_HYSTERESIS 2 //only disable heating if T>target+BED_HYSTERESIS and enable heating if T>target-BED_HYSTERESIS
#endif
#define BED_CHECK_INTERVAL 5000 //ms between checks in bang-bang control

//// Heating sanity check:
// This waits for the watch period in milliseconds whenever an M104 or M109 increases the target temperatureLCD_PROGRESS_BAR
// If the temperature has not increased at the end of that period, the target temperature is set to zero.
// It can be reset with another M104/M109. This check is also only triggered if the target temperature and the current temperature
//  differ by at least 2x WATCH_TEMP_INCREASE
//#define WATCH_TEMP_PERIOD 40000 //40 seconds
//#define WATCH_TEMP_INCREASE 10  //Heat up at least 10 degree in 20 seconds

#ifdef PIDTEMP
  // this adds an experimental additional term to the heating power, proportional to the extrusion speed.
  // if Kc is chosen well, the additional required power due to increased melting should be compensated.
  #define PID_ADD_EXTRUSION_RATE
  #ifdef PID_ADD_EXTRUSION_RATE
    #define  DEFAULT_Kc (1) //heating power=Kc*(e_speed)
  #endif
#endif


//automatic temperature: The hot end target temperature is calculated by all the buffered lines of gcode.
//The maximum buffered steps/sec of the extruder motor are called "se".
//You enter the autotemp mode by a M109 S<mintemp> B<maxtemp> F<factor>
// the target temperature is set to mintemp+factor*se[steps/sec] and limited by mintemp and maxtemp
// you exit the value by any M109 without F*
// Also, if the temperature is set to a value <mintemp, it is not changed by autotemp.
// on an Ultimaker, some initial testing worked with M109 S215 B260 F1 in the start.gcode
//#define AUTOTEMP
#ifdef AUTOTEMP
  #define AUTOTEMP_OLDWEIGHT 0.98
#endif

//Show Temperature ADC value
//The M105 command return, besides traditional information, the ADC value read from temperature sensors.
//#define SHOW_TEMP_ADC_VALUES

//  extruder run-out prevention.
//if the machine is idle, and the temperature over MINTEMP, every couple of SECONDS some filament is extruded
//#define EXTRUDER_RUNOUT_PREVENT
#define EXTRUDER_RUNOUT_MINTEMP 190
#define EXTRUDER_RUNOUT_SECONDS 30.
#define EXTRUDER_RUNOUT_ESTEPS 14. //mm filament
#define EXTRUDER_RUNOUT_SPEED 1500.  //extrusion speed
#define EXTRUDER_RUNOUT_EXTRUDE 100

//These defines help to calibrate the AD595 sensor in case you get wrong temperature measurements.
//The measured temperature is defined as "actualTemp = (measuredTemp * TEMP_SENSOR_AD595_GAIN) + TEMP_SENSOR_AD595_OFFSET"
#define TEMP_SENSOR_AD595_OFFSET 0.0
#define TEMP_SENSOR_AD595_GAIN   1.0

//This is for controlling a fan to cool down the stepper drivers
//it will turn on when any driver is enabled
//and turn off after the set amount of seconds from last driver being disabled again
#define CONTROLLERFAN_PIN -1 //Pin used for the fan to cool controller (-1 to disable)
#define CONTROLLERFAN_SECS 60 //How many seconds, after all motors were disabled, the fan should run
#define CONTROLLERFAN_SPEED 255  // == full speed

// When first starting the main fan, run it at full speed for the
// given number of milliseconds.  This gets the fan spinning reliably
// before setting a PWM value. (Does not work with software PWM for fan on Sanguinololu)
// RP: new implementation - long pulse at 100% when starting, short pulse  
#define FAN_KICK_START_TIME 800  //when starting from zero (long kick time)
#define FAN_KICK_RUN_MINPWM 25   //PWM treshold for short kicks
#define FAN_KICK_IDLE_TIME  4000 //delay between short kicks
#define FAN_KICK_RUN_TIME   50   //short kick time




//===========================================================================
//=============================Mechanical Settings===========================
//===========================================================================

#define ENDSTOPS_ONLY_FOR_HOMING // If defined the endstops will only be used for homing


//// AUTOSET LOCATIONS OF LIMIT SWITCHES
//// Added by ZetaPhoenix 09-15-2012
#ifdef MANUAL_HOME_POSITIONS  // Use manual limit switch locations
  #define X_HOME_POS MANUAL_X_HOME_POS
  #define Y_HOME_POS MANUAL_Y_HOME_POS
  #define Z_HOME_POS MANUAL_Z_HOME_POS
#else //Set min/max homing switch positions based upon homing direction and min/max travel limits
  //X axis
  #if X_HOME_DIR == -1
    #ifdef BED_CENTER_AT_0_0
      #define X_HOME_POS X_MAX_LENGTH * -0.5
    #else
      #define X_HOME_POS X_MIN_POS
    #endif //BED_CENTER_AT_0_0
  #else
    #ifdef BED_CENTER_AT_0_0
      #define X_HOME_POS X_MAX_LENGTH * 0.5
    #else
      #define X_HOME_POS X_MAX_POS
    #endif //BED_CENTER_AT_0_0
  #endif //X_HOME_DIR == -1

  //Y axis
  #if Y_HOME_DIR == -1
    #ifdef BED_CENTER_AT_0_0
      #define Y_HOME_POS Y_MAX_LENGTH * -0.5
    #else
      #define Y_HOME_POS Y_MIN_POS
    #endif //BED_CENTER_AT_0_0
  #else
    #ifdef BED_CENTER_AT_0_0
      #define Y_HOME_POS Y_MAX_LENGTH * 0.5
    #else
      #define Y_HOME_POS Y_MAX_POS
    #endif //BED_CENTER_AT_0_0
  #endif //Y_HOME_DIR == -1

  // Z axis
  #if Z_HOME_DIR == -1 //BED_CENTER_AT_0_0 not used
    #define Z_HOME_POS Z_MIN_POS
  #else
    #define Z_HOME_POS Z_MAX_POS
  #endif //Z_HOME_DIR == -1
#endif //End auto min/max positions
//END AUTOSET LOCATIONS OF LIMIT SWITCHES -ZP


//#define Z_LATE_ENABLE // Enable Z the last moment. Needed if your Z driver overheats.

// A single Z stepper driver is usually used to drive 2 stepper motors.
// Uncomment this define to utilize a separate stepper driver for each Z axis motor.
// Only a few motherboards support this, like RAMPS, which have dual extruder support (the 2nd, often unused, extruder driver is used
// to control the 2nd Z axis stepper motor). The pins are currently only defined for a RAMPS motherboards.
// On a RAMPS (or other 5 driver) motherboard, using this feature will limit you to using 1 extruder.
//#define Z_DUAL_STEPPER_DRIVERS

#ifdef Z_DUAL_STEPPER_DRIVERS
  #undef EXTRUDERS
  #define EXTRUDERS 1
#endif

// Same again but for Y Axis.
//#define Y_DUAL_STEPPER_DRIVERS

// Define if the two Y drives need to rotate in opposite directions
#define INVERT_Y2_VS_Y_DIR true

#ifdef Y_DUAL_STEPPER_DRIVERS
  #undef EXTRUDERS
  #define EXTRUDERS 1
#endif

#if defined (Z_DUAL_STEPPER_DRIVERS) && defined (Y_DUAL_STEPPER_DRIVERS)
  #error "You cannot have dual drivers for both Y and Z"
#endif

//homing hits the endstop, then retracts by this distance, before it tries to slowly bump again:
#define X_HOME_RETRACT_MM 5
#define Y_HOME_RETRACT_MM 5
#define Z_HOME_RETRACT_MM 2
//#define QUICK_HOME  //if this is defined, if both x and y are to be homed, a diagonal move will be performed initially.

#define AXIS_RELATIVE_MODES {false, false, false, false}
#define MAX_STEP_FREQUENCY 40000 // Max step frequency for Ultimaker (5000 pps / half step). Toshiba steppers are 4x slower, but Prusa3D does not use those.
//By default pololu step drivers require an active high signal. However, some high power drivers require an active low signal as step.
#define INVERT_X_STEP_PIN false
#define INVERT_Y_STEP_PIN false
#define INVERT_Z_STEP_PIN false
#define INVERT_E_STEP_PIN false

//default stepper release if idle
#define DEFAULT_STEPPER_DEACTIVE_TIME 60

#define DEFAULT_MINIMUMFEEDRATE       0.0     // minimum feedrate
#define DEFAULT_MINTRAVELFEEDRATE     0.0

// Feedrates for manual moves along X, Y, Z, E from panel


//Comment to disable setting feedrate multiplier via encoder
#ifdef ULTIPANEL
    #define ULTIPANEL_FEEDMULTIPLY
#endif

// minimum time in microseconds that a movement needs to take if the buffer is emptied.
#define DEFAULT_MINSEGMENTTIME        20000

// If defined the movements slow down when the look ahead buffer is only half full
#define SLOWDOWN

// MS1 MS2 Stepper Driver Microstepping mode table
#define MICROSTEP1 LOW,LOW
#define MICROSTEP2 HIGH,LOW
#define MICROSTEP4 LOW,HIGH
#define MICROSTEP8 HIGH,HIGH
#define MICROSTEP16 HIGH,HIGH

// Microstep setting (Only functional when stepper driver microstep pins are connected to MCU.
#define MICROSTEP_MODES {16,16,16,16,16} // [1,2,4,8,16]



// uncomment to enable an I2C based DIGIPOT like on the Azteeg X3 Pro
//#define DIGIPOT_I2C
// Number of channels available for I2C digipot, For Azteeg X3 Pro we have 8
#define DIGIPOT_I2C_NUM_CHANNELS 8
// actual motor currents in Amps, need as many here as DIGIPOT_I2C_NUM_CHANNELS
#define DIGIPOT_I2C_MOTOR_CURRENTS {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}

//===========================================================================
//=============================Additional Features===========================
//===========================================================================

//#define CHDK 4        //Pin for triggering CHDK to take a picture see how to use it here http://captain-slow.dk/2014/03/09/3d-printing-timelapses/
#define CHDK_DELAY 50 //How long in ms the pin should stay HIGH before going LOW again

#define SD_FINISHED_STEPPERRELEASE true  //if sd support and the file is finished: disable steppers?
#define SD_FINISHED_RELEASECOMMAND "M84 X Y Z E" // You might want to keep the z enabled so your bed stays in place.

#define SDCARD_RATHERRECENTFIRST  //reverse file order of sd card menu display. Its sorted practically after the file system block order.
// if a file is deleted, it frees a block. hence, the order is not purely chronological. To still have auto0.g accessible, there is again the option to do that.
// using:
//#define MENU_ADDAUTOSTART

// Show a progress bar on the LCD when printing from SD?
//#define LCD_PROGRESS_BAR

#ifdef LCD_PROGRESS_BAR
  // Amount of time (ms) to show the bar
  #define PROGRESS_BAR_BAR_TIME 2000
  // Amount of time (ms) to show the status message
  #define PROGRESS_BAR_MSG_TIME 3000
  // Amount of time (ms) to retain the status message (0=forever)
  #define PROGRESS_MSG_EXPIRE   0
  // Enable this to show messages for MSG_TIME then hide them
  //#define PROGRESS_MSG_ONCE
#endif

// The hardware watchdog should reset the microcontroller disabling all outputs, in case the firmware gets stuck and doesn't do temperature regulation.
//#define USE_WATCHDOG

#ifdef USE_WATCHDOG
// If you have a watchdog reboot in an ArduinoMega2560 then the device will hang forever, as a watchdog reset will leave the watchdog on.
// The "WATCHDOG_RESET_MANUAL" goes around this by not using the hardware reset.
//  However, THIS FEATURE IS UNSAFE!, as it will only work if interrupts are disabled. And the code could hang in an interrupt routine with interrupts disabled.
//#define WATCHDOG_RESET_MANUAL
#endif

// Enable the option to stop SD printing when hitting and endstops, needs to be enabled from the LCD menu when this option is enabled.
//#define ABORT_ON_ENDSTOP_HIT_FEATURE_ENABLED

// Babystepping enables the user to control the axis in tiny amounts, independently from the normal printing process
// it can e.g. be used to change z-positions in the print startup phase in real-time
// does not respect endstops!
#define BABYSTEPPING
#ifdef BABYSTEPPING
  #define BABYSTEP_XY  //not only z, but also XY in the menu. more clutter, more functions
  #define BABYSTEP_INVERT_Z false  //true for inverse movements in Z
  #define BABYSTEP_Z_MULTIPLICATOR 2 //faster z movements

  #ifdef COREXY
    #error BABYSTEPPING not implemented for COREXY yet.
  #endif
#endif

/**
 * Implementation of linear pressure control
 *
 * Assumption: advance = k * (delta velocity)
 * K=0 means advance disabled.
 * See Marlin documentation for calibration instructions.
 */
#define LIN_ADVANCE

#ifdef LIN_ADVANCE
  #define LIN_ADVANCE_K 0 //Try around 45 for PLA, around 25 for ABS.

  /**
   * Some Slicers produce Gcode with randomly jumping extrusion widths occasionally.
   * For example within a 0.4mm perimeter it may produce a single segment of 0.05mm width.
   * While this is harmless for normal printing (the fluid nature of the filament will
   * close this very, very tiny gap), it throws off the LIN_ADVANCE pressure adaption.
   *
   * For this case LIN_ADVANCE_E_D_RATIO can be used to set the extrusion:distance ratio
   * to a fixed value. Note that using a fixed ratio will lead to wrong nozzle pressures
   * if the slicer is using variable widths or layer heights within one print!
   *
   * This option sets the default E:D ratio at startup. Use `M900` to override this value.
   *
   * Example: `M900 W0.4 H0.2 D1.75`, where:
   *   - W is the extrusion width in mm
   *   - H is the layer height in mm
   *   - D is the filament diameter in mm
   *
   * Example: `M900 R0.0458` to set the ratio directly.
   *
   * Set to 0 to auto-detect the ratio based on given Gcode G1 print moves.
   *
   * Slic3r (including Prusa Slic3r) produces Gcode compatible with the automatic mode.
   * Cura (as of this writing) may produce Gcode incompatible with the automatic mode.
   */
  #define LIN_ADVANCE_E_D_RATIO 0 // The calculated ratio (or 0) according to the formula W * H / ((D / 2) ^ 2 * PI)
                                  // Example: 0.4 * 0.2 / ((1.75 / 2) ^ 2 * PI) = 0.033260135
#endif

// Arc interpretation settings:
#define MM_PER_ARC_SEGMENT 1
#define N_ARC_CORRECTION 25

const unsigned int dropsegments=5; //everything with less than this number of steps will be ignored as move and joined with the next movement

// If you are using a RAMPS board or cheap E-bay purchased boards that do not detect when an SD card is inserted
// You can get round this by connecting a push button or single throw switch to the pin defined as SDCARDCARDDETECT
// in the pins.h file.  When using a push button pulling the pin to ground this will need inverted.  This setting should
// be commented out otherwise
#define SDCARDDETECTINVERTED

#ifdef ULTIPANEL
 #undef SDCARDDETECTINVERTED
#endif

// Power Signal Control Definitions
// By default use ATX definition
#ifndef POWER_SUPPLY
  #define POWER_SUPPLY 1
#endif
// 1 = ATX
#if (POWER_SUPPLY == 1)
  #define PS_ON_AWAKE  LOW
  #define PS_ON_ASLEEP HIGH
#endif
// 2 = X-Box 360 203W
#if (POWER_SUPPLY == 2)
  #define PS_ON_AWAKE  HIGH
  #define PS_ON_ASLEEP LOW
#endif

// Control heater 0 and heater 1 in parallel.
//#define HEATERS_PARALLEL

//===========================================================================
//=============================Buffers           ============================
//===========================================================================

// The number of linear motions that can be in the plan at any give time.
// THE BLOCK_BUFFER_SIZE NEEDS TO BE A POWER OF 2, i.g. 8,16,32 because shifts and ors are used to do the ring-buffering.
#if defined SDSUPPORT
  #define BLOCK_BUFFER_SIZE 16   // SD,LCD,Buttons take more memory, block buffer needs to be smaller
#else
  #define BLOCK_BUFFER_SIZE 16 // maximize block buffer
#endif


//The ASCII buffer for receiving from the serial:
#define MAX_CMD_SIZE 96
#define BUFSIZE 4


// Firmware based and LCD controlled retract
// M207 and M208 can be used to define parameters for the retraction.
// The retraction can be called by the slicer using G10 and G11
// until then, intended retractions can be detected by moves that only extrude and the direction.
// the moves are than replaced by the firmware controlled ones.

#define FWRETRACT  //ONLY PARTIALLY TESTED
#ifdef FWRETRACT
  #define MIN_RETRACT 0.1                //minimum extruded mm to accept a automatic gcode retraction attempt
  #define RETRACT_LENGTH 3               //default retract length (positive mm)
  #define RETRACT_LENGTH_SWAP 13         //default swap retract length (positive mm), for extruder change
  #define RETRACT_FEEDRATE 45            //default feedrate for retracting (mm/s)
  #define RETRACT_ZLIFT 0                //default retract Z-lift
  #define RETRACT_RECOVER_LENGTH 0       //default additional recover length (mm, added to retract length when recovering)
  #define RETRACT_RECOVER_LENGTH_SWAP 0  //default additional swap recover length (mm, added to retract length when recovering from extruder change)
  #define RETRACT_RECOVER_FEEDRATE 8     //default feedrate for recovering from retraction (mm/s)
#endif

//adds support for experimental filament exchange support M600; requires display


#ifdef FILAMENTCHANGEENABLE
  #ifdef EXTRUDER_RUNOUT_PREVENT
    #error EXTRUDER_RUNOUT_PREVENT currently incompatible with FILAMENTCHANGE
  #endif
#endif

//===========================================================================
//=============================  Define Defines  ============================
//===========================================================================

#if EXTRUDERS > 1 && defined TEMP_SENSOR_1_AS_REDUNDANT
  #error "You cannot use TEMP_SENSOR_1_AS_REDUNDANT if EXTRUDERS > 1"
#endif

#if EXTRUDERS > 1 && defined HEATERS_PARALLEL
  #error "You cannot use HEATERS_PARALLEL if EXTRUDERS > 1"
#endif

#if TEMP_SENSOR_0 > 0
  #define THERMISTORHEATER_0 TEMP_SENSOR_0
  #define HEATER_0_USES_THERMISTOR
#endif
#if TEMP_SENSOR_1 > 0
  #define THERMISTORHEATER_1 TEMP_SENSOR_1
  #define HEATER_1_USES_THERMISTOR
#endif
#if TEMP_SENSOR_2 > 0
  #define THERMISTORHEATER_2 TEMP_SENSOR_2
  #define HEATER_2_USES_THERMISTOR
#endif
#if TEMP_SENSOR_BED > 0
  #define THERMISTORBED TEMP_SENSOR_BED
  #define BED_USES_THERMISTOR
#endif
#if TEMP_SENSOR_0 == -1
  #define HEATER_0_USES_AD595
#endif
#if TEMP_SENSOR_1 == -1
  #define HEATER_1_USES_AD595
#endif
#if TEMP_SENSOR_2 == -1
  #define HEATER_2_USES_AD595
#endif
#if TEMP_SENSOR_BED == -1
  #define BED_USES_AD595
#endif
#if TEMP_SENSOR_0 == -2
  #define HEATER_0_USES_MAX6675
#endif
#if TEMP_SENSOR_0 == 0
  #undef HEATER_0_MINTEMP
  #undef HEATER_0_MAXTEMP
#endif
#if TEMP_SENSOR_1 == 0
  #undef HEATER_1_MINTEMP
  #undef HEATER_1_MAXTEMP
#endif
#if TEMP_SENSOR_2 == 0
  #undef HEATER_2_MINTEMP
  #undef HEATER_2_MAXTEMP
#endif
#if TEMP_SENSOR_BED == 0
  #undef BED_MINTEMP
  #undef BED_MAXTEMP
#endif


#endif //__CONFIGURATION_ADV_H
