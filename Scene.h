#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <stdlib.h>
#include "Console.h"
#include "Const.h"
#include "Player.h"

struct Scene {
	int board[HEIGHT][WIDTH];
	int num_pellets;
	int num_powerups;
	struct Player p;
	struct Player ghost[NUM_GHOSTS];
	int counter;
	int numLevel;
	
	// TODO: add additional fields
};

void initialize_Scene(struct Scene &s);
void initialize_Ghost(struct Scene &s);
void render_Scene(struct Scene &s);
int update_Scene(struct Scene &s);
void load_Board(int board[HEIGHT][WIDTH], int &num_pellets, int &num_powerups, int &numLevel);
void draw_Board(int board[HEIGHT][WIDTH]);

#endif // SCENE_H