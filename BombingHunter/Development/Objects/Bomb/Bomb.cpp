#include "Bomb.h"
#include "DxLib.h"

//コンストラクタ
Bomb::Bomb() : animation_count(0), image(0), direction(0.0f)
{

}

//デストラクタ
Bomb::~Bomb()
{

}

//初期化処理
void Bomb::Initialize()
{
	//これがなんのオブジェクトか判別する変数(この場合プレイヤーの爆弾)
	type = PLAYER_BOMB;

	//画像の読込み
	image = LoadGraph("Resource/Images/Bomb/Bomb.png");

	//エラーチェック
	if (image == -1)
	{
		throw("ばくだんの画像がありません\n");
	}

	//向きの設定
	radian = 3.14 / 2;

	//当たり判定の大きさと設定
	box_size = 70.0f;

	//初期進行方向の設定
	direction = Vector2D(0.0f, 2.0f);
}

//更新処理
void Bomb::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	//AnimationControl();
}

//描画処理
void Bomb::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE, FALSE);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Bomb::Finalize()
{
	//使用した画像を解放
	DeleteGraph(image);
}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{

	if (hit_object->GetType() == ENEMY_HAKO)
	{
		//削除するFlgをTRUEにする
		flg = TRUE;
	}
	else if (hit_object->GetType() == ENEMY_HANE)
	{
		//削除するFlgをTRUEにする
		flg = TRUE;
	}

	else if (hit_object->GetType() == ENEMY_GOLD)
	{
		//削除するFlgをTRUEにする
		flg = TRUE;
	}

	else if (hit_object->GetType() == HARPY)
	{
		//削除するFlgをTRUEにする
		flg = TRUE;
	}

}

//移動処理
void Bomb::Movement()
{

	//進行方向に向かって、位置座標を変更する
	location += direction;
}
