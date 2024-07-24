#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

// �G���aaa
enum eEnemyState
{
	STAY,			// �ҋ@���
	TERRITORY,		// �꒣���
	CHASE,			// �ǐՏ��
	IZIKE,			// ���������
	DIE,			// ���S���
};

/// <summary>
/// �e�L�N���X
/// </summary>

class Aka : public GameObject
{
private:
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};

private:
	std::vector<int> move_animation;
	std::vector<int> dying_animation;
	Vector2D velocity;
	eEnemyState enemy_state;
	eDirectionState now_direction_state;
	float animation_time;
	int animation_count;

	// �ړ��A�j���[�V�����̏���
	const int animation_num[4] = { 0, 1, 2, 1 };

public:
	Aka();
	virtual ~Aka();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name = "hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	
public:
	/// <summary>
	/// �e�L�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�e�L�̏��</returns>
	eEnemyState GetEnemyState() const;

private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name = "delta_second">1�t���[��������̎���
	void Movement(float delta_second);

	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name = "delta_second">1�t���[��������̎���
	void AnimationControl(float delta_second);
};