#include "Harpy.h"
#include "DxLib.h"

//コンストラクタ
Harpy::Harpy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Harpy::~Harpy()
{

}

//初期化処理
void Harpy::Initialize()
{
	//これがなんのオブジェクトか判別する変数(この場合ハーピー)
	type = HARPY;

	//画像の読込み
	animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
	animation[1] = LoadGraph("Resource/Images/Harpy/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハーピーの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさと設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);

}

//更新処理
void Harpy::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void Harpy::Draw() const
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
void Harpy::Finalize()
{
	//使用した画像を解放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Harpy::OnHitCollision(GameObject* hit_object)
{

	if (hit_object->GetType() == PLAYER_BOMB)
	{
		//削除するFlgをTRUEにする
		flg = TRUE;
	}

}

//移動処理
void Harpy::Movement()
{

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void Harpy::AnimationControl()
{
	//アニメーションカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}