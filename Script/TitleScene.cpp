/* -----------
　タイトル処理
 ------------- */

#include "SceneData.h"
#include "TitleScene.h"
#include <DxLib.h>


/*　デフォルトコンストラクタ　*/
TitleScene::TitleScene(void)
{
	image_ = -1; // タイトル画像

	// 次シーン状態
	nextScene_ = SCENE_TYPE::TITLE;
}

/*　デストラクタ　*/
TitleScene::~TitleScene(void)
{

}


/* --- <<< 処理系 >>> --- */

/*　初期化処理　*/
void TitleScene::Init(void) 
{
	// 次シーン 初期化
	nextScene_ = SCENE_TYPE::TITLE;

	// タイトル画面 読み込み
	image_ = LoadGraph("image/Title.png");

	// 開始キー入力 初期化
	spaceKey_.Init(KEY_INPUT_SPACE);
}

/*　更新処理　*/
void TitleScene::Update(void)
{
	spaceKey_.Update(); // 開始キー入力 更新

	/*　開始キー入力時 ゲームシーン遷移　*/
	if (spaceKey_.GetInputKeyDown() == true)
	{
		nextScene_ = SCENE_TYPE::GAME;
	}
}

/*　描画処理　*/
void TitleScene::Draw(void)
{
	//タイトル画像 描画
	DrawGraph(0, 0, image_, true);
}

/*　解放処理　*/
void TitleScene::Release(void)
{
	// タイトル画像 解放
	DeleteGraph(image_);
}


/* --- <<< ゲッター処理 >>> --- */

/*　次シーン状態 取得　*/
SCENE_TYPE TitleScene::GetNextScene(void)
{
	return nextScene_;
}
