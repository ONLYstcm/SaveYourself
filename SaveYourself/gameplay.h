#pragma once
#include <allegro5\allegro.h>
#include <allegro5\color.h>
#include <allegro5\allegro_image.h>
#include <iostream>
#include <string>
#include "gui_buttons.h"
#include "enemies.h"
#include "player.h"
#include "nukes.h"
#include "genesis_ai_engine.h"
#include "staver_collision_engine.h"
#include "Sound_Engine_Katrina.h"
#define GAMING_WINDOW_HEIGHT 600
#define GAMING_WINDOW_WIDTH 1024
extern short points=0, lives=3;

#define FPS  60
using namespace std;
void clear_disp(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *background){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(background, 0, 0, 0);
}

void play(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *background) {
	 
	ALLEGRO_TIMER *timer;
	//Creating game objects
	Vector target;
	const __int8 no_missiles = 1;
	const __int8 no_spaceships = 3;
	player::playership playerobj;
	enemies::missile enemy[no_missiles];
	enemies::spaceship enemyspaceship[no_spaceships];
	nukes::nukes bomb;
	Sound_Engine_Katrina Bullet;

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

	/* Create the game event keystate */
	ALLEGRO_KEYBOARD_STATE keyState;

	/* Create the font text */
	/*
	ALLEGRO_FONT *points_text; //not yet used
	ALLEGRO_FONT *lives_text; //not yet used
	ALLEGRO_FONT *time_text; //not yet used
	*/

	/* Create the game event queue */
	ALLEGRO_EVENT_QUEUE *event_queue;
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(NULL, NULL, NULL, "Failed to create event queue!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(timer);
		//return -1;
	}

	//Register all events
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //stores the keyboard buttons in a queue to be executed


	clear_disp(display, background);
	al_start_timer(timer); //Timer started
	
		bool alive = true;
		bool draw = false; 
		
		srand(time(0)); //Make random function based on actual time

		
		for (int i = 0; i < no_missiles; i++) {
			enemy[i].create(AI::random_border_positition().x, AI::random_border_positition().y,6,6,6);
		}
		for (int i = 0; i < no_spaceships; i++) {
			enemyspaceship[i].create(AI::random_border_positition().x, AI::random_border_positition().y, 25, 25);
		}
		playerobj.create(20,20);


	while (alive) {
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events); //Necessary for getting mouse input
		al_get_keyboard_state(&keyState);

		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)|| al_key_down(&keyState, ALLEGRO_KEY_S))
			playerobj.particle.move('d');
		if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) || al_key_down(&keyState, ALLEGRO_KEY_A))
			playerobj.particle.move('l');
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) || al_key_down(&keyState, ALLEGRO_KEY_D))
			playerobj.particle.move('r');
		if (al_key_down(&keyState, ALLEGRO_KEY_UP) || al_key_down(&keyState, ALLEGRO_KEY_W))
			playerobj.particle.move('u');

		if (events.type == ALLEGRO_EVENT_KEY_DOWN)//Check if key was pressed 
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:
				bomb.shoot(4, 4, playerobj.particle.getVector('P'), target);
				Bullet.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1,"Bullet.wav");
				break;
			}
		}


		if (events.type == ALLEGRO_EVENT_TIMER) {
			draw = true;
			}
		
		else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			alive = false;
			break;
		}

		if (events.type == ALLEGRO_EVENT_MOUSE_AXES) {
			target.x = events.mouse.x;
			target.y = events.mouse.y;
			AI::rotate((playerobj.particle), target);
		}
		
		

		if (draw && al_is_event_queue_empty(event_queue)) {
			draw = false;
			clear_disp(display, background);
			for (int i = 0; i < no_missiles; i++) {
				AI::follow((enemy[i].particle), playerobj.particle);
				enemy[i].render(); //update
			}
			for (int i = 0; i < no_spaceships; i++) {
				AI::follow((enemyspaceship[i].particle), playerobj.particle);
				enemyspaceship[i].render(); //update
			}
			//AI::rotate((playerobj.particle), target);
			//bomb.particle.move('s', (tan(bomb.angle1) >= 1)? 1: -1, (tan(bomb.angle1) >= 1) ? 1 : -1);
			playerobj.render(); //update
			bomb.render();
			AI::hit(bomb.particle, bomb.bullets, enemy, no_missiles);
			AI::hit(bomb.particle, bomb.bullets, enemyspaceship, no_spaceships);
			for (int i = 0; i < no_missiles; i++) {
				if (collision::Collide((enemy[i].particle), playerobj.particle)&&(enemy[i].isVisible())) {
					playerobj.destroy();
				}
			}

			al_flip_display();
		}
	}

	if (true) {
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
	}
}

void setText(ALLEGRO_FONT *text, const char *word, short x_index, short y_index, ALLEGRO_DISPLAY *display, ALLEGRO_COLOR colour) {
	al_draw_text(text, colour, x_index, y_index, ALLEGRO_ALIGN_RIGHT, word); //Otherwise display the text on the screen
}