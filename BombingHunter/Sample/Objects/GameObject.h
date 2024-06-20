#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER			//���W�̌��_���摜�̒��S�ɂ���

#define ENEMY_ALL	(6)			//�G�̑���(�G�̒e���܂߂�)

/*�I�u�W�F�N�g�̎�ނ̔��ʂ�����@*/
#define P_BULLET		(0)			//�v���C���[�̒e
#define E_BULLET		(1)			//�G�̒e(�n�R�e�L����o�Ă���e)
#define ENEMY			(2)			//�G(�n�R�e�L)
#define ENEMY2			(3)			//�G(���̃e�L)
#define ENEMY3			(4)			//�G(�n�l�e�L)
#define ENEMY4			(5)			//�n�[�s�[
/*�I�u�W�F�N�g�̎�ނ̔��ʂ�����@*/

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;						//�ʒu���
	Vector2D box_size;							//��`�̑傫��
	double radian;							//����
	int image;								//�摜
	int sound;								//����
	int p[ENEMY_ALL];

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();				//����������
	virtual void Update();					//�X�V����
	virtual void Draw() const;				//�`�揈��
	virtual void Finalize();				//�I��������

	//�I�u�W�F�N�g�̎�ނ𔻕ʂ��鏈��
	virtual void GetType(GameObject* hit_object);

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�����蔻��̑傫�����擾����
	Vector2D GetBoxSize() const;

};