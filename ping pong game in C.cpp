#include <stdio.h>
#include <conio.h>
#include <graphics.h>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define WIDTH 800
#define HEIGHT 600
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 100
#define BALL_SIZE 10
#define BALL_SPEED 2
#define PADDLE_SPEED 30

void menu(); 

int paddle1X = 20, paddle1Y = (HEIGHT - PADDLE_HEIGHT) / 2;
int paddle2X = WIDTH - PADDLE_WIDTH - 20, paddle2Y = (HEIGHT - PADDLE_HEIGHT) / 2;
int ballX = (WIDTH - BALL_SIZE) / 2, ballY = (HEIGHT - BALL_SIZE) / 2;
int ballDirX = RIGHT, ballDirY = DOWN;

struct score{
	int s;
}s1,s2;

void drawPaddle(int x, int y) {
    bar(x, y, x + PADDLE_WIDTH, y + PADDLE_HEIGHT);
    floodfill(x,y,WHITE);
}

// Function to draw the ball
void drawBall(int x, int y) {
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y, BALL_SIZE, BALL_SIZE);
}
void update(){
	replay:
	s1.s=0;
	s2.s=0;
	char right[50], left[50];
	while (1) {
	cleardevice();
    settextstyle(3,0,1);
	sprintf(right,"%d",s1.s);
	outtextxy(20,10,right);
	sprintf(left,"%d",s2.s);
	outtextxy(getmaxx()-50,10,left);
	
        // Draw paddles and ball
        drawPaddle(paddle1X, paddle1Y);
        drawPaddle(paddle2X, paddle2Y);
        drawBall(ballX, ballY);

        // Move ball
        if (ballDirX == RIGHT)
            ballX += BALL_SPEED;
        else
            ballX -= BALL_SPEED;

        if (ballDirY == DOWN)
            ballY += BALL_SPEED;
        else
            ballY -= BALL_SPEED;

        // Ball collision with top and bottom walls
        if (ballY <= 0 || ballY >= HEIGHT - BALL_SIZE)
            ballDirY = 1 - ballDirY;
		
        // Ball collision with paddles
        if ((ballX <= paddle1X + PADDLE_WIDTH) && (ballY >= paddle1Y) && (ballY <= paddle1Y + PADDLE_HEIGHT))
            ballDirX = RIGHT;

        if ((ballX >= paddle2X - BALL_SIZE) && (ballY >= paddle2Y) && (ballY <= paddle2Y + PADDLE_HEIGHT))
            ballDirX = LEFT;

        // Ball out of bounds
        if (ballX < 0) {
            // Player 2 scores
            s2.s++;
            ballX = (WIDTH - BALL_SIZE) / 2;
            ballY = (HEIGHT - BALL_SIZE) / 2;
            ballDirX = RIGHT;
            ballDirY = DOWN;
        } else if (ballX > WIDTH - BALL_SIZE) {
            // Player 1 scores
            s1.s++;
            ballX = (WIDTH - BALL_SIZE) / 2;
            ballY = (HEIGHT - BALL_SIZE) / 2;
            ballDirX = LEFT;
            ballDirY = DOWN;
        }

        // Control paddles
        if (kbhit()) {
            char key = getch();
            if (key == 'u' && paddle1Y > 0)
                paddle1Y -= PADDLE_SPEED;
            if (key == 'd' && paddle1Y < HEIGHT - PADDLE_HEIGHT)
                paddle1Y += PADDLE_SPEED;
            if (key == 'o' && paddle2Y > 0)
                paddle2Y -= PADDLE_SPEED;
            if (key == 'p' && paddle2Y < HEIGHT - PADDLE_HEIGHT)
                paddle2Y += PADDLE_SPEED;
        }

        delay(10);
    	if(s1.s==5||s2.s==5){
		cleardevice();
		break;
	}

    }
    outtextxy(getmaxx()/2-50,getmaxy()/2,"GAME OVER");
	delay(1000);
	cleardevice();
	if(s1.s==5){
		outtextxy(getmaxx()/2-50,getmaxy()/2,"PLAYER 1 WINS");
	}
	else{
		outtextxy(getmaxx()/2-50,getmaxy()/2,"PLAYER 2 WINS");
	}
	delay(1000);
	cleardevice();
	settextstyle(2,0,5);
    outtextxy(getmaxx()/2-50,200,"PLAY AGAIN(p)");
    outtextxy(getmaxx()/2-50,220,"QUIT(q)");
    if(kbhit){
  	int c=getch();
  	if(c==112)
  	{
  		goto replay;
  	}

  	else if(c==113)
  	{ 
  		exit(0);
  	}
  	}
    
}
void help()
{
	cleardevice();
	outtextxy(80,115,"INSTRUCTIONS");
	outtextxy(60,135," For left paddle(Player 1): ");
	outtextxy(70,155,"u key: Move up");
	outtextxy(70,175,"d key   : Move dowm");
	outtextxy(60,195,"For right paddle(Player 2) :");
	outtextxy(70,215,"o key    : Move up");
	outtextxy(70,235,"p key       : Move down");
	outtextxy(60,325,"Press esc to return to the main menu");
	outtextxy(60,285,"Who is the winner?");
	outtextxy(70,305,"The player scoring 5 at first win the game");
	while(1){
		if(kbhit()){
			int c=getch();
			if(c==27){
				cleardevice();
				menu();
				
			}
		}
	}
}

void menu()  // prints options
	{
		settextstyle(2,0,7);
		outtextxy(230,155,"MAIN MENU");
		settextstyle(2,0,5);
		outtextxy(220,195,"Play Game(p)");
		outtextxy(220,215,"Help(h)");
		outtextxy(220,235,"Exit(e)");
		while(1){
			if(kbhit()){
				int c=getch();
					if(c==112){
						update();	
					}
			else if(c==104){
				help();
			}
			else if(c==101){
				exit(0);
			}
		}
		}
		
	}
	



void loading(){
	settextstyle(2,0,5);
	outtextxy(getmaxx()/2-150,getmaxy()/2-50,"WELCOME TO PING PONG GAME");
	outtextxy(250,350,"Loading");
	rectangle(240,330,332,338);
	for(int i=0;i<=86;i++){
		line(240+i,332,240+i,338);
		delay(50);
	}
	cleardevice();
}

int main() {
    int gd = DETECT, gm;
    

    initwindow(800, 600, "Fixed Size Window");
	loading();
	menu();
	getch();
    closegraph();
    return 0;
}

