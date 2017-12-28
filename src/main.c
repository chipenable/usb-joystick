/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "buttons.h"

bool enable_scan_keys = false; 
but_event_t but_event; 

void user_callback_sof_action(void)
{
	
	if (enable_scan_keys && but_has_event()){
		but_get_event(&but_event);

#ifdef DEBUG
		printf("code: %d action: %d\n", but_event.code, but_event.action);
#endif

		if (but_event.action == BUT_ACTION_DOWN){
			udi_hid_kbd_down(but_event.code);
		}
		else{
			udi_hid_kbd_up(but_event.code);
		}
	}
	
}

bool my_callback_keyboard_enable(void)
{
	enable_scan_keys = true;
	return true;
}

void my_callback_keyboard_disable(void)
{
	enable_scan_keys = false;
}

void usart_init(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate     = CONF_UART_BAUDRATE,
		.charlength   = CONF_UART_CHAR_LENGTH,
		.paritytype   = CONF_UART_PARITY,
		.stopbits     = CONF_UART_STOP_BITS
	};
	
	ioport_init();
	ioport_set_port_mode(IOPORT_PIOA, PIO_PA8A_URXD | PIO_PA9A_UTXD, IOPORT_MODE_MUX_A);
	ioport_disable_port(IOPORT_PIOA, PIO_PA8A_URXD | PIO_PA9A_UTXD);
	stdio_serial_init(CONF_UART, &usart_serial_options);
}

int main (void)
{
    wdt_disable(WDT);
	irq_initialize_vectors();
	cpu_irq_enable();
	sleepmgr_init();
	sysclk_init();
	udc_start();
	udc_attach();
	but_init();

#ifdef DEBUG 	
    usart_init();
#endif
	
	while(1){
		delay_ms(5);
		but_poll();
	}
}
