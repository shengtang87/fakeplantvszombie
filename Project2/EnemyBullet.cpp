#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "EnemyBullet.hpp"
#include "Turret.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

class Turret;

EnemyBullet::EnemyBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent) :
	Bullet1("play/bullet-12.png", 500, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}

void EnemyBullet::OnExplode2(Turret* turret) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), turret->Position.x, turret->Position.y));
}