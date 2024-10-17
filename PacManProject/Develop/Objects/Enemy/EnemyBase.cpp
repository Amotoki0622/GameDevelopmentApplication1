#include "EnemyBase.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"

#define D_ENEMY_SPEED   (50.0f)
    
EnemyBase::EnemyBase() :
    move_animation(),
    eye_animation(),
    old_location(0.0f),
    velocity(0.0f),
    enemy_state(eEnemyState::STAY),
    now_direction_state(eDirectionState::LEFT),
    animation_time(0.0f),
    animation_count(0),
    old_panel(ePanelID::NONE),
    switching_time(0.0f),
    image(NULL)
{
}

EnemyBase::~EnemyBase()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void EnemyBase::Initialize()
{
    ResourceManager* rm = ResourceManager::GetInstance();
    move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 2, 32, 32);
    eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 2, 32, 32);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::Update(float delta_second)
{
    //image = move_animation[1];
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
    Vector2D graph_location = this->location + screen_offset;
    DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

/// <summary>
/// 終了処理
/// </summary>
void EnemyBase::Finalize()
{

}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
    // 当たったときの処理

    // 当たった、オブジェクトが壁だったら
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

        // テキを反射させる方法  
        //velocity *= -1;
    }

    if (hit_object->GetCollision().object_type == eObjectType::player)
    {
        enemy_state = eEnemyState::EYE;
    }
}

/// <summary>
/// テキの状態を取得する
/// </summary>
/// <returns>テキの状態</returns>
eEnemyState EnemyBase::GetEnemyState() const
{
    return enemy_state;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::Movement(float delta_second)
{
    // 移動量から移動方向を更新
    if (Vector2D::Distance(old_location, location) == 0.0f)
    {

    }
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::AnimationControl(float delta_second)
{

}

/// <summary>
/// 移動処理 : 待機状態
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::Stay(float delta_second)
{

}

/// <summary>
/// 移動処理 : 縄張状態
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::Territory(float delta_second)
{

}

/// <summary>
/// 移動処理 : 追跡状態
/// </summary>
/// <param name="delta_second"></param>
void EnemyBase::Chase(float delta_second)
{

}

/// <summary>
/// 移動処理 : いじけ状態
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::Izike(float delta_second)
{

}

/// <summary>
/// 移動処理 : 目玉状態(死亡)
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::Eye(float delta_second)
{

}