#include "enemyBulletObj.h"
#include "myLib.h"

void initEnemyBullets(EnemyBullet *enemyBullets)
{
	for (int i = 0; i < ENEMYBULLETS; i++)
	{
        	enemyBullets[i].row = 0;
        	enemyBullets[i].col = 0;
        	enemyBullets[i].oldRow = 200;
        	enemyBullets[i].oldCol = 0;
        	enemyBullets[i].rd = 0;
        	enemyBullets[i].cd = 0;
        	enemyBullets[i].used = 0;
        	enemyBullets[i].eraseNext = 0;
        }
}

void updateEnemyBullets(EnemyBullet *enemyBullets)
{
	//move/update only the enemyBullets in use
	for (int i = 0; i < ENEMYBULLETS; i++)
	{
		if (enemyBullets[i].used == 1) //if its in use
		{
			enemyBullets[i].col += enemyBullets[i].cd;
			enemyBullets[i].row += enemyBullets[i].rd;
			if ((enemyBullets[i].row > SCREEN_HEIGHT) || (enemyBullets[i].col<0))
			{
				enemyBullets[i].used = 0; //stop it from being used when it goes off the screen
       				enemyBullets[i].eraseNext = 1;
			}
		}
	}
}

void drawEnemyBullets(EnemyBullet *enemyBullets)
{
	//draw the enemyBullets
	for (int i = 0; i < ENEMYBULLETS; i++)
	{
		if (enemyBullets[i].used == 1) //if its in use
		{
			drawRectBack(enemyBullets[i].oldRow, enemyBullets[i].oldCol, 3, 3, SKY, OCEAN, SAND);
			drawRect(enemyBullets[i].row, enemyBullets[i].col, 3, 3, RED);
		}
		if (enemyBullets[i].eraseNext == 1)
		{
			drawRectBack(enemyBullets[i].oldRow, enemyBullets[i].oldCol, 3, 3, SKY, OCEAN, SAND);
       			enemyBullets[i].row = 200; //reset these values as well because some weird stuff will probs happen
       			enemyBullets[i].col = 0;
       			enemyBullets[i].oldCol = 0;
			enemyBullets[i].eraseNext = 0;
		}
	}
}

void changeOldEnemyBullets(EnemyBullet *enemyBullets)
{
	for (int i = 0; i < ENEMYBULLETS; i++)
	{
		if (enemyBullets[i].used == 1) //if its in use
		{
			enemyBullets[i].oldCol = enemyBullets[i].col;
			enemyBullets[i].oldRow = enemyBullets[i].row;
		}
	}
}
