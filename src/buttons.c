/*
 * buttons.c
 *
 * Created: 17.12.2017 19:04:03
 *  Author: Pashgan
 */ 

#include "buttons.h"

#define BUF_SIZE   64     
#define BUT_AMOUNT 18
#define THRESHOLD  5

typedef struct{
	Pio* pio;
	uint32_t id;
	uint32_t pin;
	uint32_t code;
	uint32_t counter;
	bool state;
}but_t;


static but_t all_buttons[BUT_AMOUNT]; 

static uint32_t event_fifo_buffer[BUF_SIZE];
static fifo_desc_t event_fifo_desc;

void but_push_event(uint32_t code, uint32_t action);
void but_init_one(Pio* pio, uint32_t id, uint32_t pin, uint32_t code);

/********************************************************************/

void but_init_one(Pio* pio, uint32_t id, uint32_t pin, uint32_t code)
{
	but_t* but = &all_buttons[id];
	
	but->pio = pio;
	but->id = id; 
	but->pin = pin;
	but->code = code;
	but->counter = 0; 
	but->state = false;
	
	pio_set_input(pio, pin, PIO_PULLUP);
}

void but_init(void)
{
	fifo_init(&event_fifo_desc, event_fifo_buffer, BUF_SIZE);
	
	pmc_enable_periph_clk(ID_PIOD);
	pmc_enable_periph_clk(ID_PIOC);
	
	but_init_one(BUT_1_PORT, 0, BUT_1_PIN, BUT_1_CODE);
	but_init_one(BUT_2_PORT, 1, BUT_2_PIN, BUT_2_CODE);
	but_init_one(BUT_3_PORT, 2, BUT_3_PIN, BUT_3_CODE);
	but_init_one(BUT_4_PORT, 3, BUT_4_PIN, BUT_4_CODE);
	but_init_one(BUT_5_PORT, 4, BUT_5_PIN, BUT_5_CODE);
	but_init_one(BUT_6_PORT, 5, BUT_6_PIN, BUT_6_CODE);
    but_init_one(BUT_7_PORT, 6, BUT_7_PIN, BUT_7_CODE);
	but_init_one(BUT_8_PORT, 7, BUT_8_PIN, BUT_8_CODE);
	but_init_one(BUT_9_PORT, 8, BUT_9_PIN, BUT_9_CODE);
	
	but_init_one(BUT_10_PORT, 9, BUT_10_PIN, BUT_10_CODE);
	but_init_one(BUT_11_PORT, 10, BUT_11_PIN, BUT_11_CODE);
	but_init_one(BUT_12_PORT, 11, BUT_12_PIN, BUT_12_CODE);
	but_init_one(BUT_13_PORT, 12, BUT_13_PIN, BUT_13_CODE);
	but_init_one(BUT_14_PORT, 13, BUT_14_PIN, BUT_14_CODE);
	but_init_one(BUT_15_PORT, 14, BUT_15_PIN, BUT_15_CODE);
	but_init_one(BUT_16_PORT, 15, BUT_16_PIN, BUT_16_CODE);
	but_init_one(BUT_17_PORT, 16, BUT_17_PIN, BUT_17_CODE);
	but_init_one(BUT_18_PORT, 17, BUT_18_PIN, BUT_18_CODE);
}

void but_poll(void)
{
	for(uint8_t i = 0; i < BUT_AMOUNT; i++){
		
		but_t* but = &all_buttons[i];
	
		bool but_is_pressed = pio_get(but->pio, PIO_TYPE_PIO_INPUT, but->pin) == 0;
		if (but_is_pressed){
			if (but->counter < THRESHOLD){
				but->counter++;
			}
			else{
				if (!but->state){
					but->state = true;
					but_push_event(but->code, BUT_ACTION_DOWN);
				}
			}
		}
		else{
			if (but->state){
				but->state = false;
				but->counter = 0;
				but_push_event(but->code, BUT_ACTION_UP);
			}
		}
	}
	
}

bool but_has_event(void)
{
	return !fifo_is_empty(&event_fifo_desc);
}

void but_get_event(but_event_t* event)
{
	uint32_t code = -1;
	uint32_t action = -1;
	
	if (!fifo_is_empty(&event_fifo_desc)){
		cpu_irq_enter_critical();
		fifo_pull_uint32(&event_fifo_desc, &code);
		fifo_pull_uint32(&event_fifo_desc, &action);
		cpu_irq_leave_critical();
	}
	
	event->code = code;
	event->action = action;
}

void but_push_event(uint32_t code, uint32_t action)
{
	cpu_irq_enter_critical();
	fifo_push_uint32(&event_fifo_desc, code);
	fifo_push_uint32(&event_fifo_desc, action);
	cpu_irq_leave_critical();
}

uint32_t but_get_event_count(void)
{
	return fifo_get_used_size(&event_fifo_desc)/2;
}


