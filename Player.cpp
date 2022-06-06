#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {

	// NULL�|�C���^�`�F�b�N
	assert(model);

	this->model_ = model;
	this->textureHandle_ = textureHandle;

	// �V���O���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();
}

void Player::Update() {

	// �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = {0, 0, 0};

	// �L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.2f;

	// �����������ňړ��x�N�g����ύX
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

	// �ړ��l�����Z
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	// �s��̍X�V
	Matrix4 matTrans = MathUtility::Matrix4Identity();

	// �ړ��ʂ��s��ɐݒ肷��
	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;

	worldTransform_.matWorld_ = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

	worldTransform_.matWorld_ *= matTrans;

	worldTransform_.TransferMatrix();

	// �L�����N�^�[�̍��W��\�����鏈��
	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "Position:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}

void Player::Draw(ViewProjection viewProjection_) {
	// 3D���f���̕`��
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}
