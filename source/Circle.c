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
void circleMidpoint(int xCenter, int yCenter, int radius);

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
	int r;
	while (mode) {
	   printf("중심 좌표를 입력하세요 ex) 1,2 :  ");
	   scanf("%d,%d", &x1, &y1);
	   printf("반지름을 입력하세요 : ");
	   scanf("%d", &r);
	   printf("컬러를 입력하세요 R,G,B 순서 ex) 255,0,40 : ");
	   scanf("%d,%d,%d", &R, &G, &B);
	   circleMidpoint(x1, y1, r);
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
double getRadian(double num) {
	return num * (PI / 180);
}

void setPixel(int x, int y) {
	if (0 <= x && x < H && 0 <= y && y < W) {
		Iarray[x][y][0] = R;
		Iarray[x][y][1] = G;
		Iarray[x][y][2] = B;
	}
}
void circlePlot(int Cx, int Cy, int x, int y)
{

	setPixel(Cx + x, Cy + y);//marking function according to the output device
	setPixel(Cx - x, Cy + y);
	setPixel(Cx + x, Cy - y);
	setPixel(Cx - x, Cy - y);
	setPixel(Cx + y, Cy + x);
	setPixel(Cx - y, Cy + x);
	setPixel(Cx + y, Cy - x);
	setPixel(Cx - y, Cy - x);
}

void circleMidpoint(int xCenter, int yCenter, int radius)
{
	int x = 0, y = radius, p = 1 - radius;

	circlePlot(xCenter, yCenter, x, y);//start pixel marking..

	while (x <= y) {
		x++;
		if (p<0) p += 2 * x + 1;
		else { y--; p += 2 * (x - y) + 1; }

		circlePlot(xCenter, yCenter, x, y);//marking..
	}
}
