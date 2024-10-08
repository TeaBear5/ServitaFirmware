/**
 * @file pump.h
 * @brief Pump pins, functions, and variables.
 * @version 0.1
 * @date 2024-05-28
 */

#ifndef PUMP_H
#define PUMP_H

#include <Arduino.h>
#include <ArduinoJson.h>

#define GANTRY_TIMEOUT 15000
#define MOTOR_BACKOFF_TIME 200
#define LIMIT_SWITCH_DEBOUNCE 20

#define MOTOR_TYPE_TO_STRING(type) \
    (type == PUMP1) ? "PUMP1" : \
    (type == PUMP2) ? "PUMP2" : \
    (type == GANTRY) ? "GANTRY" : "UNKNOWN"

#define MOTOR_STATE_TO_STRING(state) \
    (state == MOTOR_OFF) ? "MOTOR_OFF" : \
    (state == MOTOR_ON) ? "MOTOR_ON" : \
    (state == MOTOR_UP) ? "MOTOR_UP" : \
    (state == MOTOR_DOWN) ? "MOTOR_DOWN" : "UNKNOWN"

enum motor_state_t {
    MOTOR_OFF,
    MOTOR_ON,
    MOTOR_UP,
    MOTOR_DOWN
};

enum motor_type_t {
    PUMP1,
    PUMP2,
    GANTRY,
};

enum gantry_state_t {
    GANTRY_NONE,
    GANTRY_HOMING,
    GANTRY_POURING,
    GANTRY_MANUAL_UP,
    GANTRY_MANUAL_DOWN
};

typedef struct {
    uint8_t *high_pin;  // High side for the pumps, up driver for the gantry.
    uint8_t *low_pin;  // Low side for the pumps, down driver for the gantry.
    uint8_t *enable_pin;  // Enable pin for the pumps and gantry.
    motor_state_t state;  // State of the motor. 
    motor_type_t type;  // Type of motor.
} motor_t;

extern motor_t pump1;
extern motor_t pump2;
extern motor_t gantry;
extern gantry_state_t gantry_state;


/**
 * @brief Initialize the limit switches.
*/
void init_limit_switches();

/**
 * @brief Initialize the pump pins and initial running state.
 * 
 * @param motor 
 * @return void
 */
void init_motor(motor_t *motor);

/**
 * @brief 
 * 
 * @param state 
 */
void manual_gantry_control(motor_state_t state);

/**
 * @brief 
 * 
 */
void home_gantry();

/**
 * @brief Initialize all motors.
*/
void init_motors();

/**
 * @brief Sets a motor state.
 * 
 * @param motor
 * @param state
 * @return bool True if the state was set, false if the state was invalid.
 */
bool set_motor_state(motor_t *motor, motor_state_t state);

/**
 * @brief Disable the motor interrupt service routine.
*/
void IRAM_ATTR disable_motor_isr();

/**
 * @brief Handle the motor JSON payload.
*/
void handle_motor_json(JsonObject payload);

/**
 * @brief Motor loop for the main loop.
*/
void motor_loop();


#endif // PUMP_H