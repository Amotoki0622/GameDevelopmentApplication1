#include "Bomb.h"
#include "DxLib.h"

//�R���X�g���N�^
Bomb::Bomb() : animation_count(0), image(0), direction(0.0f)
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
	radian = 3.14 / 2;

	//�����蔻��̑傫���Ɛݒ�
	box_size = 70.0f;

	//�����i�s�����̐ݒ�
	direction = Vector2D(0.0f, 2.0f);
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

	if (hit_object->GetType() == ENEMY_HAKO)
	{
		//�폜����Flg��TRUE�ɂ���
		flg = TRUE;
	}
	else if (hit_object->GetType() == ENEMY_HANE)
	{
		//�폜����Flg��TRUE�ɂ���
		flg = TRUE;
	}

	else if (hit_object->GetType() == ENEMY_GOLD)
	{
		//�폜����Flg��TRUE�ɂ���
		flg = TRUE;
	}

	else if (hit_object->GetType() == HARPY)
	{
		//�폜����Flg��TRUE�ɂ���
		flg = TRUE;
	}

}

//�ړ�����
void Bomb::Movement()
{

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}
