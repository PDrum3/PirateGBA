#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "images.h" //all image includes here

#include "playerObj.h"
#include "bulletObj.h"
#include "enemyBulletObj.h"
#include "parrotObj.h"
#include "enemyPirateObj.h"
#include "shipObj.h"
#include "kingObj.h"

void setInitialStates(Player *p, Bullet *playerBullets, Parrot *parrots,
		EnemyPirate *enemyPirates, Ship *enemyShip, King *king, EnemyBullet *enemyBullets);

int main()
{

	//add stuff for screen changing and the first frame
	enum GBAState {
		GAME,
		END,
		GAMEOVER,
		TITLE,
		STORY
	};
	enum GBAState state = TITLE;
	int firstFrame = 1;

	//intialize struct things
        Player p;
	Bullet playerBullets[MAXSHOT];
	Parrot parrots[PARROTS];
	EnemyPirate enemyPirates[ENEMYPIRATES];
	Ship enemyShip;
	King king;
	EnemyBullet enemyBullets[ENEMYBULLETS];

	setInitialStates(&p, playerBullets, parrots, enemyPirates, &enemyShip, &king, enemyBullets);

	//set timing/other variables
	int SHOT_TIMER = 15;
	int shotCount = SHOT_TIMER;
        int animCount = 0;

	//scene timing variables
	int scene = 0;
	int sceneTimer = 0;
	
	REG_DISPCTL = MODE3 | BG2_ENABLE; //start being able to draw

	while(1) // Game Loop
	{
		switch(state) {
		case GAME:
		if (firstFrame) {
			//draw the background
			unsigned short bgcolor = SKY;
			DMA[3].src = &bgcolor;
			DMA[3].dst = videoBuffer;
			DMA[3].cnt = (SCREEN_WIDTH * 41) | DMA_ON | DMA_SOURCE_FIXED;
			bgcolor = OCEAN;
			DMA[3].src = &bgcolor;
			DMA[3].dst = videoBuffer + (SCREEN_WIDTH * 41);
			DMA[3].cnt = (SCREEN_WIDTH * 36) | DMA_ON | DMA_SOURCE_FIXED;
			bgcolor = SAND;
			DMA[3].src = &bgcolor;
			DMA[3].dst = videoBuffer + (SCREEN_WIDTH * 77);
			DMA[3].cnt = (SCREEN_WIDTH * 83) | DMA_ON | DMA_SOURCE_FIXED;
			firstFrame = 0;
		}
		
		//Player movement
		focusPlayer(&p);
 		if(KEY_DOWN_NOW(BUTTON_SELECT))
		{
			firstFrame = 1;
			state = TITLE;
		}
		movePlayer(&p);
		
		//SCENE UPDATING
		sceneTimer++;
		if (scene == 0) { //a parrots only scene
			if (sceneTimer == 120) {
				parrots[0].row = -20;
				parrots[0].col = 190;
				parrots[0].used = 1;
				parrots[0].cd = -1;
				parrots[0].rd = 1;
				parrots[1].row = -20;
				parrots[1].col = 160;
				parrots[1].used = 1;
				parrots[1].cd = -2;
				parrots[1].rd = 1;
			} else if (sceneTimer == 150) {
				parrots[0].rd = 0;
				parrots[1].rd = 0;
				parrotFire(&parrots[1], enemyBullets);
				parrotFire(&parrots[0], enemyBullets);
			} else if (sceneTimer == 180) {
				parrotFire(&parrots[0], enemyBullets);
			} else if (sceneTimer == 205) {
				parrots[1].used = 0;
				parrots[1].eraseNext = 1;
			} else if (sceneTimer == 250) {
				parrotFire(&parrots[0], enemyBullets);
			} else if (sceneTimer == 320) {
				parrots[0].used = 0;
				parrots[0].eraseNext = 1;
				sceneTimer = 50; //these two var changes move the game to the next scene
				scene++;
			}
		} else if (scene == 1) { //a pirate on the ground and a ship
			if (sceneTimer == 60) {
				enemyPirates[0].row = 170;
				enemyPirates[0].col = 190;
				enemyPirates[0].used = 1;
				enemyPirates[0].cd = -1;
				enemyPirates[0].rd = -1;
			} else if (sceneTimer == 100) {
				if (enemyPirates[0].used == 1)
				{
					enemyPirates[0].cd = 0;
					enemyPirates[0].rd = -1;
					pirateFire(&enemyPirates[0], enemyBullets);
				}
			} else if (sceneTimer == 130) {
				if (enemyPirates[0].used == 1)
				{
					enemyPirates[0].cd = 0;
					enemyPirates[0].rd = 1;
					pirateFire(&enemyPirates[0], enemyBullets);
				}
			} else if (sceneTimer == 160) {
				if (enemyPirates[0].used == 1)
				{
					enemyPirates[0].cd = 0;
					enemyPirates[0].rd = -1;
					pirateFire(&enemyPirates[0], enemyBullets);
				}
			} else if (sceneTimer == 190) {
				if (enemyPirates[0].used == 1)
				{
					enemyPirates[0].cd = 0;
					enemyPirates[0].rd = 1;
				}
			} else if (sceneTimer == 260) {
				enemyPirates[0].used = 0;
				enemyPirates[0].hits = 3;
				enemyShip.used = 1;
				enemyShip.row = 11;
				enemyShip.col = 245;
				enemyShip.cd = -1;
			} else if (sceneTimer == 380) {
				enemyShip.hideBox = 1;
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 300) {
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 350) {
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 558) {
				enemyShip.used = 0;
				enemyShip.hideBox = 0;
				enemyShip.eraseNext = 1;
			} else if (sceneTimer == 560) {
				enemyShip.used = 1;
				enemyShip.row = 11;
				enemyShip.col = 245;
				enemyShip.cd = -1;
			} else if (sceneTimer == 610) {
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 620) {
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 630) {
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 640) {
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 650) {
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 660) {
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 670) {
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 680) {
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 690) {
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 681) {
				enemyShip.hideBox = 1;
			} else if (sceneTimer == 858) {
				enemyShip.used = 0;
				enemyShip.hideBox = 0;
				enemyShip.eraseNext = 1;
				scene++;
				sceneTimer = 50;
			}
		} else if (scene == 2) {
			if (sceneTimer == 60) {
				enemyPirates[0].row = 170;
				enemyPirates[0].col = 170;
				enemyPirates[0].used = 1;
				enemyPirates[0].cd = -1;
				enemyPirates[0].rd = -1;

				enemyPirates[1].row = 170;
				enemyPirates[1].col = 190;
				enemyPirates[1].used = 1;
				enemyPirates[1].cd = 0;
				enemyPirates[1].rd = -1;
			} else if (sceneTimer == 100) {
				enemyPirates[0].cd = 0;
				enemyPirates[0].rd = -1;
				pirateFire(&enemyPirates[0], enemyBullets);
				enemyPirates[1].cd = 0;
				enemyPirates[1].rd = 0;
			} else if (sceneTimer == 130) {
				enemyPirates[0].cd = 0;
				enemyPirates[0].rd = 0;
				pirateFire(&enemyPirates[0], enemyBullets);
				pirateFire(&enemyPirates[1], enemyBullets);
			} else if (sceneTimer == 180) {
				enemyPirates[0].cd = 0;
				enemyPirates[0].rd = 0;
				pirateFire(&enemyPirates[0], enemyBullets);
				pirateFire(&enemyPirates[1], enemyBullets);
			} else if (sceneTimer == 230) {
				enemyPirates[0].cd = 0;
				enemyPirates[0].rd = 0;
				pirateFire(&enemyPirates[0], enemyBullets);
				pirateFire(&enemyPirates[1], enemyBullets);
				parrots[0].row = -20;
				parrots[0].col = 190;
				parrots[0].used = 1;
				parrots[0].cd = -1;
				parrots[0].rd = 1;
			} else if (sceneTimer == 260) {
				parrots[0].rd = 0;
			} else if (sceneTimer == 290) {
				parrotFire(&parrots[0], enemyBullets);
			} else if (sceneTimer == 320) {
				parrotFire(&parrots[0], enemyBullets);
				enemyPirates[0].rd = 1;
				enemyPirates[1].rd = 2;
			} else if (sceneTimer == 330) {
				parrotFire(&parrots[0], enemyBullets);
			} else if (sceneTimer == 340) {
				parrotFire(&parrots[0], enemyBullets);
			} else if (sceneTimer == 380) {
				enemyPirates[0].used = 0;
				enemyPirates[0].hits = 3;
				enemyPirates[1].used = 0;
				enemyPirates[1].hits = 3;
			} else if (sceneTimer == 435) {
				parrots[0].used = 0;
				parrots[0].eraseNext = 1;
				sceneTimer = 50;
				scene++;
			}
		} else if (scene == 3) {
			if (sceneTimer == 60) {
				enemyShip.used = 1;
				enemyShip.row = 11;
				enemyShip.col = 245;
				enemyShip.cd = -1;
				enemyPirates[0].row = 170;
				enemyPirates[0].col = 170;
				enemyPirates[0].used = 1;
				enemyPirates[0].cd = 0;
				enemyPirates[0].rd = -1;
			} else if (sceneTimer == 90) {
				pirateFire(&enemyPirates[0], enemyBullets);
			} else if (sceneTimer == 100) {
				pirateFire(&enemyPirates[0], enemyBullets);
			} else if (sceneTimer == 120) {
				pirateFire(&enemyPirates[0], enemyBullets);
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 130) {
				pirateFire(&enemyPirates[0], enemyBullets);
				shipFire(&enemyShip, enemyBullets);
			} else if (sceneTimer == 140) {
				pirateFire(&enemyPirates[0], enemyBullets);
				shipFire(&enemyShip, enemyBullets);
				enemyPirates[0].rd = 1;
			} else if (sceneTimer == 140) {
				pirateFire(&enemyPirates[0], enemyBullets);
			} else if (sceneTimer == 150) {
				pirateFire(&enemyPirates[0], enemyBullets);
			} else if (sceneTimer == 160) {
				pirateFire(&enemyPirates[0], enemyBullets);
			} else if (sceneTimer == 180) {
				enemyShip.hideBox = 1;
			} else if (sceneTimer == 190) {
				shipFire(&enemyShip, enemyBullets);
				pirateFire(&enemyPirates[0], enemyBullets);
			} else if (sceneTimer == 200) {
				shipFire(&enemyShip, enemyBullets);
				pirateFire(&enemyPirates[0], enemyBullets);
			} else if (sceneTimer == 210) {
				enemyPirates[0].used = 0;
				enemyPirates[0].hits = 3;
			} else if (sceneTimer == 360) {
				enemyShip.used = 0;
				enemyShip.hideBox = 0;
				enemyShip.eraseNext = 1;
				sceneTimer = 50;
				scene++;
			}
		
		} else if (scene == 4) {
			if (sceneTimer == 60) {
				king.row = 200;
				king.col = 200;
				king.used = 1;
				king.rd = -1;
				king.lives = 8;
			} else if (sceneTimer == 170) {
				king.rd = 1;
				kingFire(&king, enemyBullets);
			} else if (sceneTimer == 220) {
				king.rd = -1;
				kingFire(&king, enemyBullets);
				if (king.lives > 0) {
					sceneTimer = 120;
				}
			} else if (sceneTimer == 270) {
				king.rd = 0;
				king.lives = 10;
				kingFire3(&king, enemyBullets);
			} else if (sceneTimer == 320) {
				kingFire2(&king, enemyBullets);
			} else if (sceneTimer == 370) {
				kingFire3(&king, enemyBullets);
				if (king.lives > 0) {
					sceneTimer = 271;
				}
			} else if (sceneTimer == 371) {
				king.lives = 15;
				king.rd = 1;
			} else if (sceneTimer == 390) {
				king.rd = 0;
			} else if (sceneTimer == 420) {
				kingFire(&king, enemyBullets);
				kingFire3(&king, enemyBullets);
				king.rd = -1;
			} else if (sceneTimer == 430) {
				kingFire(&king, enemyBullets);
				kingFire3(&king, enemyBullets);
			} else if (sceneTimer == 440) {
				kingFire(&king, enemyBullets);
				kingFire3(&king, enemyBullets);
			} else if (sceneTimer == 450) {
				king.rd = 1;
			} else if (sceneTimer == 480) {
				king.rd = 0;
				if (king.lives > 1) {
					sceneTimer = 419;
				} else {
					king.rd = -1;
				}
			} else if (sceneTimer == 500) {
				king.rd = 0;
				drawSprite(king.row - 10, king.col + 6, OOF_HEIGHT, OOF_WIDTH, oof_data);
			} else if (sceneTimer == 610) {
				drawRect(king.row - 10, king.col + 6, OOF_HEIGHT, OOF_WIDTH, SAND);
				king.rd = 2;
			} else if (sceneTimer == 650) {
				king.used = 0;
			} else if (sceneTimer == 700) {
				firstFrame = 1;
				state = END;
			}
		}
		//END OF SCENE UPDATING
		

		//Check to fire bullets
		if (shotCount < SHOT_TIMER) { shotCount++; }
		if (KEY_DOWN_NOW(BUTTON_A)) //the player is pressing fire
		{
			if(shotCount >= SHOT_TIMER) //ready to fire
			{
				fireBullet(playerBullets, &p);
				shotCount = 0; //reset so you have to wait to fire again
			}
		}

		//UPDATING
		//move only bullets in use, and check for them going out of bounds
		updateBullets(playerBullets);
		//move/update only the parrots in use
		updateParrots(parrots);
		//move/update only the enemy pirates in use
		updateEnemyPirates(enemyPirates, playerBullets);

		//move/update the king if its in use
		updateKing(&king, playerBullets);
		//move/update the ship if its in use
		updateShip(&enemyShip);

		//move/update the enemy bullets
		updateEnemyBullets(enemyBullets);

		//move/update the player. Also check for bullets
		updatePlayer(&p, enemyBullets);

		//prepare animation stuff here
		animCount++;
		if (animCount > 20) {animCount = 0;}
		//set the correct player animation
		const unsigned short *animPlayer;
		const unsigned short *animParrot;
		const unsigned short *animEnemyPirate;
		const unsigned short *animShip;
		const unsigned short *animKing;
		animPlayer = setAnim(animCount);
		//set the parrot animation
		animParrot = setAnimParrot(animCount);
		//set the enemy pirate animation
		animEnemyPirate = setAnimEnemyPirate(animCount);
		//set the ship animation
		animShip = setAnimShip(animCount);
		//set the king animation
		animKing = setAnimKing(animCount);

                waitForVblank();
		//drawing code here! This is the part that needs optimization if shearing starts

		drawPlayer(&p, animPlayer);
		//draw the enemy pirates
		drawEnemyPirates(enemyPirates, animEnemyPirate);
		//draw the king
		drawKing(&king, animKing);
		//draw the bullets
		drawBullets(playerBullets);
		//draw the hearts
		drawSprite(2, 2, HEARTS_HEIGHT, HEARTS_WIDTH, hearts_data);
		if (p.lives < 3)
		{
			drawSprite(2, 22, GHEART_HEIGHT, GHEART_WIDTH, gheart_data);
			if (p.lives < 2)
			{
				drawSprite(2, 12, GHEART_HEIGHT, GHEART_WIDTH, gheart_data);
				if (p.lives < 1)
				{
					drawSprite(2, 2, GHEART_HEIGHT, GHEART_WIDTH, gheart_data);
					firstFrame = 1;
					state = GAMEOVER;
				}
			}
		}
		//draw the parrots
		drawParrots(parrots, animParrot);
		//draw the ship and necessary blocks to hide it
		drawEnemyShip(&enemyShip, animShip);
		//draw the enemyBullets
		drawEnemyBullets(enemyBullets);

		//any things that need to be updated before next frame		
		p.oldRow = p.row;
		p.oldCol = p.col;
		//updates enemyShip
		enemyShip.oldCol = enemyShip.col;
		//update the bullets (old row/col)
		changeOldBullets(playerBullets);
		//do the same for the parrots
		changeOldParrots(parrots);
		//do the same for the enemy pirates
		changeOldEnemyPirates(enemyPirates);
		//do the same for king boss
		changeOldKing(&king);
		//do the same for the enemyBullets
		changeOldEnemyBullets(enemyBullets);
		break;
		case END:
		{
		int delay;
		if (firstFrame)
		{
			delay = 160000;
			firstFrame = 0;
			drawScreen(winScreen_data);
		}
		if (delay > 0) {delay--;}
		if ((KEY_DOWN_NOW(BUTTON_A) || KEY_DOWN_NOW(BUTTON_SELECT)) && delay < 1)
		{
			firstFrame = 1;
			state = TITLE;
		}
		}
		break;
		case GAMEOVER:
		{
		int delay;
		if (firstFrame)
		{
			delay = 160000;
			firstFrame = 0;
			drawScreen(over_data);
		}
		if (delay > 0) {delay--;}
		if ((KEY_DOWN_NOW(BUTTON_A) || KEY_DOWN_NOW(BUTTON_SELECT)) && delay < 1)
		{
			firstFrame = 1;
			state = TITLE;
		}
		}
		break;
		case TITLE:
		if (firstFrame) {
			firstFrame = 0;
			//init all the stuff from above!
			scene = 0;
			sceneTimer = 0;
			p.lives = 3;
			setInitialStates(&p, playerBullets, parrots, enemyPirates, &enemyShip, &king, enemyBullets);
			drawScreen(title_data);
		}
		if (KEY_DOWN_NOW(BUTTON_START))
		{
			firstFrame = 1;
			state = STORY;
		}
		break;
		case STORY:
		if (firstFrame) {
			firstFrame = 0;
			drawScreen(story_data);
			drawSprite(100, 54, CONTROLS_HEIGHT, CONTROLS_WIDTH, controls_data);
		}
		if (KEY_DOWN_NOW(BUTTON_A))
		{
			firstFrame = 1;
			state = GAME;
		} else if (KEY_DOWN_NOW(BUTTON_SELECT)) {
			firstFrame = 1;
			state = TITLE;
		}
		break;

		}//end of switch statement
	} // Game Loop
}


//init game objects/arrays for use
void setInitialStates(Player *p, Bullet *playerBullets, Parrot *parrots,
		EnemyPirate *enemyPirates, Ship *enemyShip, King *king, EnemyBullet *enemyBullets)
{
	//set up player for use
	initPlayer(p);
	//set up bullets for use
	initBullet(playerBullets);
	//set up parrots for use
	initParrots(parrots);
	//set up enemy pirates for use
	initEnemyPirates(enemyPirates);
	//set up the ship for use
        initShip(enemyShip);
	//set up the king for use
	initKing(king);
	//set up enemyBullets for use
	initEnemyBullets(enemyBullets);
}

