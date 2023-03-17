#include <allegro5/base.h>
#include <cmath>
#include <string>
#include <cmath>
#include <random>
#include <utility>
#include <string>
#include <vector>
#include "AudioHelper.hpp"
#include "Group.hpp"
#include "BombTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include "ExplosionEffect.hpp"
#include "DirtyEffect.hpp"
#include "Collider.hpp"
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>

const int BombTurret::Price = 100;
BombTurret::BombTurret(float x, float y) :
	Turret("play/turret-5.png", x, y, 10, Price, 0.5, 1) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void BombTurret::CreateBullet() {
}
void BombTurret::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
	for (auto& it : getPlayScene()->EnemyGroup->GetObjects()) {
		Enemy* enemy = dynamic_cast<Enemy*>(it);
		if (Engine::Collider::IsCircleOverlap(Position, 200, enemy->Position, enemy->CollisionRadius))
			enemy->Hit(150);
	}
}


