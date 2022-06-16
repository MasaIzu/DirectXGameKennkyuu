#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>
#include "DebugCamera.h"
#include "Vector3.h"
#include "myVector3.h"



/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	DirectX::XMFLOAT3 vertices[8];
	Mesh* mesh_ = nullptr;
	Mesh::VertexPosNormalUv vertexPosNormalUv_;
	// 頂点データ配列
	std::vector<Mesh::VertexPosNormalUv> vertices_;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	//カメラ上方向の角度
	float viewAngle = 0.0f;

	float x[8] = {};
	float y[8] = {};
	float z[8] = {};

	//ベクトルの正規化
	float normalize;

	myVector3 v;
	myVector3 normal1;
	myVector3 normal2;
	myVector3 normal3;
	myVector3 normal4;
	myVector3 normal5;
	myVector3 normal6;

	myVector3 vertex;


	myVector3 vertex1Normalize;
	myVector3 vertex2Normalize;
	myVector3 vertex3Normalize;
	myVector3 vertex4Normalize;
	myVector3 vertex5Normalize;
	myVector3 vertex6Normalize;
	myVector3 vertex7Normalize;
	myVector3 vertex8Normalize;

	Model* model_ = nullptr;
	myVector3* vector3_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};