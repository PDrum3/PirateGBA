#ifndef ENEMYPIRATE_OBJ_H
#define ENEMYPIRATE_OBJ_H
#define ENEMYPIRATES 3
#include "bulletObj.h"
#include "enemyBulletObj.h"

typedef struct
{
	int row;
	int col;
	int oldRow;
	int oldCol;
	int rd;
	int cd;
	int hits;
	int used;
	int eraseNext;
} EnemyPirate;

void initEnemyPirates(EnemyPirate *enemyPirates);
void updateEnemyPirates(EnemyPirate *enemyPirates, Bullet *playerBullets);
const unsigned short* setAnimEnemyPirate(int animCount);
void drawEnemyPirates(EnemyPirate *enemyPirates, const unsigned short *animEnemyPirate);
void changeOldEnemyPirates(EnemyPirate *enemyPirates);
void pirateFire(EnemyPirate *toFire, EnemyBullet *eBullets);

#endif
