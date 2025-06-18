/* --------------
　ゲーム終了処理
 ---------------- */
#include "GameExit.h"
#include "SceneManager.h"
#include <DxLib.h>


/*　デフォルトコンストラクタ　*/
GameExit::GameExit(void)
{
	select_ = SELECT::NO; // 終了確認状態

	mainImage_ = -1; // メインテキスト画像

	/*　各選択画像　*/
	for (int i = 0; i < static_cast<int>(SELECT::MAX); i++)
	{
		selectImage_[i] = -1;
	}
	isEnd_			= false; // ゲーム終了 有効化フラグ
	isSelectActive_ = false; // 終了選択 有効化フラグ
}

/*　デストラクタ　*/
GameExit::~GameExit(void)
{
	// メインテキスト画像 解放
	DeleteGraph(mainImage_);

	/*　各選択画像 解放　*/
	for (int i = 0; i < static_cast<int>(SELECT::MAX); i++)
	{
		DeleteGraph(selectImage_[i]);
	}
}

/*　初期化処理　*/
void GameExit::Init(void)
{
	// メイン画像 読み込み
	mainImage_ = LoadGraph("Image/ExitGame.png");

	// 各選択画像 読み込み
	LoadDivGraph("Image/ExitSelect.png",
				  static_cast<int>(SELECT::MAX),
				  1, static_cast<int>(SELECT::MAX),
				  SELECT_SIZE_X, SELECT_SIZE_Y,
				  selectImage_);

	select_ = SELECT::NO;	 // 終了無効 状態化
	isEnd_	= false;		 // 終了無効化
	isSelectActive_ = false; // 終了画面 無効化

	/*　各入力キー 初期化　*/
	enterKey_.Init(KEY_INPUT_RETURN);
	escapeKey_.Init(KEY_INPUT_ESCAPE);
	aKey_.Init(KEY_INPUT_A);
	dKey_.Init(KEY_INPUT_D);
	leftKey_.Init(KEY_INPUT_LEFT);
	rightKey_.Init(KEY_INPUT_RIGHT);
}

/*　更新処理　*/
void GameExit::Update(void)
{
	escapeKey_.Update(); // Escapeキー入力 更新

	if(!isSelectActive_)
	{
		if (escapeKey_.GetInputKeyDown())
		{
			isSelectActive_ = true; // 終了確認画面 有効化
			select_ = SELECT::NO;	// 終了無効 状態化
		}
	}
	else
	{
		/*　各選択キー 更新処理　*/
		enterKey_.Update();
		leftKey_.Update();
		rightKey_.Update();
		aKey_.Update();
		dKey_.Update();

		/*　選択状態 遷移処理　*/
		if (leftKey_.GetInputKeyDown() || aKey_.GetInputKeyDown() ||
			rightKey_.GetInputKeyDown() || dKey_.GetInputKeyDown())
		{
			if (select_ == SELECT::YES)
			{
				select_ = SELECT::NO; // 終了状態無効 状態化
			}
			else if (select_ == SELECT::NO)
			{
				select_ = SELECT::YES; // ゲーム終了 状態化
			}
		}

		/*　ゲーム終了処理　*/
		if (select_ == SELECT::YES && enterKey_.GetInputKeyDown())
		{
			isEnd_ = true;
		}

		/*　終了確認画面 無効化　*/
		else if (select_ == SELECT::NO && enterKey_.GetInputKeyDown() ||
			escapeKey_.GetInputKeyDown())
		{
			isSelectActive_ = false;
		}
	}
}

void GameExit::Draw(void)
{
	if (isSelectActive_)
	{
		/*　背景 半透明描画　*/
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, BACK_ALPHA);
		DrawBox(BACK_POS_X, BACK_POS_Y, (BACK_POS_X + BACK_SIZE_X), (BACK_POS_Y + BACK_SIZE_Y), BACK_COLOR, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// タイトル画像
		DrawGraph(MAIN_POS_X, MAIN_POS_Y, mainImage_, true);

		/*　選択画像位置 割り当て　*/
		int yesX = ((SceneManager::SCREEN_SIZE_X / 2) - SELECT_SIZE_X - SELECT_POS_WID);
		int noX = ((SceneManager::SCREEN_SIZE_X / 2) + SELECT_POS_WID);

		// テキスト表示
		DrawString((SceneManager::SCREEN_SIZE_X / 2) - (GetDrawStringWidth("P U S H  to  E N T E R", 22) / 2),
				   (SceneManager::SCREEN_SIZE_Y / 2),
					"P U S H  to  E N T E R",0xAA0000);

		if (select_ == SELECT::YES)
		{
			// "YES"選択 通常描画
			DrawGraph(yesX, SELECT_POS_Y, selectImage_[static_cast<int>(SELECT::YES)], true);

			/* "NO"選択 半透明描画　*/
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, SELECT_ALPHA);
			DrawGraph(noX, SELECT_POS_Y, selectImage_[static_cast<int>(SELECT::NO)], true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		if (select_ == SELECT::NO)
		{
			// "NO"選択 通常描画
			DrawGraph(noX, SELECT_POS_Y, selectImage_[static_cast<int>(SELECT::NO)], true);

			/* "YES"選択 半透明描画　*/
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, SELECT_ALPHA);
			DrawGraph(yesX, SELECT_POS_Y, selectImage_[static_cast<int>(SELECT::YES)], true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

/*　解放処理　*/
void GameExit::Release(void)
{
	/*　各選択画像 解放　*/
	for (int i = 0; i < static_cast<int>(SELECT::MAX); i++)
	{
		DeleteGraph(selectImage_[i]);
	}

	// メインテキスト画像 解放
	DeleteGraph(mainImage_);
}


/* --- <<< ゲッター処理 >>> --- */

/*　終了確認画面有効判定 取得 　*/
bool GameExit::GetIsSelectActive(void)
{
	return isSelectActive_;
}

/*　ゲーム終了判定 取得　*/
bool GameExit::GetIsEnd(void)
{
	return isEnd_;
}
