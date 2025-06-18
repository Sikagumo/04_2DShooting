/* -----------
　シーンデータ
 ------------- */

#pragma once

// 画面の種類
enum class SCENE_TYPE
{
	NONE	   = 0,
	TITLE	   = 1, // タイトル
	GAME	   = 2, // ゲームプレイ
	GAME_OVER  = 3, // ゲームオーバー
	GAME_CLEAR = 4  // ゲームクリア
};