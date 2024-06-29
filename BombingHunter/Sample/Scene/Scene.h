#pragma once

#include "../Objects/GameObject.h"
#include <vector>

class Scene
{
private:
	std::vector<GameObject*> objects;		//�I�u�W�F�N�g���X�g

private:
	int image;					//�w�i�摜
	int count;					//���������J�E���g
	int time_count;				//�J�E���g
	int time;					//����
	int number_image[12];		//�����̉摜
	int score;					//�X�R�A	
	int score_im;				//�X�R�A�̉摜

public:
	Scene();
	~Scene();

	void Initialize();				//����������
	void Update();					//�ړ�����
	void SpawnEnemy();				//�G�̎蓮����
	void OutoSpawnEnemy();			//�G�̎�������
	void Draw() const;				//�`�揈��
	void Finalize();				//�I��������
	void Delete();					//�폜����
	void ScreenOutDelete();			//��ʊO�̍폜����
	void Timer();
	void TotalScore();				//���v�_��


private:
	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b); 

	//�I�u�W�F�N�g��������
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObject�N���X���p�����Ă邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("GameObject�������ł��܂���ł����B\n");
		}

		//����������
		new_object->Initialize();
		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};