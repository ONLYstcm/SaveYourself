#pragma once
#include <allegro5\allegro.h>
#include <allegro5\color.h>
#include <allegro5\allegro_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include "gui_buttons.h"
#include "enemies.h"
#include "player.h"
#include "nukes.h"
#include "genesis_ai_engine.h"
#include "staver_collision_engine.h"
#include "Sound_Engine_Katrina.h"
#define GAMING_WINDOW_HEIGHT 768
#define GAMING_WINDOW_WIDTH 1366
extern short points = 0, lives = 3, level = 1, enemy_timer = 0, spaceship_timer=0, missilesPresent = 0, spaceshipPresent = 0, time_left=120, stopwatch=0;

#define FPS  60
using namespace std;
void clear_disp(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *background){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(background, 0, 0, 0);
}

void play(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *background, int loadlevel=1, int loadscore=0, int loadlives=3) {
	level = loadlevel;
	points = loadscore;
	lives = loadlives;
	ALLEGRO_TIMER *timer;
	ALLEGRO_COLOR blue = al_map_rgb(0, 222, 255);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255); 
	ALLEGRO_COLOR orange = al_map_rgb(255, 140, 0);
	ALLEGRO_COLOR green = al_map_rgb(66, 233, 40);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_BITMAP* spaceshipimage = al_load_bitmap("enemyship.png");
	bool levelChangeFlag = false;
	bool levelChangeFlag2 = false;
	bool levelChangeFlag3 = false;
	bool loadstate = false;

	//Creating game objects
	Vector target;
	player::playership playerobj;
	player::PowerUps PowerObj;
	player::PowerUps PowerObj2;
	const short no_missiles = 100, no_spaceships = 50;
	enemies::missile missile[no_missiles];
	enemies::spaceship enemyspaceship[no_spaceships];
	nukes::nukes bomb;
	Sound_Engine_Katrina background_music;
	background_music.playSound(ALLEGRO_PLAYMODE_LOOP, 1, 0, 1, "Sounds from outer space, audio atmosphere.ogg");
	Sound_Engine_Katrina Level_Change;
	Sound_Engine_Katrina Bullet;
	Sound_Engine_Katrina Explosion;
	Sound_Engine_Katrina hurry; //not yet used 
	Sound_Engine_Katrina incomming_missile; //not yet used
	Sound_Engine_Katrina laser_shot; //not yet used

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
	
	ALLEGRO_FONT *text = al_load_ttf_font("ROCKWELL_BOLD.TTF", 16, 0); //not yet used
	if (text == nullptr)  //Check if pointer was created if not show error
	{
		cerr << "Cannot Load Text" << endl;
		al_rest(5.0);
		//return -1;
	} 

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
		
		/*for (int i = 0; i < no_spaceships; i++) {
			enemyspaceship[i].create(AI::random_border_positition().x, AI::random_border_positition().y, 25, 25,spaceshipimage);
		}*/

		playerobj.create(20,20);
		int countspaceship = 0;
	while (alive) {
		if (countspaceship < no_spaceships)
		{
			enemyspaceship[countspaceship].create(AI::random_border_positition().x, AI::random_border_positition().y, 25, 25, spaceshipimage);
			countspaceship++;
		}
		
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events); //Necessary for getting mouse input
		al_get_keyboard_state(&keyState);
		if ((points >= 25 && levelChangeFlag == false) || (loadstate == true && loadlevel == 2))//the flag was used so that code runs only once
		{
			Level_Change.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1, "alert-5.ogg");
			al_rest(1);
			al_destroy_bitmap(background);
			background = al_load_bitmap("Background_Level2.jpg");
			spaceshipimage = al_load_bitmap("EnemyLevel2.png");
			level = 2;
			levelChangeFlag = true;
		}
		if ((points >= 100 && levelChangeFlag2 == false) ||(loadstate==true && loadlevel==3))//the flag was used so that code runs only once
		{
			Level_Change.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1, "alert-5.ogg");
			al_rest(1);
			al_destroy_bitmap(background);
			background = al_load_bitmap("Background_Level3.jpg");
			spaceshipimage = al_load_bitmap("EnemyLevel3.png");
			level = 3;
			levelChangeFlag2 = true;
		}
		if (points >= 150 && levelChangeFlag3 == false && loadstate==false)
		{
			Level_Change.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1, "alert-5.ogg");
			//End Credits go here
			clear_disp(display, background);
			background = al_load_bitmap("winner.jpg");
			al_flip_display();
			al_rest(10);
			levelChangeFlag3 = true;
			exit(0);
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_1))// Saves Game
		{
		ofstream outfile;
			outfile.open("Save_State.txt");	
			outfile << level <<lives << points;
			outfile.close();


		}
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)|| al_key_down(&keyState, ALLEGRO_KEY_S))
			playerobj.particle.move('d');
		if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) || al_key_down(&keyState, ALLEGRO_KEY_A))
			playerobj.particle.move('l');
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) || al_key_down(&keyState, ALLEGRO_KEY_D))
			playerobj.particle.move('r');
		if (al_key_down(&keyState, ALLEGRO_KEY_UP) || al_key_down(&keyState, ALLEGRO_KEY_W))
			playerobj.particle.move('u');
		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
			exit(0);
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
		
		enemy_timer++;
		spaceship_timer++;
		stopwatch++;
		if (draw && al_is_event_queue_empty(event_queue)) {
			draw = false;
			clear_disp(display, background);

			switch (level)	//This switch statement determines how the enemies attack in the level
			{
			case 1:
				for (int i = 0; i < missilesPresent; i++) {
					missile[i].particle.travel(0, 0, missile[i].particle.getVector('U').x, missile[i].particle.getVector('U').y); //update
					missile[i].render(); //update
				}
				if (enemy_timer > 100) {
					missile[missilesPresent] = AI::launchMissile(level);
					enemy_timer = 0;
					missilesPresent++;
				}

				if (spaceship_timer > 500) {
					for (int i = 0; i < spaceshipPresent; i++) {
						if(enemyspaceship[i].isVisible()){
							bomb.fire(4, 4, enemyspaceship[i].particle.getVector('P'), playerobj.particle.getVector('P'));
						}
					}
					if (spaceshipPresent<no_spaceships){
					enemyspaceship[spaceshipPresent].setVisible(true);
					spaceshipPresent++;
					}
					spaceship_timer = 0;
				}

				for (int i = 0; i < spaceshipPresent; i++) {
					AI::rotate((enemyspaceship[i].particle), playerobj.particle.getVector('P')); //face the player
					enemyspaceship[i].render(spaceshipimage); //update
				}
					break;
				case 2:
					PowerObj.render();
					PowerObj.move();
					for (int i = 0; i < 20; i++) {
						AI::follow((missile[i].particle), playerobj.particle);
						missile[i].particle.travel(0.25, 0.25, missile[i].particle.getVector('U').x, missile[i].particle.getVector('U').y); //update
						missile[i].render(); //update
					}
					if (enemy_timer > 100) {
						missile[missilesPresent] = AI::launchMissile(level);
						enemy_timer = 0;
						missilesPresent++;
					}

					if (spaceship_timer > 500) {
						for (int i = 0; i < spaceshipPresent; i++) {
							if (enemyspaceship[i].isVisible()) {
								bomb.fire(4, 4, enemyspaceship[i].particle.getVector('P'), playerobj.particle.getVector('P'));
							}
						}
						if (spaceshipPresent<no_spaceships) {
							enemyspaceship[spaceshipPresent].setVisible(true);
							spaceshipPresent++;
						}
						spaceship_timer = 0;
					}

					for (int i = 0; i < 10; i++) {
						AI::follow((enemyspaceship[i].particle), playerobj.particle);
						AI::rotate((enemyspaceship[i].particle), playerobj.particle.getVector('P')); //face the player
						enemyspaceship[i].render(spaceshipimage); //update
					}
					break;
				case 3:
					
					PowerObj2.render();
					PowerObj2.move();
					for (int i = 0; i < missilesPresent; i++) {
						missile[i].particle.travel(0, 0, missile[i].particle.getVector('U').x, missile[i].particle.getVector('U').y); //update
						missile[i].render(); //update
					}
					if (enemy_timer > 100) {
						missile[missilesPresent] = AI::launchMissile(level);
						enemy_timer = 0;
						missilesPresent++;
					}

					if (spaceship_timer > 500) {
						for (int i = 0; i < spaceshipPresent; i++) {
							if (enemyspaceship[i].isVisible()) {
								bomb.fire(4, 4, enemyspaceship[i].particle.getVector('P'), playerobj.particle.getVector('P'));
							}
						}
						if (spaceshipPresent<no_spaceships) {
							enemyspaceship[spaceshipPresent].setVisible(true);
							spaceshipPresent++;
						}
						spaceship_timer = 0;
					}

					for (int i = 0; i < spaceshipPresent; i++) {
						AI::rotate((enemyspaceship[i].particle), playerobj.particle.getVector('P')); //face the player
						enemyspaceship[i].render(spaceshipimage); //update
					}
					break;
				default:
					break;
				}


			playerobj.render(); //update
			bomb.render();
			bomb.enemyrender();
			al_draw_text(text, orange, 1250, 20, ALLEGRO_ALIGN_LEFT, "Points: ");
			al_draw_text(text, orange, 1300, 20, ALLEGRO_ALIGN_INTEGER, (to_string(points).c_str()));
			al_draw_text(text, green, 1250, 40, ALLEGRO_ALIGN_LEFT, "Lives: ");
			al_draw_text(text, green, 1300, 40, ALLEGRO_ALIGN_INTEGER, (to_string(lives).c_str()));
			al_draw_text(text, blue, 1250, 60, ALLEGRO_ALIGN_LEFT, "Level: ");
			al_draw_text(text, blue, 1300, 60, ALLEGRO_ALIGN_INTEGER, (to_string(level).c_str()));
			if (stopwatch > 500) {
				time_left--;
				if (time_left <= 15) {
					hurry.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1, "alert-5.ogg");
				}
				stopwatch = 0;
			}
			if (time_left <= 15) {
				al_draw_text(text, white, 1250, 80, ALLEGRO_ALIGN_LEFT, "Time: ");
				al_draw_text(text, white, 1300, 80, ALLEGRO_ALIGN_INTEGER, (to_string(time_left).c_str()));
			}
			else{
			al_draw_text(text, white, 1250, 80, ALLEGRO_ALIGN_LEFT, "Time: ");
			al_draw_text(text, white, 1300, 80, ALLEGRO_ALIGN_INTEGER, (to_string(time_left).c_str()));
			}

			//Check collisions - If anyone has been hit
			AI::hit(bomb.particle, bomb.bullets, missile, no_missiles);
			AI::hit(bomb.particle, bomb.bullets, enemyspaceship, no_spaceships);
			AI::playerhit(bomb.atom, bomb.enemybullets, playerobj);

			for (int i = 0; i < no_missiles; i++) {
				if (collision::Collide((missile[i].particle), playerobj.particle) && (missile[i].isVisible())) {
					if (PowerObj.enabled) {
						playerobj.playershipimage = al_load_bitmap("playa.png");
						PowerObj.enabled = false;
						lives++;
					}
					else if (PowerObj2.enabled) {
						playerobj.playershipimage = al_load_bitmap("playa.png");
						PowerObj2.enabled = false;
						lives++;
					}
					else {
						Explosion.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1, "Explosion.wav");
						al_rest(1);
						missile[i].destroy();
						lives--;
					}

				}
			}

			for (int i = 0; i < no_spaceships; i++) {
				if (collision::Collide((enemyspaceship[i].particle), playerobj.particle) && (enemyspaceship[i].isVisible())) {
					if (PowerObj.enabled) {
						playerobj.playershipimage = al_load_bitmap("playa.png");
						PowerObj.enabled = false;
						enemyspaceship[i].destroy();
					}

					else if (PowerObj2.enabled) {
						playerobj.playershipimage = al_load_bitmap("playa.png");
						PowerObj2.enabled = false;
						enemyspaceship[i].destroy();
					}
					else
					{
						Explosion.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1, "Explosion.wav");
						al_rest(1);
						enemyspaceship[i].destroy();
						lives--;
					}
				}
			}

			if (collision::Collide((PowerObj.particle), playerobj.particle)) {
				PowerObj.enabled = true;
				PowerObj.destroy();
				playerobj.playershipimage = al_load_bitmap("playa shield.png");


			}
			if (collision::Collide((PowerObj2.particle), playerobj.particle)) {
				PowerObj2.enabled = true;
				PowerObj2.destroy();
				playerobj.playershipimage = al_load_bitmap("playa shield.png");
			}
			if (lives==0)
			{
				playerobj.destroy();
				//background = al_load_bitmap("Game_Over.jpg");
				//al_rest(5);
				alive = false;
				background_music.destroySound();
				al_destroy_timer(timer);
				al_destroy_display(display);
				al_destroy_event_queue(event_queue);
				exit(0);

			}
			al_flip_display();
		}
	}

	
}
/*
void setText(ALLEGRO_FONT *text, const char *word, short x_index, short y_index, ALLEGRO_DISPLAY *display, ALLEGRO_COLOR colour) {
	al_draw_text(text, colour, x_index, y_index, ALLEGRO_ALIGN_RIGHT, word); //Otherwise display the text on the screen
}
*/