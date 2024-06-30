#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER			//���W�̌��_���摜�̒��S�ɂ���

/*�o������I�u�W�F�N�g�̃|�C���g*/
#define HAKOENEMY_P		(200)
#define HANEENEMY_P		(30)
#define GOLDENEMY_P		(2000)
#define HARPY_P			(-100)

enum Objects
{
	PLAYER_BOMB,		//�v���C���[�e
	ENEMY_HAKO,			//�n�R�e�L
	ENEMY_HANE,			//�n�l�e�L
	ENEMY_GOLD,			//���̃e�L
	HARPY			//�n�[�s�[
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

	//�폜�t���O
	bool DeleteFlg();

};