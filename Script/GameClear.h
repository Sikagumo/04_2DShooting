/* -----------------
　ゲームクリアデータ
 -------------------- */
#pragma once

#include "SceneData.h"
#include "KeyTrigger.h"

class GameClear
{
public:

	/* --- <<< 定数定義 >>> --- */

	static constexpr int SIZE_X = 640; // 横サイズ
	static constexpr int SIZE_Y = 480; // 縦サイズ


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// デフォルトコンストラクタ
	GameClear(void);

	// デストラクタ
	~GameClear(void);


	// 初期化処理(最初の１回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム処理)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);


	/* --- <<< ゲッター処理 >>> --- */

	// 次のシーン状態 取得
	SCENE_TYPE GetNextScene(void);

private:

	/* --- <<< 変数定義 >>> --- */
	
	int image_; // 画像

	KeyTrigger spaceKey_;  // 入力キー
	SCENE_TYPE nextScene_; // 次のシーン状態
};