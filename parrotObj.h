#ifndef PARROT_OBJ_H
#define PARROT_OBJ_H
#define PARROTS 2
#include "enemyBulletObj.h"

typedef struct
{
	int row;
	int col;
	int oldRow;
	int oldCol;
	int rd;
	int cd;
	int used;
	int eraseNext;
} Parrot;

void initParrots(Parrot *parrots);
void updateParrots(Parrot *parrots);
const unsigned short* setAnimParrot(int animCount);
void drawParrots(Parrot *parrots, const unsigned short *animParrot);
void changeOldParrots(Parrot *parrots);
void parrotFire(Parrot *toFire, EnemyBullet *eBullets);

#endif
