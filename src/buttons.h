/*
 * buttons.h
 *
 * Created: 17.12.2017 19:04:16
 *  Author: Pashgan
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <asf.h>
#include <conf_board.h>

#define BUT_ACTION_UP     1
#define BUT_ACTION_DOWN   2

typedef struct{
	uint32_t code;
	uint32_t action;
}but_event_t;

void but_init(void);
void but_get_event(but_event_t* event);
bool but_has_event(void);
void but_poll(void);
uint32_t but_get_event_count(void);


#endif /* BUTTONS_H_ */