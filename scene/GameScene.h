#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "math.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 3Dモデル
	Model* model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	const float PI = 3.1415f;

	Vector3 vertex[8] = {
	  {0.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 5.0f},
      {0.0f, 0.0f, 5.0f},
	  {0.0f, 5.0f, 0.0f},
      {5.0f, 5.0f, 0.0f},
      {5.0f, 5.0f, 5.0f},
      {0.0f, 5.0f, 5.0f}
    };

	Vector3 temporary[8] = {};
	Vector3 vertexTranslation[8] = {};
	Vector3 vertexRotateX[8] = {};
	Vector3 vertexRotateY[8] = {};
	Vector3 vertexRotateZ[8] = {};
	Vector3 vertexScale[8] = {};

	// 平行移動
	float Translation[4][4] = {
	  {1.0f, 0.0f, 0.0f, 5.0f}, // X軸方向の移動値
	  {0.0f, 1.0f, 0.0f, 5.0f}, // Y軸方向の移動値
	  {0.0f, 0.0f, 1.0f, 5.0f}, // Z軸方向の移動値
	  {0.0f, 0.0f, 0.0f, 1.0f}
    };

	// 回転移動(X軸周りの回転)
	float RotateX[4][4] = {
	  {1.0f, 0.0f,        0.0f,         0.0f},
	  {0.0f, cos(PI / 4), -sin(PI / 4), 0.0f},
	  {0.0f, sin(PI / 4), cos(PI / 4),  0.0f},
	  {0.0f, 0.0f,        0.0f,         1.0f}
    };

	// 回転移動(Y軸周りの回転)
	float RotateY[4][4] = {
	  {cos(PI / 4),  0.0f, sin(PI / 4), 0.0f},
	  {0.0f,         1.0f, 0.0f,        0.0f},
	  {-sin(PI / 4), 0.0f, cos(PI / 4), 0.0f},
	  {0.0f,         0.0f, 0.0f,        1.0f}
    };

	// 回転移動(Z軸周りの回転)
	float RotateZ[4][4] = {
	  {cos(PI / 4), -sin(PI / 4), 0.0f, 0.0f},
	  {sin(PI / 4), cos(PI / 4),  0.0f, 0.0f},
	  {0.0f,        0.0f,         1.0f, 0.0f},
	  {0.0f,        0.0f,         0.0f, 1.0f}
    };

	// 拡縮
	float Scale[4][4] = {
	  {2.0f, 0.0f, 0.0f, 0.0f}, // X軸方向の倍率
	  {0.0f, 2.0f, 0.0f, 0.0f}, // Y軸方向の倍率
	  {0.0f, 0.0f, 2.0f, 0.0f}, // Z軸方向の倍率
	  {0.0f, 0.0f, 0.0f, 1.0f}
    };

	int edgeList[12][2] = {
	  {0, 1},
      {1, 2},
      {2, 3},
      {3, 0},
      {0, 4},
      {1, 5},
	  {2, 6},
      {3, 7},
      {4, 5},
      {5, 6},
      {6, 7},
      {7, 4}
    };

	const Vector4 WHITE = {1.0f, 1.0f, 1.0f, 1.0f};
	const Vector4 RED = {1.0f, 0.25f, 0.25f, 1.0f};
	const Vector4 GREEN = {0.25f, 1.0f, 0.25f, 1.0f};
	const Vector4 BLACK = {0.0f, 0.0f, 0.0f, 1.0f};

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
