#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include "Const.h"
#include "Console.h"

// TODO: Add player structure
struct Player{
	int x, y, dx, dy;
	char avatar;
	int color;
	int score;
};

// TODO: Add player function prototypes
void initialize_Player(struct Player &p, int x, int y, int dx, int dy, char avatar, int color, int score);
void draw_Player(struct Player &p);
void player_AI(struct Player &p, int board[HEIGHT][WIDTH]);
void ghost_AI(struct Player &g, int board[HEIGHT][WIDTH]);
void check_Player_Move(struct Player &p, int board[HEIGHT][WIDTH]);
void update_Player(struct Player &p);

#endif // PLAYER_H
