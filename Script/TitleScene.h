/* -------------------
　タイトルシーンデータ
 --------------------- */

#pragma once
#include "SceneData.h"
#include "KeyTrigger.h"

class TitleScene
{
public:

	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// デフォルトコンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	// 初期化処理(最初の１回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);


	/* --- <<< ゲッター処理 >>> --- */

	//次のシーンの種類を取得
	SCENE_TYPE GetNextScene(void);


private:

	/* --- <<< 変数定義 >>> --- */

	int image_; //タイトル画像

	KeyTrigger spaceKey_; // タイトル遷移入力キー

	// 次シーン状態
	SCENE_TYPE nextScene_;
};