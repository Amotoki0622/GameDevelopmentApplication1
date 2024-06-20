#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/WingEnemy.h"
#include "../Objects/Enemy/GoldEnemy.h"
#include "../Objects/Enemy/Harpy.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include "../Utility/Vector2D.h"
#include "DxLib.h"

#define D_PIVOT_CENTER

//�R���X�g���N�^
Scene::Scene() : objects(), image(0.0f)
{

}

//�f�X�g���N�^
Scene::~Scene()
{
	//����Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	image = LoadGraph("Resource/Images/BackGround.png");

	if (image == -1)
	{
		throw("�w�i�摜������܂���B\n");
	}


	//�v���C���[����ʒ���������ɐ�������(�����ʒu���̐ݒ�)
	CreateObject<Player>(Vector2D(320.0f, 45.0f));
}

//�X�V����
void Scene::Update()
{

	SpawnEnemy();

	Vector2D p = 0.0;
	p = objects[0]->GetLocation().x;
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}


	//�X�y�[�X�L�[����������A�o�N�_���𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D(p.x, 114.0f));
	}



	//Z�L�[����������A�G�𐶐�����(�����ʒu���̐ݒ�)
	//if (InputControl::GetKeyDown(KEY_INPUT_Z))
	//{
	//	//�������擾(Y���W��150�`390�Ɏ��߂�悤��)
	//	//int a = GetRand(3);
	//	//CreateObject<Enemy>(Vector2D(100.0f, 150.0f + (a * 80)));
	//}
	
}

void Scene::SpawnEnemy()
{
	//Z�L�[����������A�G�𐶐�����(�����ʒu���̐ݒ�)
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		//�������擾(Y���W��150�`390�Ɏ��߂�悤��)
		int ran = GetRand(2);
		int ran2 = GetRand(3);

		switch (ran2)
		{
		case 0:
			CreateObject<Enemy>(Vector2D(100.0f, 390.0f));
			break;

		case 1:
			CreateObject<GoldEnemy>(Vector2D(100.0f, 390.0f));
			break;

		case 2:
			CreateObject<Harpy>(Vector2D(100.0f, 150.0f + (ran* 80.0f)));
			break;

		case 3:
			CreateObject<WingEnemy>(Vector2D(100.0f, 150.0f + (ran * 80.0f)));
			break;
		}

		//switch (ran2)
		//{
		//case 0:
		//	CreateObject<Enemy>(Vector2D(100.0f, 150.0f + (ran * 80)));
		//	break;
		//
		//case 1:
		//	CreateObject<GoldEnemy>(Vector2D(100.0f, 150.0f + (ran * 80)));
		//	break;
		//
		//case 2:
		//	CreateObject<Harpy>(Vector2D(100.0f, 150.0f + (ran * 80)));
		//	break;
		//
		//case 3:
		//	CreateObject<WingEnemy>(Vector2D(100.0f, 150.0f + (ran * 80)));
		//	break;
		//}
		//CreateObject<Enemy>(Vector2D(100.0f, 150.0f + (ran * 80)));
	} 

	//C�L�[����������A�G�𐶐�����(�f�o�b�N�p)
	if (InputControl::GetKeyDown(KEY_INPUT_C))
	{
		CreateObject<Enemy>(Vector2D(100.0f, 390.0f));
	}

	//B�L�[����������A�G����������(�f�o�b�N�p)
	if (InputControl::GetKeyDown(KEY_INPUT_B))
	{
		CreateObject<GoldEnemy>(Vector2D(100.0f, 390.0f));
	}
}


//�`�揈��
void Scene::Draw() const
{

	DrawExtendGraph(0.0f, 0.0f, 640.0f, 480.0f, image, TRUE);


	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Scene::Finalize()
{
	//�I�u�W�F�N�g���X�g������Ȃ�A�������I������
	if (objects.empty())
	{
		return;
	}

	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���������
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�Ɋm�ۂ������X�g���������
	objects.clear();
}

#ifdef D_PIVOT_CENTER
//�����蔻��`�F�b�N����(��`�̒��S�œ����蔻������)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else

//�����蔻��`�F�b�N����(����̍��W���瓖���蔻��v�Z���s��)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�㒸�_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif // D_PIVOT_CENTER
