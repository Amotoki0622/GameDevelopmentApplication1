#include "RedEnemy.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/ResourceManager.h"
#include "DxLib.h"

#define D_PLAYER_SPEED	(50.0f)


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
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 2, 32, 32);


	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	//�ŏ��̃e�L�̏��
	enemy_state = eEnemyState::TERRITORY;
	//enemy_state = eEnemyState::STAY;

	/* (���˂���悤�ɓ���) */
	 velocity = Vector2D(5.0f, 0.0f);

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
		// �摜�̐ݒ�
		image = move_animation[3];
		// �ړ�����(�꒣��Ԃ̎�)
		Stay(delta_second);
		// �A�j���[�V��������
		//AnimationControl(delta_second);
		break;

	case eEnemyState::TERRITORY:
		image = move_animation[0];
		Territory(delta_second);
		AnimationControl(delta_second);
		break;

	case eEnemyState::CHASE:
		// �A�j���[�V��������
		//AnimationControl(delta_second);
		break;

	case eEnemyState::IZIKE:
		image = move_animation[18];
		// �A�j���[�V��������
		//AnimationControl(delta_second);

		break;

	case eEnemyState::EYE:
		image = move_animation[18];
		break;

	default:
		break;
	}
}

void RedEnemy::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
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
	__super::OnHitCollision(hit_object);

	int move = GetRand(4);

	switch (move)
	{
	case 1:
		velocity.x = 0.0f;
		velocity.y = -(5.0f);
		break;
	case 2:
		velocity.x = 0.0f;
		velocity.y = 5.0f;
		break;
	case 3:
		velocity.x = -(5.0f);
		velocity.y = 0.0f;

		break;
	case 4:
		velocity.x = 5.0f;
		velocity.y = 0.0f;
		break;
	default:
		break;
	}



/*// ���������A�I�u�W�F�N�g���ǂ�������		
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
	}*/

/*/	// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�	�k��
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
	location += dv.Normalize() * diff;*/
}

/// <summary>
/// �e�L�̏�Ԃ��擾����
/// </summary>
/// <returns>�e�L�̏��</returns>
eEnemyState RedEnemy::GetEnemyState() const
{
	return enemy_state;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void RedEnemy::Movement(float delta_second)
{
	// �O����W�̍X�V
	 old_location = location;


	// �ړ��� * ���� * ���� �ňړ�������肷��
	location += velocity * D_PLAYER_SPEED * delta_second;

	// ��ʊO�ɍs������A���Α��Ƀ��[�v������
	if (location.x < 0.0f)
	{
		old_location.x = 672.0f;
		location.x = 672.0f - collision.radius;
		velocity.y = 0.0f;
	}
	if (672.0f < location.x)
	{
		old_location.x = 0.0f;
		location.x = collision.radius;
		velocity.y = 0.0f;
	}

}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void RedEnemy::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
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

/// <summary>
/// �ړ����� : �ҋ@���
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void RedEnemy::Stay(float delta_second)
{
	Movement(delta_second);

}

/// <summary>
/// �ړ����� : �꒣���
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void RedEnemy::Territory(float delta_second)
{

	Movement(delta_second);

}

/// <summary>
/// �ړ����� : �ǐՏ��
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void RedEnemy::Chase(float delta_second)
{

}

/// <summary>
/// �ړ����� : ���������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void RedEnemy::Izike(float delta_second)
{

}

/// <summary>
/// �ړ����� : �ڋʏ��(���S)
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void RedEnemy::Eye(float delta_second)
{

}