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
//�t���[�����[�g
#define FRAME_RATE	(144)

//�R���X�g���N�^
Scene::Scene() : objects(), image(0), count(0), time(10), time_count(0), score(0), watch_image(0), finish_flg(FALSE)
{
	for (int i = 0; i < 12; i++)
	{
		number_image[i] = NULL;
	}
	for (int j = 0; j < 6; j++)
	{
		ui_finish[j] = NULL;
	}
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
	//�w�i�摜���i�[����ϐ�
	image = LoadGraph("Resource/Images/BackGround.png");

	//1�`9�܂ł̐����̉摜���i�[����z��
	number_image[0] = LoadGraph("Resource/Images/Score/0.png");
	number_image[1] = LoadGraph("Resource/Images/Score/1.png");
	number_image[2] = LoadGraph("Resource/Images/Score/2.png");
	number_image[3] = LoadGraph("Resource/Images/Score/3.png");
	number_image[4] = LoadGraph("Resource/Images/Score/4.png");
	number_image[5] = LoadGraph("Resource/Images/Score/5.png");
	number_image[6] = LoadGraph("Resource/Images/Score/6.png");
	number_image[7] = LoadGraph("Resource/Images/Score/7.png");
	number_image[8] = LoadGraph("Resource/Images/Score/8.png");
	number_image[9] = LoadGraph("Resource/Images/Score/9.png");
	//�t�H���g��UI	��ɕϐ���ύX
	number_image[10] = LoadGraph("Resource/Images/Score/font-21.png");
	number_image[11] = LoadGraph("Resource/Images/Score/hs.png");
	watch_image = LoadGraph("Resource/Images/TimeLimit/timer-03.png");

	//�I������UI
	ui_finish[0] = LoadGraph("Resource/Images/Evaluation/BAD.png");
	ui_finish[1] = LoadGraph("Resource/Images/Evaluation/Finish.png");
	ui_finish[2] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	ui_finish[3] = LoadGraph("Resource/Images/Evaluation/OK.png");
	ui_finish[4] = LoadGraph("Resource/Images/Evaluation/Perfect.png");

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

	//�����I���t���O��TRUE�������ꍇ�A�������I������
	if (finish_flg != TRUE)
	{
		if (count > 200)
		{
			count = 0;
		}
		else
		{
			//�e�L������������
			OutoSpawnEnemy();
			count++;
		}
	}


	Vector2D p = 0.0;		//	�v���C���[�̈ʒu�̍X�V�����l���i�[����ϐ�
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
		//delete?

		/*if (objects[i]->GetType() == ENEMY_HAKO && objects[i]->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + i);
		}
		 else if (objects[i]->GetType() == ENEMY_GOLD && objects[i]->DeleteFlg() == TRUE)
			{
				objects.erase(objects.begin() + i);
			}
		else if (objects[i]->GetType() == ENEMY_HANE && objects[i]->DeleteFlg() == TRUE)
			{
				objects.erase(objects.begin() + i);
			}
		else if (objects[i]->GetType() == PLAYER_BOMB && objects[i]->DeleteFlg() == TRUE)
			{
				objects.erase(objects.begin() + i);
			}
		else if (objects[i]->GetType() == HARPY && objects[i]->DeleteFlg() == TRUE)
			{
				objects.erase(objects.begin() + i);
			}*/
	}

	Timer();

	FinishFlg();

	//�_���̍��v
	TotalScore();

	//�v���C���[�̂��܂ɓ����������̍폜����
	Delete();

	//�I�u�W�F�N�g���͈͊O�ɍs�������̍폜����
	ScreenOutDelete();

	//�X�y�[�X�L�[����������A�o�N�_���𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D(p.x, 114.0f));
	}

	//�e�L�蓮��������(�f�o�b�N)
	SpawnEnemy();

}

//����e�L������������
void Scene::OutoSpawnEnemy()
{
	//CreateObject<Enemy>(Vector2D(100.0f, 390.0f));
	int a;
	a = rand() % 100 + 1;	//0�`100�܂ł̃����_���Ȑ������o��
	if (a <= 1)
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
			CreateObject<Harpy>(Vector2D(100.0f, 150.0f + (ran * 80.0f)));
			break;

		case 3:
			CreateObject<WingEnemy>(Vector2D(100.0f, 150.0f + (ran * 80.0f)));
			break;
		}
		/*switch (ran2)
		{
		case 0:
			CreateObject<Enemy>(Vector2D(100.0f, 390.0f));
			break;

		case 1:
			CreateObject<GoldEnemy>(Vector2D(100.0f, 390.0f));
			break;

		case 2:
			CreateObject<Harpy>(Vector2D(100.0f, 150.0f + (ran * 80.0f)));
			break;

		case 3:
			CreateObject<WingEnemy>(Vector2D(100.0f, 150.0f + (ran * 80.0f)));
			break;
		}*/
	}



}

//����I�u�W�F�N�g�蓮��������
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
			CreateObject<Harpy>(Vector2D(100.0f, 150.0f + (ran * 80.0f)));
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
		CreateObject<Enemy>(Vector2D(-70.0f, 390.0f));
	}

	//B�L�[����������A�G����������(�f�o�b�N�p)
	if (InputControl::GetKeyDown(KEY_INPUT_B))
	{
		CreateObject<GoldEnemy>(Vector2D(100.0f, 390.0f));
	}
}

//�e�Ɠ��������Ƃ��̍폜����
void Scene::Delete()
{
	for (int i = 0; i < objects.size(); i++)
	{

		if (objects[i]->GetType() == ENEMY_HAKO && objects[i]->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + i);
		}
		else if (objects[i]->GetType() == ENEMY_GOLD && objects[i]->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + i);
		}
		else if (objects[i]->GetType() == ENEMY_HANE && objects[i]->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + i);
		}
		else if (objects[i]->GetType() == PLAYER_BOMB && objects[i]->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + i);
		}
		else if (objects[i]->GetType() == HARPY && objects[i]->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + i);
		}
	}
}

//�X�R�A�̍��v����
void Scene::TotalScore()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetType() == ENEMY_HAKO && objects[i]->DeleteFlg() == TRUE)
		{
			score += HAKOENEMY_P;
		}
		else if (objects[i]->GetType() == ENEMY_HANE && objects[i]->DeleteFlg() == TRUE)
		{
			score += HANEENEMY_P;
		}
		else if (objects[i]->GetType() == ENEMY_GOLD && objects[i]->DeleteFlg() == TRUE)
		{
			score += GOLDENEMY_P;
		}
		else if (objects[i]->GetType() == HARPY && objects[i]->DeleteFlg() == TRUE)
		{
			score += HARPY_P;
		}

	}
	//�X�R�A�̍��v������-�ɂȂ����Ƃ��A�l��0�ɂ���
	if (score < 0)
	{
		score = 0;
	}
}

//��ʊO�ɂ������I�u�W�F�N�g�̍폜����
void Scene::ScreenOutDelete()
{
	for (int i = 0; i < objects.size(); i++)
	{
		//�n�R�e�L����ʊO�ɍs������A�폜����
		if (objects[i]->GetLocation().x > 700.0f && objects[i]->GetType() == ENEMY_HAKO && objects[i]->DeleteFlg() == FALSE)
		{
			objects.erase(objects.begin() + i);
		}
		else if (objects[i]->GetLocation().x > 700.0f && objects[i]->GetType() == ENEMY_HANE && objects[i]->DeleteFlg() == FALSE)
		{
			objects.erase(objects.begin() + i);
		}
	}
}

//�`�揈��
void Scene::Draw() const
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//��������(����)�̏���
void Scene::Timer()
{
	time_count++;
	if (time != 0)
	{
		if (time_count >= FRAME_RATE)
		{
			time--;
			time_count = 0;
		}
	}
	/*�f�o�b�N(�����ƒl�������Ă��邩�m�F�p)*/
	/*if (time < 0)
	{
		time = 0;
	}*/
}


//�Q�[���I�������t���O
void Scene::FinishFlg()
{
	if (time == 0)
	{
		finish_flg = TRUE;
	}
}


//��ʂ�UI�`�揈��
void Scene::UiDraw()
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0.0f, 0.0f, 640.0f, 480.0f, image, TRUE);


	DrawRotaGraphF(190, 460, 1.0, 0, number_image[10], TRUE, 0);
	if (score < 10)
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[0], TRUE, 0);
	}
	else if (score < 100)
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[(score / 10) % 10], TRUE, 0);
		DrawRotaGraphF(245, 460, 1.0, 0, number_image[0], TRUE, 0);
	}
	else if (score < 999)
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[(score / 100) % 10], TRUE, 0);
		DrawRotaGraphF(245, 460, 1.0, 0, number_image[(score / 10) % 10], TRUE, 0);
		DrawRotaGraphF(260, 460, 1.0, 0, number_image[0], TRUE, 0);
	}
	else if (score < 9999)
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[(score / 1000) % 10], TRUE, 0);
		DrawRotaGraphF(245, 460, 1.0, 0, number_image[(score / 100) % 10], TRUE, 0);
		DrawRotaGraphF(260, 460, 1.0, 0, number_image[(score / 10) % 10], TRUE, 0);
		DrawRotaGraphF(275, 460, 1.0, 0, number_image[0], TRUE, 0);
	}
	else if (score <= 99999)
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[(score / 10000) % 10], TRUE, 0);
		DrawRotaGraphF(245, 460, 1.0, 0, number_image[(score / 1000) % 10], TRUE, 0);
		DrawRotaGraphF(260, 460, 1.0, 0, number_image[(score / 100) % 10], TRUE, 0);
		DrawRotaGraphF(275, 460, 1.0, 0, number_image[(score / 10) % 10], TRUE, 0);
		DrawRotaGraphF(290, 460, 1.0, 0, number_image[0], TRUE, 0);
	}
	else
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[9], TRUE, 0);
		DrawRotaGraphF(245, 460, 1.0, 0, number_image[9], TRUE, 0);
		DrawRotaGraphF(260, 460, 1.0, 0, number_image[9], TRUE, 0);
		DrawRotaGraphF(275, 460, 1.0, 0, number_image[9], TRUE, 0);
		DrawRotaGraphF(290, 460, 1.0, 0, number_image[9], TRUE, 0);
	}

	//UI�̎��v�̕`��
	//���v�̃C���X�g�̕`��
	DrawRotaGraphF(20, 460, 0.6, 0, watch_image, TRUE, 0);
	/*�����^�C�}�[��2���̏ꍇ*/
	if (time >= 10)
	{
		DrawRotaGraphF(45, 460, 1.0, 0, number_image[time / 10], TRUE, 0);
		DrawRotaGraphF(60, 460, 1.0, 0, number_image[time % 10], TRUE, 0);
	}
	//�^�C�}�[��1���̏ꍇ
	else if (time < 10)
	{
		DrawRotaGraphF(45, 460, 1.0, 0, number_image[time % 10], TRUE, 0);
	}
	//�^�C�}�[��0�b�̏ꍇ
	else if (time == 0)
	{
		DrawRotaGraphF(45, 460, 1.0, 0, number_image[0], TRUE, 0);
	}

	//0�b�ɂȂ�����A�Q�[���I����UI�Ɉړ�����
	if (time < 0)
	{
		//UiFinishDraw();		//Finish��UI��`�悷�鏈��
		UiFinish();
	}


	//���� ���Ԃ̕`��
		//DrawFormatString(30, 460, GetColor(255, 255, 255), "%d", time);

	//�������Ԃ̕`��
//	DrawFormatString(30, 460, GetColor(255, 255, 255), "%d", time);
//	DrawFormatString(150, 460, GetColor(255, 255, 255), "�X�R�A%d", score);

	//���� ���Ԃ̕`��(UI�Ȃ�)
//	DrawRotaGraphF(190, 460, 1.0, 0, number_image[10], TRUE, 0);

	//DrawRotaGraphF(100, 460, 1.0, 0, number_image[10], TRUE, 0);
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


//�Q�[���I����UI
void Scene::UiFinish()
{
	DrawRotaGraphF(320, 240, 1.0, 0, ui_finish[1], TRUE, 0);

	int a, b;
	a = 1;
	b = 0;
	b++;

	if (a != 0)
	{
		if (b >= FRAME_RATE)
		{
			a--;
			b = 0;
		}

	}


	//if (score < 1000)
	//{
	//	//BAD
	//	DrawRotaGraphF(320, 240, 1.0, 0, ui_finish[0], TRUE, 0);
	//}
	//else if (score < 4999)
	//{
	//	//OK
	//	DrawRotaGraphF(320, 240, 0.5, 0, ui_finish[3], TRUE, 0);
	//}
	//else if (score < 9999)
	//{
	//	//GOOD
	//	DrawRotaGraphF(320, 240, 0.7, 0, ui_finish[2], TRUE, 0);
	//}
	//else if (score < 49999)
	//{
	//	//Perfect
	//	DrawRotaGraphF(320, 240, 1.0, 0, ui_finish[4], TRUE, 0);
	//}


}

void Scene::UiFinishDraw()
{
	DrawRotaGraphF(320, 240, 1.0, 0, ui_finish[1], TRUE, 0);
	int a, b;
	a = 1;
	b = 0;
	b++;

	if (a != 0)
	{
		if (b >= FRAME_RATE)
		{
			a--;
			b = 0;
		}

	}
	//DeleteGraph(ui_finish[1]);

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
		//delete?
		/*if (a->GetType() == ENEMY_HAKO && a->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + 1);
		}*/
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
