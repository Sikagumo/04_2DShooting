/* -----------------
　ゲームオーバー処理
 ------------------- */
#include "GameOverScene.h"
#include <DxLib.h>


/*　デフォルトコンストラクタ　*/
GameOver::GameOver(void)
{
	// ゲームオーバー画像
	image_ = -1;

	// 次シーン状態
	nextScene_ = SCENE_TYPE::GAME_OVER;
}

/*　デストラクタ　*/
GameOver::~GameOver(void)
{
	// ゲームオーバー画像 解放処理
	DeleteGraph(image_);
}


/*　初期化処理　*/
void GameOver::Init(void)
{
	// 画像割り当て
	image_ = LoadGraph("Image/Gameover.png");

	// 次のシーン状態 初期化
	nextScene_ = SCENE_TYPE::GAME_OVER;

	// 入力キー初期化
	spaceKey_.Init(KEY_INPUT_SPACE);
}

/*　更新処理　*/
void GameOver::Update(void)
{
	spaceKey_.Update(); // キー入力更新

	/*　キー入力でタイトルに遷移　*/
	if (spaceKey_.GetInputKeyDown() == true)
	{
		nextScene_ = SCENE_TYPE::TITLE;
	}
}

/*　描画処理　*/
void GameOver::Draw(void)
{
	// ゲームオーバー画像 描画
	DrawGraph(0, 0, image_, true);
}

/*　解放処理　*/
void GameOver::Release(void) 
{
	// ゲームオーバー画像 解放処理
	DeleteGraph(image_);
}


/* --- <<< ゲッター処理 >>> --- */

/*　次のシーン状態 取得　*/
SCENE_TYPE GameOver::GetNextScene(void)
{
	return nextScene_;
}
