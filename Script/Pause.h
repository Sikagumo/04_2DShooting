/* -------------
　一時停止データ
 --------------- */
#pragma once
#include "KeyTrigger.h"

class Pause
{
public:

	/* --- <<< 列挙型定義 >>> --- */

	/*　画像状態　*/
	enum class IMAGE
	{
		MAIN = 0, // メインのラベル
		SUB  = 1, // サブのラベル
		MAX	 = 2, // 画像最大数
	};


	/* --- <<< 定数定義 >>> --- */

	static constexpr int SIZE_X = 202; // 横画像サイズ
	static constexpr int SIZE_Y = (88 / (int)IMAGE::MAX);  // 縦画像サイズ

	static constexpr int MAIN_POS_Y = (50 + SIZE_Y); // メイン画像縦位置
	static constexpr int SUB_POS_Y  = (50 + SIZE_Y); // サブ画像縦位置


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	Pause(void); // デフォルトコンストラクタ

	~Pause(); // デストラクタ

	// 初期化処理(最初の1回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム処理)
	void Update(void);

	// 描画処理(毎フレーム処理)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);


	/* --- <<< セッター処理 >>> --- */

	// 一時停止フラグ 割り当て
	void SetIsActive(bool isActive);

	/* --- <<< ゲッター処理 >>> --- */

	// 一時停止フラグ 取得
	bool GetIsActive(void);


private:

	/* --- <<< 変数定義 >>> --- */

	int image_[(int)IMAGE::MAX]; // 画像ハンドル
	int isActive_;				 // 一時停止フラグ
	KeyTrigger pauseKey_;		 // 一時停止入力キー
};
