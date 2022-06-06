#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"
#include "ViewProjection.h"
#include "math.h"
#include <cassert>

class Player {

  public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name = "model" > ���f�� </param>
	/// <param name = "textureHamdle" > �e�N�X�`���n���h�� </param>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <patam name = "viewProjection"> �r���[�v���W�F�N�V���� (�Q�Ɠn��) </patam>
	void Draw(ViewProjection viewProjection_);

  private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint16_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};
