/* -------
　弾データ
 --------- */

#pragma once
#include "Vector2.h"
#include "KeyTrigger.h"

class Shot
{
public:
	
	/* --- <<< 定数定義 >>> --- */

	static constexpr int SIZE_X = 32; // 横サイズ
	static constexpr int SIZE_Y = 32; // 縦サイズ
	static constexpr int SPEED  = 10; // 移動速度


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	//コンストラクタ
	Shot(void);

	//デストラクタ
	~Shot(void);

	// 初期化処理(最初の１回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム処理)
	void Update(void);

	// 描画処理(毎フレーム処理)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);


	// 弾丸生成処理
	void Create(int posX, int posY);


	/* --- <<< セッター処理 >>> --- */

	// 弾丸有効フラグ 割り当て
	void SetIsAlive(bool flag);


	/* --- <<< ゲッター処理 >>> --- */

	// 弾丸有効フラグ 取得
	bool GetIsAlive(void);

	// 弾丸位置 取得
	Vector2 GetPos(void);

	// 発射有効判定 取得
	bool GetIsShotActive(void);


private:


	/* --- <<< 変数定義 >>> --- */

	int image_;	   // 画像
	Vector2 pos_;  // 位置
	bool isAlive_; // 有効フラグ

	KeyTrigger zKey_;	  //発射キー(Z)
	KeyTrigger spaceKey_; //発射キー(Space)
};