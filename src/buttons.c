/*
 * buttons.c
 *
 * Created: 17.12.2017 19:04:03
 *  Author: Pashgan
 */ 

#include "buttons.h"

#define BUF_SIZE   64      
#define BUT_AMOUNT 5
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

void but_handler(const uint32_t port_id, const uint32_t pins); 
void but_push_event(uint32_t code, uint32_t action);

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
	
	pmc_enable_periph_clk(BUT_PORT_ID);
	but_init_one(BUT_PORT, 0, BUT_1_PIN, BUT_1_CODE);
	but_init_one(BUT_PORT, 1, BUT_2_PIN, BUT_2_CODE);
	but_init_one(BUT_PORT, 2, BUT_3_PIN, BUT_3_CODE);
	but_init_one(BUT_PORT, 3, BUT_4_PIN, BUT_4_CODE);
	but_init_one(BUT_PORT, 4, BUT_5_PIN, BUT_5_CODE);
	

}

void but_poll(void)
{
	for(uint32_t i = 0; i < BUT_AMOUNT; i++){
		
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

but_event_t but_get_event(void)
{
	uint32_t code = -1;
	uint32_t action = -1;
	
	if (!fifo_is_empty(&event_fifo_desc)){
		cpu_irq_enter_critical();
		fifo_pull_uint32(&event_fifo_desc, &code);
		fifo_pull_uint32(&event_fifo_desc, &action);
		cpu_irq_leave_critical();
	}
	
	but_event_t event;
	event.code = code;
	event.action = action;
	return event;
}

void but_push_event(uint32_t code, uint32_t action)
{
	cpu_irq_enter_critical();
	fifo_push_uint32(&event_fifo_desc, code);
	fifo_push_uint32(&event_fifo_desc, action);
	cpu_irq_leave_critical();
}


