/* ----------------
　プレイヤーデータ
 ------------------ */

#pragma once
#include "Vector2.h"
#include "HPBer.h"

class Player
{
public:

	/* --- <<< 定数定義 >>> --- */

	/* <<< 画像系 >>> */
	static constexpr int SIZE_X = 32; // 横サイズ
	static constexpr int SIZE_Y = 32; // 縦サイズ

	/* <<< ステータス系 >>> */
	static constexpr int MAX_HP	   = 10;  // 最大HP
	static constexpr int START_Y   = 175; // 開始縦位置
	static constexpr int SPEED_X   = 4;   // 横移動速度
	static constexpr int SPEED_Y   = 4;   // 縦移動速度
	static constexpr int INV_COUNT = 128; // 最大無敵カウント

	/* <<< HP系 >>> */
	static constexpr int HP_POS_X  = 125; // HP横位置
	static constexpr int HP_POS_Y  = 8;   // HP縦位置
	static constexpr int HP_SIZE_X = 435; // HP横サイズ
	static constexpr int HP_SIZE_Y = 25;  // HP縦サイズ

	/* <<< HPフレーム系 >>> */
	static constexpr int HP_FRAME_COLOR = 0x002000;	// HPの枠の色(16進数)
	static constexpr int HP_COLOR	   = 0x00FF00;	// HPの色(16進数)
	static constexpr int HP_COLOR_BACK = 0x005500;	// HPの背景色(16進数)
	static constexpr int HP_TEXT_POS_X = 22;		// HPテキスト横位置
	static constexpr int HP_TEXT_POS_Y = 12;		// HPテキスト縦位置
	static constexpr int HP_TEXT_COLOR = 0xFFFF00;	// HPテキストの色(16進数)


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// デフォルトコンストラクタ
	Player(void);

	// デストラクタ
	~Player(void);


	// 初期化処理(最初の１回のみ実行)
	void Init();

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// HP描画処理
	void DrawHP(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);


	//プレイヤー被ダメ処理
	void Damage(void);


	/* --- <<< セッター処理 >>> --- */

	void SetPosLimitY(int limitY);


	/* --- <<< ゲッター処理 >>> --- */

	// 現在HP 取得
	int GetHP();

	// 位置 取得
	Vector2 GetPos();

	// 有効判定 取得
	bool GetIsAlive();

	// 無敵時間 取得
	int GetInvCount();


private:

	/* --- <<< 変数定義 >>> --- */

	int image_;	    // プレイヤー画像
	Vector2 pos_;   // 現在位置
	bool isAlive_;  // 有効フラグ
	int posLimitY_; // 移動制限位置

	int hp_;	   // 現在HP
	int invCount_; // 無敵時間

	HPBer hpBer_;  //HPバー


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// 移動処理
	void PlayerMove(int moveX, int moveY, int keyCode1, int keyCode2);
};