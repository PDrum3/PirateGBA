#ifndef SHIP_OBJ_H
#define SHIP_OBJ_H
#include "enemyBulletObj.h"

typedef struct 
{
	int row;
	int col; //they only move left to right, so no oldRow necessary
        int oldCol;
        int cd;
	int hideBox; // set the state of a box that hides the ship so it looks like it smoothly comes on screen
	int used; //1 if used and 0 if not. Decides if it should be drawn/updated
	int eraseNext; //1 if its at the end of the screen and needs to be erased, 0 if not
} Ship;

void initShip(Ship *enemyShip);
void updateShip(Ship *enemyShip);
const unsigned short* setAnimShip(int animCount);
void drawEnemyShip(Ship *enemyShip, const unsigned short* animShip);
void shipFire(Ship *toFire, EnemyBullet *eBullets);

#endif
