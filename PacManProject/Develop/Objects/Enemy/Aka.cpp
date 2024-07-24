#include "Aka.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include  "DxLib.h"


Aka::Aka() :
	move_animation(),
	dying_animation(),
	velocity(0.0f),
	enemy_state(eEnemyState::STAY),
	now_direction_state(eDirectionState::LEFT),
	animation_time(0.0f),
	animation_count(0)
{

}

Aka::~Aka()
{

}

void Aka::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/pacman.png", 12, 12, 1, 32, 32);
	//dying_animation = rm->GetImages("Resource/Images/dying.png", 11, 11, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::player;
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::food);
	collision.hit_object_type.push_back(eObjectType::power_food);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

}

void Aka::Update(float delta_second)
{
	// �ړ�����
	Movement(delta_second);
	AnimationControl(delta_second);
}

void Aka::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void Aka::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	dying_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name = "hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Aka::OnHitCollision(GameObjectBase* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Player����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;
	}

	// ���������I�u�W�F�N�g���G��������
	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		enemy_state = eEnemyState::DIE;
	}
}

/// <summary>
/// �e�L�̏�Ԃ��擾����
/// </summary>
/// <returns>�e�L�̏��</returns>
eEnemyState Aka::GetEnemyState() const
{
	return enemy_state;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name = "delta_second">1�t���[��������̎���</param>
void Aka::Movement(float delta_second)
{

}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name = "delta_second">1�t���[��������̎���</param>
void Aka::AnimationControl(float delta_second)
{
	//�ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// �摜�̐ݒ�
		int dir_num = (int)now_direction_state;
		if (0 <= dir_num && dir_num < 4)
		{
			image = move_animation[(dir_num * 3) + animation_num[animation_count]];
		}
	}
}