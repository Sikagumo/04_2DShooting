/* ------------
　一時停止処理
 -------------- */

#include "Pause.h"
#include "SceneManager.h"
#include <DxLib.h>


/*　デフォルトコンストラクタ　*/
Pause::Pause(void)
{
	for (int i = 0; i < (int)IMAGE::MAX; i++)
	{
		image_[i] = -1; // 各 停止画像
	}
	isActive_ = false; // 停止有効フラグ
}

/*　デストラクタ　*/
Pause::~Pause(void)
{
	/*　各停止画像 解放処理　*/
	for (int i = 0; i < (int)IMAGE::MAX; i++)
	{
		DeleteGraph(image_[i]);
	}
}


/* --- <<< 処理系 >>> --- */

/*　初期化処理　*/
void Pause::Init(void)
{
	// 各停止画像 読み込み
	LoadDivGraph("Image/Pause.png",
				(int)IMAGE::MAX, 1, (int)IMAGE::MAX,
				 SIZE_X, SIZE_Y,
				 image_);

	// 一時停止キー入力 割り当て
	pauseKey_.Init(KEY_INPUT_P);
}

/*　更新処理　*/
void Pause::Update(void)
{
	pauseKey_.Update(); //一時停止キー入力 更新


	if (pauseKey_.GetInputKeyDown())
	{
		if (!isActive_)
		{
			isActive_ = true; // 一時停止 有効化
		}
		else
		{
			isActive_ = false; // 一時停止 無効化
		}
	}
}

/*　描画処理　*/
void Pause::Draw(void)
{
	/*　画像位置　*/
	int imageX = (SceneManager::SCREEN_SIZE_X / 2) - (SIZE_X / 2);
	int imageY = (SceneManager::SCREEN_SIZE_Y / 2);

	if (isActive_) 
	{
		// メインラベル 描画
		DrawGraph(imageX, imageY - MAIN_POS_Y, image_[(int)IMAGE::MAIN], true);

		// サブラベル 描画
		DrawGraph(imageX, imageY + SUB_POS_Y, image_[(int)IMAGE::SUB], true);
	}
}

/*　画像解放処理　*/
void Pause::Release(void) 
{
	/*　各停止画像 解放　*/
	for (int i = 0; i < (int)IMAGE::MAX; i++)
	{
		DeleteGraph(image_[i]);
	}
}


/* --- <<< セッター処理 >>> --- */

/*　一時停止フラグ 割り当て　*/
void Pause::SetIsActive(bool isActive)
{
	isActive_ = isActive;
}


/* --- <<< ゲッター処理 >>> --- */

/*　一時停止フラグ 取得　*/
bool Pause::GetIsActive(void)
{
	return isActive_;
}