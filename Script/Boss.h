/* ---------
　ボスデータ
 ----------- */

#pragma once
#include "Vector2.h"
#include "HPBer.h"
#include "Boss.h"

// ボスクラス
class Boss
{
public:

	/* --- <<< 列挙型定義 >>> --- */

	enum class STATE
	{
		NONE,
		IDLE,	// 待機状態
		MOVE,	// 移動状態
		ACTIVE, // 停止状態
	};


	/* --- <<< 定数定義 >>> --- */

	/*　本体系　*/
	static constexpr int SIZE_X = 200;	// 横サイズ
	static constexpr int SIZE_Y = 269;	// 縦サイズ

	static constexpr int MAX_HP	   = 15; // 最大HP
	static constexpr int SPEED	   = 1;  // 移動速度
	static constexpr int INV_COUNT = 35; // 無敵カウント
	
	static constexpr int IDLE_CONUT = 50; // 出現待機時間

	/*　HPバー系　*/
	static constexpr int BER_POS_X  = 20;  // 横位置
	static constexpr int BER_POS_Y  = 5;   // 縦位置
	static constexpr int BER_SIZE_X = 600; // 横サイズ
	static constexpr int BER_SIZE_Y = 65;  // 縦サイズ
	static constexpr int BER_COLOR  = 0x500000; // HPバーの色(16進数)

	/*　HP系　*/
	static constexpr int HP_POS_X  = (BER_POS_X + 15); // 横位置
	static constexpr int HP_POS_Y  = (BER_POS_Y + 25); // 縦位置
	static constexpr int HP_SIZE_X = (BER_SIZE_X - HP_POS_X - 15); // 横サイズ
	static constexpr int HP_SIZE_Y = (BER_SIZE_Y - HP_POS_Y - 5);  // 縦サイズ

	/*　HP色(16進数)　*/
	static constexpr int HP_COLOR	   = 0xFF0000; // 現在HP色
	static constexpr int HP_COLOR_BACK = 0x100000; // HP背景色
	static constexpr int TEXT_COLOR	   = 0xFFFFFF; // テキスト色


	/*　警告演出系　*/
	static constexpr int WARNING_ALPHA	 = (255 - 50); // 演出透明度
	static constexpr float WARNING_SPEED = 0.05f;	   // 演出速度


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// デフォルトコンストラクタ
	Boss(void);

	// デストラクタ
	~Boss(void);

	// 初期処理(最初の１回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// HP描画処理
	void DrawHP(void);

	// 警告演出　描画処理
	void DrawWarning(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);

	// 被ダメ処理
	void Damage(void);


	/* --- <<< ゲッター処理 >>> --- */

	// 生存フラグ 取得
	bool GetIsAlive(void);

	// 座標 取得
	Vector2 GetPos(void);

	// 現在HP 取得
	int GetHP(void);
	
	// 無敵状態確認(true = 無敵状態)
	bool GetIsInvincive(void);


private:

	/* --- <<< 変数定義 >>> --- */

	int image_;	   // 画像

	Vector2 pos_;  // 座標
	int hp_;	   // 現在HP
	int invCount_; // 無敵時間
	bool isAlive_; // 生存フラグ

	STATE state_; // 行動状態
	HPBer hpBer_; // HPバー

	int idleCounter_; // 待機カウンタ

	float warningCounter_; // 警告演出カウンタ
	float warningAlpha_;   // 警告透明値


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	/*　状態別更新処理　*/
	void UpdateIdle(void);	 // 停止状態
	void UpdateMove(void);	 // 移動状態
	void UpdateActive(void); // 停止状態

	// 状態遷移処理
	void ChangeState(STATE state);
};
