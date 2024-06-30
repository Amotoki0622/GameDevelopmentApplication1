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
Scene::Scene() : objects(), image(0), count(0), time(60), time_count(0), score(0), watch_image(0), finish_flg(FALSE)
{
	for (int i = 0; i < 12; i++)
	{
		number_image[i] = NULL;
	}
	for (int j = 0; j < 5; j++)
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
		//�G�����J�E���g
		if (count > 200)
		{
			count = 0;
		}
		else
		{
			//�e�L������������
			OutoSpawnEnemy();
			//�J�E���g�𑝉�����
			count++;
		}
	}


	Vector2D p = 0.0;		//	�v���C���[�̈ʒu�̍X�V�����l���i�[����ϐ�
	
	//�v���C���[�̈ʒu���W���Ăяo��
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

	//��������(����)�̏���
	Timer();

	//�Q�[���I�����t���O
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

	//�폜�t���O��TRUE��������A
	if (finish_flg != TRUE)
	{
		//�e�L�蓮��������(�f�o�b�N)
		SpawnEnemy();
	}
	
}

//����e�L������������
void Scene::OutoSpawnEnemy()
{
	//�������擾����ϐ�
	int rd;
	rd = rand() % 100 + 1;	//100�܂ł̃����_���Ȑ������o��
	//������1�ȉ��̎�
	if (rd <= 1)
	{
		//�������擾(Y���W��150�`390�Ɏ��߂�悤��)
		int ran = GetRand(2);
		//�����_���œG�̎�ނ��o��悤��(0�`3�̗������擾)
		int ran2 = GetRand(3);

		switch (ran2)
		{
		case 0:
			CreateObject<Enemy>(Vector2D(-70.0f, 390.0f));
			break;

		case 1:
			CreateObject<GoldEnemy>(Vector2D(-70.0f, 390.0f));
			break;

		case 2:
			CreateObject<Harpy>(Vector2D(-70.0f, 150.0f + (ran * 80.0f)));
			break;

		case 3:
			CreateObject<WingEnemy>(Vector2D(-70.0f, 150.0f + (ran * 80.0f)));
			break;
		}
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
		//�����_���œG�̎�ނ��o��悤��(0�`3�̗������擾)
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
		//���������G�̎�ނ��n�R�e�L���폜�t���O��TRUE�̎�
		if (objects[i]->GetType() == ENEMY_HAKO && objects[i]->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + i);
		}
		//���������G�̎�ނ����̃e�L���폜�t���O��TRUE�̎�
		else if (objects[i]->GetType() == ENEMY_GOLD && objects[i]->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + i);
		}
		//���������G�̎�ނ��n�l�e�L���폜�t���O��TRUE�̎�
		else if (objects[i]->GetType() == ENEMY_HANE && objects[i]->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + i);
		}
		//���������G�̎�ނ��n�[�s�[���폜�t���O��TRUE�̎�
		else if (objects[i]->GetType() == HARPY && objects[i]->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + i);
		}	
		//���������G�̎�ނ��v���C���[�e���폜�t���O��TRUE�̎�
		else if (objects[i]->GetType() == PLAYER_BOMB && objects[i]->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + i);
		}
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
		//�n�l�e�L����ʊO�ɍs������A�폜����
		else if (objects[i]->GetLocation().x > 700.0f && objects[i]->GetType() == ENEMY_HANE && objects[i]->DeleteFlg() == FALSE)
		{
			objects.erase(objects.begin() + i);
		}
		//���̃e�L����ʊO�ɍs������A�폜����
		else if (objects[i]->GetLocation().x > 700.0f && objects[i]->GetType() == ENEMY_GOLD && objects[i]->DeleteFlg() == FALSE)
		{
			objects.erase(objects.begin() + i);
		}
		//�n�[�s�[����ʊO�ɍs������A�폜����
		else if (objects[i]->GetLocation().x > 700.0f && objects[i]->GetType() == HARPY && objects[i]->DeleteFlg() == FALSE)
		{
			objects.erase(objects.begin() + i);
		}
		//�v���C���[�̒e����ʊO�ɍs������A�폜����
		else if (objects[i]->GetLocation().y > 440.0f && objects[i]->GetType() == PLAYER_BOMB && objects[i]->DeleteFlg() == FALSE)
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
		//���������G�̎�ނ��n�R�e�L����
		if (objects[i]->GetType() == ENEMY_HAKO && objects[i]->DeleteFlg() == TRUE)
		{
			score += HAKOENEMY_P;
		}
		//���������G�̎�ނ��n�l�e�L���폜�t���O��TRUE�̎�
		else if (objects[i]->GetType() == ENEMY_HANE && objects[i]->DeleteFlg() == TRUE)
		{
			score += HANEENEMY_P;
		}
		//���������G�̎�ނ����̃e�L���폜�t���O��TRUE�̎��폜�t���O��TRUE�̎�
		else if (objects[i]->GetType() == ENEMY_GOLD && objects[i]->DeleteFlg() == TRUE)
		{
			score += GOLDENEMY_P;
		}
		//���������G�̎�ނ��n�[�s�[���폜�t���O��TRUE�̎�
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


//�`�揈��
void Scene::Draw() const
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//��������(����)����
void Scene::Timer()
{
	//Time�J�E���g�𑝉�������
	time_count++;
	if (time != 0)
	{
		//time�̃J�E���g���t���[�����[�g���ɂȂ�����A
		if (time_count >= FRAME_RATE)
		{
			//�b����1����������
			time--;
			//�J�E���g��0�ɂ���
			time_count = 0;
		}
	}
}

//�Q�[���I�������t���O
void Scene::FinishFlg()
{
	if (time == 0)
	{
		//�^�C�}�[��0�ɂȂ�����ATRUE�ɂ���
		finish_flg = TRUE;
	}
}


//��ʂ�UI�`�揈��
void Scene::UiDraw()
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0.0f, 0.0f, 640.0f, 480.0f, image, TRUE);

	//UI�u�X�R�A�̕`��v
	DrawRotaGraphF(190, 460, 1.0, 0, number_image[10], TRUE, 0);

	//UI�u���v�v�̕`��
	DrawRotaGraphF(20, 460, 0.6, 0, watch_image, TRUE, 0);

	//UI���v�X�R�A�̕`��
	//���v�X�R�A��10��菬������
	if (score < 10)
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[0], TRUE, 0);
	}
	//���v�X�R�A��100��菬�����̎�
	else if (score < 100)
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[(score / 10) % 10], TRUE, 0);
		DrawRotaGraphF(245, 460, 1.0, 0, number_image[0], TRUE, 0);
	}
	//���v�X�R�A��1000��菬�����̎�
	else if (score < 999)
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[(score / 100) % 10], TRUE, 0);
		DrawRotaGraphF(245, 460, 1.0, 0, number_image[(score / 10) % 10], TRUE, 0);
		DrawRotaGraphF(260, 460, 1.0, 0, number_image[0], TRUE, 0);
	}
	//���v�X�R�A��10000��菬�����̎�
	else if (score < 9999)
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[(score / 1000) % 10], TRUE, 0);
		DrawRotaGraphF(245, 460, 1.0, 0, number_image[(score / 100) % 10], TRUE, 0);
		DrawRotaGraphF(260, 460, 1.0, 0, number_image[(score / 10) % 10], TRUE, 0);
		DrawRotaGraphF(275, 460, 1.0, 0, number_image[0], TRUE, 0);
	}
	//���v�X�R�A��100000�ȉ��̎�
	else if (score <= 99999)
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[(score / 10000) % 10], TRUE, 0);
		DrawRotaGraphF(245, 460, 1.0, 0, number_image[(score / 1000) % 10], TRUE, 0);
		DrawRotaGraphF(260, 460, 1.0, 0, number_image[(score / 100) % 10], TRUE, 0);
		DrawRotaGraphF(275, 460, 1.0, 0, number_image[(score / 10) % 10], TRUE, 0);
		DrawRotaGraphF(290, 460, 1.0, 0, number_image[0], TRUE, 0);
	}
	//�J���X�g�p
	else
	{
		DrawRotaGraphF(230, 460, 1.0, 0, number_image[9], TRUE, 0);
		DrawRotaGraphF(245, 460, 1.0, 0, number_image[9], TRUE, 0);
		DrawRotaGraphF(260, 460, 1.0, 0, number_image[9], TRUE, 0);
		DrawRotaGraphF(275, 460, 1.0, 0, number_image[9], TRUE, 0);
		DrawRotaGraphF(290, 460, 1.0, 0, number_image[9], TRUE, 0);
	}

	//UI�^�C�}�[(��������)�̕`��
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
	if (time == 0)
	{
		UiFinish();
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


//�Q�[���I����UI
void Scene::UiFinish()
{
	//�X�R�A��������菬����������A
	if (score < 1000)
	{
		//BAD��`�悷��
		DrawRotaGraphF(320, 240, 1.0, 0, ui_finish[0], TRUE, 0);
	}
	else if (score < 4999)
	{
		//OK��`�悷��
		DrawRotaGraphF(320, 240, 0.5, 0, ui_finish[3], TRUE, 0);
	}
	else if (score < 19999)
	{
		//GOOD��`�悷��
		DrawRotaGraphF(320, 240, 0.7, 0, ui_finish[2], TRUE, 0);
	}
	else if (score > 99999)
	{
		//Perfect��`�悷��
		DrawRotaGraphF(320, 240, 1.0, 0, ui_finish[4], TRUE, 0);
	}
	else
	{
		//�X�R�A�J���X�g�p
		DrawRotaGraphF(320, 240, 1.0, 0, ui_finish[4], TRUE, 0);
	}
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
		if (finish_flg != TRUE)
		{
			a->OnHitCollision(b);
			b->OnHitCollision(a);
		}
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
