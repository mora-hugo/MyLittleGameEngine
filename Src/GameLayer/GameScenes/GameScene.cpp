#include "GameScenes/GameScene.h"

HC::GameScene::GameScene(const char* name) : Scene(name) {

}

HC::GameScene::~GameScene() {

}

void HC::GameScene::BeginPlay() {
    Scene::BeginPlay();
}

void HC::GameScene::Update(float deltaTime) {
    Scene::Update(deltaTime);
}

void HC::GameScene::Draw() {
    Scene::Draw();
}

void HC::GameScene::EndPlay() {
    Scene::EndPlay();
}
