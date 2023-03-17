#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "Fkoff.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"	
const int Fkoff::Price = 0;
Fkoff::Fkoff(float x, float y) :
	Turret("play/bomb.png", x, y, 53, Price, 0.5, 0) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Fkoff::CreateBullet() {
}
