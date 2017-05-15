#include "bulletObj.h"
#include "myLib.h"

void initBullet(Bullet *playerBullets) {
	for (int i = 0; i < MAXSHOT; i++)
	{
		playerBullets[i].row = 0;
		playerBullets[i].col = 0;
		playerBullets[i].oldCol = 0;
		playerBullets[i].cd = BULLETSPD;
		playerBullets[i].used = 0;
		playerBullets[i].eraseNext = 0;
        }
}

void updateBullets(Bullet *bulletArr)
{
	for (int i = 0; i < MAXSHOT; i++)
	{
		if ((bulletArr + i)->used == 1) //if its in use
		{
			(bulletArr + i)->col += BULLETSPD;
			if ((bulletArr + i)->col > SCREEN_WIDTH - 4) //4 is bullet width
			{
				(bulletArr + i)->used = 0; //stop it from being used when it goes off the screen
  	     				(bulletArr + i)->eraseNext = 1;
			}
		}
	}
}

void fireBullet(Bullet *bulletArr, Player *p)
{
	Bullet *toFire; //get a spot ready for a reference to the ready bullet
	for (int i = 0; i < MAXSHOT; i++) //find a bullet in the array that isn't being used
	{
		if (bulletArr[i].used == 0)
		{
			toFire = &bulletArr[i];
			break;
		}
	}
	//now put the bullet on the player and let it start getting updated
	toFire->row = p->row + 20; //play with these to make it come out of the gun
	toFire->col = p->col + 26;
	toFire->used = 1; //can now be updated
	toFire->eraseNext = 0; //reset this so it isn't immediately erased
}


void drawBullets(Bullet *playerBullets)
{
	for (int i = 0; i < MAXSHOT; i++)
	{
		if (playerBullets[i].used == 1) //if its in use
		{
			drawRect(playerBullets[i].row, playerBullets[i].oldCol, 2, 4, SAND);
			drawRect(playerBullets[i].row, playerBullets[i].col, 2, 4, BLACK);
		}
		if (playerBullets[i].eraseNext == 1)
		{
			drawRect(playerBullets[i].row, playerBullets[i].oldCol, 2, 4, SAND);
       			playerBullets[i].row = 200; //reset these values as well because some weird stuff will probs happen
       			playerBullets[i].col = 0;
       			playerBullets[i].oldCol = 0;
		}
	}
}

void changeOldBullets(Bullet *playerBullets)
{
	for (int i = 0; i < MAXSHOT; i++)
	{
		if (playerBullets[i].used == 1) //if its in use
		{
			playerBullets[i].oldCol = playerBullets[i].col;
		}
	}
}
