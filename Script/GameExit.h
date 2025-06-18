/* --------------
　ゲーム終了処理
 ---------------- */
#pragma once
#include "KeyTrigger.h"

class GameExit
{
public:

	/* --- <<< 列挙型定義 >>> --- */

	/*　終了確認状態　*/
	enum class SELECT
	{
		YES = 0, // ゲーム終了
		NO  = 1, // 終了無効
		MAX = 2, // 要素数
	};


	/* --- <<< 定数定義 >>> --- */

	/*　メインテキスト画像　*/
	static constexpr int MAIN_SIZE_X = 446; // 横サイズ
	static constexpr int MAIN_SIZE_Y = 44;	// 縦サイズ
	static constexpr int MAIN_POS_X  = 100; // 横位置
	static constexpr int MAIN_POS_Y  = 100; // 横位置

	/*　選択画像　*/
	static constexpr int SELECT_SIZE_X	= 84;		   // 横サイズ
	static constexpr int SELECT_SIZE_Y	= (60 / 2);    // 縦サイズ
	static constexpr int SELECT_POS_WID	= 100;		   // 横位置(中央からの値)
	static constexpr int SELECT_POS_Y	= 320;		   // 縦位置
	static constexpr int SELECT_ALPHA	= (255 - 155); // 非選択時の透明度

	/*　背景系　*/
	static constexpr int BACK_SIZE_X = 550;		   // 横サイズ
	static constexpr int BACK_SIZE_Y = 400;		   // 縦サイズ
	static constexpr int BACK_POS_X	 = 50;		   // 横位置
	static constexpr int BACK_POS_Y	 = 50;		   // 縦位置
	static constexpr int BACK_COLOR	 = 0xDDDDDD;   // 背景色
	static constexpr int BACK_ALPHA  = (255 - 35); // 透明度


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// デフォルトコンストラクタ
	GameExit(void);

	// デストラクタ
	~GameExit(void);

	// 初期化処理(最初の１回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム処理)
	void Update(void);

	// 描画処理(毎フレーム処理)
	void Draw(void);

	// 解放処理(最後の1回のみ実行)
	void Release(void);


	/* --- <<< ゲッター処理 >>> --- */

	// キー入力判定
	bool GetIsSelectActive(void);

	// 終了判定 取得
	bool GetIsEnd(void);

private:

	/* --- <<< 変数定義 >>> --- */

	int mainImage_;		 // メインテキスト画像
	int selectImage_[2]; // 選択画像

	SELECT select_;		  // 終了確認状態
	bool isSelectActive_; // 終了確認画面有効化フラグ
	bool isEnd_;		  // ゲーム終了フラグ

	KeyTrigger escapeKey_; // ゲーム終了準備キー

	KeyTrigger enterKey_;  // 選択確定入力キー

	/*　各選択変更入力キー　*/
	KeyTrigger aKey_;
	KeyTrigger dKey_;
	KeyTrigger leftKey_;
	KeyTrigger rightKey_;
};
