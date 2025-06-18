/* -------------
　キー入力データ
 --------------- */
#pragma once

class KeyTrigger
{
public:

	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// デフォルトコンストラクタ
	KeyTrigger(void);

	// デストラクタ
	~KeyTrigger(void);

	// 初期化処理
	void Init(int keyType);

	// 更新処理
	void Update(void);


	/* --- <<< ゲッター処理 >>> --- */

	/*　キー入力 連続押下判定 取得　*/
	bool GetInputKey(void);

	/*　キー入力 押下判定 取得　*/
	bool GetInputKeyDown(void);

	/*　キー入力 解放判定 取得　*/
	bool GetInputKeyUp(void);


private:

	/* --- <<< 定数定義 >>> --- */

	int preKey_;  //  前 キー入力状態
	int curKey_;  // 現在キー入力状態
	int keyType_; // 入力キー種類
};