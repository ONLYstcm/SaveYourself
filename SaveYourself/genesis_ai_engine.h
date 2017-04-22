#pragma once
#pragma once
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include < stdio.h>
#include <string>
#include <ctime>
#include "gameplay.h"
#define GAMING_WINDOW_HEIGHT 600
#define GAMING_WINDOW_WIDTH 1024
#include "reeko_physics_engine.h"

using namespace std;

namespace AI {
		void random_border_positition() {
		}

		void follow(physics::object &object, physics::object &target, double acceleration=1) {
			//Get angle between target and object
			object.setAngle(atan2(object.getVector('P').y - (target.getVector('P').y), (target.getVector('P').x)-object.getVector('P').x));	//Get angle from missile to mouse icon
			Vector dir;
			//Convert to unit vector
			dir.x = cos(object.getAngle());
			dir.y = sin(object.getAngle());
			if (dir.x < 0)
				object.accelerate('L');
			else {
				object.accelerate('R');
			}
			if (dir.y < 0)
				object.accelerate('D');
			else {
				object.accelerate('U');
			}
		}

		void follow(physics::object &object, Vector target, double acceleration = 1) {
			//Get angle between target and object
			object.setAngle(atan2(object.getVector('P').y - (target.y), (target.x) - object.getVector('P').x));	//Get angle from missile to mouse icon
			Vector dir;

			//Convert to unit vector
			dir.x = cos(object.getAngle());
			dir.y = sin(object.getAngle());
			if (dir.x < 0)
				object.accelerate('L',1,1,1,1,abs(dir.x), abs(dir.y));
			else {
				object.accelerate('R', 1, 1, 1, 1, abs(dir.x), abs(dir.y));
			}
			if (dir.y < 0)
				object.accelerate('D', 1, 1, 1, 1, abs(dir.x), abs(dir.y));
			else {
				object.accelerate('U', 1, 1, 1, 1, abs(dir.x), abs(dir.y));
			}
		}
}