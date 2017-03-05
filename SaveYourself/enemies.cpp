#include <cmath>
#include "enemies.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>

namespace enemies
{
	void missile::create(ALLEGRO_DISPLAY *display, float initial_vx, float initial_vy)
	{
		srand(time(NULL)); //Make random function based on actual time
		image = al_load_bitmap("Rocket-ship-icon.png");
		x_pos = (rand() % al_get_display_height(display) + 1);
		y_pos = (rand() % al_get_display_width(display) + 1);
		x_v = initial_vx;
		y_v = initial_vy;
		visible = true;
	}

	//float old_angle=0;
	void missile::update(ALLEGRO_DISPLAY *display)
	{
		if (visible) {
			al_draw_rotated_bitmap(image, 16, 16, x_pos, y_pos, 0, NULL); //Rotate bitmap in direction of mouse
			//old_angle = angle;
		}
	}

	void missile::setDir(short x, short y) {
		if(visible){
		angle = atan2(y_pos - (y), (x)-x_pos)*180.0 / ALLEGRO_PI;	//Get angle from missile to mouse icon
		x_dir = cos(angle*ALLEGRO_PI / 180.0);
		y_dir = sin(angle*ALLEGRO_PI / 180.0);

		if (x_pos == x || y_pos == y) //Collosion detection
			destroy();
		}
	}

	void missile::advance_by_time(__int8 setpace, float speed)
	{
		if (visible) {
			pace++; /*This scales the movement of the rocket according to the framrate
					Framrate: 0.02 seconds
					Setpace: 10
					Therefore missile will move after 10*o.o2 seconds = 0.1 second
					*/
			if (pace >= setpace) {
				x_pos += short(x_dir*speed);
				y_pos -= short(y_dir*speed);
				pace = 0;
			}
		}
	}

	void missile::destroy() {
		visible = false;
	}
}