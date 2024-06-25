#include "Bomb.h"
#include "DxLib.h"

//コンストラクタ
Bomb::Bomb() : animation_count(0),image(0), direction(0.0f)	
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
	radian = 3.14/2;

	//当たり判定の大きさと設定
	box_size = 70.0f;

	//初期進行方向の設定
	direction = Vector2D(0.0f, 1.0f);
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
	////画像反転フラグ
	//int flip_flag = FALSE;
	//
	////進行方向によって、反転状態を決定する
	//if (direction.x > 0.0f)
	//{
	//	flip_flag = FALSE;
	//}
	//else
	//{
	//	flip_flag = TRUE;
	//}
	//情報を基にバクダン画像を描画する
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
	//当たったときの処理
	//if(もし当たったのが敵だったら)
	//{
	// AnimationControl(当たったとき)
	//	弾を削除する(画像だけでなく、オブジェクト自体を)
	//}
	//direction = 0.0f;
 	if (hit_object->GetType() == ENEMY_HAKO)
	{
		direction = 0.0f;		//この後は消す処理にする(画像だけでなくオブジェクトから送られた値すべて)
	}

	if (hit_object->GetType() == ENEMY_HANE)
	{
		direction = 0.0f;		//この後は消す処理にする(画像だけでなくオブジェクトから送られた値すべて)
	}

	if (hit_object->GetType() == ENEMY_GOLD)
	{
		direction = 0.0f;		//この後は消す処理にする(画像だけでなくオブジェクトから送られた値すべて)
	}

	if (hit_object->GetType() == HARPY)
	{
		direction = 0.0f;		//この後は消す処理にする(画像だけでなくオブジェクトから送られた値すべて)
	}

}

//移動処理
void Bomb::Movement()
{
	//画面端に到達したら、進行方向を反転する
	//if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	//{
	//	direction.x *= -1.0f;
	//}
	//if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	//{
	//	direction.y *= -1.0f;
	//}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
//void Bomb::AnimationControl()
//{
//	//アニメーションカウントを加算する
//	animation_count++;
//
//	//30フレーム目に到達したら
//	if (animation_count >= 60)
//	{
//		//カウントのリセット
//		animation_count = 0;
//
//		//画像の切り替え
//		if (image == animation[0])
//		{
//			image = animation[1];
//		}
//		else
//		{
//			image = animation[0];
//		}
//	}
//}