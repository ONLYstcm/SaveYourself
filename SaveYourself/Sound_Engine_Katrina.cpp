#include "Sound_Engine_Katrina.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;


Sound_Engine_Katrina::Sound_Engine_Katrina()
{

}

bool checkSound()
{
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return false;
	}

	if (!al_install_audio()) {
		fprintf(stderr, "failed to initialize audio!\n");
		return false;
	}

	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return false;
	}

	if (!al_reserve_samples(10)) {//reserves 10 sample/"Sound"
		fprintf(stderr, "failed to reserve samples!\n");
		return false;
	}
	return true;
}


void Sound_Engine_Katrina::playSound( ALLEGRO_PLAYMODE Loop, float gain, float pan, float speed, char* type)
{
	//pan=0 results in even distribution between left and right speaker
	if (checkSound() == false)
		return;
	sound.sample = al_load_sample(type);//Loads specified sound
	
	if (!sound.sample) {
		printf("Audio clip sample not loaded!\n");
	}

	al_play_sample(sound.sample, gain, pan, speed, Loop, NULL); //Plays Sound

}
void Sound_Engine_Katrina::destroySound()
{
	al_destroy_sample(sound.sample);
}