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

//#define DEBUG

//кнопки джойстика
#define BUT_PORT_ID      ID_PIOD
#define BUT_PORT         PIOD
#define BUT_IRQn         PIOD_IRQn

#define BUT_1_PIN        PIO_PD0
#define BUT_1_CODE       HID_UP

#define BUT_2_PIN        PIO_PD1
#define BUT_2_CODE       HID_DOWN

#define BUT_3_PIN        PIO_PD2
#define BUT_3_CODE       HID_LEFT

#define BUT_4_PIN        PIO_PD3
#define BUT_4_CODE       HID_RIGHT

#define BUT_5_PIN        PIO_PD4
#define BUT_5_CODE       HID_SPACEBAR


#endif // CONF_BOARD_H
