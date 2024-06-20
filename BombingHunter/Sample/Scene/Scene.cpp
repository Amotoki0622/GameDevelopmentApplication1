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

//コンストラクタ
Scene::Scene() : objects(), image(0.0f)
{

}

//デストラクタ
Scene::~Scene()
{
	//解放忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	image = LoadGraph("Resource/Images/BackGround.png");

	if (image == -1)
	{
		throw("背景画像がありません。\n");
	}


	//プレイヤーを画面中央あたりに生成する(初期位置情報の設定)
	CreateObject<Player>(Vector2D(320.0f, 45.0f));
}

//更新処理
void Scene::Update()
{

	SpawnEnemy();

	Vector2D p = 0.0;
	p = objects[0]->GetLocation().x;
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}


	//スペースキーを押したら、バクダンを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D(p.x, 114.0f));
	}



	//Zキーを押したら、敵を生成する(初期位置情報の設定)
	//if (InputControl::GetKeyDown(KEY_INPUT_Z))
	//{
	//	//乱数を取得(Y座標を150～390に収めるように)
	//	//int a = GetRand(3);
	//	//CreateObject<Enemy>(Vector2D(100.0f, 150.0f + (a * 80)));
	//}
	
}

void Scene::SpawnEnemy()
{
	//Zキーを押したら、敵を生成する(初期位置情報の設定)
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		//乱数を取得(Y座標を150～390に収めるように)
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

	//Cキーを押したら、敵を生成する(デバック用)
	if (InputControl::GetKeyDown(KEY_INPUT_C))
	{
		CreateObject<Enemy>(Vector2D(100.0f, 390.0f));
	}

	//Bキーを押したら、敵が生成する(デバック用)
	if (InputControl::GetKeyDown(KEY_INPUT_B))
	{
		CreateObject<GoldEnemy>(Vector2D(100.0f, 390.0f));
	}
}


//描画処理
void Scene::Draw() const
{

	DrawExtendGraph(0.0f, 0.0f, 640.0f, 480.0f, image, TRUE);


	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
void Scene::Finalize()
{
	//オブジェクトリスト内が空なら、処理を終了する
	if (objects.empty())
	{
		return;
	}

	//オブジェクトリスト内のオブジェクトを解放する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的に確保したリストを解放する
	objects.clear();
}

#ifdef D_PIVOT_CENTER
//当たり判定チェック処理(矩形の中心で当たり判定を取る)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else

//当たり判定チェック処理(左上の座標から当たり判定計算を行う)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右上頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//矩形Aと矩形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHit判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif // D_PIVOT_CENTER
