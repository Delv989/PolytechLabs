#pragma once

struct GameConfiguration
{
	/*-------------- GEM SETTINGS ---------------*/
	float ONE_SPRITE_WIDTH = 48.f;
	int GEM_SIZE = 50;

	/*------------- BOARD SETTINGS --------------*/
	int X0 = 20;
	int Y0 = 100;
	int GEMS_WIDTH_COUNT = 16;
	int GEMS_HEIGHT_COUNT = 9;

	/*------------- WINDOW SETTINGS -------------*/
	unsigned int WINDOW_WIDTH = 840;
	unsigned int WINDOW_HEIGHT = 570;
	int CLEAR_COLOR_RGB = 0x00003264;


};