#include <allegro5\allegro.h>
#include <allegro5\color.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h> //Normal font
#include <allegro5\allegro_ttf.h> //True Type Font
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "gui_buttons.h"
#include "enemies.h"
#include "gameplay.h"
#include "player.h"
#include "Sound_Engine_Katrina.h"

using namespace std;

ALLEGRO_COLOR blue, white;

button item;
int savedscore, savedlevel, savedlives;
void LoadScore() {
	string line;
	ifstream file;
	savedscore = 0;
	int j = 0;
	file.open("Save_State.txt");
	getline(file, line);
	savedlevel = (line[0] - '0');
	savedlives = (line[1] - '0');
	cout << line.length();
	for (int i = line.length() - 1; i>1; i--)
	{
		savedscore += (line[i] - '0')*pow(10, j);
		j++;
	}
	file.close();
}
int main() {
	system("playBootAnimation.bat");
	Sound_Engine_Katrina soundObj;
	Sound_Engine_Katrina menu_item;
	soundObj.playSound(ALLEGRO_PLAYMODE_LOOP, 1, 0, 1, "Background.ogg");

	ALLEGRO_TIMER *timer;
	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL, "Failed to initialise Allegro 5!\n", NULL, NULL);
		return -1;
	}

	/* Create the game timer */
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		al_show_native_message_box(NULL, NULL, NULL, "Failed to create timer!\n", NULL, NULL);
		return -1;
	}
	al_init_image_addon(); //Initialise image loader
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();


	/* Center the game window on the desktop */
	ALLEGRO_MONITOR_INFO aminfo;
	al_get_monitor_info(0, &aminfo);
	int desktopWidth = aminfo.x2 - aminfo.x1 + 1;
	int desktopHeight = aminfo.y2 - aminfo.y1 + 1;


	ALLEGRO_DISPLAY *display = nullptr; //Create 'display' object (The window itself)
	ALLEGRO_BITMAP *background = nullptr; //Create 'bitmap' object (The image itself)

	ALLEGRO_DISPLAY_MODE   disp_data;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_set_new_display_flags(ALLEGRO_NOFRAME);
	display = al_create_display(disp_data.width, disp_data.height);// gets maximum supported resolution

	if (!display) {
		al_show_native_message_box(NULL, NULL, NULL, "Failed to create display!\n", NULL, NULL);
		al_destroy_timer(timer);
		return -1;
	}

	al_set_window_position(display, 0, 0);
	al_set_window_title(display, "SAVE YOURSELF!");
	
	/*cout << "Please enter your name?" << endl;
	string name;
	getline(cin, name);
	*/

	al_clear_to_color(al_map_rgb(0, 0, 0)); //Make window black

	background = al_load_bitmap("Main_Menu.jpg");
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
			//START		- is HEAD in queue
			start->next = save;
			save->prev = start;
			start->text = "START";
			start->height = 200;
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
		start->font = item.createMenuText("START", 200, display, blue);
		save->font = item.createMenuText("SAVE", 275, display, white);
		load->font = item.createMenuText("LOAD", 350, display, white);
		options->font = item.createMenuText("OPTIONS", 425, display, white);
		leaderboards->font = item.createMenuText("LEADERBOARDS", 500, display, white);
		leave->font = item.createMenuText("LEAVE", 575, display, white);
	}
	else {
		cout << "Couldn't load Menu Items. No memory left" << endl;
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
				menu_item.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1, "menu_item.ogg");
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
						soundObj.destroySound();
						system("playCredits.bat");
						menu_item.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1, "futuresoundfx-19.ogg");
						al_destroy_bitmap(background);
						background = al_load_bitmap("Background_Level1.jpg");
			
							play(display, background);
						
						break;
					case 2:
						break;
					case 3:
						LoadScore();
						soundObj.destroySound();
						menu_item.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1, "futuresoundfx-19.ogg");
						al_destroy_bitmap(background);
						background = al_load_bitmap("Background_Level1.jpg");
						play(display, background, savedlevel,savedscore,savedlives,true);
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

	//al_rest(30);
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
