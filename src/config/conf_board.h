/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

//#define DEBUG_BUILD

/** player 1 */

#define BUT_1_PORT       PIOD
#define BUT_1_PIN        PIO_PD9
#define BUT_1_CODE       HID_R

#define BUT_2_PORT       PIOD
#define BUT_2_PIN        PIO_PD10
#define BUT_2_CODE       HID_Y

#define BUT_3_PORT       PIOC
#define BUT_3_PIN        PIO_PC1
#define BUT_3_CODE       HID_T

#define BUT_4_PORT       PIOC
#define BUT_4_PIN        PIO_PC2
#define BUT_4_CODE       HID_G

#define BUT_5_PORT       PIOC
#define BUT_5_PIN        PIO_PC3
#define BUT_5_CODE       HID_F

#define BUT_6_PORT       PIOC
#define BUT_6_PIN        PIO_PC4
#define BUT_6_CODE       HID_D

#define BUT_7_PORT       PIOC
#define BUT_7_PIN        PIO_PC5
#define BUT_7_CODE       HID_A

#define BUT_8_PORT       PIOC
#define BUT_8_PIN        PIO_PC6
#define BUT_8_CODE       HID_W

#define BUT_9_PORT       PIOC
#define BUT_9_PIN        PIO_PC7
#define BUT_9_CODE       HID_S

/** player 2 */

#define BUT_10_PORT       PIOC
#define BUT_10_PIN        PIO_PC15
#define BUT_10_CODE       HID_O

#define BUT_11_PORT       PIOC
#define BUT_11_PIN        PIO_PC16
#define BUT_11_CODE       HID_P

#define BUT_12_PORT       PIOC
#define BUT_12_PIN        PIO_PC17
#define BUT_12_CODE       HID_OPEN_BRACKET

#define BUT_13_PORT       PIOC
#define BUT_13_PIN        PIO_PC18
#define BUT_13_CODE       HID_L

#define BUT_14_PORT       PIOC
#define BUT_14_PIN        PIO_PC19
#define BUT_14_CODE       HID_COLON

#define BUT_15_PORT       PIOA
#define BUT_15_PIN        PIO_PA20
#define BUT_15_CODE       HID_K

#define BUT_16_PORT       PIOA
#define BUT_16_PIN        PIO_PA19
#define BUT_16_CODE       HID_H

#define BUT_17_PORT       PIOC
#define BUT_17_PIN        PIO_PC9
#define BUT_17_CODE       HID_U

#define BUT_18_PORT       PIOC
#define BUT_18_PIN        PIO_PC8
#define BUT_18_CODE       HID_J

#endif // CONF_BOARD_H
