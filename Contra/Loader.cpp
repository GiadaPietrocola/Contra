#include "Loader.h"
#include "Bill.h"
#include "Block.h"
#include "Water.h"
#include "Bridge.h"
#include "Game.h"
#include "GameConfig.h"
#include "Sniper.h"
#include "HidingSniper.h"
#include "Soldier.h"
#include "Turret.h"
#include "Cannon.h"
#include "FlyingPowerUp.h"
#include "Elements.h"
#include "Explosion.h"
#include "TurretPowerUp.h"
#include "RepeaterCannon.h"
#include "Core.h"
#include <QBrush>

using namespace Contra;

Bill* Loader::load(int round)
{
	if (round == 0)
	{
		new Title();

		return nullptr;
	}
	else if (round == 1)
	{

		Game::instance()->world()->addPixmap(QPixmap(":/sprites/Jungle.png"));

		new FlashingElements();
		new Medals();

		new Block(QPointF(1.3 * TILE, 4.4 * TILE), 29.4 * TILE, 0.3 * TILE);

		new Block(QPointF(6.4 * TILE, 5.7 * TILE), 3.8 * TILE, 0.3 * TILE);
		new Block(QPointF(10.2 * TILE, 7.1 * TILE), 1.3 * TILE, 0.3 * TILE);
		new Block(QPointF(11.5 * TILE, 8.5 * TILE), 2.5 * TILE, 0.3 * TILE, false);

		new Block(QPointF(14 * TILE, 7.1 * TILE), 1.3 * TILE, 0.3 * TILE);
		new Block(QPointF(16.6 * TILE, 5.7 * TILE), 2.5 * TILE, 0.3 * TILE);

		new Block(QPointF(24.3 * TILE, 8.5 * TILE), 2.5 * TILE, 0.3 * TILE, false);
		new Block(QPointF(25.6 * TILE, 6.4 * TILE), 3.8 * TILE, 0.3 * TILE);

		new Block(QPointF(35.78 * TILE, 4.4 * TILE), 6.42 * TILE, 0.3 * TILE);

		new Block(QPointF(47.28 * TILE, 4.4 * TILE), 10.2 * TILE, 0.3 * TILE);
		new Block(QPointF(55.1 * TILE, 3 * TILE), 20.4 * TILE, 0.3 * TILE);

		new Block(QPointF(56.3 * TILE, 8.5 * TILE), 3.8 * TILE, 0.3 * TILE);
		new Block(QPointF(60.2 * TILE, 6.4 * TILE), 2.5 * TILE, 0.3 * TILE);

		new Block(QPointF(64 * TILE, 5.7 * TILE), 8.9 * TILE, 0.3 * TILE);
		new Block(QPointF(69.1 * TILE, 8.5 * TILE), 7.7 * TILE, 0.3 * TILE, false);

		new Block(QPointF(74.2 * TILE, 4.4 * TILE), 2.6 * TILE, 0.3 * TILE);
		new Block(QPointF(76.8 * TILE, 4.4 * TILE), 2.5 * TILE, 0.3 * TILE);
		new Block(QPointF(79.3 * TILE, 4.4 * TILE), 1.4 * TILE, 0.3 * TILE, false);
		new Block(QPointF(80.7 * TILE, 4.4 * TILE), 2.5 * TILE, 0.3 * TILE);
		new Block(QPointF(81.9 * TILE, 3 * TILE), 1.3 * TILE, 0.3 * TILE);
		new Block(QPointF(83.2 * TILE, 3 * TILE), 1.3 * TILE, 0.3 * TILE, false);
		new Block(QPointF(84.5 * TILE, 3 * TILE), 1.2 * TILE, 0.3 * TILE);
		new Block(QPointF(85.7 * TILE, 3 * TILE), 1.4 * TILE, 0.3 * TILE, false);
		new Block(QPointF(87.1 * TILE, 3 * TILE), 1.2 * TILE, 0.3 * TILE);

		new Block(QPointF(76.8 * TILE, 7.1 * TILE), 2.5 * TILE, 0.3 * TILE, false);
		new Block(QPointF(80.7 * TILE, 7.1 * TILE), 2.5 * TILE, 0.3 * TILE, false);

		new Block(QPointF(84.5 * TILE, 6.4 * TILE), 1.2 * TILE, 0.3 * TILE, false);
		new Block(QPointF(87.1 * TILE, 5.7 * TILE), 3.8 * TILE, 0.3 * TILE, false);
		new Block(QPointF(89.6 * TILE, 4.4 * TILE), 1.3 * TILE, 0.3 * TILE);
		new Block(QPointF(90.9 * TILE, 4.4 * TILE), 1.2 * TILE, 0.3 * TILE, false);

		new Block(QPointF(93.5 * TILE, 5.7 * TILE), 2.5 * TILE, 0.3 * TILE);
		new Block(QPointF(94.7 * TILE, 4.4 * TILE), 1.3 * TILE, 0.3 * TILE);
		new Block(QPointF(96 * TILE, 4.4 * TILE), 1.2 * TILE, 0.3 * TILE, false);

		new Block(QPointF(98.6 * TILE, 5.7 * TILE), 2.5 * TILE, 0.3 * TILE);
		new Block(QPointF(98.6 * TILE, 8.5 * TILE), 1.2 * TILE, 0.3 * TILE, false);
		new Block(QPointF(99.9 * TILE, 7.1 * TILE), 3.8 * TILE, 0.3 * TILE, false);
		new Block(QPointF(103.7 * TILE, 4.4 * TILE), 1.3 * TILE, 0.3 * TILE, false);
		new Block(QPointF(105 * TILE, 4.4 * TILE), 1.2 * TILE, 0.3 * TILE);
		new Block(QPointF(105 * TILE, 8.5 * TILE), 1.2 * TILE, 0.3 * TILE, false);
		new Block(QPointF(105 * TILE, 3 * TILE), 2.5 * TILE, 0.3 * TILE);
		new Block(QPointF(106.3 * TILE, 6.3 * TILE), 1.2 * TILE, 0.3 * TILE);

		new Block(QPointF(108.8 * TILE, 4.4 * TILE), 1.3 * TILE, 0.3 * TILE, false);
		new Block(QPointF(110.1 * TILE, 4.4 * TILE), 1.2 * TILE, 0.3 * TILE);
		new Block(QPointF(110.1 * TILE, 5.7 * TILE), 3.8 * TILE, 0.3 * TILE, false);
		new Block(QPointF(113.9 * TILE, 5.7 * TILE), 2.5 * TILE, 0.3 * TILE);
		new Block(QPointF(113.9 * TILE, 8.5 * TILE), 3.9 * TILE, 0.3 * TILE, false);

		new Block(QPointF(119.1 * TILE, 7.1 * TILE), 2.5 * TILE, 0.3 * TILE);

		new Block(QPointF(122.9 * TILE, 5.7 * TILE), 2.5 * TILE, 0.3 * TILE);
		new Block(QPointF(125.5 * TILE, 4.4 * TILE), 5 * TILE, 0.3 * TILE);
		new Block(QPointF(125.5 * TILE, 8.5 * TILE), 9.6 * TILE, 0.3 * TILE, false);
		new Block(QPointF(126.8 * TILE, 6.4 * TILE), 3.8 * TILE, 0.3 * TILE);
		new Block(QPointF(130.6 * TILE, 5.7 * TILE), 1.2 * TILE, 0.3 * TILE);
		new Block(QPointF(131.9 * TILE, 7.1 * TILE), 1.2 * TILE, 0.3 * TILE);
		new Block(QPointF(134 * TILE, 3.2 * TILE), 1 * TILE, 0.3 * TILE);

		new Water(QPointF(0 * TILE, 8.51 * TILE), 11.5 * TILE, 0.3 * TILE);
		new Water(QPointF(14 * TILE, 8.51 * TILE), 10.3 * TILE, 0.3 * TILE);
		new Water(QPointF(26.8 * TILE, 8.51 * TILE), 29.5 * TILE, 0.3 * TILE);
		new Water(QPointF(60.1 * TILE, 8.51 * TILE), 9 * TILE, 0.3 * TILE);

		new Bridge(QPointF(30.7 * TILE, 4.4 * TILE), 5.12 * TILE, TILE);
		new Bridge(QPointF(42.20 * TILE, 4.4 * TILE), 5.12 * TILE, TILE);

		new Turret(QPointF(TILE * 50, TILE * 5.5));
		new Turret(QPointF(TILE * 65.5, TILE * 4.4));
		new Turret(QPointF(TILE * 72.9, TILE * 4.4));
		new Turret(QPointF(TILE * 124.2, TILE * 7.2));
		new Turret(QPointF(TILE * 129.2, TILE * 7.2));

		new TurretPowerUp(QPointF(TILE * 12.8, TILE * 5.5), 'M');
		new TurretPowerUp(QPointF(TILE * 62.7, TILE * 5.5), 'R');
		new TurretPowerUp(QPointF(TILE * 90, TILE * 6.8), 'B');

		new FlyingPowerUp(QPointF(TILE * 10, 61), 'R');
		new FlyingPowerUp(QPointF(TILE * 45, 61), 'M');
		new FlyingPowerUp(QPointF(TILE * 93, 61), 'M');

		new Sniper(QPointF(TILE * 12.5, TILE * 6.5));
		new Sniper(QPointF(TILE * 25, TILE * 6.5));
		new Sniper(QPointF(TILE * 50.5, TILE * 2.4));
		new Sniper(QPointF(TILE * 99, TILE * 3.7));
		new Sniper(QPointF(TILE * 133.8, TILE * 1.1), true);

		new HidingSniper(QPointF(TILE * 53.5, TILE * 2.4));
		new HidingSniper(QPointF(TILE * 61, TILE * 1));

		new Cannon(QPointF(TILE * 82, TILE * 5.8));
		new Cannon(QPointF(TILE * 87, TILE * 1.7));
		new Cannon(QPointF(TILE * 115, TILE * 4.4));


		new Soldier(QPointF(TILE * 10, TILE * 2.4));
		new Soldier(QPointF(TILE * 18, TILE * 2.4));
		new Soldier(QPointF(TILE * 25, TILE * 2.4));
		new Soldier(QPointF(TILE * 37, TILE * 2.4));
		new Soldier(QPointF(TILE * 41, TILE * 2.4));
		new Soldier(QPointF(TILE * 49, TILE * 2.4));
		new Soldier(QPointF(TILE * 63, TILE * 1));
		new Soldier(QPointF(TILE * 66, TILE * 1));
		new Soldier(QPointF(TILE * 61, TILE * 5.4));
		new Soldier(QPointF(TILE * 71, TILE * 1));
		new Soldier(QPointF(TILE * 70, TILE * 3.7));
		new Soldier(QPointF(TILE * 75, TILE * 6.5));
		new Soldier(QPointF(TILE * 80, TILE * 2.4));
		new Soldier(QPointF(TILE * 83, TILE * 1));
		new Soldier(QPointF(TILE * 88, TILE * 3.7));
		new Soldier(QPointF(TILE * 102, TILE * 5.1));
		new Soldier(QPointF(TILE * 110, TILE * 2.4));

		new RepeaterCannon(QPointF(3347, 120), 0);
		new RepeaterCannon(QPointF(3368, 119), 1);

		new Core(QPointF(3351, 152));


		return new Bill(QPointF(TILE * 2, TILE * 1));

	}
	else
	{
		std::cerr << "Level \"" << round << "\" not yet implemented\n";
		return nullptr;
	}
}