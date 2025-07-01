#include "Player.h"
#include <Novice.h>


/// <summary>
/// 初期化
/// </summary>
void Player::Initialize() {
	// プレイヤーの初期座標
	pos_.x = 640.0f;
	pos_.y = 360.0f;

	// プレイヤーの半径
	radius_ = 32.0f;

	// プレイヤーの速度
	speed_.x = 0.0f;
	speed_.y = 0.0f;

	//velocity_ = {0.0f, 0.0f};

	acceleration_ = {-10.0f, 0.0f};

	kGravity_ = {0.0f, -9.8f};

	miu_ = 0.4f;

	mass_ = 1.0f;

	magnitude_ = 0.0f;

	direction_ = {0.0f, 0.0f};

	frictionalForce_ = {};
}

/// <summary>
/// 更新
/// </summary>
void Player::Updata() {
	/*pos_.x += speed_.x;

	//if (pos_.x <= 0.0f || pos_.x >= 1280.0f - radius_) {
		//speed_.x *= -1.0f;
	//}

	//pos_.y += speed_.y;

	//if (pos_.y <= 0.0f || pos_.y >= 720.0f - radius_) {
		//speed_.y *= -1.0f;
	//}*/

	// 動いてる場合に摩擦
	if (fabs(speed_.x) > 0.01f || fabs(speed_.y) > 0.01f) {
		// 資料p19を参考に摩擦の処理を行う

		magnitude_ = miu_ * function_->Length({-mass_ * kGravity_.x, -mass_ * kGravity_.y});

		if (speed_.x > 0.0f) {
			direction_.x = -1.0f;
		} else {
			direction_.x = 1.0f;
		}

		frictionalForce_ = {magnitude_ * direction_.x, magnitude_ * direction_.y};

		acceleration_.x = frictionalForce_.x / mass_;

		if (fabs(acceleration_.x / 60.0f) > fabs(speed_.x)) {
			acceleration_.x = speed_.x * 60.0f;
		}

	} else {
		acceleration_.x = 0.0f;
		acceleration_.y = 0.0f;
	}

	// 速度に1フレーム辺りの加速度を加算する
	speed_.x += acceleration_.x / 60.0f;
	speed_.y += acceleration_.y;

	// velocity_が小さすぎる場合は0にする
	// fabsで絶対値を取るとやりやすい
	pos_.x += speed_.x / 60.0f;
	pos_.y += speed_.y / 60.0f;
}

void Player::Draw() { Novice::DrawBox(static_cast<int>(pos_.x), static_cast<int>(pos_.y), static_cast<int>(radius_), static_cast<int>(radius_), 0.0f, WHITE, kFillModeSolid); }