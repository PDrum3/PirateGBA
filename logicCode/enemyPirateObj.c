#include "enemyPirateObj.h"
#include "images.h"
#include "myLib.h"

void initEnemyPirates(EnemyPirate *enemyPirates)
{
	for (int i = 0; i < ENEMYPIRATES; i++)
	{
        	enemyPirates[i].row = 0;
        	enemyPirates[i].col = 0;
        	enemyPirates[i].oldRow = 200;
        	enemyPirates[i].oldCol = 0;
        	enemyPirates[i].rd = 0;
        	enemyPirates[i].cd = 0;
		enemyPirates[i].hits = 3;
        	enemyPirates[i].used = 0;
        	enemyPirates[i].eraseNext = 0;
        }
}

void updateEnemyPirates(EnemyPirate *enemyPirates, Bullet *playerBullets)
{
		for (int i = 0; i < ENEMYPIRATES; i++)
		{
			if (enemyPirates[i].used == 1) //if its in use
			{
				enemyPirates[i].col += enemyPirates[i].cd;
				enemyPirates[i].row += enemyPirates[i].rd;
				for (int i = 0; i < MAXSHOT; i++)
				{
					if (playerBullets[i].used == 1)
					{
						//COLLISION WITH PLAYER BULLETS
						if (((playerBullets[i].row) > (enemyPirates[i].row)) &&
						((playerBullets[i].row) < (ENEMYPIRATE0_HEIGHT + enemyPirates[i].row)))
						{
							if (((playerBullets[i].col)>(enemyPirates[i].col)) &&
							((playerBullets[i].col) <(ENEMYPIRATE0_WIDTH + enemyPirates[i].col + 100)))
							{
								playerBullets[i].used = 0;
								playerBullets[i].eraseNext = 1;
								enemyPirates[i].hits -= 1;
								if (enemyPirates[i].hits < 1) {
									enemyPirates[i].used = 0;
									enemyPirates[i].eraseNext = 1;
								}
							}
						}
					}
				}
			}
		}
}

const unsigned short* setAnimEnemyPirate(int animCount)
{
	if (animCount < 5) {
		return enemyPirate0_data;
	} else if (animCount < 10) {
		return enemyPirate2_data;
	} else if (animCount < 15) {
		return enemyPirate0_data;
	} else {
		return enemyPirate1_data;
	}
}

void drawEnemyPirates(EnemyPirate *enemyPirates, const unsigned short *animEnemyPirate)
{
	//draw the enemy pirates
	for (int i = 0; i < ENEMYPIRATES; i++)
	{
		if (enemyPirates[i].used == 1) //if its in use
		{
			drawRect(enemyPirates[i].oldRow, enemyPirates[i].oldCol, ENEMYPIRATE0_HEIGHT, ENEMYPIRATE0_WIDTH, SAND);
			drawSprite(enemyPirates[i].row,enemyPirates[i].col,ENEMYPIRATE0_HEIGHT,ENEMYPIRATE0_WIDTH,animEnemyPirate);
		}
		if (enemyPirates[i].eraseNext == 1)
		{
			drawRect(enemyPirates[i].oldRow, enemyPirates[i].oldCol, ENEMYPIRATE0_HEIGHT, ENEMYPIRATE0_WIDTH, SAND);
       			enemyPirates[i].row = 200; //reset these values as well because some weird stuff will probs happen
       			enemyPirates[i].col = 0;
       			enemyPirates[i].oldCol = 0;
			enemyPirates[i].eraseNext = 0;
		}
	}
}

void changeOldEnemyPirates(EnemyPirate *enemyPirates)
{
	for (int i = 0; i < ENEMYPIRATES; i++)
	{
		if (enemyPirates[i].used == 1) //if its in use
		{
			enemyPirates[i].oldCol = enemyPirates[i].col;
			enemyPirates[i].oldRow = enemyPirates[i].row;
		}
	}
}

void pirateFire(EnemyPirate *toFire, EnemyBullet *eBullets)
{
	int bulletFired = 0;
	for (int i = 0; (i < ENEMYBULLETS) && !bulletFired; i++)
	{
		if (eBullets[i].used == 0) {
			eBullets[i].used = 1;
			eBullets[i].row = toFire->row + 10;
			eBullets[i].col = toFire->col;
			eBullets[i].rd = 0;
			eBullets[i].cd = -2;
			bulletFired = 1;
		}
	}
	
}
