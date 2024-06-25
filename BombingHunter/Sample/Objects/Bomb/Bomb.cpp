#include "Bomb.h"
#include "DxLib.h"

//�R���X�g���N�^
Bomb::Bomb() : animation_count(0),image(0), direction(0.0f)	
{

}

//�f�X�g���N�^
Bomb::~Bomb()
{

}

//����������
void Bomb::Initialize()
{
	//���ꂪ�Ȃ�̃I�u�W�F�N�g�����ʂ���ϐ�(���̏ꍇ�v���C���[�̔��e)
	type = PLAYER_BOMB;

	//�摜�̓Ǎ���
	image = LoadGraph("Resource/Images/Bomb/Bomb.png");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("�΂�����̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 3.14/2;

	//�����蔻��̑傫���Ɛݒ�
	box_size = 70.0f;

	//�����i�s�����̐ݒ�
	direction = Vector2D(0.0f, 1.0f);
}

//�X�V����
void Bomb::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	//AnimationControl();
}

//�`�揈��
void Bomb::Draw() const
{
	////�摜���]�t���O
	//int flip_flag = FALSE;
	//
	////�i�s�����ɂ���āA���]��Ԃ����肷��
	//if (direction.x > 0.0f)
	//{
	//	flip_flag = FALSE;
	//}
	//else
	//{
	//	flip_flag = TRUE;
	//}
	//������Ƀo�N�_���摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE, FALSE);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Bomb::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(image);
}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//���������Ƃ��̏���
	//if(�������������̂��G��������)
	//{
	// AnimationControl(���������Ƃ�)
	//	�e���폜����(�摜�����łȂ��A�I�u�W�F�N�g���̂�)
	//}
	//direction = 0.0f;
 	if (hit_object->GetType() == ENEMY_HAKO)
	{
		direction = 0.0f;		//���̌�͏��������ɂ���(�摜�����łȂ��I�u�W�F�N�g���瑗��ꂽ�l���ׂ�)
	}

	if (hit_object->GetType() == ENEMY_HANE)
	{
		direction = 0.0f;		//���̌�͏��������ɂ���(�摜�����łȂ��I�u�W�F�N�g���瑗��ꂽ�l���ׂ�)
	}

	if (hit_object->GetType() == ENEMY_GOLD)
	{
		direction = 0.0f;		//���̌�͏��������ɂ���(�摜�����łȂ��I�u�W�F�N�g���瑗��ꂽ�l���ׂ�)
	}

	if (hit_object->GetType() == HARPY)
	{
		direction = 0.0f;		//���̌�͏��������ɂ���(�摜�����łȂ��I�u�W�F�N�g���瑗��ꂽ�l���ׂ�)
	}

}

//�ړ�����
void Bomb::Movement()
{
	//��ʒ[�ɓ��B������A�i�s�����𔽓]����
	//if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	//{
	//	direction.x *= -1.0f;
	//}
	//if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	//{
	//	direction.y *= -1.0f;
	//}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�A�j���[�V��������
//void Bomb::AnimationControl()
//{
//	//�A�j���[�V�����J�E���g�����Z����
//	animation_count++;
//
//	//30�t���[���ڂɓ��B������
//	if (animation_count >= 60)
//	{
//		//�J�E���g�̃��Z�b�g
//		animation_count = 0;
//
//		//�摜�̐؂�ւ�
//		if (image == animation[0])
//		{
//			image = animation[1];
//		}
//		else
//		{
//			image = animation[0];
//		}
//	}
//}