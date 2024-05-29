/**
 * @file pour.h
 * @author Tyler Bair (tyler.bair@protonmail.com)
 * @brief Pour size management, sequencing, and control.
 * @version 0.1
 * @date 2024-05-28
*/

#ifndef POUR_H
#define POUR_H

enum pour_states_t {
    IDLE,
    GANTRY_DECENDING,
    POURING,
    GANTRY_ASCENDING,
};

enum drink_t {
    DRINK1,
    DRINK2,
    MIXED,
};

enum pour_size_setting_t {
    DRINK1_POUR_SIZE,
    DRINK2_POUR_SIZE,
    MIXED_POUR_1_SIZE,
    MIXED_POUR_2_SIZE,
};

typedef struct {
    drink_t drink;
    pour_states_t state;
} drink_pour_t;


extern uint8_t drink1_pour_size;
extern uint8_t drink2_pour_size;
extern uint8_t mixed1_pour_size;
extern uint8_t mixed2_pour_size;

extern drink_pour_t drink_pour;

/**
 * @brief Initialize the pour system by setting the pour sizes and the drink pour state.
*/
void init_pour_system();

/**
 * @brief Set the pour size for a drink.
 * 
 * @param drink The drink to set the pour size for.
 * @param pour_size The pour size to set.
*/
void set_pour_size(pour_size_setting_t setting, uint8_t pour_size);

/**
 * @brief Start the pour sequence for a drink.
 * 
 * @param drink The drink to pour.
*/
void start_pour(drink_t drink);

/**
 * @brief Pour drink sequence driver. Place in main while loop
*/
void pour_seq_loop();

#endif // POUR_H