#include <stdint.h>
#include <stdbool.h>
#include "baremetal_binary.h"

// VIEW
#define MATRIX_WIDTH (16)
#define MATRIX_BASE ((volatile uint8_t *)0xE020U)
#define HEX_DISP ((volatile uint8_t *)0xE800U)
#define COLOR_DISP ((volatile bool *)0xE000U)

// CONTROLLER
#define KEYPAD ((volatile uint8_t *)0xD010U)

// UART debug output
#define UART_DATA_OUT ((volatile uint8_t *)0xE040U)

// typedefs

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    TOGGLE_COLOR
} command;

// MODEL state and prototypes:

typedef struct {
    uint8_t matrix[16];
    uint8_t row, col;
    bool color; // false = black, true = yellow
} model_t;

model_t m;

// MODEL functions
void model_paint_row_col(void);

void model_init(void){
    for (uint8_t i = 0; i < MATRIX_WIDTH; i=i+1) {
        m.matrix[i] = B8(00000000);
    }
    m.row = 3;
    m.col = 4;
    m.color = true;
    model_paint_row_col();
}

void model_paint_row_col(void){
    if (m.color) {
        // set dot, don't touch others
        m.matrix[m.col] = m.matrix[m.col] | (1U << m.row);
    } else {
        // clear dot, don't touch others
        m.matrix[m.col] = m.matrix[m.col] & ~(1U << m.row);
    }
}

void model_toggle_color(void){
    m.color = !m.color;
}

// MODEL move
void model_update(command c) {

    // declare new state
    uint8_t new_row, new_col;
    bool new_color;

    // new_state = f(state, input)
    new_row      = m.row;
    new_col      = m.col;
    new_color    = m.color;

    switch (c) {
        case DOWN:  new_row = (m.row == 0) ? m.row : m.row - 1;
                    break;
        case UP:    new_row = (m.row == 7) ? m.row : m.row + 1;
                    break;
        case LEFT:  new_col = (m.col == 0) ? m.col : m.col - 1;
                    break;
        case RIGHT: new_col = (m.col == (MATRIX_WIDTH-1)) ? m.col: m.col + 1;
                    break;
        case TOGGLE_COLOR:  
                    new_color = !m.color;
                    break;
        default:    break;
    }

    // state <= next_state
    m.row      = new_row;
    m.col      = new_col;
    m.color    = new_color;
    // update model
    model_paint_row_col();
}

// VIEW update - transfer MODEL to VIEW
void update_view(model_t m_copy){
    for (uint8_t i = 0; i < MATRIX_WIDTH; i=i+1) {
        *(MATRIX_BASE + i) = m_copy.matrix[i];
    }
    *(HEX_DISP +1) = m_copy.row;
    *(HEX_DISP)    = m_copy.col;
    *(COLOR_DISP)  = m_copy.color;
}

// CONTROLLER
void read_keypad_and_model_update(void){
    uint8_t key = *KEYPAD;  // remember KEYPAD is read2clear
    if (key & B8(10000000)) {
        // key is valid, strip valid bit
        key = key & B8(01111111);
        *UART_DATA_OUT = key;
    } else {
        // key is not valid, return
        return;
    }
    switch (key) {
        case B8(00010001) : // row 1 col 1, UP arrow
                            model_update(UP);
                            break;
        case B8(00100000) : // row 2 col 0, LEFT arrow
                            model_update(LEFT);
                            break;
        case B8(00100010) : // row 2 col 2, RIGHT arrow
                            model_update(RIGHT);
                            break;
        case B8(00110001) : // row 3 col 1, DOWN arrow
                            model_update(DOWN);
                            break;
        case B8(00110011) : // row 3 col 3, TOGGLE_COLOR
                            model_update(TOGGLE_COLOR);
                            break;
        default:            break;
    }
}

void main(void){
    model_init();
    while (true) {
        read_keypad_and_model_update();
        update_view(m);
    }
}
