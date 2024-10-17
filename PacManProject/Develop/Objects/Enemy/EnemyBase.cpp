#include "EnemyBase.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"

#define D_ENEMY_SPEED   (50.0f)
    
EnemyBase::EnemyBase() :
    move_animation(),
    eye_animation(),
    old_location(0.0f),
    velocity(0.0f),
    enemy_state(eEnemyState::STAY),
    now_direction_state(eDirectionState::LEFT),
    animation_time(0.0f),
    animation_count(0),
    old_panel(ePanelID::NONE),
    switching_time(0.0f),
    image(NULL)
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
    ResourceManager* rm = ResourceManager::GetInstance();
    move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 2, 32, 32);
    eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 2, 32, 32);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::Update(float delta_second)
{
    //image = move_animation[1];
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
    Vector2D graph_location = this->location + screen_offset;
    DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
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

        // �e�L�𔽎˂�������@  
        //velocity *= -1;
    }

    if (hit_object->GetCollision().object_type == eObjectType::player)
    {
        enemy_state = eEnemyState::EYE;
    }
}

/// <summary>
/// �e�L�̏�Ԃ��擾����
/// </summary>
/// <returns>�e�L�̏��</returns>
eEnemyState EnemyBase::GetEnemyState() const
{
    return enemy_state;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::Movement(float delta_second)
{
    // �ړ��ʂ���ړ��������X�V
    if (Vector2D::Distance(old_location, location) == 0.0f)
    {

    }
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