#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <allegro5\allegro.h>
#include <allegro5\color.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h> //Normal font
#include <allegro5\allegro_ttf.h> //True Type Font
#include "reeko_physics_engine.h"
#define GAMING_WINDOW_HEIGHT 768;
#define GAMING_WINDOW_WIDTH 1360;

using namespace std;

namespace collision {

	bool Collide(physics::object &object, physics::object &target)
	{
		if (object.getVector('P').x > (target.getVector('P').x - target.getVector('B').x) && object.getVector('P').x < (target.getVector('P').x + target.getVector('B').x) && object.getVector('P').y > (target.getVector('P').y - target.getVector('B').y) && object.getVector('P').y < (target.getVector('P').y + target.getVector('B').y)){
			return true;
		}
		else
			return false;
	}
}