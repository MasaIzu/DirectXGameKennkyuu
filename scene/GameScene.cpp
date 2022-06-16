#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	//デバイスの取得
	ID3D12Device* device_ = dxCommon_->GetDevice();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	//3Dモデルの生成
	model_ = Model::CreateFromOBJ("cube", false);


	//正面
	myVector3 v1(1.000000, 1.000000, 1.000000);//右上
	myVector3 v2(1.000000, -1.000000, 1.000000);//右下
	myVector3 v3(-1.000000, 1.000000, 1.000000);//左上
	myVector3 v4(-1.000000, -1.000000, 1.000000);//左下

	//後方
	myVector3 v5(1.000000, 1.000000, -1.000000);//右上
	myVector3 v6(1.000000, -1.000000, -1.000000);//右下
	myVector3 v7(-1.000000, 1.000000, -1.000000);//左上
	myVector3 v8(-1.000000, -1.000000, -1.000000);//左下



	normal1 = vector3_->faceNormal(v1, v2, v3);//正面
	normal2 = vector3_->faceNormal(v1, v2, v5);//右
	normal3 = vector3_->faceNormal(v7, v3, v5);//上
	normal4 = vector3_->faceNormal(v4, v3, v8);//左
	normal5 = vector3_->faceNormal(v7, v8, v5);//裏
	normal6 = vector3_->faceNormal(v8, v6, v4);//下

#pragma region 正面

	//正面右上頂点
	vertex = vector3_->vertexNormal(normal1, normal2, normal3);
	normalize = std::sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z);
	vertex1Normalize.x = vertex.x / normalize;
	vertex1Normalize.y = vertex.y / normalize;
	vertex1Normalize.z = vertex.z / normalize;

	//正面右下頂点
	vertex = vector3_->vertexNormal(normal1, normal2, normal6);
	normalize = std::sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z);
	vertex2Normalize.x = vertex.x / normalize;
	vertex2Normalize.y = vertex.y / normalize;
	vertex2Normalize.z = vertex.z / normalize;

	//正面左上頂点
	vertex = vector3_->vertexNormal(normal1, normal4, normal3);
	normalize = std::sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z);
	vertex3Normalize.x = vertex.x / normalize;
	vertex3Normalize.y = vertex.y / normalize;
	vertex3Normalize.z = vertex.z / normalize;

	//正面左下頂点
	vertex = vector3_->vertexNormal(normal1, normal4, normal6);
	normalize = std::sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z);
	vertex4Normalize.x = vertex.x / normalize;
	vertex4Normalize.y = vertex.y / normalize;
	vertex4Normalize.z = vertex.z / normalize;

#pragma endregion

#pragma region 裏面

	//正面右上頂点
	vertex = vector3_->vertexNormal(normal5, normal2, normal3);
	normalize = std::sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z);
	vertex5Normalize.x = vertex.x / normalize;
	vertex5Normalize.y = vertex.y / normalize;
	vertex5Normalize.z = vertex.z / normalize;

	//正面右下頂点
	vertex = vector3_->vertexNormal(normal5, normal2, normal6);
	normalize = std::sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z);
	vertex6Normalize.x = vertex.x / normalize;
	vertex6Normalize.y = vertex.y / normalize;
	vertex6Normalize.z = vertex.z / normalize;

	//正面左上頂点
	vertex = vector3_->vertexNormal(normal5, normal4, normal3);
	normalize = std::sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z);
	vertex7Normalize.x = vertex.x / normalize;
	vertex7Normalize.y = vertex.y / normalize;
	vertex7Normalize.z = vertex.z / normalize;

	//正面左下頂点
	vertex = vector3_->vertexNormal(normal5, normal4, normal6);
	normalize = std::sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z);
	vertex8Normalize.x = vertex.x / normalize;
	vertex8Normalize.y = vertex.y / normalize;
	vertex8Normalize.z = vertex.z / normalize;

#pragma endregion

}

void GameScene::Update() {
	debugCamera_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>


	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	//面法線
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(normal1.x, normal1.y, normal1.z), Vector4(0, 255, 255, 100));//正面
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(normal2.x, normal2.y, normal2.z), Vector4(0, 255, 255, 100));//右
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(normal3.x, normal3.y, normal3.z), Vector4(0, 255, 255, 100));//上
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(normal4.x, normal4.y, normal4.z), Vector4(0, 255, 255, 100));//左
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(normal5.x, normal5.y, normal5.z), Vector4(0, 255, 255, 100));//裏
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(normal6.x, normal6.y, normal6.z), Vector4(0, 255, 255, 100));//下

	//正面頂点法線
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(vertex1Normalize.x * 4, vertex1Normalize.y * 4, vertex1Normalize.z * 4), Vector4(200, 0, 0, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(vertex2Normalize.x * 4, vertex2Normalize.y * 4, vertex2Normalize.z * 4), Vector4(200, 0, 0, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(vertex3Normalize.x * 4, vertex3Normalize.y * 4, vertex3Normalize.z * 4), Vector4(200, 0, 0, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(vertex4Normalize.x * 4, vertex4Normalize.y * 4, vertex4Normalize.z * 4), Vector4(200, 0, 0, 100));

	//裏面頂点法線
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(vertex5Normalize.x * 4, vertex5Normalize.y * 4, vertex5Normalize.z * 4), Vector4(200, 0, 0, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(vertex6Normalize.x * 4, vertex6Normalize.y * 4, vertex6Normalize.z * 4), Vector4(200, 0, 0, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(vertex7Normalize.x * 4, vertex7Normalize.y * 4, vertex7Normalize.z * 4), Vector4(200, 0, 0, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(vertex8Normalize.x * 4, vertex8Normalize.y * 4, vertex8Normalize.z * 4), Vector4(200, 0, 0, 100));

}