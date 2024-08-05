#include "EnemyBase.h"
    
EnemyBase::EnemyBase() :
    move_animation(),
    eye_animation(),
    velocity(0.0f),
    enemy_state(eEnemyState::STAY),
    now_direction_state(eDirectionState::LEFT),
    animation_time(0.0f),
    animation_count(0),
    switching_time(0.0f)
{
}

EnemyBase::~EnemyBase()
{
}

/// <summary>
/// ����������
/// </summary>
void EnemyBase::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::Update(float delta_second)
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void EnemyBase::Draw(const Vector2D& screen_offset) const
{

}

/// <summary>
/// �I������
/// </summary>
void EnemyBase::Finalize()
{

}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
    // ���������Ƃ��̏���
}

/// <summary>
/// �e�L�̏�Ԃ��擾����
/// </summary>
/// <returns>�e�L�̏��</returns>
eEnemyState EnemyBase::GetEnemyState() const
{

}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::Movement(float delta_second)
{

}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::AnimationControl(float delta_second)
{

}

/// <summary>
/// �ړ����� : �ҋ@���
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::Stay(float delta_second)
{

}

/// <summary>
/// �ړ����� : �꒣���
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::Territory(float delta_second)
{

}

/// <summary>
/// �ړ����� : �ǐՏ��
/// </summary>
/// <param name="delta_second"></param>
void EnemyBase::Chase(float delta_second)
{

}

/// <summary>
/// �ړ����� : ���������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::Izike(float delta_second)
{

}

/// <summary>
/// �ړ����� : �ڋʏ��(���S)
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::Eye(float delta_second)
{

}