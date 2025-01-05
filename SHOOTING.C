#include <graphics.h>


int x = 100, y = 100;
int x1 = 100, y1 = 100, x2 = 150, y2 = 100;

//targets
	int cx1 = 500, cy1 = 100;
	int cx2 = 490, cy2 = 200;
	int cx3 = 550, cy3 = 350;
	int cx4 = 590, cy4 = 400;
	int r1 = 50, r2 = 25, r3 = 15, r4 = 7;
//score
int score = 0;
void displayScore() {
	char str[50];
	cleardevice();
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	sprintf(str, "Score:: %d ", score);
	outtext(str);

}

void destroyTarget(int dp, int x_mid, int y_mid, int x, int y) {
	do {
		putpixel(x_mid + x, y_mid + y, 0);
		putpixel(x_mid + x, y_mid - y, 0);

		putpixel(x_mid + y, y_mid + x, 0);
		putpixel(x_mid + y, y_mid - x, 0);

		putpixel(x_mid - x, y_mid + y, 0);
		putpixel(x_mid - x, y_mid - y, 0);

		putpixel(x_mid - y, y_mid + x, 0);
		putpixel(x_mid - y, y_mid - x, 0);

		delay(50);
		if(dp < 0) dp += (2 * x) + 1;
		else {
			y = y - 1;
			dp += (2 * x) - (2 * y) + 1;
		}
		x = x + 1;
	}
	while(y > x);

}
void createTarget(int dp, int x_mid, int y_mid, int x, int y) {
	do {
		putpixel(x_mid + x, y_mid + y, 15);
		putpixel(x_mid + x, y_mid - y, 15);

		putpixel(x_mid + y, y_mid + x, 15);
		putpixel(x_mid + y, y_mid - x, 15);

		putpixel(x_mid - x, y_mid + y, 15);
		putpixel(x_mid - x, y_mid - y, 15);

		putpixel(x_mid - y, y_mid + x, 15);
		putpixel(x_mid - y, y_mid - x, 15);


		if(dp < 0) dp += (2 * x) + 1;
		else {
			y = y - 1;
			dp += (2 * x) - (2 * y) + 1;
		}
		x = x + 1;
	}
	while(y > x);

}
void targets() {
	int dp;

	dp = 1 - r1;
	createTarget(dp, cx1, cy1, 0, r1);
	dp = 1 - r2;
	createTarget(dp, cx2, cy2, 0, r2);
	dp = 1 - r3;
	createTarget(dp, cx3, cy3, 0, r3);
	dp = 1 - r4;
	createTarget(dp, cx4, cy4, 0, r4);

}
void tank() {
	circle(x, y, 20);
	line(x1, y1, x2, y2);
}

void shooter(int y1, int y2) {
	int bx1 = 100;
	int bx2 = 110;
	int dp;
	while(1) {
		tank();
		targets();
		bx1 = bx1 + 5;
		bx2 = bx2 + 5;
		line(bx1, y1, bx2, y2);
		delay(10);

		if(bx2 == cx1 && y2 == cy1) {
			score = score + 10;
			dp = 1 - r1;
			destroyTarget(dp, cx1, cy1, 0, r1);
			break;
		}
		else if(bx2 == cx2 && y2 == cy2) {
			score = score + 30;
			dp = 1 - r2;
			destroyTarget(dp, cx2, cy2, 0, r2);
			break;
		}
		else if(bx2 == cx3 && y2 == cy3) {
			score = score + 50;
			dp = 1 - r3;
			destroyTarget(dp, cx3, cy3, 0, r3);
			break;
		}
		else if(bx2 == cx4 && y2 == cy4) {
			score = score + 100;
			dp = 1 - r4;
			destroyTarget(dp, cx4, cy4, 0, r4);
			break;
		}
		cleardevice();
		if(bx2 >= 600) {
			break;
		}
	}

}

void mover() {
	char ch;
	displayScore();
	while(1) {
		tank();
		targets();
		if(kbhit()) {
			ch = getch();
			if (ch == 'w') {
				y = y - 5;
				y1 = y1 - 5;
				y2 = y2 - 5;
			}
			else if (ch == 's') {
				y = y + 5;
				y1 = y1 + 5;
				y2 = y2 + 5;
			}

			else if (ch == 'f') {
				shooter(y1, y2);
			}
			else if (ch == 'x') break;
			cleardevice();
			displayScore();
		}
	}
}

int main() {
	int gd = DETECT, gm;

	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	tank();
	targets();
	mover();
	displayScore();
	getch();
	closegraph();
	return 0;
}