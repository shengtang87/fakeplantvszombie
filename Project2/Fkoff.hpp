#ifndef FKOFF_HPP
#define FKOFF_HPP
#include "Turret.hpp"

class Fkoff : public Turret {
public:
	static const int Price;
	Fkoff(float x, float y);
	void CreateBullet() override;
};
#endif // WBCELLTURRET_HPP
