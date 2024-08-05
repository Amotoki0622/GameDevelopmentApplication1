#include "EnemyBase.h"
    
EnemyBase::EnemyBase() :
    move_animation(),
    eye_animation(),
    velocity(0.0f),
    enemy_state(eEnemyState::STAY),
    now_direction_state(eDirectionState::LEFT),
    animation_time(0.0f),
    animation_count(0),
    switching_time(0.0f)
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

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::Update(float delta_second)
{

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void EnemyBase::Draw(const Vector2D& screen_offset) const
{

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
}

/// <summary>
/// テキの状態を取得する
/// </summary>
/// <returns>テキの状態</returns>
eEnemyState EnemyBase::GetEnemyState() const
{

}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::Movement(float delta_second)
{

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