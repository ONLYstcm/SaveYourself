#include <cmath>
#include "enemies.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>

namespace enemies
{
	void missile::create(float initial_vx, float initial_vy)
	{
		srand(time(NULL)); //Make random function based on actual time
		image = al_load_bitmap("Rocket-ship-icon.png");
		x_pos = 0;
		y_pos = (rand() % 800 + 1);
		x_v = initial_vx;
		y_v = initial_vy;
	}

	void missile::update(ALLEGRO_DISPLAY *display)
	{
		al_draw_bitmap(image, x_pos, y_pos, NULL);
	}

	void missile::advance_by_time(double *dt, short *x, short *y, float *speed)
	{
		if((*x)!=(x_pos)){
		dir = atan2(y_pos - (*y), (*x) - x_pos)*180.0 / ALLEGRO_PI;//(remember to check if the points are equal)
		}

		x_v = (*speed)*cos(dir*ALLEGRO_PI / 180.0);
		y_v = -(*speed)*sin(dir*ALLEGRO_PI / 180.0);
		x_pos=(*x);
		if (x_pos >= 1 && x_pos <= 600 && y_pos >= 1 && y_pos <= 800) {
		x_pos += int(x_v*(*dt));
		y_pos += int(y_v*(*dt));
		}
	}

	void destroy() {

	}
}