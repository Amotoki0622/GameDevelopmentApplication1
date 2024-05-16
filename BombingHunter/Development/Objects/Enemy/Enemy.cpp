#include "Enemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//コンストラクタ
Enemy::Enemy() : animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("敵の画像がありません確認してください\n");
	}

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	scale = 64.0f;

	//初期画像の設定
	image = animation[0];
}

//更新処理
void Enemy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimationControl();
}

//描画処理
void Enemy::Draw() const
{
	//敵画像の描画
	DrawRotaGraph(location.x, location.y, 1.0, radian, image, TRUE);
}

//終了時処理
void Enemy::Finalize()
{
	//使用していた画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//移動処理
void Enemy::Movement()
{
	Vector2D velocity = 0.0f;

	velocity.x += -1.0f;

	location += velocity;
}

//アニメーション制御
void Enemy::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
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