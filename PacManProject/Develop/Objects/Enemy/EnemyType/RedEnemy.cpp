#include "RedEnemy.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/ResourceManager.h"
#include "DxLib.h"


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
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 2, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 2, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::player;
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::food);
	collision.hit_object_type.push_back(eObjectType::power_food);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

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
		break;

	case eEnemyState::TERRITORY:
		break;

	case eEnemyState::CHASE:
		break;

	case eEnemyState::IZIKE:
		break;

	case eEnemyState::EYE:
		break;

	default:
		break;
	}
}

void RedEnemy::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset	);
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
}

eEnemyState RedEnemy::GetEnemyState() const
{
	return enemy_state;
}

void RedEnemy::Movement(float delta_second)
{
	// 移動量から移動方向を更新
	
}