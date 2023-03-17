#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "BlockTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"	
const int BlockTurret::Price = 30;
BlockTurret::BlockTurret(float x, float y) :
	Turret("play/turret-4.png", x, y, 10, Price, 0.5, 20) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void BlockTurret::CreateBullet() {
}
