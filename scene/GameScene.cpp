#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	// 3Dモデルの生成
	model_ = Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 960);

	// 軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを初期化する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	for (int i = 0; i < 8; i++) {

		//平行移動
		vertexTranslation[i].x = vertex[i].x * Translation[0][0] + vertex[i].y * Translation[0][1] +
		                         vertex[i].z * Translation[0][2] +
		                         1 * Translation[0][3]; // X軸方向の移動

		vertexTranslation[i].y = vertex[i].x * Translation[1][0] + vertex[i].y * Translation[1][1] +
		                         vertex[i].z * Translation[1][2] +
		                         1 * Translation[1][3]; // Y軸方向の移動

		vertexTranslation[i].z = vertex[i].x * Translation[2][0] + vertex[i].y * Translation[2][1] +
		                         vertex[i].z * Translation[2][2] +
		                         1 * Translation[2][3]; // Z軸方向の移動
	}


	for (int i = 0; i < 8; i++) {
		// X軸周りの回転
		vertexRotateX[i].x =
		  vertex[i].x * RotateX[0][0] + vertex[i].y * RotateX[0][1] + vertex[i].z * RotateX[0][2];

		vertexRotateX[i].y =
		  vertex[i].x * RotateX[1][0] + vertex[i].y * RotateX[1][1] + vertex[i].z * RotateX[1][2];

		vertexRotateX[i].z =
		  vertex[i].x * RotateX[2][0] + vertex[i].y * RotateX[2][1] + vertex[i].z * RotateX[2][2];
	}

	for (int i = 0; i < 8; i++) {
		// Y軸周りの回転
		vertexRotateY[i].x =
		  vertex[i].x * RotateY[0][0] + vertex[i].y * RotateY[0][1] + vertex[i].z * RotateY[0][2];

		vertexRotateY[i].y =
		  vertex[i].x * RotateY[1][0] + vertex[i].y * RotateY[1][1] + vertex[i].z * RotateY[1][2];

		vertexRotateY[i].z =
		  vertex[i].x * RotateY[2][0] + vertex[i].y * RotateY[2][1] + vertex[i].z * RotateY[2][2];

	}

	for (int i = 0; i < 8; i++) {
		// Z軸周りの回転
		vertexRotateZ[i].x =
		  vertex[i].x * RotateZ[0][0] + vertex[i].y * RotateZ[0][1] + vertex[i].z * RotateZ[0][2];

		vertexRotateZ[i].y =
		  vertex[i].x * RotateZ[1][0] + vertex[i].y * RotateZ[1][1] + vertex[i].z * RotateZ[1][2];

		vertexRotateZ[i].z =
		  vertex[i].x * RotateZ[2][0] + vertex[i].y * RotateZ[2][1] + vertex[i].z * RotateZ[2][2];
	}

	for (int i = 0; i < 8; i++) {
		// 拡縮
		vertexScale[i].x =
		  vertex[i].x * Scale[0][0] + vertex[i].y * Scale[0][1] + vertex[i].z * Scale[0][2];

		vertexScale[i].y =
		  vertex[i].x * Scale[1][0] + vertex[i].y * Scale[1][1] + vertex[i].z * Scale[1][2];

		vertexScale[i].z =
		  vertex[i].x * Scale[2][0] + vertex[i].y * Scale[2][1] + vertex[i].z * Scale[2][2];
	}
}

void GameScene::Update() { debugCamera_->Update(); }

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	// model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  vertex[edgeList[i][0]], vertex[edgeList[i][1]], WHITE);

		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  vertexTranslation[edgeList[i][0]], vertexTranslation[edgeList[i][1]], RED);

		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  vertexRotateX[edgeList[i][0]], vertexRotateX[edgeList[i][1]], GREEN);

		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  vertexRotateY[edgeList[i][0]], vertexRotateY[edgeList[i][1]], GREEN);

		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  vertexRotateZ[edgeList[i][0]], vertexRotateZ[edgeList[i][1]], GREEN);

		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  vertexScale[edgeList[i][0]], vertexScale[edgeList[i][1]], BLACK);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
