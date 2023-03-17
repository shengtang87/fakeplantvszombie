#ifndef ENEMYBULLET_HPP
#define ENEMYBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
	struct Point;
}  // namespace Engine

class EnemyBullet : public Bullet1 {
public:
	explicit EnemyBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	void OnExplode2(Turret* turret) override;
};
#endif // ENEMYBULLET_HPP
