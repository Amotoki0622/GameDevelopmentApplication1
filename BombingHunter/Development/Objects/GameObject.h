#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER			//座標の原点を画像の中心にする

//#define ENEMY_ALL	(6)			//敵の総数(敵の弾も含める)	


/*試作 (Developmentに書くときはもっとわかりやすく)*/
//#define PLAYER_BOMB		(0)			//敵の弾
//#define ENEMY_HAKO		(1)		//敵(ハコテキのオブジェクト)
//#define ENEMY_HANE		(2)		//敵(一応ハネテキのオブジェクト)
//#define ENEMY_GOLD		(3)		//敵(一応金のテキのオブジェクト)
//#define HARPY		(4)		//敵(一応ハコテキのオブジェクト)

/*試作 (出現するオブジェクトのポイント)*/
#define HAKOENEMY_P		(200)
#define HANEENEMY_P		(30)
#define GOLDENEMY_P		(2000)
#define HARPY_P			(-100)

enum Object
{
	PLAYER_BOMB,
	ENEMY_HAKO,
	ENEMY_HANE,
	ENEMY_GOLD,
	HARPY
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

	bool DeleteFlg();

	//スコアの値を判別する処理
	//int GetScere();
};