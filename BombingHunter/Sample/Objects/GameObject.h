#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER			//座標の原点を画像の中心にする

#define ENEMY_ALL	(6)			//敵の総数(敵の弾も含める)

/*オブジェクトの種類の判別する方法*/
#define P_BULLET		(0)			//プレイヤーの弾
#define E_BULLET		(1)			//敵の弾(ハコテキから出てくる弾)
#define ENEMY			(2)			//敵(ハコテキ)
#define ENEMY2			(3)			//敵(金のテキ)
#define ENEMY3			(4)			//敵(ハネテキ)
#define ENEMY4			(5)			//ハーピー
/*オブジェクトの種類の判別する方法*/

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;						//位置情報
	Vector2D box_size;							//矩形の大きさ
	double radian;							//向き
	int image;								//画像
	int sound;								//音源
	int p[ENEMY_ALL];

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();				//初期化処理
	virtual void Update();					//更新処理
	virtual void Draw() const;				//描画処理
	virtual void Finalize();				//終了時処理

	//オブジェクトの種類を判別する処理
	virtual void GetType(GameObject* hit_object);

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//位置情報取得処理
	Vector2D GetLocation() const;

	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//当たり判定の大きさを取得する
	Vector2D GetBoxSize() const;

};