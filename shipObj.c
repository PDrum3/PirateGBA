#include "shipObj.h"
#include "images.h"
#include "myLib.h"

void initShip(Ship *enemyShip)
{
	//set up the ship for use
       	enemyShip->row = 170; //they'll never see it!
       	enemyShip->col = 0;
       	enemyShip->oldCol = 0;
       	enemyShip->cd = 0;
	enemyShip->hideBox = 0;
       	enemyShip->used = 0;
       	enemyShip->eraseNext = 0;
}

void updateShip(Ship *enemyShip)
{
	if (enemyShip->used == 1) {
		enemyShip->col += enemyShip->cd;
	}
}

const unsigned short* setAnimShip(int animCount)
{
	if (animCount < 13) {
		return ship0_data;
	} else {
		return ship1_data;
	}
}

void drawEnemyShip(Ship *enemyShip, const unsigned short* animShip)
{
	//draw the ship and necessary blocks to hide it
	if (enemyShip->used == 1)
	{
		drawRectBack(enemyShip->row, enemyShip->oldCol, SHIP0_HEIGHT, SHIP0_WIDTH, SKY, OCEAN, SAND);
		drawSprite(enemyShip->row, enemyShip->col, SHIP0_HEIGHT, SHIP0_WIDTH, animShip);
		if (!enemyShip->hideBox) { //as its coming on screen draw a rectangle to hide it
			drawRectBack(10, 0, 48, 55, SKY, OCEAN, SAND);
		} else { //as its going off draw a rectangle to hide it
			drawRectBack(9, 185, 48, 55, SKY, OCEAN, SAND);
		}
	}
	if (enemyShip->eraseNext == 1)
	{
        	enemyShip->row = 200; //reset these values as well because some weird stuff will probs happen
        	enemyShip->col = 0;
        	enemyShip->oldCol = 0;
		enemyShip->eraseNext = 0;
	}
}

void shipFire(Ship *toFire, EnemyBullet *eBullets)
{
	int amtToFire = 2; //how many bullets to fire in this attack
	int bulletsDrawn = 0;
	for (int i = 0; (i < ENEMYBULLETS) && (bulletsDrawn < amtToFire); i++)
	{
		if (eBullets[i].used == 0) {
			if (bulletsDrawn == 0) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row + 20;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = 2;
				eBullets[i].cd = -1;
				bulletsDrawn++;
			} else if (bulletsDrawn == 1) {
				eBullets[i].used = 1;
				eBullets[i].row = toFire->row + 20;
				eBullets[i].col = toFire->col;
				eBullets[i].rd = 2;
				eBullets[i].cd = -2;
				bulletsDrawn++;
			}
		}
	}
	
}
