/* ----------------------
　シーンマネージャー処理
 ------------------------ */

#include "SceneManager.h"
#include <DxLib.h>


/*　デフォルトコンストラクタ　*/
SceneManager::SceneManager(void)
{
	sceneType_ = SCENE_TYPE::TITLE; // 現在シーン状態
}

/*　デストラクタ　*/
SceneManager::~SceneManager(void)
{

}


/* --- <<< 処理系 >>> --- */

/*　ゲーム処理　*/
void SceneManager::Run(void)
{
	//ゲームループ
	while (ProcessMessage() == 0 && gameExit_.GetIsEnd() == false)
	{
		frameRate_.Update(); // フレームレート更新

		/*　フレームレート制限　*/
		if (frameRate_.GetLimitFrameRate() == false)
		{
			// フレームレート 割り当て
			frameRate_.SetFrameRate();

			//更新
			Update();

			//描画
			Draw();
		}
	}
}

/*　初期化処理　*/
void SceneManager::Init(void)
{
	/*　システム系初期化　*/
	SetWindowText("前期の初期シューティング");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 画面解像度
	ChangeWindowMode(true);		// true == ウィンドウ、false == フルスクリーン

	SetWaitVSyncFlag(0); // 垂直同期 無効化

	if (DxLib_Init() == -1)		// DXLIB使うときはこの後から
	{
		OutputDebugString("DxLibが初期化されていません\n");
		return;
	}


	// シーンタイプをタイトルに変更
	ChangeScene(SCENE_TYPE::TITLE);

	gameExit_.Init(); // ゲーム終了処理 初期化
}

/*　更新処理　*/
void SceneManager::Update(void)
{
	gameExit_.Update(); // ゲーム終了確認 更新

	/*　ゲーム終了確認状態 無効時処理　*/
	if (gameExit_.GetIsSelectActive() == false)
	{
		// 現在シーン状態
		SCENE_TYPE nextSceneType = sceneType_;

		switch (sceneType_)
		{

		case SCENE_TYPE::TITLE:
			// タイトルシーン 更新
			title_.Update();

			// 次のシーン遷移情報 取得
			nextSceneType = title_.GetNextScene();
			break;


		case SCENE_TYPE::GAME:
			// ゲームシーン 更新
			game_.Update();

			// 次のシーン遷移情報 取得
			nextSceneType = game_.GetNextScene();
			break;


		case SCENE_TYPE::GAME_OVER:
			// ゲームオーバーシーン 更新
			gameOver_.Update();

			// 次のシーン遷移情報 取得
			nextSceneType = gameOver_.GetNextScene();
			break;


		case SCENE_TYPE::GAME_CLEAR:
			// ゲームクリアシーン 更新
			gameClear_.Update();

			// 次のシーン遷移情報 取得
			nextSceneType = gameClear_.GetNextScene();
		}

		// シーン状態 遷移処理
		if (sceneType_ != nextSceneType)
		{
			ChangeScene(nextSceneType);
		}
	}
}

/*　描画処理　*/
void SceneManager::Draw(void)
{
	//描画先をバックバッファにする
	SetDrawScreen(DX_SCREEN_BACK);

	//描画先をクリア
	ClsDrawScreen();

	switch (sceneType_)
	{
	case SCENE_TYPE::TITLE:
		//タイトルシーン 描画
		title_.Draw();
		break;


	case SCENE_TYPE::GAME:
		//ゲームシーン 描画
		game_.Draw();
		break;


	case SCENE_TYPE::GAME_OVER:
		// ゲームオーバーシーン 描画
		gameOver_.Draw();
		break;


	case SCENE_TYPE::GAME_CLEAR:
		// ゲームクリアシーン 描画
		gameClear_.Draw();
		break;
	}

	frameRate_.Draw(); // フレームレート描画
	gameExit_.Draw();  // 終了処理 描画

	//バックバッファとフロントバッファの入れ替え[
	ScreenFlip();
}

/*　解放処理　*/
void SceneManager::Release(void)
{
	// 終了状態 解放
	gameExit_.Release();

	// タイトルシーン 解放
	title_.Release();

	// ゲームシーン 解放
	game_.Release();

	// ゲームオーバーシーン 解放
	gameOver_.Release();

	// ゲームクリアシーン 解放
	gameClear_.Release();

	// 終了処理
	DxLib_End();
}

/*　シーン遷移処理　*/
void SceneManager::ChangeScene(SCENE_TYPE type)
{
	// シーンIDを変更
	sceneType_ = type;

	/*　シーン遷移時に各シーン初期化　*/
	switch (sceneType_)
	{
	case SCENE_TYPE::TITLE:
		// タイトルシーン 初期化
		title_.Init();
		break;

	case SCENE_TYPE::GAME:
		// ゲームシーン 初期化
		game_.Init();
		break;

	case SCENE_TYPE::GAME_OVER:
		// ゲームオーバーシーン 初期化
		gameOver_.Init();
		break;

	case SCENE_TYPE::GAME_CLEAR:
		// ゲームクリアシーン初期化
		gameClear_.Init();
		break;
	}
}