#pragma once

#include "../EnemyBase.h"

/// <summary>
/// �e�L�N���X(�Ԃׂ�)
/// </summary>
class RedEnemy : EnemyBase
{

public:
	RedEnemy();
	virtual ~RedEnemy();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;


	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	/// <summary>
	/// �e�L�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�e�L�̏��</returns>
	virtual eEnemyState GetEnemyState() const override;

private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Movement(float delta_second) override;
	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void AnimationControl(float delta_second) override;

private:
	/// <summary>
	/// �ړ����� : �ҋ@���
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Stay(float delta_second);
	/// <summary>
	/// �ړ����� : �꒣���
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Territory(float delta_second);
	/// <summary>
	/// �ړ����� : �ǐՏ��
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Chase(float delta_second);
	/// <summary>
	/// �ړ����� : ���������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Izike(float delta_second);
	/// <summary>
	/// �ړ����� : �ڋʏ��(���S)
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Eye(float delta_second);
};