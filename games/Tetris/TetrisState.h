#pragma once

enum class TetrisState {
	LOGO,
	IDLE,
	SELECT_LEVEL,
	READY,
	GAME_RUNNING,
	END_OF_GAME,
	TRY_AGAIN,
	NEW_HIGHSCORE
};
