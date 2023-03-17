#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <allegro5/base.h>
#include <list>
#include <vector>
#include <string>

#include "Point.hpp"
#include "Sprite.hpp"
#include "IceCreamBullet.hpp"
class Bullet;
class Turret;
class PlayScene;

class Enemy : public Engine::Sprite {
protected:
	Engine::Point target;
	float speed;
	float coolDown;
	float hp;
	int money;
	bool slowed;
	float reload = 0;
    std::list<Enemy*>::iterator lockedEnemyIterator;
	PlayScene* getPlayScene();
	virtual void OnExplode();
	virtual void CreateBullet();
public:
	float reachEndTime;
	Turret* mf = nullptr;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, float x, float y, float radius, float speed, float coolDown, float hp, int money );
 	void Hit(float damage);
	void Update(float deltaTime) override;
	void Draw() const override;
	friend IceCreamBullet;
};
#endif // ENEMY_HPP
