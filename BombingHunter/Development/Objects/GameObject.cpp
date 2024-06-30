#include "GameObject.h"
#include "DxLib.h"

//�R���X�g���N�^
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0f),
	radian(0.0),
	image(NULL),
	sound(NULL),
	type(0),
	flg(FALSE),
	score(0)
{
}

//�f�X�g���N�^
GameObject::~GameObject()
{

}

//����������
void GameObject::Initialize()
{

}

//�X�V����
void GameObject::Update()
{

}

//�`�揈��
void GameObject::Draw() const
{
	/*�����蔻��̉���*/
//#ifdef D_PIVOT_CENTER
//	Vector2D t1 = location - (box_size / 2.0f);
//	Vector2D br = location + (box_size / 2.0f);
//
//	DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
//#else
//	Vector2D t1 = location;
//	Vector2D br = location + box_size;
//
//	DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
//#endif D_PIVOT_CENTER
}

//�I��������
void GameObject::Finalize()
{

}


//�����蔻��ʒm����
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//���������Ƃ��ɍs������
}

//�ʒu���擾����
Vector2D GameObject::GetLocation() const
{
	return location;
}

//�ʒu���ݒ�ύX
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�����蔻��̑傫�����擾����
Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}

//�I�u�W�F�N�g�̃^�C�v�𔻕ʂ��鏈��
int GameObject::GetType()
{
	return this->type;
}

//�폜�t���O
bool GameObject::DeleteFlg()
{
	return this->flg;
}
