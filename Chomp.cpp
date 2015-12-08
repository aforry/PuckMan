#include <stdlib.h>
#include <time.h>
#include "Console.h"
#include "Scene.h"

#define ANIMATION_DELAY 50

// Main game loop - do not modify
int main()
{
	int done;
	Scene myScene;
	
	srand(time(0));
	
	myScene.numLevel=0;
	initialize_Scene(myScene);

	done = false;
	while (!done) {
		cons_clear_screen();
		render_Scene(myScene);
		cons_move_cursor(25,80);
		cons_update();

		cons_sleep_ms(ANIMATION_DELAY);

		done = update_Scene(myScene);
	}
	
	// Print Game Over
	cons_clear_screen();
	render_Scene(myScene);
	cons_move_cursor(23,0);
	cons_change_color(YELLOW,BLACK);
	cons_printw("GAME OVER! Press SPACE to Exit!");
	cons_update();
	
	
	//exit game after ending
	int keep_going=1;
	while(keep_going==1){
		if(cons_get_keypress()==32){
			keep_going=0;
			return 0;
		}
	}
}
