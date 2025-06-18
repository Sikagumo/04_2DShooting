#include <DxLib.h>
#include "SceneManager.h"

// 定数定義

#define SCREEN_SIZE_X 640			// 画面の横サイズ
#define SCREEN_SIZE_Y 480			// 画面の縦サイズ
#define BG_SIZE_Y 960				// 背景の縦サイズ
#define PLAYER_SIZE_X 32			// 自機の横サイズ
#define PLAYER_SIZE_Y 32			// 自機の縦サイズ
#define SHOT_SIZE_X 32				// 弾の横サイズ
#define SHOT_SIZE_Y 32				// 弾の縦サイズ
#define ENEMY_SIZE_X 64				// 敵の横サイズ
#define ENEMY_SIZE_Y 64				// 敵の縦サイズ

#define BLAST_SIZE_X 96				// 爆発画像サイズ
#define BLAST_SIZE_Y 96				// 爆発画像サイズ

// 変数定義

// プレイヤー関連
int playerImage;	// グラフィックハンドル
int playerPosX;		// X座標
int playerPosY;		// Y座標
int playerSpeed;	// 移動速度
bool playerAlive;	// 生存フラグ
int playerInvCnt;	// 無敵時間カウント

// 弾関連
int shotImage;		// グラフィックハンドル
int shotPosX;		// X座標
int shotPosY;		// Y座標
int shotSpeed;		// 移動速度
bool shotAlive;		// 生存フラグ(true:発射中・false:非発射中)
int shotKey;		// 弾を撃つキーの状態
int shotKeyOld;		// 弾を撃つキーの状態（１フレーム前の状態）

// 敵関連
int enemyImage;		// グラフィックハンドル
int enemyPosX;		// X座標
int enemyPosY;		// Y座標
int enemySpeed;		// 移動速度
bool enemyAlive;	// 生存フラグ

// 背景関連
int bgImage;		// グラフィックハンドル
int bgPosY1;		// １枚目の背景座標
int bgPosY2;		// ２枚目の背景座標
int gameoverImage;	// ゲームオーバー画面ハンドル
int timeupImage;	// タイムアップ画面ハンドル

// 画面遷移
enum class SCENE_ID
{
	NONE,
	TITLE,		// タイトル
	PLAY,		// ゲームプレイ
};
SCENE_ID sceneId;

// 爆発関連
int blastImage[21];			// グラフィックハンドル
bool blastAlive;			// フラグ
int blastCnt;				// カウント
int blastPosX;				// X座標
int blastPosY;				// Y座標

// 前方宣言
bool SysInit(void);
void GameLoop(void);
void GameInitialize(void);
void GameTitle(void);
void GamePlay(void);

int WINAPI WinMain(_In_ HINSTANCE hinstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//シーン管理
	SceneManager sceneManager;

	//初期化
	sceneManager.Init();

	//ゲーム起動
	sceneManager.Run();

	//解放
	sceneManager.Release();

	return 0;

}

void GameLoop(void)
{

	switch (sceneId)
	{
	case SCENE_ID::NONE:
		// ゲーム変数の初期化
		GameInitialize();
		break;
	case SCENE_ID::TITLE:
		// タイトル画面
		GameTitle();
		break;
	case SCENE_ID::PLAY:
		// ゲームプレイ画面
		GamePlay();
		break;
	}

}

bool SysInit(void)
{
	// ゲーム用初期化

	// グラフィックの登録
	playerImage = LoadGraph("Image/Player.png");
	if (playerImage == -1)
	{
		return false;
	}

	shotImage = LoadGraph("Image/Shot.png");
	if (shotImage == -1)
	{
		return false;
	}

	enemyImage = LoadGraph("Image/Enemy.png");
	if (enemyImage == -1)
	{
		return false;
	}

	bgImage = LoadGraph("Image/Haikei.png");
	if (bgImage == -1)
	{
		return false;
	}

	gameoverImage = LoadGraph("Image/Gameover.png");	// ゲームオーバー画面読み込み
	timeupImage = LoadGraph("Image/Timeup.png");		// タイムアップ画面読み込み

	// 爆発エフェクト読み込み
	LoadDivGraph("Image/Blast.png", 21, 6, 4, BLAST_SIZE_X, BLAST_SIZE_Y, blastImage, true);

	// 変数の初期化
	sceneId = SCENE_ID::NONE;

	return true;

}

void GameInitialize(void)
{

	// プレイヤー関連
	playerPosX = SCREEN_SIZE_X / 2 - PLAYER_SIZE_X / 2;
	playerPosY = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
	playerSpeed = 5;
	playerAlive = true;
	playerInvCnt = 0;

	// 弾関連
	shotPosX = playerPosX;
	shotPosY = playerPosY;
	shotSpeed = 10;
	shotAlive = false;
	shotKey = 0;
	shotKeyOld = 0;

	// 敵関連
	enemyPosX = SCREEN_SIZE_X / 2 - ENEMY_SIZE_X / 2;
	enemyPosY = 0;
	enemyAlive = true;
	enemySpeed = 3;

	// 背景関連
	bgPosY1 = 0;
	bgPosY2 = -BG_SIZE_Y;

	// 爆発エフェクト関連
	blastAlive = false;
	blastCnt = 0;
	blastPosX = 0;
	blastPosY = 0;

	sceneId = SCENE_ID::TITLE;

}

void GameTitle(void)
{

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		sceneId = SCENE_ID::PLAY;
	}

	SetDrawScreen(DX_SCREEN_BACK);			// 描画先をバックアップ
	ClsDrawScreen();						// 描画先をクリア
}

void GamePlay(void)
{

	// 背景スクロール処理
	bgPosY1 += 2;
	bgPosY2 += 2;
	if (bgPosY1 >= SCREEN_SIZE_Y)
	{
		bgPosY1 = bgPosY2 - BG_SIZE_Y;
	}
	if (bgPosY2 >= SCREEN_SIZE_Y)
	{
		bgPosY2 = bgPosY1 - BG_SIZE_Y;
	}

	// 再出現処理

	// プレイヤーの再出現処理
	if (playerAlive == false)
	{
		playerAlive = true;
		// 無敵時間
		playerInvCnt = 120;
	}

	if (playerInvCnt > 0)
	{
		playerInvCnt--;
	}

	// 弾の再出現処理
	shotKeyOld = shotKey;
	shotKey = CheckHitKey(KEY_INPUT_Z);
	if (shotKey && shotKeyOld == 0) // 発射判定
	{
		if (shotAlive == false)
		{
			shotPosX = playerPosX;
			shotPosY = playerPosY;
			shotAlive = true;
		}
	}

	// 敵の再出現処理
	if (enemyAlive == false)
	{
		int min = 0;
		int max = SCREEN_SIZE_X - ENEMY_SIZE_X;
		enemyPosX = min + GetRand(max - min);
		enemyPosY = -ENEMY_SIZE_Y;
		enemyAlive = true;
	}


	// 移動関係

	// プレイヤー移動操作
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		if (playerPosX - playerSpeed >= 0)
		{
			playerPosX -= playerSpeed;
		}
		else
		{
			playerPosX = 0;
		}
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		if (playerPosX + playerSpeed <= SCREEN_SIZE_X - PLAYER_SIZE_X)
		{
			playerPosX += playerSpeed;
		}
		else
		{
			playerPosX = SCREEN_SIZE_X - PLAYER_SIZE_X;
		}
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		if (playerPosY - playerSpeed >= 0)
		{
			playerPosY -= playerSpeed;
		}
		else
		{
			playerPosY = 0;
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (playerPosY + playerSpeed <= SCREEN_SIZE_Y - PLAYER_SIZE_Y)
		{
			playerPosY += playerSpeed;
		}
		else
		{
			playerPosY = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
		}
	}

	// 弾の移動処理
	if (shotAlive == true)
	{
		shotPosY -= shotSpeed;
	}

	// 敵の移動処理
	if (enemyAlive)
	{
		enemyPosY += enemySpeed;
	}

	// 座標判定関係

	// 弾のY座標判定
	if (shotPosY <= -SHOT_SIZE_Y)
	{
		shotAlive = false;
	}

	// 敵のY座標判定
	if (enemyPosY >= SCREEN_SIZE_Y)
	{
		enemyAlive = false;
	}


	// 当たり判定

	// プレイヤーと敵の当たり判定
	if (playerAlive && enemyAlive && playerInvCnt == 0)
	{
		int posX1 = enemyPosX;
		int posX2 = enemyPosX + ENEMY_SIZE_X;
		int posY1 = enemyPosY;
		int posY2 = enemyPosY + ENEMY_SIZE_Y;
		if (playerPosX < posX2 &&
			posX1 < playerPosX + PLAYER_SIZE_X &&
			playerPosY < posY2 &&
			posY1 < playerPosY + PLAYER_SIZE_Y)
		{
			playerAlive = false;
			enemyAlive = false;
		}
	}

	// 弾と敵の当たり判定
	if (shotAlive && enemyAlive)
	{
		int posX1 = enemyPosX;
		int posX2 = enemyPosX + ENEMY_SIZE_X;
		int posY1 = enemyPosY;
		int posY2 = enemyPosY + ENEMY_SIZE_Y;
		if (shotPosX < posX2 &&
			posX1 < shotPosX + SHOT_SIZE_X &&
			shotPosY < posY2 &&
			posY1 < shotPosY + SHOT_SIZE_Y)
		{
			shotAlive = false;
			enemyAlive = false;
			blastAlive = true;
			blastPosX = enemyPosX + (ENEMY_SIZE_X - BLAST_SIZE_X) / 2;
			blastPosY = enemyPosY + (ENEMY_SIZE_Y - BLAST_SIZE_Y) / 2;
		}
	}

	// 描画関連
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	// 背景の描画
	DrawGraph(0, bgPosY1, bgImage, true);
	// 背景の描画
	DrawGraph(0, bgPosY2, bgImage, true);

	// 敵
	if (enemyAlive)
	{
		DrawGraph(enemyPosX, enemyPosY, enemyImage, true);
	}

	// 弾
	if (shotAlive)
	{
		DrawGraph(shotPosX, shotPosY, shotImage, true);			// 弾の描画
	}

	// 爆発エフェクト
	if (blastAlive)
	{
		DrawGraph(blastPosX, blastPosY, blastImage[(blastCnt / 2) % 21], true);
		blastCnt++;
		if ((blastCnt / 2) % 21 + 1 == 21)
		{
			blastAlive = false;
			blastCnt = 0;
		}
	}

	// プレイヤー
	if (playerAlive)
	{
		// 半透明フラグ
		bool isTrans = false;
		if (playerInvCnt > 0)
		{
			if (playerInvCnt / 5 % 2 == 0)
			{
				isTrans = true;
			}
		}

		if (isTrans)
		{
			// 被ダメ時の自機の描画
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawGraph(playerPosX, playerPosY, playerImage, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
		{
			// 自機の描画
			DrawGraph(playerPosX, playerPosY, playerImage, true);
		}

	}

}
