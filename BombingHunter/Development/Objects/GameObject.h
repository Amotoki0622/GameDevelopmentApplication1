#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER			//座標の原点を画像の中心にする

/*出現するオブジェクトのポイント*/
#define HAKOENEMY_P		(200)
#define HANEENEMY_P		(30)
#define GOLDENEMY_P		(2000)
#define HARPY_P			(-100)

enum Objects
{
	PLAYER_BOMB,		//プレイヤー弾
	ENEMY_HAKO,			//ハコテキ
	ENEMY_HANE,			//ハネテキ
	ENEMY_GOLD,			//金のテキ
	HARPY			//ハーピー
};

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;						//位置情報
	Vector2D box_size;							//矩形の大きさ
	double radian;							//向き
	int image;								//画像
	int sound;								//音源
	int type;							//種類(試作)
	bool flg;							//フラッグ
	int score;							//スコア

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();				//初期化処理
	virtual void Update();					//更新処理
	virtual void Draw() const;				//描画処理
	virtual void Finalize();				//終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//位置情報取得処理
	Vector2D GetLocation() const;

	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//当たり判定の大きさを取得する
	Vector2D GetBoxSize() const;

	//オブジェクトのタイプを判別する処理
	int GetType();

	//削除フラグ
	bool DeleteFlg();

};