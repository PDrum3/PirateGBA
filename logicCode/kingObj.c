#include "kingObj.h"
#include "myLib.h"

void initKing(King *king)
{
        king->row = 0;
        king->col = 0;
        king->oldRow = 200;
        king->oldCol = 0;
        king->rd = 0;
        king->cd = 0;
        king->used = 0;
        king->eraseNext = 0;
}

void updateKing(King *king, Bullet *playerBullets)
{
	if (king->used == 1)
	{
		king->col += king->cd;
		king->row += king->rd;
		for (int i = 0; i < MAXSHOT; i++)
		{
			if (playerBullets[i].used == 1)
			{
				//COLLISION WITH PLAYER BULLETS
				if (((playerBullets[i].row) > (king->row)) && ((playerBullets[i].row) < (KING0_HEIGHT + king->row)))
				{
					if (((playerBullets[i].col)>(king->col))&&((playerBullets[i].col) < (KING0_WIDTH + king->col)))
					{
						playerBullets[i].used = 0;
						playerBullets[i].eraseNext = 1;
						king->lives--;
					}
				}
			}
		}
	}
}

const unsigned short* setAnimKing(int animCount)
{
	if (animCount < 5) {
		return king0_data;
	} else if (animCount < 10) {
		return king2_data;
	} else if (animCount < 15) {
		return king0_data;
	} else {
		return king1_data;
	}
}

void drawKing(King *king, const unsigned short *animKing)
{
	if (king->used == 1)
	{
		drawRect(king->oldRow, king->oldCol, KING0_HEIGHT, KING0_WIDTH, SAND);
		drawSprite(king->row,king->col,KING0_HEIGHT,KING0_WIDTH, animKing);	
	}
}

void changeOldKing(King *king)
{
	if (king->used == 1)
	{
		king->oldCol = king->col;
		king->oldRow = king->row;
	}
}

void kingFire(King *toFire, EnemyBullet *eBullets)
{
	int amtToFire = 3; //how many bullets to fire in this attack
	int bulletsDrawn = 0;
	for (int i = 0; (i < ENEMYBULLETS) && (bulletsDrawn < amtToFire); i++)
	{
		if (eBullets[i].used == 0) {
			if (bulletsDrawn == 0) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row + 15;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = 0;
				eBullets[i].cd = -4;
				bulletsDrawn++;
			} else if (bulletsDrawn == 1) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row + 15;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = 1;
				eBullets[i].cd = -4;
				bulletsDrawn++;
			} else if (bulletsDrawn == 2) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row + 15;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = -1;
				eBullets[i].cd = -4;
				bulletsDrawn++;
			}
		}
	}	
}

void kingFire2(King *toFire, EnemyBullet *eBullets)
{
	int amtToFire = 3; //how many bullets to fire in this attack
	int bulletsDrawn = 0;
	for (int i = 0; (i < ENEMYBULLETS) && (bulletsDrawn < amtToFire); i++)
	{
		if (eBullets[i].used == 0) {
			if (bulletsDrawn == 0) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row + 15;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = -1;
				eBullets[i].cd = -5;
				bulletsDrawn++;
			} else if (bulletsDrawn == 1) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row + 15;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = 1;
				eBullets[i].cd = -5;
				bulletsDrawn++;
			} else if (bulletsDrawn == 2) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row + 15;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = 2;
				eBullets[i].cd = -5;
				bulletsDrawn++;
			}
		}
	}	
}

void kingFire3(King *toFire, EnemyBullet *eBullets)
{
	int amtToFire = 3; //how many bullets to fire in this attack
	int bulletsDrawn = 0;
	for (int i = 0; (i < ENEMYBULLETS) && (bulletsDrawn < amtToFire); i++)
	{
		if (eBullets[i].used == 0) {
			if (bulletsDrawn == 0) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row + 15;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = 0;
				eBullets[i].cd = -5;
				bulletsDrawn++;
			} else if (bulletsDrawn == 1) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row + 15;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = -1;
				eBullets[i].cd = -5;
				bulletsDrawn++;
			} else if (bulletsDrawn == 2) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row + 15;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = -2;
				eBullets[i].cd = -5;
				bulletsDrawn++;
			}
		}
	}	
}
