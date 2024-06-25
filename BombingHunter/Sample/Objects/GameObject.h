#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER			//���W�̌��_���摜�̒��S�ɂ���

//#define ENEMY_ALL	(6)			//�G�̑���(�G�̒e���܂߂�)


/*���� (Development�ɏ����Ƃ��͂����Ƃ킩��₷��)*/
#define PLAYER_BOMB		(0)			//�G�̒e
#define ENEMY_HAKO		(1)		//�G(�n�R�e�L�̃I�u�W�F�N�g)
#define ENEMY_HANE		(2)		//�G(�ꉞ�n�l�e�L�̃I�u�W�F�N�g)
#define ENEMY_GOLD		(3)		//�G(�ꉞ���̃e�L�̃I�u�W�F�N�g)
#define HARPY		(4)		//�G(�ꉞ�n�R�e�L�̃I�u�W�F�N�g)

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;						//�ʒu���
	Vector2D box_size;							//��`�̑傫��
	double radian;							//����
	int image;								//�摜
	int sound;								//����
	int type;							//���(����)

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();				//����������
	virtual void Update();					//�X�V����
	virtual void Draw() const;				//�`�揈��
	virtual void Finalize();				//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�����蔻��̑傫�����擾����
	Vector2D GetBoxSize() const;

	//�I�u�W�F�N�g�̃^�C�v�𔻕ʂ��鏈��
	int GetType();
};