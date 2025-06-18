/* ---------------
　ゲームクリア処理
 ----------------- */

#include "GameClear.h"
#include <DxLib.h>


/*　デフォルトコンストラクタ　*/
GameClear::GameClear(void)
{
	// ゲームクリア画像
	image_ = -1;

	// 次のシーン状態
	nextScene_ = SCENE_TYPE::GAME_CLEAR;
}

/*　デストラクタ　*/
GameClear::~GameClear(void)
{
	// ゲームクリア画像 解放
	DeleteGraph(image_);
}


/* --- <<< 処理系 >>> --- */

/*　初期化処理　*/
void GameClear::Init(void)
{
	// 画像割り当て
	image_ = LoadGraph("Image/GameClear.png");

	// 次のシーン状態 初期化
	nextScene_ = SCENE_TYPE::GAME_CLEAR;

	// 入力キー初期化
	spaceKey_.Init(KEY_INPUT_SPACE);
}

/*　更新処理　*/
void GameClear::Update(void) 
{
	spaceKey_.Update(); // キー入力更新

	/*　Spaceキーでタイトルに遷移　*/
	if (spaceKey_.GetInputKeyDown() == true)
	{
		nextScene_ = SCENE_TYPE::TITLE;
	}
}

/*　描画処理　*/
void GameClear::Draw(void)
{
	// ゲームクリア画像 描画
	DrawGraph(0, 0, image_, true);
}

/*　解放処理　*/
void GameClear::Release(void)
{
	// ゲームクリア画像 解放
	DeleteGraph(image_);
}


/* --- <<< ゲッター処理 >>> --- */

/*　次のシーン状態 取得　*/
SCENE_TYPE GameClear::GetNextScene(void)
{
	return nextScene_;
}