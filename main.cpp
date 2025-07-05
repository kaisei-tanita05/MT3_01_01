#include <Novice.h>
#include "Function.h"
#include "Player.h"

const char kWindowTitle[] = "LE2C_20_タニタ_カイセイ";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//Function* function = new Function();

	Player* player = new Player();
	player->pos_.x = 640.0f;
	player->pos_.y = 360.0f;

	// マウスでクリックされた座標
	player->clickPos_.x = 0.0f;
	player->clickPos_.y = 0.0f;

	player->mousePos.x = 0.0f;
	player->mousePos.y = 0.0f;

	// プレイヤーの半径
	player->radius_ = 32.0f;

	// プレイヤーの速度
	player->speed_.x = 0.0f;
	player->speed_.y = 0.0f;

	player->velocity_ = {0.0f, 0.0f};

	player->draggLimit = 20.0f;

	player->velocity_ = {0.0f, 0.0f};

	player->dir = {0.0f, 0.0f};

	player->len_ = 0.0f;

	player->acceleration_ = {-50.0f, -50.0f};

	player->kGravity_ = {-9.8f, -9.8f};

	player->miu_ = 0.4f;

	player->mass_ = 1.0f;

	player->magnitude_ = 0.0f;

	player->direction_ = {0.0f, 0.0f};

	player->frictionalForce_ = {};



	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		player->Updata();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		player->Draw();

		Novice::ScreenPrintf(0, 0, "nowMousePosition%d %d", player->mousePos.x, player->mousePos.y);
		Novice::ScreenPrintf(0, 20, "mousClick%d", Novice::IsPressMouse(0));
		Novice::ScreenPrintf(0, 40, "playerPosition%f %f", player->pos_.x, player->pos_.y);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	delete player;
	return 0;
}
