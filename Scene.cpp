#include "Scene.h"
int score_backup=0;

void initialize_Scene(struct Scene &s)
{
	s.counter = 0;
	load_Board(s.board, s.num_pellets, s.num_powerups, s.numLevel);
	initialize_Player(s.p, PLAYER_HOME_X, PLAYER_HOME_Y, 0, 0, PLAYER_CHAR, PLAYER_COLOR, score_backup);
	for(int i=0; i<NUM_GHOSTS; i++){
		initialize_Player(s.ghost[i], GHOST_HOME_X, GHOST_HOME_Y, 1, 0, GHOST_CHAR, GHOST_COLOR, 0);
	}
}

void render_Scene(struct Scene &s)
{
	draw_Board(s.board);
	draw_Player(s.p);
	for(int i=0; i<NUM_GHOSTS; i++){
		draw_Player(s.ghost[i]);
	}
	
	//scoreboard
	cons_move_cursor(2, WIDTH+2);
	cons_change_color(WHITE, BLACK);
	cons_printw("Score: %i", s.p.score);
	cons_move_cursor(4, WIDTH+2);
	cons_printw("Press and Hold 'Q' to Quit");
}

// Routine to update scene
int update_Scene(struct Scene &s)
{
	player_AI(s.p, s.board);
	update_Player(s.p);
	
	if(s.counter==GHOST_DELAY){
		for(int i=0; i<NUM_GHOSTS; i++){
			ghost_AI(s.ghost[i], s.board);
			update_Player(s.ghost[i]);
		}
		s.counter=0;
	}else{
		s.counter++;
	}
	
	//gobblin' up wakka wakka wakka!
	if(s.board[s.p.x][s.p.y]==PELLET){
		s.board[s.p.x][s.p.y]=EMPTY;
		s.p.score+=PELLET_VAL;
		s.num_pellets--;
	}
	if(s.board[s.p.x][s.p.y]==POWER_UP){
		s.board[s.p.x][s.p.y]=EMPTY;
		s.p.score+=POWER_VAL;
		s.num_powerups--;
	}
	
	//gameover condition for touching ghost
	for(int i=0; i<NUM_GHOSTS; i++){
		if((s.p.y==s.ghost[i].y)&&(s.p.x==s.ghost[i].x)){
			return 1;
		}
	}
	
	//gameover condition for winning
	if((s.num_pellets==0)&&(s.num_powerups==0)){
		s.numLevel++;
		score_backup=s.p.score;
		if(s.numLevel!=NUM_BOARDS){
			initialize_Scene(s);
		} else {
			return 1;
		}
	}
	//gameover condition for holding Q
	int key = cons_get_keypress();
	if((key==81)||(key==113)){
		return 1;
	}
	
	return 0;
}

// Routine to load board from text file
void load_Board(int board[HEIGHT][WIDTH], int &num_pellets, int &num_powerups, int &numLevel)
{
	FILE* in;
	char ch;
	int i,j;
	
	num_pellets = 0;
	num_powerups = 0;
	
	//level increase
	if(numLevel==0){
		in = fopen("board.txt","r");
	}else if(numLevel==1){
		in = fopen("board2.txt","r");
	}else if(numLevel==2){
		in = fopen("funboard.txt","r");
	}
	
	if(!in)
	{
		printf("Unable to open file.");
		exit(0);
	}

	for(i=0; i<HEIGHT; i++)
	{
		for(j=0; j<WIDTH; j++)
		{
			fscanf(in,"%c",&ch);
			if(ch=='+')
			{
				board[i][j] = WALL;
			}
			else if(ch=='.')
			{
				board[i][j] = PELLET;
				(num_pellets)++;
			}
			else if(ch=='O')
			{
				board[i][j] = POWER_UP;
				(num_powerups)++;
			}
			else
			{
				board[i][j] = EMPTY;
			}
		}
		fscanf(in,"%c",&ch);
		fscanf(in,"%c",&ch);
	}

	fclose(in);

	return;
}

void draw_Board(int board[HEIGHT][WIDTH]){
//checks values assigned by load board, prints desired object
	for(int i=0; i<HEIGHT; i++){
		for(int j=0; j<WIDTH; j++){
		cons_move_cursor(i,j);
			if(board[i][j]==WALL){
				cons_change_color(BLUE,BLUE);
				cons_printw(" ");
			}else if(board[i][j]==PELLET){
				cons_change_color(WHITE,BLACK);
				cons_printw(".");
			}else if(board[i][j]==POWER_UP){
				cons_change_color(WHITE,BLACK);
				cons_printw("O");
			}else if(board[i][j]==EMPTY){
				cons_change_color(WHITE,BLACK);
				cons_printw(" ");
			}
		}
	}
}
