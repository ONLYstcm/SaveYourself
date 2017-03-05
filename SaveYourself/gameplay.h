#pragma once
#include <allegro5\allegro.h>
#include <allegro5\color.h>
#include <allegro5\allegro_image.h>
#include <iostream>
#include <string>
#include "gui_buttons.h"
#include "enemies.h"
#define FPS  60

void play(ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *background) {
	ALLEGRO_TIMER *timer = al_create_timer(1 / FPS);
	
	al_init(); //Initialise Allegro
	al_init_image_addon(); //Initialise image loader
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue(); 

	//al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	enemies::missile badboy;
	badboy.create(display, 0, 0);
	
	short m_x, m_y; //Mouse x & Mouse y
	float speed = 2;
	__int8 pace = 10; //The smaller this value, the faster the rockets move
	bool alive = true;
	bool draw = false;

	al_start_timer(timer); //Timer started

	while(alive) {
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events); //Necessary for getting mouse input
		if (events.type == ALLEGRO_EVENT_TIMER && !draw) {
		   draw = true;
		}
		else if (events.type == ALLEGRO_EVENT_MOUSE_AXES) {
			m_x = events.mouse.x;
			m_y = events.mouse.y;
			badboy.setDir(m_x, m_y);
		}
		else if (draw && al_is_event_queue_empty(event_queue)) {
			draw = false;
			badboy.advance_by_time(pace,speed);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(background, 0, 0, 0);
			badboy.update(display);
			al_flip_display();
		}
	}
	al_destroy_timer(timer);
}

