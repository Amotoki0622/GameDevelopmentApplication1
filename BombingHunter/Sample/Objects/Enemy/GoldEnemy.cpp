#include "GoldEnemy.h"
#include "DxLib.h"

//コンストラクタ
GoldEnemy::GoldEnemy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
}

//デストラクタ
GoldEnemy::~GoldEnemy()
{

}

//初期化処理
void GoldEnemy::Initialize()
{
	//これがなんのオブジェクトか判別する変数(この場合金のテキ)
	type = ENEMY_GOLD;

	//画像の読込み
	animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1 || animation[4] == -1)
	{
		throw("金のテキの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさと設定
	box_size = 45.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);

//	int spran = GetRand(5);
//	direction = Vector2D(spran / 10.0f, 0.0f);

}

//更新処理
void GoldEnemy::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void GoldEnemy::Draw() const
{
	//画像反転フラグ
	int flip_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//情報を基にハコ敵画像を描画する
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void GoldEnemy::Finalize()
{
	//使用した画像を解放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void GoldEnemy::OnHitCollision(GameObject* hit_object)
{
	//当たったときの処理
	//direction = 0.0f;

	//プレイヤーの弾と当たったとき
	if (hit_object->GetType() == PLAYER_BOMB)
	{
		direction = 0.0f;				//この後は消す処理にする(画像だけでなくオブジェクトから送られた値すべて)
	}
}

//移動処理
void GoldEnemy::Movement()
{
	//画面端に到達したら、進行方向を反転する
	if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}
	if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void GoldEnemy::AnimationControl()
{
	//アニメーションカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else if(image == animation[1])
		{
			image = animation[2];
		}
		else if (image == animation[2])
		{
			image = animation[3];
		}
		else if (image == animation[3])
		{
			image = animation[4];
		}
		else
		{
			image = animation[0];
		}
	}
}