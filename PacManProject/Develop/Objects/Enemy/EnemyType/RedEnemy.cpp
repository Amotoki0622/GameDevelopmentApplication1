#include "RedEnemy.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/ResourceManager.h"
#include "DxLib.h"


RedEnemy::RedEnemy()
{

}

RedEnemy::~RedEnemy()
{
	
}

void RedEnemy::Initialize()
{
	// �A�j���[�V�����摜�̓Ǎ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 2, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 2, 32, 32);

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

void RedEnemy::Update(float delta_second)
{
	// �e�L�̏�Ԃɂ���āA�����ς���
	switch (enemy_state)
	{
	case eEnemyState::STAY:
		break;

	case eEnemyState::TERRITORY:
		break;

	case eEnemyState::CHASE:
		break;

	case eEnemyState::IZIKE:
		break;

	case eEnemyState::EYE:
		break;

	default:
		break;
	}
}

void RedEnemy::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset	);
}

void RedEnemy::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	eye_animation.clear();
}

/// <summary>
/// �����蔻��ʒm
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void RedEnemy::OnHitCollision(GameObjectBase* hit_object)
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

eEnemyState RedEnemy::GetEnemyState() const
{
	return enemy_state;
}

void RedEnemy::Movement(float delta_second)
{
	// �ړ��ʂ���ړ��������X�V
	
}