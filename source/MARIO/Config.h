#pragma once
class Config
{

public:
	static const int NUM_HOR   = 16;
	static const int NUM_VER   = 15;
	static const int W_UNIT    = (32 * 2);
	static const int H_UNIT    = (32 * 2);
	static const int TILE_SIZE = (32 * 2);
	static const int W_SCREEN = NUM_HOR * W_UNIT;
	static const int H_SCREEN = NUM_VER * H_UNIT;
};

