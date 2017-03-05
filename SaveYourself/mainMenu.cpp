#include <allegro5\allegro.h>
#include <allegro5\color.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h> //Normal font
#include <allegro5\allegro_ttf.h> //True Type Font
#include <iostream>
#include <string>
#include "gui_buttons.h"
#include "enemies.h"
#include "gameplay.h"
#define screenHeight 600
#define screenWidth 1024

using namespace std;

ALLEGRO_COLOR blue, white;

button item;

int main() {
	al_init(); //Initialise Allegro
	al_init_image_addon(); //Initialise image loader
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();

	ALLEGRO_DISPLAY *display = nullptr; //Create 'display' object (The window itself)
	ALLEGRO_BITMAP *background = nullptr; //Create 'bitmap' object (The image itself)

	al_set_app_name("Main Menu");
	display = al_create_display(screenWidth, screenHeight); //Dimension of window

	if (display == nullptr) //Check if display was not created
	{
		std::cerr << "Cannot Load Main Menu" << std::endl;
		al_rest(5.0);
		return EXIT_FAILURE;
	}
	
	/*cout << "Please enter your name?" << endl;
	string name;
	getline(cin, name);
	*/

	al_clear_to_color(al_map_rgb(0, 0, 0)); //Make window black

	background = al_load_bitmap("seamless space_0.PNG");
	al_draw_bitmap(background, 0, 0, 0);

	blue = al_map_rgb(0, 222,255);
	white = al_map_rgb(255, 255, 255);

	struct menuItem{	//Circular Queue implementation for menu items
		const char * text;
		ALLEGRO_FONT *font;
		menuItem *next;
		menuItem *prev;
		short number;
		int height;
	}*start, *save, *load, *options, *leaderboards, *leave,*index;

	//Memory allocation for menu items (linked list/circular queue)
	{
		start = (struct menuItem *) malloc(sizeof(struct menuItem));
		save = (struct menuItem *) malloc(sizeof(struct menuItem));
		load = (struct menuItem *) malloc(sizeof(struct menuItem));
		options = (struct menuItem *) malloc(sizeof(struct menuItem));
		leaderboards = (struct menuItem *) malloc(sizeof(struct menuItem));
		leave = (struct menuItem *) malloc(sizeof(struct menuItem));
		index = (struct menuItem *) malloc(sizeof(struct menuItem));
	}
	if ((start != NULL) && (save != NULL) && (load != NULL) && (options != NULL) && (leaderboards != NULL) && (leave != NULL) && (index != NULL)) {
		//Set queue order
			//START		HEAD in queue
			start->next = save;
			save->prev = start;
			start->text = "START";
			start->height = 100;
			start->number = 1;

			//SAVE
			save->next = load;
			load->prev = save;
			save->text = "SAVE";
			save->height = (save->prev->height)+75;
			save->number = 2;

			//LOAD
			load->next = options;
			options->prev = load;
			load->text = "LOAD";
			load->height = (load->prev->height) + 75;
			load->number = 3;

			//OPTIONS
			options->next = leaderboards;
			leaderboards->prev = options;
			options->text = "OPTIONS";
			options->height = (options->prev->height) + 75;
			options->number = 4;

			//LEADERBOARDS
			leaderboards->next = leave;
			leave->prev = leaderboards;
			leaderboards->text = "LEADERBOARDS";
			leaderboards->height = (leaderboards->prev->height) + 75;
			leaderboards->number = 5;

			//LEAVE		Tail in Queue
			leave->next = start;
			start->prev = leave;
			leave->text = "LEAVE";
			leave->height = (leave->prev->height) + 75;
			leave->number = 6;

			index = start;

		//Initial menu item properties (position & colour)
		start->font = item.createMenuText("START", 100, display, blue);
		save->font = item.createMenuText("SAVE", 175, display, white);
		load->font = item.createMenuText("LOAD", 250, display, white);
		options->font = item.createMenuText("OPTIONS", 325, display, white);
		leaderboards->font = item.createMenuText("LEADERBOARDS", 400, display, white);
		leave->font = item.createMenuText("LEAVE", 475, display, white);
	}
	else {

	}

	al_flip_display();
	bool selection = false;

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //Necessary for getting keyboard input
	ALLEGRO_EVENT events;

	while (!selection) {
		al_wait_for_event(event_queue, &events); //Necessary for getting keyboard input
			if (events.type == ALLEGRO_EVENT_KEY_DOWN)//Check if key was pressed 
			{
				switch (events.keyboard.keycode)
				{
				case ALLEGRO_KEY_DOWN:
					index->font = item.changeMenuText(index->font, index->text, index->height, display, white);
					index = index->next;
					index->font = item.changeMenuText(index->font, index->text, index->height, display, blue);
					break;
				case ALLEGRO_KEY_UP:
					index->font = item.changeMenuText(index->font, index->text, index->height, display, white);
					index = index->prev;
					index->font = item.changeMenuText(index->font, index->text, index->height, display, blue);
					break;
				case ALLEGRO_KEY_ENTER:
					switch (index->number)
					{
						selection = true; //Makes the selection true 
					case 1:
						play(display,background);
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						exit(0);
						break;
					default:
						selection = false; //If the selected item cannot be found, then selection is changed back to false
						break;
					}
					break;
				default:
					break;
				}
		}

		al_flip_display();
	}

	al_rest(30);
	al_destroy_display(display);
	al_destroy_bitmap(background);

	{
		free(start);
		free(save);
		free(load);
		free(options);
		free(leaderboards);
		free(leave);
	}
	return 0;
}
