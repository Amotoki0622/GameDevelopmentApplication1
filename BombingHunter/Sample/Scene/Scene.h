#pragma once

#include "../Objects/GameObject.h"
#include <vector>

class Scene
{
private:
	std::vector<GameObject*> objects;		//オブジェクトリスト

private:
	int image;					//背景画像
	int count;					//自動生成カウント
	int time_count;				//カウント
	int time;					//時間
	int number_image[12];		//数字の画像
	int score;					//スコア	
	int score_im;				//スコアの画像

public:
	Scene();
	~Scene();

	void Initialize();				//初期化処理
	void Update();					//移動処理
	void SpawnEnemy();				//敵の手動生成
	void OutoSpawnEnemy();			//敵の自動生成
	void Draw() const;				//描画処理
	void Finalize();				//終了時処理
	void Delete();					//削除処理
	void ScreenOutDelete();			//画面外の削除処理
	void Timer();
	void TotalScore();				//合計点数


private:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b); 

	//オブジェクト生成処理
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObjectクラスを継承してるか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("GameObjectが生成できませんでした。\n");
		}

		//初期化処理
		new_object->Initialize();
		//位置情報の設定
		new_object->SetLocation(location);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};