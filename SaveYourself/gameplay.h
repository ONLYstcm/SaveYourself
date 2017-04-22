#pragma once
#include <allegro5\allegro.h>
#include <allegro5\color.h>
#include <allegro5\allegro_image.h>
#include <iostream>
#include <string>
#include "gui_buttons.h"
#include "enemies.h"
#include "genesis_ai_engine.h"
#define GAMING_WINDOW_HEIGHT 600
#define GAMING_WINDOW_WIDTH 1024

#define FPS  60

void clear_disp(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *background){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(background, 0, 0, 0);
}

void play(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *background) {
	 
	ALLEGRO_TIMER *timer;
	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL, "Failed to initialise Allegro 5!\n", NULL, NULL);
		//return -1;
	}


	/* Create the game timer */
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		al_show_native_message_box(NULL, NULL, NULL, "Failed to create timer!\n", NULL, NULL);
		//return -1;
	}


	al_init_image_addon(); //Initialise image loader
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();
	al_init_primitives_addon();


	/* Create the game event queue */
	ALLEGRO_EVENT_QUEUE *event_queue;
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(NULL, NULL, NULL, "Failed to create event queue!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(timer);
		//return -1;
	}


	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	clear_disp(display, background);
	al_start_timer(timer); //Timer started
	
		//short m_x, m_y; //Mouse x & Mouse y
		//The smaller this value, the faster the rockets move
		bool alive = true;
		bool draw = false; 
		
		srand(time(0)); //Make random function based on actual time

		const __int8 no_missiles = 1;
		enemies::missile enemy[no_missiles];
		for (int i = 0; i < no_missiles; i++) {
			enemy[i].create(6);
		}

		Vector target;

	while (alive) {
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events); //Necessary for getting mouse input
		
		if (events.type == ALLEGRO_EVENT_TIMER) {
			draw = true;
		}
		else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			alive = false;
			break;
		}

		else if (events.type == ALLEGRO_EVENT_MOUSE_AXES) {
			target.x = events.mouse.x;
			target.y = events.mouse.y;
		}

		if (draw && al_is_event_queue_empty(event_queue)) {
			draw = false;
			clear_disp(display, background);
			for (int i = 0; i < no_missiles; i++) {
				//AI::follow(enemy[i].particle, target);
				AI::follow((enemy[i].particle), target);
				enemy[i].render(); //update
			}
			al_flip_display();
		}
	}
	if (1) {
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
	}
}