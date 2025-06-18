/* ------------------
　ゲームシーンデータ
 -------------------- */
#pragma once

#include "Pause.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "Shot.h"
#include "Blast.h"
#include "Boss.h"
#include "KeyTrigger.h"


class GameScene
{
public:

	/* --- <<< 列挙型定義 >>> --- */

	enum class ENEMY_PARAM
	{
		NONE		= 0,
		MOB_ACTIVE  = 1,
		BOSS_ACTIVE = 2,
	};


	/* --- <<< 定数定義 >>> --- */

	/*　ゲーム領域　*/
	static constexpr int GAME_AREA_X = 640;
	static constexpr int GAME_AREA_Y = (500 - 40);

	// ヒットストップ時間
	static constexpr int HIT_STOP = 88;

	// スロー最大カウント数
	static constexpr int SLOW_CONUT = (HIT_STOP - 23);

	// 振動終了時間
	static constexpr int SHAKE_STOP_COUNT = (HIT_STOP - 45);


	/* ヒットストップ時間内の 画面揺れの回数　*/
	static constexpr int SHAKE_COUNT_X = 8;
	static constexpr int SHAKE_COUNT_Y = 3;

	/*　振動の揺れ幅　*/
	static constexpr int SHAKE_WIDTH_X = 8;
	static constexpr int SHAKE_WIDTH_Y = 5;

	// 敵撃破数
	static constexpr int KILL_COUNT = 6;


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// デフォルトコンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	// 初期処理(最初の1回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);


	/* --- <<< ゲッター処理 >>> --- */

	// 次シーン状態 取得
	SCENE_TYPE GetNextScene(void);


private:

	/* --- <<< 変数定義 >>> --- */

	ENEMY_PARAM enemyParam_; // 敵出現状態

	// 次のシーン
	SCENE_TYPE nextGameScene_;

	BackGround backGround_; // 背景
	Pause pause_;			// 一時停止
	Player player_;			// プレイヤー
	Enemy enemy_;			// 敵
	Shot shot_;				// 弾
	Blast blast_;			// 爆発
	Boss boss_;				// ボス敵


	// ヒットストップ
	int hitStopCnt_;

	// 一時的描画領域
	int tempScreen_;

	/*　振動カウンタ　*/
	int shakeCounterX_;
	int shakeCounterY_;

	// 振動地点の座標
	Vector2 shakePos_;

	// 画面遅延カウンタ
	int slowCounter_;

	// 敵撃破数
	int enemyKillCounter_;


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// 当たり判定
	void Collision(void);

	//二つの当たり判定の衝突を判定する
	bool CheckCollisions(Vector2 pos1, int sizeX1, int sizeY1,
					   Vector2 pos2, int sizeX2, int sizeY2);

	// ヒットストップ処理
	void HitStop(void);

	// 衝突時の演出 有効化処理
	void HitPerform(void);

	// 敵状態 遷移処理
	void ChangeEnemyParam(ENEMY_PARAM param);

};