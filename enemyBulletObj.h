#ifndef ENEMYBULLET_OBJ_H
#define ENEMYBULLET_OBJ_H
#define ENEMYBULLETS 40

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
} EnemyBullet;

void initEnemyBullets(EnemyBullet *enemyBullets);
void updateEnemyBullets(EnemyBullet *enemyBullets);
void drawEnemyBullets(EnemyBullet *enemyBullets);
void changeOldEnemyBullets(EnemyBullet *enemyBullets);

#endif
