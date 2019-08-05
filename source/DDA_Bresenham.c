#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define H 1000
#define W 1000
#define maxlevel   255
#define PI 3.141592
unsigned char Iarray[H][W][3];//for an interleaved color array
int R, G, B;
void init();
int patte[3][8] = { { 1,1,1,1,1,1,1,1 },{ 1,1,1,1,0,0,0,0 },{ 1,0,1,0,1,0,1,0 } };
void lineDDA(int x1, int y1, int x2, int y2, int patt);
void lineBres(int x1, int y1, int x2, int y2, int patt);
enum patterm {
	solid, Dash, Dot, w = 8
};
void main(void)
{
	FILE* fp;
	int i, j, k;
	int x1, y1, x2, y2;
	fp = fopen("test.ppm", "wb");
	fprintf(fp, "P6\n"); //magic no.: ASCII header and Binary body.. 
	fprintf(fp, "%d %d\n", H, W); //file size 
	fprintf(fp, "%d\n", maxlevel); //max level 
	init();
	int mode = 1;
	int patt;
	while (mode) {
	   printf("시작 좌표를 입력하세요 ex) 1,2 :  ");
	   scanf("%d,%d", &x1, &y1);
	   printf("종료 좌표를 입력하세요 ex) 40,20 :  ");
	   scanf("%d,%d", &x2, &y2);
	   printf("컬러를 입력하세요 R,G,B 순서 ex) 255,0,40 : ");
	   scanf("%d,%d,%d", &R, &G, &B);
	   printf("선의 종류를 선택하세요 1=실선,2=파선,3=점선"); 
	   scanf("%d", &patt);
	   //lineDDA(x1, y1, x2, y2, patt-1);
	   lineBres(x1,y1,x2,y2,patt-1);
	   printf("종료하시겠습니까? yes(0),no(1) :");
	   scanf("%d", &mode);
	}
	

	for (i = 0; i < H; i++)
		for (j = 0; j < W; j++)
			for (k = 0; k < 3; k++)
				putc(Iarray[i][j][k], fp);
	//fwrite(Iarray,sizeof(char),H*W*3,fp);
	fclose(fp);
}
void init() {
	int i, j, k;
	for (i = 0; i < H; i++)
		for (j = 0; j < W; j++)
			for (k = 0; k < 3; k++)
				Iarray[i][j][k] = 255;
}
void lineDDA(int x1, int y1, int x2, int y2, int patt)
{
	int dx = x2 - x1, dy = y2 - y1, step, k;
	float xinc, yinc, x = (float)x1, y = (float)y1;

	if (abs(dx) > abs(dy)) step = abs(dx);
	else step = abs(dy);
	xinc = dx / (float)step;
	yinc = dy / (float)step;
	Iarray[x1][y1][0] = R;
	Iarray[x1][y1][1] = G;
	Iarray[x1][y1][2] = B;
	// start pixel marking(setpixel function)
	for (k = 0; k < step; k++) {
		x += xinc;
		y += yinc;
		if (patte[patt][k%w] == 1) {
			Iarray[(int)(x + 0.5)][(int)(y + 0.5)][0] = R;// marking(setpixel function)
			Iarray[(int)(x + 0.5)][(int)(y + 0.5)][1] = G;
			Iarray[(int)(x + 0.5)][(int)(y + 0.5)][2] = B;
		}
	}


}
void lineBres(int x1, int y1, int x2, int y2, int patt)
{
	int dx = abs(x2 - x1), dy = abs(y2 - y1);
	int p, twoDy, twoDyDx;
	int x, y, xEnd, yEnd, IorD;

	if (dx > dy) {
		p = 2 * dy - dx; twoDy = 2 * dy; twoDyDx = 2 * (dy - dx);

		if (x1>x2) { x = x2; y = y2; xEnd = x1; if (y1 - y2>0)IorD = 1; else IorD = -1; }
		else { x = x1; y = y1; xEnd = x2; if (y2 - y1>0)IorD = 1; else IorD = -1; }

		Iarray[x][y][0] = R; Iarray[x][y][1] = G; Iarray[x][y][2] = B;// start point marking with a user-defined color(r,g,b) 

		while (x<xEnd) {
			x++;
			if (p<0) p += twoDy;
			else { y += IorD; p += twoDyDx; }
			if (patte[patt][x%w] == 1) {
				Iarray[(int)(x + 0.5)][(int)(y + 0.5)][0] = R;// marking(setpixel function)
				Iarray[(int)(x + 0.5)][(int)(y + 0.5)][1] = G;
				Iarray[(int)(x + 0.5)][(int)(y + 0.5)][2] = B;
			}
		}// end of while
	}// end of if
	else {
		int p1, twoDx, twoDxDy;
		p1 = 2 * dx - dy; twoDx = 2 * dx; twoDxDy = 2 * (dx - dy);
		if (y1>y2) { x = x2; y = y2; yEnd = y1; if (x1 - x2>0)IorD = 1; else IorD = -1; }
		else { x = x1; y = y1; yEnd = y2; if (x2 - x1>0)IorD = 1; else IorD = -1; }

		Iarray[x][y][0] = R; Iarray[x][y][1] = G; Iarray[x][y][2] = B;// start point marking with a user-defined color(r,g,b) 

		while (y<yEnd) {
			y++;
			if (p1<0) p1 += twoDx;
			else { x += IorD; p1 += twoDxDy; }
			if (patte[patt][y%w] == 1) {
				Iarray[(int)(x + 0.5)][(int)(y + 0.5)][0] = R;// marking(setpixel function)
				Iarray[(int)(x + 0.5)][(int)(y + 0.5)][1] = G;
				Iarray[(int)(x + 0.5)][(int)(y + 0.5)][2] = B;
			}
		}// end of while

		 //You should complete this block....
		 //Hint: The role of x has to be changed with that of y...


	}// end of else

}