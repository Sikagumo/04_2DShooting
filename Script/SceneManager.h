/* ------------------------
　シーンマネージャーデータ
 -------------------------- */

#pragma once

#include "FrameRate.h"
#include "KeyTrigger.h"
#include "SceneData.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "GameClear.h"
#include "GameExit.h"


class SceneManager
{
public:

	/* --- <<< 定数定義 >>> --- */

	static constexpr int SCREEN_SIZE_X = 640; //画面の横サイズ
	static constexpr int SCREEN_SIZE_Y = 500; //画面の縦サイズ


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// デフォルトコンストラクト
	SceneManager(void);

	// デストラクタ
	~SceneManager(void);

	// ゲーム起動
	void Run(void);

	// 初期処理(最初の1回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);

private:

	/* --- <<< 定数定義 >>> --- */

	// 現在のシーン
	SCENE_TYPE sceneType_;


	TitleScene title_;	  // タイトルシーン
	GameScene game_;	  // ゲームシーン
	GameOver gameOver_;	  // ゲームオーバーシーン
	GameClear gameClear_; // ゲームクリアシーン

	// フレームレート
	FrameRate frameRate_;

	GameExit gameExit_;


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// シーン遷移
	/// <summary>
	/// シーン遷移
	/// </summary>
	/// <param name="引数:シーン状態"></param>
	void ChangeScene(SCENE_TYPE type);
};