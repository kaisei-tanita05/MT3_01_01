#pragma once
#include <Vector2.h>
#include "Function.h"

class Player 
{

	public:
	void Initialize();

	void Updata();

	void Draw();

	Vector2 pos_;

	Vector2 speed_;

	Vector2 velocity_;

	Vector2 acceleration_;

	float mass_;

	float radius_;

	Vector2 kGravity_;

	float miu_;

	float magnitude_;

	Vector2 direction_;

	Vector2 frictionalForce_;

	
	Function* function_ = new Function;
};
