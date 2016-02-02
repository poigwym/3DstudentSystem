#pragma once

#include"Gobals.h"
#include"chars.h"


extern ID3DXEffect *gAnimationEffect;


struct GameB
{

	void init();
	void update(float dt);
	void render();
	void clear();
};