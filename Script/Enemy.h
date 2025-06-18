/* -----------
　雑魚敵データ
 ------------- */

#pragma once
#include "Vector2.h"
#include "HPBer.h"

class Enemy
{
public:

	/* --- <<< 定数定義 >>> --- */

	static constexpr int SIZE_X = 64; // 横画像サイズ
	static constexpr int SIZE_Y = 64; // 縦画像サイズ

	static constexpr int MAX_HP		 = 3;  // 最大HP
	static constexpr int SPEED_Y	 = 3;  // 縦移動速度
	static constexpr int SPEED_X_DEC = 50; // 横移動速度減少率

	static constexpr int HP_SIZE_Y	   = 5;			// HP縦サイズ
	static constexpr int HP_COLOR	   = 0xFF0000;	// HPの色(16進数)
	static constexpr int HP_COLOR_BACK = 0x550000;	// HPの背景色(16進数)


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	Enemy(void);

	~Enemy(void);

	// 初期化処理(最初の１回のみ実行)
	void Init(void);

	// ゲーム内初期化
	void GameInit(void);

	// 更新処理(毎フレーム実行)
	void Update(int playerPosX, int playerSizeX);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);


	// 横移動処理
	void MovePosX(int playerPosX, int playerSizeX);

	// 被ダメ処理
	void Damage(void);

	// 移動速度 復活
	void ResetSpeedY(void);


	/* --- <<< ゲッター処理 >>> --- */

	// 位置 取得
	Vector2 GetPos();

	// 敵有効フラグ 取得
	bool GetIsAlive();

	// 現在HP取得
	int GetHP();


private:

	/* --- <<< 定数定義 >>> --- */

	int enemyImage_; // 敵画像
	Vector2 pos_;	 // 座標
	bool isAlive_;	 // 有効化フラグ

	int hp_;	 // 現在HP
	int speedY_; // 縦移動速度

	HPBer hpBer_; // HPバー
};