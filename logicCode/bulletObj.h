#ifndef BULLET_OBJ_H
#define BULLET_OBJ_H

#include "playerObj.h"
#define BULLETSPD 4
#define MAXSHOT 8

typedef struct 
{
	int row;
	int col; //they only move left to right, so no oldRow necessary
        int oldCol;
        int cd;
	int used; //1 if used and 0 if not. Decides if it should be drawn/updated
	int eraseNext; //1 if its at the end of the screen and needs to be erased, 0 if not
} Bullet;
void initBullet(Bullet *curr);
void updateBullets(Bullet *bulletArr);
void fireBullet(Bullet *bulletArr, Player *p);
void drawBullets(Bullet *bulletArr);
void changeOldBullets(Bullet *bulletArr);

#endif
