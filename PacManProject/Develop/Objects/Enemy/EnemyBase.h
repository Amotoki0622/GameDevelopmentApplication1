#pragma once

#include "../GameObject.h"

// テキ状態
enum eEnemyState
{
	STAY,				// 待機状態
	TERRITORY,			// 縄張状態
	CHASE,				// 追跡状態
	IZIKE,				// いじけ状態
	EYE,				// 目玉状態(死亡)
};

/// <summary>
/// 基底クラス(テキ)
/// </summary>
class EnemyBase : public GameObject
{
	// 進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};
protected:
	std::vector<int> move_animation;
	std::vector<int> eye_animation;
	Vector2D velocity;
	eEnemyState enemy_state;
	eDirectionState now_direction_state;
	float animation_time;
	int animation_count;
	float switching_time;
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const;
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
	virtual eEnemyState GetEnemyState() const;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void AnimationControl(float delta_second);

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