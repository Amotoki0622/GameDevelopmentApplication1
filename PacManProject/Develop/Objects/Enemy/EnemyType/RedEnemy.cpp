#include "RedEnemy.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/ResourceManager.h"
#include "DxLib.h"

#define D_PLAYER_SPEED	(50.0f)


RedEnemy::RedEnemy()
{
}

RedEnemy::~RedEnemy()
{
	
}

void RedEnemy::Initialize()
{
	// アニメーション画像の読込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 2, 32, 32);


	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	//最初のテキの状態
	enemy_state = eEnemyState::TERRITORY;
	//enemy_state = eEnemyState::STAY;

	/* (反射するように動く) */
	 velocity = Vector2D(5.0f, 0.0f);

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

}

void RedEnemy::Update(float delta_second)
{
	// テキの状態によって、動作を変える
	switch (enemy_state)
	{
	case eEnemyState::STAY:
		// 画像の設定
		image = move_animation[3];
		// 移動処理(縄張状態の時)
		Stay(delta_second);
		// アニメーション制御
		//AnimationControl(delta_second);
		break;

	case eEnemyState::TERRITORY:
		image = move_animation[0];
		Territory(delta_second);
		AnimationControl(delta_second);
		break;

	case eEnemyState::CHASE:
		// アニメーション制御
		//AnimationControl(delta_second);
		break;

	case eEnemyState::IZIKE:
		image = move_animation[18];
		// アニメーション制御
		//AnimationControl(delta_second);

		break;

	case eEnemyState::EYE:
		image = move_animation[18];
		break;

	default:
		break;
	}
}

void RedEnemy::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void RedEnemy::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	eye_animation.clear();
}

/// <summary>
/// 当たり判定通知
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void RedEnemy::OnHitCollision(GameObjectBase* hit_object)
{
	__super::OnHitCollision(hit_object);

	int move = GetRand(4);

	switch (move)
	{
	case 1:
		velocity.x = 0.0f;
		velocity.y = -(5.0f);
		break;
	case 2:
		velocity.x = 0.0f;
		velocity.y = 5.0f;
		break;
	case 3:
		velocity.x = -(5.0f);
		velocity.y = 0.0f;

		break;
	case 4:
		velocity.x = 5.0f;
		velocity.y = 0.0f;
		break;
	default:
		break;
	}



/*// 当たった、オブジェクトが壁だったら		
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Playerからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;
	}*/

/*/	// 当たり判定情報を取得して、カプセルがある位置を求める	北案
	CapsuleCollision hc = hit_object->GetCollision();
	hc.point[0] += hit_object->GetLocation();
	hc.point[1] += hit_object->GetLocation();

	// 最近傍点を求める
	Vector2D near_point = NearPointCheck(hc, this->location);

	// Playerからnear_pointへの方向ベクトルを取得
	Vector2D dv2 = near_point - this->location;
	Vector2D dv = this->location - near_point;

	// めり込んだ差分
	float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

	// diffの分だけ戻る
	location += dv.Normalize() * diff;*/
}

/// <summary>
/// テキの状態を取得する
/// </summary>
/// <returns>テキの状態</returns>
eEnemyState RedEnemy::GetEnemyState() const
{
	return enemy_state;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void RedEnemy::Movement(float delta_second)
{
	// 前回座標の更新
	 old_location = location;


	// 移動量 * 速さ * 時間 で移動先を決定する
	location += velocity * D_PLAYER_SPEED * delta_second;

	// 画面外に行ったら、反対側にワープさせる
	if (location.x < 0.0f)
	{
		old_location.x = 672.0f;
		location.x = 672.0f - collision.radius;
		velocity.y = 0.0f;
	}
	if (672.0f < location.x)
	{
		old_location.x = 0.0f;
		location.x = collision.radius;
		velocity.y = 0.0f;
	}

}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void RedEnemy::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// 画像の設定
		int dir_num = (int)now_direction_state;
		if (0 <= dir_num && dir_num < 4)
		{
			image = move_animation[(dir_num * 3) + animation_num[animation_count]];
		}

	}
}

/// <summary>
/// 移動処理 : 待機状態
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void RedEnemy::Stay(float delta_second)
{
	Movement(delta_second);

}

/// <summary>
/// 移動処理 : 縄張状態
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void RedEnemy::Territory(float delta_second)
{

	Movement(delta_second);

}

/// <summary>
/// 移動処理 : 追跡状態
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void RedEnemy::Chase(float delta_second)
{

}

/// <summary>
/// 移動処理 : いじけ状態
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void RedEnemy::Izike(float delta_second)
{

}

/// <summary>
/// 移動処理 : 目玉状態(死亡)
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void RedEnemy::Eye(float delta_second)
{

}