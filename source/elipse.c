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
void ellipsePlot(int Cx, int Cy, int x, int y, int th);
void ellipseMidpoint(int xCenter, int yCenter, int Rx, int Ry, int th);
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
	int th;
	while (mode) {
	   printf("중심 좌표를 입력하세요 ex) 1,2 :  ");
	   scanf("%d,%d", &x1, &y1);
	   printf("x축 반지름과 y축 반지름을 입력하세요 ex) 40,20 :  ");
	   scanf("%d,%d", &x2, &y2);
	   printf("컬러를 입력하세요 R,G,B 순서 ex) 255,0,40 : ");
	   scanf("%d,%d,%d", &R, &G, &B);
	   printf("회전각도를 입력하세요 (중심점 기준으로 시계방향) : ");
	   scanf("%d", &th);
	   ellipseMidpoint(x1, y1, x2, y2,th);
	 
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
void ellipsePlot(int Cx, int Cy, int x, int y, int th)
{
	int x_c, y_c;
	x_c = (int)(x * cos(getRadian(th)) + y * sin(getRadian(th)) + 0.5);
	y_c = (int)(y * cos(getRadian(th)) - x * sin(getRadian(th)) - 0.5);
	setPixel(Cx + x_c, Cy + y_c);//marking function according to the output device
	x = -x;
	x_c = (int)(x * cos(getRadian(th)) + y * sin(getRadian(th)) + 0.5);
	y_c = (int)(y * cos(getRadian(th)) - x * sin(getRadian(th)) - 0.5);
	setPixel(Cx + x_c, Cy + y_c);
	y = -y;
	x_c = (int)(x * cos(getRadian(th)) + y * sin(getRadian(th)) + 0.5);
	y_c = (int)(y * cos(getRadian(th)) - x * sin(getRadian(th)) - 0.5);
	setPixel(Cx + x_c, Cy + y_c);
	x = -x;
	x_c = (int)(x * cos(getRadian(th)) + y * sin(getRadian(th)) + 0.5);
	y_c = (int)(y * cos(getRadian(th)) - x * sin(getRadian(th)) - 0.5);
	setPixel(Cx + x_c, Cy + y_c);
}

void ellipseMidpoint(int xCenter, int yCenter, int Rx, int Ry, int th)
{
	int Rx2 = Rx * Rx, Ry2 = Ry * Ry, twoRx2 = 2 * Rx2, twoRy2 = 2 * Ry2;
	int p, x = 0, y = Ry, px = 0, py = twoRx2 * y;
	ellipsePlot(xCenter, yCenter, x, y, th);//start pixel marking..

											//Region 1
	p = (int)round(Ry2 - (Rx2*Ry) + (0.25*Rx2));
	while (px<py) {
		x++;
		px += twoRy2;
		if (p<0) p += Ry2 + px;
		else { y--; py -= twoRx2; p += Ry2 + px - py; }

		ellipsePlot(xCenter, yCenter, x, y, th);//marking..
	}

	//Region 2
	p = (int)round(Ry2*(x + 0.5)*(x + 0.5) + Rx2 * (y - 1)*(y - 1) - Rx2 * Ry2);
	while (y>0) {
		y--;
		py -= twoRx2;
		if (p>0) p += Rx2 - py;
		else { x++; px += twoRy2; p += Rx2 - py + px; }

		ellipsePlot(xCenter, yCenter, x, y, th);//marking..
	}
}