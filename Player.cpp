#include "Player.h"

// TODO: Add player functions
void initialize_Player(struct Player &p, int x, int y, int dx, int dy, char avatar, int color, int score){
	p.x=x;
	p.y=y;
	p.dx=dx;
	p.dy=dy;
	p.avatar=avatar;
	p.color=color;
	p.score=score;
}

void draw_Player(struct Player &p){
	cons_move_cursor(p.x, p.y);
	cons_change_color(p.color, BLACK);
	cons_printw("%c", p.avatar);
}

void player_AI(struct Player &p, int board[HEIGHT][WIDTH]){
	int key;
	key=cons_get_keypress();
	
	if(key==UP_ARROW){
		p.dx=-1;
		p.dy=0;
		p.avatar='V';
	}else if(key==DOWN_ARROW){
		p.dx=1;
		p.dy=0;
		p.avatar='^';
	}else if(key==LEFT_ARROW){
		p.dy=-1;
		p.dx=0;
		p.avatar='>';
	}else if(key==RIGHT_ARROW){
		p.dy=1;
		p.dx=0;
		p.avatar='<';
	}else{
		p.dx=0;
		p.dy=0;
		p.avatar=p.avatar;
	}
	
	check_Player_Move(p, board);
	
}

void ghost_AI(struct Player &g, int board[HEIGHT][WIDTH]){
	int chanceSame = (rand()%100)+1;
	int chanceXY = (rand()%2);
	int chanceVelocity = (rand()%2);
	
	if((chanceSame>=75)||((g.dx==0)&&(g.dy==0))){
		if((chanceXY==0)&&(chanceVelocity==0)){
			g.dx=1;
			g.dy=0;
		}else if((chanceXY==0)&&(chanceVelocity==1)){
			g.dx=-1;
			g.dy=0;
		}
		if((chanceXY==1)&&(chanceVelocity==0)){
			g.dy=1;
			g.dx=0;
		}else if((chanceXY==1)&&(chanceVelocity==1)){
			g.dy=-1;
			g.dx=0;
		}
	}
	
	check_Player_Move(g, board);
}

void check_Player_Move(struct Player &p, int board[HEIGHT][WIDTH]){
	if((p.dy==1)&&(board[p.x][p.y+1]==WALL)){
		p.dx=0;
		p.dy=0;
	}if((p.dy==-1)&&(board[p.x][p.y-1]==WALL)){
		p.dx=0;
		p.dy=0;
	}if((p.dx==1)&&(board[p.x+1][p.y]==WALL)){
		p.dx=0;
		p.dy=0;
	}if((p.dx==-1)&&(board[p.x-1][p.y]==WALL)){
		p.dx=0;
		p.dy=0;
	}if((p.x==TUNNEL_Y)&&(p.y==0)){
		p.y=WIDTH-2;
	}if((p.x==TUNNEL_Y)&&(p.y==WIDTH-1)){
		p.y=1;
	}
}

void update_Player(struct Player &p){
	p.x+=p.dx;
	p.y+=p.dy;
}