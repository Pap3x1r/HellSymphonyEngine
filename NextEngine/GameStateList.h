#pragma once

enum GameState {
	// list of all game states 
	GS_MAINMENU = 0,
	GS_LOADINGSCREEN,
	GS_LIMBO,
	GS_ZIZ,
	GS_LUCIFER,

	// special game state. Do not change
	GS_RESTART,
	GS_QUIT,
	GS_NONE
};