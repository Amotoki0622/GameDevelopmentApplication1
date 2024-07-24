#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

// 敵情報aaa
enum eEnemyState
{
	STAY,			// 待機状態
	TERRITORY,		// 縄張状態
	CHASE,			// 追跡状態
	IZIKE,			// いじけ状態
	DIE,			// 死亡状態
};

/// <summary>
/// テキクラス
/// </summary>

class Aka : public GameObject
{
private:
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};

private:
	std::vector<int> move_animation;
	std::vector<int> dying_animation;
	Vector2D velocity;
	eEnemyState enemy_state;
	eDirectionState now_direction_state;
	float animation_time;
	int animation_count;

	// 移動アニメーションの順番
	const int animation_num[4] = { 0, 1, 2, 1 };

public:
	Aka();
	virtual ~Aka();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name = "hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	
public:
	/// <summary>
	/// テキの状態を取得する
	/// </summary>
	/// <returns>テキの状態</returns>
	eEnemyState GetEnemyState() const;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name = "delta_second">1フレーム当たりの時間
	void Movement(float delta_second);

	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name = "delta_second">1フレーム当たりの時間
	void AnimationControl(float delta_second);
};