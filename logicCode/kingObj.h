#ifndef KING_OBJ_H
#define KING_OBJ_H
#include "bulletObj.h"
#include "images.h"

typedef struct
{
	int row;
	int col;
	int oldRow;
	int oldCol;
	int rd;
	int cd;
	int lives;
	int drawOof;
	int used;
	int eraseNext;
} King;

void initKing(King *king);
void updateKing(King *king, Bullet *playerBullets);
const unsigned short* setAnimKing(int animCount);
void drawKing(King *king, const unsigned short *animKing);
void changeOldKing(King *king);
void kingFire(King *toFire, EnemyBullet *eBullets);
void kingFire2(King *toFire, EnemyBullet *eBullets);
void kingFire3(King *toFire, EnemyBullet *eBullets);

#endif
