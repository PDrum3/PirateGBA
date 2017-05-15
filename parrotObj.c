#include "parrotObj.h"
#include "myLib.h"
#include "images.h"

void initParrots(Parrot *parrots)
{
	for (int i = 0; i < PARROTS; i++)
	{
        	parrots[i].row = 0;
        	parrots[i].col = 0;
        	parrots[i].oldRow = 200;
        	parrots[i].oldCol = 0;
        	parrots[i].rd = 0;
        	parrots[i].cd = 0;
        	parrots[i].used = 0;
        	parrots[i].eraseNext = 0;
        }
}

void updateParrots(Parrot *parrots)
{
	for (int i = 0; i < PARROTS; i++)
	{
		if (parrots[i].used == 1) //if its in use
		{
			parrots[i].col += parrots[i].cd;
			parrots[i].row += parrots[i].rd;
		}
	}
}

const unsigned short* setAnimParrot(int animCount)
{
	if (animCount < 10) {
		return parrot0_data;
	} else if (animCount < 20) {
		return parrot1_data;
	} else {
		return parrot0_data;
	}
}

void drawParrots(Parrot *parrots, const unsigned short *animParrot)
{
	for (int i = 0; i < PARROTS; i++)
	{
		if (parrots[i].used == 1) //if its in use
		{
			drawRect(parrots[i].oldRow, parrots[i].oldCol, PARROT0_WIDTH, PARROT0_HEIGHT, SKY);
			drawSprite(parrots[i].row, parrots[i].col, PARROT0_WIDTH, PARROT0_HEIGHT, animParrot);
		}
		if (parrots[i].eraseNext == 1)
		{
			drawRect(parrots[i].oldRow, parrots[i].oldCol, PARROT0_WIDTH, PARROT0_HEIGHT, SKY);
       			parrots[i].row = 200; //reset these values as well because some weird stuff will probs happen
       			parrots[i].col = 0;
       			parrots[i].oldCol = 0;
			parrots[i].eraseNext = 0;
		}
	}
	//draw a box to hide the screen wraping parrots
	drawRect(0, SCREEN_WIDTH - PARROT0_WIDTH, 40, PARROT0_WIDTH, SKY);
}

void changeOldParrots(Parrot *parrots)
{
	for (int i = 0; i < PARROTS; i++)
	{
		if (parrots[i].used == 1) //if its in use
		{
			parrots[i].oldCol = parrots[i].col;
			parrots[i].oldRow = parrots[i].row;
		}
	}
}

void parrotFire(Parrot *toFire, EnemyBullet *eBullets)
{
	int amtToFire = 2; //how many bullets to fire in this attack
	int bulletsDrawn = 0;
	for (int i = 0; (i < ENEMYBULLETS) && (bulletsDrawn < amtToFire); i++)
	{
		if (eBullets[i].used == 0) {
			if (bulletsDrawn == 0) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = 2;
				eBullets[i].cd = -1;
				bulletsDrawn++;
			} else if (bulletsDrawn == 1) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = 2;
				eBullets[i].cd = -2;
				bulletsDrawn++;
			}
		}
	}
}
