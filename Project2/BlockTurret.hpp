#ifndef BLOCKTURRET_HPP
#define BLOCKTURRET_HPP
#include "Turret.hpp"

class BlockTurret : public Turret {
public:
	static const int Price;
	BlockTurret(float x, float y);
	void CreateBullet() override;
};
#endif // WBCELLTURRET_HPP
