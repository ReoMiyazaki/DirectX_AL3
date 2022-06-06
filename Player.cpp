#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	this->textureHandle_ = textureHandle;

	// シングルインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Update() {

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move = {-kCharacterSpeed, 0, 0};
	} else if (input_->PushKey(DIK_RIGHT)) {
		move = {kCharacterSpeed, 0, 0};
	}
	if (input_->PushKey(DIK_UP)) {
		move = {0, kCharacterSpeed, 0};
	} else if (input_->PushKey(DIK_DOWN)) {
		move = {0, -kCharacterSpeed, 0};
	}

	// 移動値を加算
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	// 行列の更新
	Matrix4 matTrans = MathUtility::Matrix4Identity();

	// 移動量を行列に設定する
	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;

	worldTransform_.matWorld_ = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

	worldTransform_.matWorld_ *= matTrans;

	worldTransform_.TransferMatrix();

	// キャラクターの座標を表示する処理
	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "Position:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}

void Player::Draw(ViewProjection viewProjection_) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}
