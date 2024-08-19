#include "Core.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Bill.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Sounds.h"
#include "RepeaterCannon.h"

using namespace Contra;

Core::Core(QPointF pos) : Enemy(pos, 26, 33)
{
	_sprite = Sprites::instance()->getSprite("FinalBoss");

	Sprites::instance()->getAnimation("Core", &_animGlowing[0]);

	_collider.adjust(3, 3, -3, -3);

	_mirror_x_dir = Direction::NONE;
}

void Core::advance()
{

	if (_life == 0)
	{

		if (isVisible())
		{
			new Explosion(2, pos() - QPoint(5, 2));
			Sounds::instance()->playSound("CoreExplosion");

			schedule("Game_win", 180, [this]()
				{
					Bill* player = Game::instance()->player();

					player->victory();

				});
			setVisible(false);
		}
	}
}

void Core::animate()
{
	_animRect = &_animGlowing[(FRAME_COUNT / 9) % 3];
}


bool Core::hit(Object* what, Direction fromDir)
{
	Bill* player = Game::instance()->player();

	int num_cannon = 0;
	QRectF curRect = qsceneCollider();
	curRect.adjust(0, -50, 0, 0);

	QList<QGraphicsItem*> items_in_rect = Game::instance()->world()->items(curRect);
	for (auto item : items_in_rect)
	{
		Object* obj = dynamic_cast<Object*>(item);
		if (obj->to<RepeaterCannon*>())
			num_cannon++;
	}

	if (num_cannon == 0)
	{
		if (what->to<Bullet*>() && what->to<Bullet*>()->getOwner() == 0)
		{
			if (player->PowerUp() == 'M')
				_life = _life - 2;
			else _life--;

		}
	}

	return true;
}