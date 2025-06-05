#pragma once

enum GameState {
	// list of all game states 
	GS_MAINMENU = 0,
	GS_LOADINGSCREEN,
	GS_LIMBO1,
	GS_LIMBO2,
	GS_ZIZ,
	GS_LUCIFER,
	GS_CREDITS,

	// special game state. Do not change
	GS_RESTART,
	GS_QUIT,
	GS_NONE
};