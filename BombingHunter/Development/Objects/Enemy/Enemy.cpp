#include "Enemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�R���X�g���N�^
Enemy::Enemy() : animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�G�̉摜������܂���m�F���Ă�������\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	scale = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];
}

//�X�V����
void Enemy::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Enemy::Draw() const
{
	//�G�摜�̕`��
	DrawRotaGraph(location.x, location.y, 1.0, radian, image, TRUE);
}

//�I��������
void Enemy::Finalize()
{
	//�g�p���Ă����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�ړ�����
void Enemy::Movement()
{
	Vector2D velocity = 0.0f;

	velocity.x += -1.0f;

	location += velocity;
}

//�A�j���[�V��������
void Enemy::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}