#ifndef BULLET_HPP
#define BULLET_HPP
#include <string>

#include "Sprite.hpp"

class Enemy;
class PlayScene;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class Bullet : public Engine::Sprite {
protected:
	float speed;
	float damage;
	Engine::Sprite* parent;
	PlayScene* getPlayScene();
	virtual void OnExplode(Enemy* enemy);
	virtual void OnExplode2(Turret* turret);
public:
	Enemy* Target = nullptr;
	Turret* mf = nullptr;
	explicit Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation,Turret* parent);
	void Update(float deltaTime) override;
};


class Bullet1 : public Engine::Sprite {
protected:
	float speed;
	float damage;
	Engine::Sprite* parent;
	PlayScene* getPlayScene();
	virtual void OnExplode(Enemy* enemy);
	virtual void OnExplode2(Turret* turret);
public:
	Enemy* Target = nullptr;
	Turret* mf = nullptr;
	explicit Bullet1(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	void Update(float deltaTime) override;
};
#endif // BULLET_HPP
