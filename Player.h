#pragma once
#include <Vector2.h>
#include "Function.h"
#include <math.h>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>


class Player 
{

	public:
	void Initialize();

	void Updata();

	void Draw();

	Vector2 getVector(Vector2 from,Vector2);

	float getLength(Vector2 vec);

	Vector2 Normalize(Vector2 vec);

	Vector2 pos_;

	//マウスのクリック時に取得する座標
	Vector2 clickPos_;

	//マウスのクリックをやめたときに座標を渡す
	Vector2 mousePos;

	//二つの座標から座標の差分を取得
	Vector2 dist;

	//自機の移動スピード
	Vector2 speed_;

	Vector2 velocity_;

	//2つの座標の差分
	Vector2 dir;

	float len_;

	//摩擦
	Vector2 acceleration_;

	//質量
	float mass_;

	float radius_;

	//重力
	Vector2 kGravity_;

	float miu_;

	float magnitude_;

	Vector2 direction_;

	Vector2 frictionalForce_;

	bool dragging;

	float draggLimit;
	
	Function* function_ = new Function;
};
