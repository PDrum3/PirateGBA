#include "playerObj.h"
#include "myLib.h"
#include "images.h"

void movePlayer(Player *p)
{
	//get up/down controls
	if(KEY_DOWN_NOW(BUTTON_UP) && (p->row > SCREEN_HEIGHT - 82))
	{
		p->rd = -(p->speed);
	} 	
	else if(KEY_DOWN_NOW(BUTTON_DOWN) && (p->row < SCREEN_HEIGHT - 28))
	{
		p->rd = (p->speed);
	} else {
		p->rd = 0;
        }
	//get left/right controls
	if(KEY_DOWN_NOW(BUTTON_LEFT) && (p->col >= 6))
	{
		p->cd = -(p->speed);
	}
	else if(KEY_DOWN_NOW(BUTTON_RIGHT) && (p->col <= SCREEN_WIDTH - 122))
	{
		p->cd = (p->speed);
	} else {
		p->cd = 0;
        }
	//set the coord changes and stuff to 0 here if you're out of bounds
}


void updatePlayer(Player *p, EnemyBullet *enemyBullets)
{
	p->row += p->rd;
	p->col += p->cd;
	for (int i = 0; i < ENEMYBULLETS; i++)
	{
		if (enemyBullets[i].used == 1)
		{
			if (((enemyBullets[i].row + 1) > (p->row + 14)) && ((enemyBullets[i].row + 1) < (p->row + 26)))
			{
				if (((enemyBullets[i].col + 1) > (p->col + 8)) && ((enemyBullets[i].col + 1) < (p->col + 20)))
				{
						enemyBullets[i].used = 0;
						enemyBullets[i].eraseNext = 1;
						p->lives -= 1;
				}
			}
		}
	}
}


void focusPlayer(Player *p)
{
	if(KEY_DOWN_NOW(BUTTON_B))
	{
	p->speed = 1;
	//SHOT_TIMER = 10;
	} else {
	p->speed = 2;
	//SHOT_TIMER = 15;
	}
}

void initPlayer(Player *p)
{
        p->row = 90;
        p->col = 30;
        p->oldRow = p->row;
        p->oldCol = p->col;
        p->rd = 0;
        p->cd = 0;
	p->speed = 2;
	p->lives = 3;
        p->size = 30;
}

const unsigned short* setAnim(int animCount)
{
	if (animCount < 5) {
		return pirate0_data;
	} else if (animCount < 10) {
		return pirate2_data;
	} else if (animCount < 15) {
		return pirate0_data;
	} else {
		return pirate1_data;
	}
}

void drawPlayer(Player *p, const unsigned short *animPlayer)
{
	/*if (p->speed == 1) { //hitbox only seen when moving slowly
		drawRect(p.row + 14, p.col + 8, 12, 12, RED); //offsets to put the hitbox in the middle
	}*/
	drawRect(p->oldRow, p->oldCol, p->size, p->size, SAND);
	drawSprite(p->row, p->col, p->size, p->size, animPlayer);
}


