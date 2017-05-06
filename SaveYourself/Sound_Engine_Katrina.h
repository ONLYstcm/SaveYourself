#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include<string>
using namespace std;
class Sound_Engine_Katrina
{
private:
	struct SAMPLE_DATA
	{
		ALLEGRO_SAMPLE* sample;
		ALLEGRO_SAMPLE_INSTANCE* sample_id;
	};
public:
	Sound_Engine_Katrina();
	SAMPLE_DATA sound;
	ALLEGRO_DISPLAY *display = NULL;
	void playSound(ALLEGRO_PLAYMODE Loop, float gain, float pan, float speed, char* type);
	void destroySound();


};




