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
//フレームレート
#define FRAME_RATE	(144)

//コンストラクタ
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

//デストラクタ
Scene::~Scene()
{
	//解放忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//背景画像を格納する変数
	image = LoadGraph("Resource/Images/BackGround.png");

	//1～9までの数字の画像を格納する配列
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
	//フォントのUI	後に変数を変更
	number_image[10] = LoadGraph("Resource/Images/Score/font-21.png");
	number_image[11] = LoadGraph("Resource/Images/Score/hs.png");
	watch_image = LoadGraph("Resource/Images/TimeLimit/timer-03.png");

	//終了時のUI
	ui_finish[0] = LoadGraph("Resource/Images/Evaluation/BAD.png");
	ui_finish[1] = LoadGraph("Resource/Images/Evaluation/Finish.png");
	ui_finish[2] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	ui_finish[3] = LoadGraph("Resource/Images/Evaluation/OK.png");
	ui_finish[4] = LoadGraph("Resource/Images/Evaluation/Perfect.png");

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

	//もし終了フラグがTRUEだった場合、生成を終了する
	if (finish_flg != TRUE)
	{
		if (count > 200)
		{
			count = 0;
		}
		else
		{
			//テキ自動生成処理
			OutoSpawnEnemy();
			count++;
		}
	}


	Vector2D p = 0.0;		//	プレイヤーの位置の更新した値を格納する変数
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

	//点数の合計
	TotalScore();

	//プレイヤーのたまに当たった時の削除処理
	Delete();

	//オブジェクトが範囲外に行った時の削除処理
	ScreenOutDelete();

	//スペースキーを押したら、バクダンを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D(p.x, 114.0f));
	}

	//テキ手動生成処理(デバック)
	SpawnEnemy();

}

//試作テキ自動生成処理
void Scene::OutoSpawnEnemy()
{
	//CreateObject<Enemy>(Vector2D(100.0f, 390.0f));
	int a;
	a = rand() % 100 + 1;	//0～100までのランダムな数字を出す
	if (a <= 1)
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

//試作オブジェクト手動生成処理
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

	//Cキーを押したら、敵を生成する(デバック用)
	if (InputControl::GetKeyDown(KEY_INPUT_C))
	{
		CreateObject<Enemy>(Vector2D(-70.0f, 390.0f));
	}

	//Bキーを押したら、敵が生成する(デバック用)
	if (InputControl::GetKeyDown(KEY_INPUT_B))
	{
		CreateObject<GoldEnemy>(Vector2D(100.0f, 390.0f));
	}
}

//弾と当たったときの削除処理
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

//スコアの合計処理
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
	//スコアの合計がもし-になったとき、値を0にする
	if (score < 0)
	{
		score = 0;
	}
}

//画面外にいったオブジェクトの削除処理
void Scene::ScreenOutDelete()
{
	for (int i = 0; i < objects.size(); i++)
	{
		//ハコテキが画面外に行ったら、削除する
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

//描画処理
void Scene::Draw() const
{
	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//制限時間(減少)の処理
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
	/*デバック(ちゃんと値が入っているか確認用)*/
	/*if (time < 0)
	{
		time = 0;
	}*/
}


//ゲーム終了処理フラグ
void Scene::FinishFlg()
{
	if (time == 0)
	{
		finish_flg = TRUE;
	}
}


//画面のUI描画処理
void Scene::UiDraw()
{
	//背景画像の描画
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

	//UIの時計の描画
	//時計のイラストの描画
	DrawRotaGraphF(20, 460, 0.6, 0, watch_image, TRUE, 0);
	/*もしタイマーが2桁の場合*/
	if (time >= 10)
	{
		DrawRotaGraphF(45, 460, 1.0, 0, number_image[time / 10], TRUE, 0);
		DrawRotaGraphF(60, 460, 1.0, 0, number_image[time % 10], TRUE, 0);
	}
	//タイマーが1桁の場合
	else if (time < 10)
	{
		DrawRotaGraphF(45, 460, 1.0, 0, number_image[time % 10], TRUE, 0);
	}
	//タイマーが0秒の場合
	else if (time == 0)
	{
		DrawRotaGraphF(45, 460, 1.0, 0, number_image[0], TRUE, 0);
	}

	//0秒になったら、ゲーム終了時UIに移動する
	if (time < 0)
	{
		//UiFinishDraw();		//FinishのUIを描画する処理
		UiFinish();
	}


	//試作 時間の描画
		//DrawFormatString(30, 460, GetColor(255, 255, 255), "%d", time);

	//制限時間の描画
//	DrawFormatString(30, 460, GetColor(255, 255, 255), "%d", time);
//	DrawFormatString(150, 460, GetColor(255, 255, 255), "スコア%d", score);

	//試作 時間の描画(UIなし)
//	DrawRotaGraphF(190, 460, 1.0, 0, number_image[10], TRUE, 0);

	//DrawRotaGraphF(100, 460, 1.0, 0, number_image[10], TRUE, 0);
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


//ゲーム終了時UI
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
		//delete?
		/*if (a->GetType() == ENEMY_HAKO && a->DeleteFlg() == TRUE)
		{
			objects.erase(objects.begin() + 1);
		}*/
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
