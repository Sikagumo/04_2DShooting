/* --------
　背景処理
 ---------- */

#include "SceneManager.h"
#include "BackGround.h"
#include <DxLib.h>


/*　デフォルトコンストラクタ　*/
BackGround::BackGround(void)
{
	image_ = -1; // 背景画像
	posY_  = 0;  // 縦位置
}

/*　デストラクタ　*/
BackGround::~BackGround(void)
{
	// 背景画像 解放
	DeleteGraph(image_);
}


/* --- <<< 処理系 >>> --- */

/*　初期化処理　*/
void BackGround::Init(void)
{
	// 背景画像 割り当て
	image_ = LoadGraph("Image/Haikei.png");

	// 位置初期化
	posY_ = -(SIZE_Y - SceneManager::SCREEN_SIZE_Y);
}

/*　更新処理　*/
void BackGround::Update(void)
{
	if (posY_ < SceneManager::SCREEN_SIZE_Y)
	{
		posY_ += MOVE_SPEED; // 背景移動
	}
	else
	{
		// 背景位置 初期化
		posY_ = -(SIZE_Y - SceneManager::SCREEN_SIZE_Y);
	}
}

/*　描画処理　*/
void BackGround::Draw(void)
{
	/*　背景描画　*/
	DrawGraph(0, posY_, image_, true);
	DrawGraph(0, (posY_ - SIZE_Y), image_, true);
}

/*　解放処理　*/
void BackGround::Release(void)
{
	// 背景画像 解放処理
	DeleteGraph(image_);
}