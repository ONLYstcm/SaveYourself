#pragma once
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\color.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h> //Normal font
#include <allegro5\allegro_ttf.h> //True Type Font
#include <string>

using namespace std;

class button {
public:
	ALLEGRO_FONT * createMenuText(const char *word, short y_index, ALLEGRO_DISPLAY *display, ALLEGRO_COLOR colour) {
		al_init_font_addon();
		al_init_ttf_addon();
		ALLEGRO_FONT *text = al_load_ttf_font("ROCKWELL_BOLD.TTF", 36, 0);//Create font pointer
		if (text == nullptr)  //Check if pointer was created if not show error
		{
			cerr << "Cannot Load Menu Item" << endl;
			al_rest(5.0);
			return nullptr;
		}
		else {
			al_draw_text(text, colour, (al_get_display_width(display) / 2), y_index, ALLEGRO_ALIGN_CENTER, word); //Otherwise display the text on the screen
			return text;
		}
	}

		ALLEGRO_FONT * changeMenuText(ALLEGRO_FONT *text, const char *word, short y_index, ALLEGRO_DISPLAY *display, ALLEGRO_COLOR colour) {
		al_init_font_addon();
		al_init_ttf_addon();
		al_draw_text(text, colour,(al_get_display_width(display)/2), y_index, ALLEGRO_ALIGN_CENTER, word); //Otherwise display the text on the screen
		return text;
	}
};