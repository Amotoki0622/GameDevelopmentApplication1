#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER			//���W�̌��_���摜�̒��S�ɂ���

//#define ENEMY_ALL	(6)			//�G�̑���(�G�̒e���܂߂�)	


/*���� (Development�ɏ����Ƃ��͂����Ƃ킩��₷��)*/
//#define PLAYER_BOMB		(0)			//�G�̒e
//#define ENEMY_HAKO		(1)		//�G(�n�R�e�L�̃I�u�W�F�N�g)
//#define ENEMY_HANE		(2)		//�G(�ꉞ�n�l�e�L�̃I�u�W�F�N�g)
//#define ENEMY_GOLD		(3)		//�G(�ꉞ���̃e�L�̃I�u�W�F�N�g)
//#define HARPY		(4)		//�G(�ꉞ�n�R�e�L�̃I�u�W�F�N�g)

/*���� (�o������I�u�W�F�N�g�̃|�C���g)*/
#define HAKOENEMY_P		(200)
#define HANEENEMY_P		(30)
#define GOLDENEMY_P		(2000)
#define HARPY_P			(-100)

enum Object
{
	PLAYER_BOMB,
	ENEMY_HAKO,
	ENEMY_HANE,
	ENEMY_GOLD,
	HARPY
};

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
	bool flg;							//�t���b�O
	int score;							//�X�R�A

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

	bool DeleteFlg();

	//�X�R�A�̒l�𔻕ʂ��鏈��
	//int GetScere();
};