#pragma once

#include "../EnemyBase.h"

/// <summary>
/// テキクラス(赤べぇ)
/// </summary>
class RedEnemy : EnemyBase
{

public:
	RedEnemy();
	virtual ~RedEnemy();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;


	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	/// <summary>
	/// テキの状態を取得する
	/// </summary>
	/// <returns>テキの状態</returns>
	virtual eEnemyState GetEnemyState() const override;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Movement(float delta_second) override;
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void AnimationControl(float delta_second) override;

private:
	/// <summary>
	/// 移動処理 : 待機状態
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Stay(float delta_second);
	/// <summary>
	/// 移動処理 : 縄張状態
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Territory(float delta_second);
	/// <summary>
	/// 移動処理 : 追跡状態
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Chase(float delta_second);
	/// <summary>
	/// 移動処理 : いじけ状態
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Izike(float delta_second);
	/// <summary>
	/// 移動処理 : 目玉状態(死亡)
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Eye(float delta_second);
};