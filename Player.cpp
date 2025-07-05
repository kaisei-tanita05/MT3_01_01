#include "Player.h"
#include <Novice.h>
#include <Vector2.h>
#include <cassert>

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize() {
	// プレイヤーの初期座標
	pos_.x = 640.0f;
	pos_.y = 360.0f;

	// マウスでクリックされた座標
	clickPos_.x = 0.0f;
	clickPos_.y = 0.0f;

	mousePos = {0.0f, 0.0f};

	// プレイヤーの半径
	radius_ = 32.0f;

	draggLimit = 20.0f;

	velocity_ = {0.0f, 0.0f};

	dir = {0.0f, 0.0f};

	len_ = 0.0f;

#pragma region 摩擦

	// 摩擦に関する変数
	acceleration_ = {-10.0f, -10.0f};

	kGravity_ = {-9.8f, -9.8f};

	miu_ = 0.4f;

	mass_ = 1.0f;

	magnitude_ = 0.0f;

	direction_ = {0.0f, 0.0f};

	frictionalForce_ = {};
#pragma endregion

	// 引っ張っていることを感知するフラグ
	dragging = false;
}

// マウスをクリックし始めた座標と終わりの座標の差分の計算
Vector2 Player::getVector(Vector2 from, Vector2 to) { return {to.x - from.x, to.y - from.y}; }

//
float Player::getLength(Vector2 vec) { return sqrtf(vec.x * vec.x + vec.y * vec.y); }

Vector2 Player::Normalize(Vector2 vec) {
	float len = getLength(vec);

	if (len == 0)
		return {0, 0};

	return {vec.x / len, vec.y / len};
}



/// <summary>
/// 更新
/// </summary>
void Player::Updata() {

	Novice::GetMousePosition(reinterpret_cast<int*>(&mousePos.x), reinterpret_cast<int*>(&mousePos.y));

	// 自機のスピードが０の時にしか引っ張れない
	// 引っ張り開始
	if (Novice::IsPressMouse(0) == 1) {
		// 修正されたコード
		if (getLength(getVector(mousePos, pos_)) <= draggLimit) {

			dragging = true;
		}
	}

	// マウスを離した
	if (Novice::IsPressMouse(0) == 0 && dragging) {
		Novice::GetMousePosition(reinterpret_cast<int*>(&mousePos.x), reinterpret_cast<int*>(&mousePos.y));

		dir = {pos_.x - mousePos.x, pos_.y - mousePos.y};

		len_ = getLength(dir);
		if (len_ > 0) {
			// Replace the problematic line with the following code to fix the error
			velocity_ = {dir.x / len_, dir.y / len_};
		}
		dragging = false;
	}

	pos_ += velocity_;

	// 動いてる場合に摩擦
	if (fabs(velocity_.x) > 0.01f || fabs(velocity_.y) > 0.01f) {
		// 資料p19を参考に摩擦の処理を行う

		magnitude_ = miu_ * function_->Length({-mass_ * kGravity_.x, -mass_ * kGravity_.y});

		if (velocity_.x > 0.0f) {
			direction_.x = -1.0f;
		} else {
			direction_.x = 1.0f;
		}

		if (velocity_.y > 0.0f) {
			direction_.y = -1.0f;
		} else {
			direction_.y = 1.0f;
		}

		frictionalForce_ = {magnitude_ * direction_.x, magnitude_ * direction_.y};

		acceleration_.x = frictionalForce_.x / mass_;

		acceleration_.y = frictionalForce_.y / mass_;

		if (fabs(acceleration_.x / 60.0f) > fabs(velocity_.x)) {
			acceleration_.x = velocity_.x * 60.0f;
		}

		if (fabs(acceleration_.y / 60.0f) > fabs(velocity_.y)) {
			acceleration_.y = velocity_.y * 60.0f;
		}

	} else {
		acceleration_.x = 0.0f;
		acceleration_.y = 0.0f;
	}

	// 速度に1フレーム辺りの加速度を加算する
	velocity_.x += acceleration_.x / 60.0f;
	velocity_.y += acceleration_.y / 60.0f;

	// velocity_が小さすぎる場合は0にする
	// fabsで絶対値を取るとやりやすい
	pos_.x += velocity_.x / 60.0f;
	pos_.y += velocity_.y / 60.0f;

	if (pos_.x <= 0.0f || pos_.x >= 1280.0f - radius_) {
		velocity_.x *= -1.0f;
	}

	if (pos_.y <= 0.0f || pos_.y >= 720.0f - radius_) {
		velocity_.y *= -1.0f;
	}
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw() { Novice::DrawBox(static_cast<int>(pos_.x), static_cast<int>(pos_.y), static_cast<int>(radius_), static_cast<int>(radius_), 0.0f, WHITE, kFillModeSolid); }
