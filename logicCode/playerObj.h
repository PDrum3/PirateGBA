#ifndef PLAYER_OBJ_H
#define PLAYER_OBJ_H
#include "enemyBulletObj.h"

typedef struct 
{
	int row;
	int col;
        int oldRow;
        int oldCol;
	int rd;
	int cd;
	int speed;
	int size;
	int lives;
        
} Player;
void movePlayer(Player *p);
void updatePlayer(Player *p, EnemyBullet *enemyBullets);
void focusPlayer(Player *p);
void initPlayer(Player *p);
const unsigned short* setAnim(int animCount);
void drawPlayer(Player *p, const unsigned short *animPlayer);

#endif
