#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <utility>
#include <string>
#include <vector>

#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "EnemyBullet.hpp"
#include "ExplosionEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "LOG.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"
#include "Collider.hpp"

PlayScene* Enemy::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Enemy::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
}
Enemy::Enemy(std::string img, float x, float y, float radius, float speed, float coolDown, float hp, int money) :
	Engine::Sprite(img, x, y), speed(speed), coolDown(coolDown), hp(hp), money(money) {
	CollisionRadius = radius;
	reachEndTime = 0;
	slowed = false;
	Velocity = Engine::Point(speed , 0);
	target = Engine::Point(PlayScene::EndGridPointx , static_cast<int>(floor(Position.y / PlayScene::BlockSize))) * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
}
void Enemy::Hit(float damage) {
	hp -= damage;
	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		getPlayScene()->EarnMoney(money);
		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}
	
void Enemy::Update(float deltaTime) {
	PlayScene* scene = getPlayScene();
	float remainSpeed = speed * deltaTime;
	if (slowed == true) {
		if (money == 30 && hp < 15) {
			Position.x -= Velocity.x * deltaTime * 2;
			Position.y += Velocity.y * deltaTime * 2;
		}
		else if (money == 1000 && Position.x <= 1280) {
			Position.x = 1280;
			scene->gogogo = true;
		}
		else{
			Position.x -= Velocity.x * deltaTime/2;
			Position.y += Velocity.y * deltaTime/2;
		}
	}
	else if(slowed == false){
		if (money == 30&&hp<15) {
			Position.x -= Velocity.x * deltaTime*2;
			Position.y += Velocity.y * deltaTime*2;
		}
		else if (money == 1000 && Position.x <= 1280) {
			Position.x = 1280;
			scene->gogogo = true;
		}
		else {
			Position.x -= Velocity.x * deltaTime;
			Position.y += Velocity.y * deltaTime;
		}
	}
	if(Position.x <= PlayScene::EndGridPointx * PlayScene::BlockSize + PlayScene::BlockSize / 2){
		getPlayScene()->Hit(hp);
		Hit(hp);
		reachEndTime = 0;
		return;
	}
	if (money == 1000&&scene->gogogo==true) {
		if (mf) {
			// Shoot reload.
			reload -= deltaTime;
			if (reload <= 0) {
				AudioHelper::PlaySample("laugh.mp3", false, 1, 0);
				std::cout << mf->GetPrice();
				mf->Hit(5000);
				//mf = nullptr;
				reload = coolDown;
			}
		}
		if (!mf) {
			for (auto& it : scene->TowerGroup->GetObjects()) {
				int rnd = rand() % 6;
				if (rnd == 1) {
					mf = dynamic_cast<Turret*>(it);
					mf->lockedEnemy.push_back(this);
					lockedEnemyIterator = std::prev(mf->lockedEnemy.end());
				}
				//break;
			}
		}
		for (auto& it : scene->TowerGroup->GetObjects()) {
			Turret* t;
			t = dynamic_cast<Turret*>(it);
			if (Engine::Collider::IsCircleOverlap(Position, 500, t->Position, t->CollisionRadius))
				t->Hit(t->GetHp());
		}
	}
	else if (money != 1000) {
		if (mf) {
			Velocity.x = 0;
			if (mf->Position.x > Position.x && mf->Position.y >= Position.y && mf->Position.y < Position.y + scene->BlockSize) {
				mf->lockedEnemy.erase(lockedEnemyIterator);
				mf = nullptr;
				lockedEnemyIterator = std::list<Enemy*>::iterator();
			}
			// Shoot reload.
			reload -= deltaTime;
			if (reload <= 0) {
				// shoot.
				reload = coolDown;
				CreateBullet();
			}
		}
		if (!mf) {
			Velocity.x = speed;
			for (auto& it : scene->TowerGroup->GetObjects()) {
				if (Position.x - it->Position.x < 100 && it->Position.x < Position.x && it->Position.y >= Position.y && it->Position.y < Position.y + scene->BlockSize) {
					mf = dynamic_cast<Turret*>(it);
					mf->lockedEnemy.push_back(this);
					lockedEnemyIterator = std::prev(mf->lockedEnemy.end());
					break;
				}
			}
		}
	}

	Engine::Point vec = target - Position;
	reachEndTime = (vec.Magnitude() - remainSpeed) / speed;
}
void Enemy::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}

void Enemy::CreateBullet() {
	Engine::Point diff = Engine::Point(-1, 0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new EnemyBullet(Position, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
