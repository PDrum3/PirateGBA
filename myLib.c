#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}


/*void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r = 0; r<height; r++)
	{
		for(int c=0; c<width; c++)
		{
			setPixel(r+row, c+col, color);
		}
	}
}*/

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r = 0; r<height; r++)
	{	
		DMA[3].src = &color;
		DMA[3].dst = videoBuffer + OFFSET(row+r, col, 240);
		DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
	}
}

void drawRectBack(int row, int col, int height, int width, unsigned short top, unsigned short mid, unsigned short bot)
{
	unsigned short color;
	for(int r = 0; r<height; r++)
	{	
		if (row + r < 41) {
			color = top;
		} else if (row + r < 77) {
			color = mid;
		} else {
			color = bot;
		}
		DMA[3].src = &color;
		DMA[3].dst = videoBuffer + OFFSET(row+r, col, 240);
		DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
	}
}

void drawSprite(int row, int col, int height, int width, const unsigned short *image)
{
	for(int r = 0; r < height; r++)
	{	
		DMA[3].src = image + (width*r);
		DMA[3].dst = videoBuffer + OFFSET(row+r, col, 240);
		DMA[3].cnt = width | DMA_ON;
	}
}

void drawScreen(const unsigned short *image) //draws a 240x160 image to the screen
{
	DMA[3].src = image;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 240*160 | DMA_ON;
}

void delay(int n)
{
	int volatile x = 0;
	for(int i =0; i<n*8000; i++)
	{
		x = x + 1;
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 159);
}
