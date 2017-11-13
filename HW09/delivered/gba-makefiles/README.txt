GAME_INTRODUCTION:

This game has two modes: doge-mode and bomb-mode

doge-mode:
	The player will control his character, which is a Squirtle that will be born on the top-left corner, to avoid his enemies, which are an alien and a spider. The alien will be born on the top-right corner, and the spider will be born on the bottom-right corner. They will be floating around to catch the Squirtle, and the spider is faster than the alien. There will also be a Blue Gem floating around that the Squirtle can use to evolve into Blastoise, which will have a fasterer speed. However, the evolved Blastoise can only last for 5 time-unit. After this 5 time-unit the Blastoise will transform back into a Squirtle and the Blue Gem starts to float around in the world again. 

bomb-mode:
	The player will control his character, which is a Blastoise that will be born on the top-left corner, to avoid his enemies, which are an alien and a spider. The alien will be born on the top-right corner, and the spider will be born on the bottom-right corner. They will be floating around to catch the Blastoise, and the spider is faster than the alien. The Blastoise can put a bomb at any location, which will explode in a short while and everything next to it will be destoryed. The game ends when the Blastoise dies (caught by enemies or killed by bomb) or all enemies are killed


TIME_UNIT:

dodge-mode:
	For every 80 pixel units the player travels, the time-unit will increment by 1 to encourage the player to move around more.

bomb-mode:
	One time-unit is one loop/iteration through the game. The bomb explodes in 100 time-unit and the explosion stays for 20 time-unit


OPERATION:

Press 'A' ('Z') to proceed from title screen to the dodge-mode game screen.
Press 'B' ('X') to proceed from title screen to the bomb-mode game screen.
Press 'SELECT' ('DELETE') to go from the game over screen to the title screen. 
Press 'SELECT' ('DELETE') anytime can go to the title screen

dodge-mode:
	During the game, the up, down, left and right arrow will control the squirtle to go in the corresponding direction.

bomb-mode:
	During the game, the button 'A' ('Z') will put a bomb on the screen


GAME_PROGRESS:

dodge-mode:
	The bottom left corner will have a score tracker and the bottom right will hve a count down timer only when the Squirtle is evolved into a Blastoise. The count down timer will show how much longer the Blastoise will last until transforming back to a Squirtle.

bomb-mode:
	the game progress is basically how many enemies are left to kill on the screen. There is no need to use any text display for this.