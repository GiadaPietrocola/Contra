#include "Sprites.h"
#include "GameConfig.h"
#include <iostream>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>

using namespace Contra;

static QPixmap loadImage(const std::string& file, QColor mask_color = Qt::magenta)
{
	QPixmap pixmap(file.c_str());
	pixmap.setMask(pixmap.createMaskFromColor(mask_color));
	return pixmap;
}

QPixmap replaceColor(QPixmap pix, QColor old_color, QColor new_color)
{
	QBitmap mask = pix.createMaskFromColor(old_color, Qt::MaskOutColor);
	QPainter p(&pix);
	p.setPen(new_color);
	p.drawPixmap(pix.rect(), mask, mask.rect());
	p.end();
	return pix;
}

Sprites* Sprites::instance()
{
	static Sprites uniqueInstance;
	return &uniqueInstance;
}

Sprites::Sprites()
{
	_sprites["Bill"] = loadImage(":/sprites/Bill.png", QColor(4, 2, 4));
	_sprites["title"] = loadImage(":/sprites/Title.png", QColor(4, 2, 4));
	_sprites["fonts"] = loadImage(":/sprites/Fonts.png", QColor(4, 2, 4));
	_sprites["Bullet"] = loadImage(":/sprites/Bullet.png", QColor(4, 2, 4));
	_sprites["Bridge"] = loadImage(":/sprites/Bridge.png", QColor(4, 2, 4));
	_sprites["Enemies"] = loadImage(":/sprites/Enemies.png", QColor(4, 2, 4));
	_sprites["Towers"] = loadImage(":/sprites/Towers.png", QColor(4, 2, 4));
	_sprites["PowerUps"] = loadImage(":/sprites/PowerUps.png", QColor(4, 2, 4));
	_sprites["FlashingElements"] = loadImage(":/sprites/FlashingElements.png", QColor(4, 2, 4));
	_sprites["Explosion"] = loadImage(":/sprites/Explosions.png", QColor(4, 2, 4));
	_sprites["Medals"] = loadImage(":/sprites/Medals.png", QColor(4, 2, 4));
	_sprites["GameOver"] = loadImage(":/sprites/GameOver.png", QColor(4, 2, 4));
	_sprites["GameWin"] = loadImage(":/sprites/GameWin.png", QColor(4, 2, 4));
	_sprites["FinalBoss"] = loadImage(":/sprites/FinalBoss.png", QColor(4, 2, 4));

}

QPixmap* Sprites::getSprite(const std::string& id)
{
	if (_sprites.find(id) != _sprites.end())
		return &_sprites[id];
	else
	{
		std::cerr << "Cannot find sprite \"" << id << "\"\n";
		return nullptr;
	}
}

void Sprites::getAnimation(const std::string& id, QRect animOutput[])
{
	if (id == "Bill_stand")
	{
		animOutput[0] = QRect(0, 0, TILE, 2*TILE);
	}
	if (id == "Bill_walk")
	{
		animOutput[0] = QRect(0, 2*TILE, TILE, 2 * TILE);
		animOutput[1] = QRect(2 * TILE, 2 * TILE, TILE, 2 * TILE);
		animOutput[2] = QRect(TILE, 2*TILE, TILE, 2 * TILE);
		animOutput[3] = QRect(3*TILE, 2*TILE, TILE, 2 * TILE);
		animOutput[4] = QRect(2* TILE, 2*TILE, TILE, 2 * TILE);
		animOutput[5] = QRect(4*TILE, 2*TILE, TILE, 2 * TILE);
	}
	if (id == "Bill_jump")
	{
		animOutput[0] = QRect(0, 4 * TILE, TILE, TILE);
		animOutput[1] = QRect(TILE, 4 * TILE, TILE, TILE);
		animOutput[2] = QRect(2*TILE, 4 * TILE, TILE, TILE);
		animOutput[3] = QRect(3 * TILE, 4 * TILE, TILE, TILE);

	}
	if (id == "Bill_fall")
	{
		animOutput[0] = QRect(0, 2 * TILE, TILE, 2 * TILE);
	}
	if (id == "Bill_laying")
	{
		animOutput[0] = QRect(0, 5 * TILE, 2 * TILE, TILE);

	}
	if (id == "Bill_water")
	{
		animOutput[0] = QRect(0, 7 * TILE, TILE, TILE);
		animOutput[1] = QRect(TILE, 7 * TILE, TILE, TILE);
		animOutput[2] = QRect(2 * TILE, 7 * TILE, TILE, TILE);

	}
	if (id == "Bill_fire_horizontal")
	{
		animOutput[0] = QRect(0, 0, TILE, 2*TILE);
		animOutput[1] = QRect(TILE, 0, TILE, 2 * TILE);
	}
	if (id == "Bill_fire_horizontal_walk")
	{
		animOutput[0] = QRect(5 * TILE,2*  TILE, TILE, 2 * TILE);
		animOutput[1] = QRect(6 * TILE, 2 * TILE, TILE, 2 * TILE);
		animOutput[1] = QRect(7 * TILE, 2 * TILE, TILE, 2 * TILE);
	}
	if (id == "Bill_fire_horizontal_water")
	{
		animOutput[0] = QRect(3 * TILE, 7 * TILE, TILE, TILE);
		animOutput[1] = QRect(4 * TILE, 7 * TILE, TILE, TILE);
	}
	if (id == "Bill_fire_vertical")
	{
		animOutput[0] = QRect(2*TILE, 0, TILE, 2 * TILE);
		animOutput[1] = QRect(3*TILE, 0, TILE, 2 * TILE);
	}
	if (id == "Bill_fire_vertical_water")
	{
		animOutput[0] = QRect(5 * TILE, 7 * TILE, TILE, TILE);
		animOutput[1] = QRect(6 * TILE, 7 * TILE, TILE, TILE);
	}
	if (id == "Bill_fire_diagonal_up")
	{
		animOutput[0] = QRect(4 * TILE, 0, TILE, 2 * TILE);
		animOutput[1] = QRect(5 * TILE, 0, TILE, 2 * TILE);
		animOutput[2] = QRect(6 * TILE, 0, TILE, 2 * TILE);
	}
	if (id == "Bill_fire_diagonal_up_water")
	{
		animOutput[0] = QRect(7 * TILE, 7 * TILE, TILE, TILE);
		animOutput[1] = QRect(8 * TILE, 7 * TILE, TILE, TILE);
	}
	if (id == "Bill_fire_diagonal_down")
	{
		animOutput[0] = QRect(7 * TILE, 0, TILE, 2 * TILE);
		animOutput[1] = QRect(8 * TILE, 0, TILE, 2 * TILE);
		animOutput[2] = QRect(9 * TILE, 0, TILE, 2 * TILE);
	}
	if (id == "Bill_down_water")
	{
		animOutput[0] = QRect(0, 8 * TILE, TILE, TILE);
	}
	if (id == "Bill_dying")
	{
		animOutput[0] = QRect(0, 6 * TILE, TILE, TILE);
		animOutput[1] = QRect(TILE, 6 * TILE, TILE,TILE);
		animOutput[2] = QRect(2*TILE, 6 * TILE, TILE,TILE);
		animOutput[3] = QRect(3*TILE, 6 * TILE, TILE, TILE);
		animOutput[4] = QRect(4*TILE, 6 * TILE, 2*TILE, TILE);
	}
	if (id == "Bill_dead")
	{
		animOutput[0] = QRect(4 * TILE, 6 * TILE, 2 * TILE, TILE);
	}
	if (id == "Bullet_fire")
	{
		animOutput[0] = QRect(1, 9, 5, 5);
	}
	if (id == "Bullet_fire_power_up")
	{
		animOutput[0] = QRect(8, 7, 7, 7);
	}
	if (id == "Bomb")
	{
		animOutput[0] = QRect(21, 4, 12, 12);
	}
	if (id == "Bridge")
	{
		animOutput[0] = QRect(0, 0, 5.12*TILE, 30);
		animOutput[1] = QRect(5.12 * TILE, 0, 5.12 * TILE, 30);
		animOutput[2] = QRect(5.12 * 2 * TILE, 0, 5.12 * TILE, 30);
	}
	if (id == "Bridge_exploding_1")
	{
		animOutput[0] = QRect(26, 36, 4.08 * TILE, 30);
		animOutput[1] = QRect(154, 36, 4.08 * TILE, 30);
		animOutput[2] = QRect(282, 36, 4.08 * TILE, 30);

	}
	if (id == "Bridge_exploding_2")
	{
		animOutput[0] = QRect(58, 73, 2.8 * TILE, 30);
		animOutput[1] = QRect(186, 73, 2.8 * TILE, 30);
		animOutput[2] = QRect(314, 73, 2.8 * TILE, 30);
	}
	if (id == "Bridge_exploding_3")
	{
		animOutput[0] = QRect(90, 110, 1.52 * TILE, 30);
		animOutput[1] = QRect(218, 110, 1.52 * TILE, 30);
		animOutput[2] = QRect(346, 110, 1.52 * TILE, 30);
	}
	if (id == "Sniper_Fire_Horizontal")
	{
		animOutput[0] = QRect(2 *TILE, 0, TILE, 2 * TILE);
		animOutput[1] = QRect(3 * TILE, 0, TILE, 2 * TILE);
	}
	if (id == "Sniper_Fire_Diagonal_Up")
	{
		animOutput[0] = QRect(4 * TILE, 0, TILE, 2 * TILE);
		animOutput[1] = QRect(5 * TILE, 0, TILE, 2 * TILE);
	}
	if (id == "Sniper_Fire_Diagonal_Down")
	{
		animOutput[0] = QRect(0, 0, TILE, 2 * TILE);
		animOutput[1] = QRect(TILE, 0, TILE, 2 * TILE);
	}
	if (id == "Sniper_Dying")
	{
		animOutput[0] = QRect(6 * TILE, 0, TILE+6, 2 * TILE);
		animOutput[1] = QRect(7 * TILE+6, 0, TILE + 6, 2 * TILE);
		animOutput[2] = QRect(8 * TILE + 12, 0, TILE + 6, 2 * TILE);
		animOutput[3] = QRect(9 * TILE+18, 0, TILE + 6, 2 * TILE);
	}
	if (id == "Sniper_Hiding")
	{
		animOutput[0] = QRect(70, 4 * TILE, TILE, 2 * TILE);
	}
	if (id == "Sniper_Rising")
	{
		animOutput[0] = QRect(95, 4 * TILE, TILE, 2 * TILE);
	}
	if (id == "Hiding_Sniper_Hiding")
	{
		animOutput[0] = QRect(2, 4 * TILE, TILE+6, 2 * TILE);
	}
	if (id == "Hiding_Sniper_Fire_Horizontal")
	{
		animOutput[0] = QRect(TILE+12, 4 * TILE, TILE+6, 2 * TILE);
	}
	if (id == "Soldier_Walking")
	{
		animOutput[0] = QRect(0, 2 * TILE, TILE, 2 * TILE);
		animOutput[1] = QRect(TILE, 2 * TILE, TILE, 2 * TILE);
		animOutput[2] = QRect(2*TILE, 2 * TILE, TILE, 2 * TILE);
		animOutput[3] = QRect(3*TILE, 2 * TILE, TILE, 2 * TILE);
		animOutput[4] = QRect(4 * TILE, 2 * TILE, TILE, 2 * TILE);
	}
	if (id == "Soldier_Jump")
	{
		animOutput[0] = QRect(5*TILE, 2 * TILE, TILE, 2 * TILE);
	}
	if (id == "Soldier_Dying")
	{
		animOutput[0] = QRect(6 * TILE, 2*TILE, TILE + 6, 2 * TILE);
		animOutput[1] = QRect(7 * TILE + 6, 0, TILE + 6, 2 * TILE);
		animOutput[2] = QRect(8 * TILE + 12, 0, TILE + 6, 2 * TILE);
		animOutput[3] = QRect(9 * TILE + 18, 0, TILE + 6, 2 * TILE);
	}
	if (id == "Soldier_Water")
	{
		animOutput[0] = QRect(7 * TILE, 2 * TILE, TILE, 2 * TILE);
		animOutput[1] = QRect(8 * TILE, 2 * TILE, TILE, 2 * TILE);
	}
	if (id == "Turret_Close")
	{
		animOutput[0] = QRect(1 * (TILE + 7), 3 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(4 * (TILE + 7), 3 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(7 * (TILE + 7), 3 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Turret_Opening")
	{
		animOutput[0] = QRect(1 * (TILE + 7), 2 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Turret_Fire_Right")
	{
		animOutput[0] = QRect(2 * (TILE + 7), 3 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(5 * (TILE + 7), 3 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(8 * (TILE + 7), 3 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Turret_Fire_Left")
	{
		animOutput[0] = QRect(0 * (TILE + 7), 3 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(3 * (TILE + 7), 3 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(6 * (TILE + 7), 3 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Turret_Fire_Up")
	{
		animOutput[0] = QRect(1 * (TILE + 7), 1 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(4 * (TILE + 7), 1 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(7 * (TILE + 7), 1 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Turret_Fire_Down")
	{
		animOutput[0] = QRect(1 * (TILE + 7), 5 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(4 * (TILE + 7), 5 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(7 * (TILE + 7), 5 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Turret_Fire_Diagonal_Up_Right")
	{
		animOutput[0] = QRect(2 * (TILE + 7), 2 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(5 * (TILE + 7), 2 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(8 * (TILE + 7), 2 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Turret_Fire_Diagonal_Up_Left")
	{
		animOutput[0] = QRect(0 * (TILE + 7), 2 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(3 * (TILE + 7), 2 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(6 * (TILE + 7), 2 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Turret_Fire_Diagonal_Down_Right")
	{
		animOutput[0] = QRect(2 * (TILE + 7), 4 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(5 * (TILE + 7), 4 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(8 * (TILE + 7), 4 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Turret_Fire_Diagonal_Down_Left")
	{
		animOutput[0] = QRect(0 * (TILE + 7), 4 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(3 * (TILE + 7), 4 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(6 * (TILE + 7), 4 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Flying_PowerUp")
	{
		animOutput[0] = QRect(0, 0, TILE, 15);
	}
	if (id == "Power_up")
	{
		animOutput[0] = QRect(6 * TILE, 0, TILE, 15);
		animOutput[1] = QRect(TILE, 0, TILE, 15);
		animOutput[2] = QRect(2 * TILE, 0, TILE, 15);
	}
	if (id == "Turret_power_up_closed")
	{
		animOutput[0] = QRect(0, 15,(TILE + 7), (TILE + 7));
	}
	if (id == "Turret_power_up")
	{
		animOutput[0] = QRect(4 * (TILE + 7), 15, (TILE + 7), (TILE + 7));
		animOutput[1] = QRect(5 * (TILE + 7), 15, (TILE + 7), (TILE + 7));
		animOutput[2] = QRect(6 * (TILE + 7), 15, (TILE + 7), (TILE + 7));
	}
	if (id == "Flashing_elements")
	{
		animOutput[0] = QRect(0, 0, 3456, 229);
		animOutput[1] = QRect(0, 229, 3456, 229);
	}
	if (id == "Cannon_Opening_1")
	{
		animOutput[0] = QRect(0 , 6 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(0 , 7 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(0 , 8 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Cannon_Opening_2")
	{
		animOutput[0] = QRect(1 * (TILE + 7), 6 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(1 * (TILE + 7), 7 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(1 * (TILE + 7), 8 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Cannon_Fire_Left")
	{
		animOutput[0] = QRect(2 * (TILE + 7), 6 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(2 * (TILE + 7), 7 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(2 * (TILE + 7), 8 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Cannon_Fire_Diagonal_Up_Left")
	{
		animOutput[0] = QRect(3 * (TILE + 7), 6 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(3 * (TILE + 7), 7 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(3 * (TILE + 7), 8 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Cannon_Fire_Up")
	{
		animOutput[0] = QRect(4 * (TILE + 7), 6 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[1] = QRect(4 * (TILE + 7), 7 * (TILE + 7), TILE + 7, TILE + 7);
		animOutput[2] = QRect(4 * (TILE + 7), 8 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Cannon_Closed")
	{
		animOutput[0] = QRect(5 * (TILE + 7), 6 * (TILE + 7), TILE + 7, TILE + 7);
	}
	if (id == "Explosion_Bridge")
	{
		animOutput[0] = QRect(0 * (45), 0, 45, 45);
		animOutput[1] = QRect(1 * (45), 0, 45, 45);
		animOutput[2] = QRect(2 * (45), 0, 45, 45);
		animOutput[3] = QRect(3 * (45), 0, 45, 45);
		animOutput[4] = QRect(4 * (45), 0, 45, 45);
		animOutput[5] = QRect(5 * (45), 0, 45, 45);
		animOutput[6] = QRect(6 * (45), 0, 45, 45);
	}
	if (id == "Explosion")
	{
		animOutput[0] = QRect(0 * (45), 45, 45, 45);
		animOutput[1] = QRect(1 * (45), 45, 45, 45);
		animOutput[2] = QRect(2 * (45), 45, 45, 45);
		animOutput[3] = QRect(3 * (45), 45, 45, 45);
		animOutput[4] = QRect(4 * (45), 45, 45, 45);
	}
	if (id == "Medals")
	{
		animOutput[0] = QRect(2 * TILE, 0, 76, 30); 
		animOutput[1] = QRect(130, 0, TILE, TILE);
		animOutput[2] = QRect(TILE, 0, TILE, TILE);
		animOutput[3] = QRect(0, 0, TILE, TILE);
	}
	if (id == "Repeater_Cannon_Fire") 
	{
		animOutput[0] = QRect(0, 0, 12, 8);
		animOutput[1] = QRect(12, 0, 12, 8);
		animOutput[2] = QRect(0, 0, 12, 8);
		animOutput[3] = QRect(0, 0, 12, 8);
	}
	if (id == "Core") 
	{
		animOutput[0] = QRect(0, 8, 26, 33);
		animOutput[1] = QRect(26, 8, 26, 33);
		animOutput[2] = QRect(2 * 26, 8, 26, 33);
	}
	else
		std::cerr << "Cannot find animation \"" << id << "\"\n";
}

QRect moveBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1)
{
	rect.moveTo(QPoint(rect.x() + x * dx + x * border_x, rect.y() + y * dy + y * border_y));
	return rect;
}

QPixmap Sprites::getTexture(const std::string& id)
{
	if (id == "title-screen")
		return _sprites["title"].copy(0, 0, TILE * 16, TILE * 14);
	if (id == "game_over_screen")
		return _sprites["GameOver"].copy(0, 0, TILE * 16, TILE * 14);
	if (id == "game_win_screen")
		return _sprites["GameWin"].copy(0, 0, TILE * 16, TILE * 14);
	else if (id.rfind("char-", 0) == 0)
	{
		char c = id[5];
		int xDist = c - '0', yDist = 0;
		if (c >= 'A' && c - 'A' < 13)
		{
			xDist = c - 'A';
			yDist = 1;
		}
		else if (c >= 'A' && c - 'A' < 26)
		{
			xDist = c - 'N';
			yDist = 2;
		}
		else
			std::cerr << "Cannot find sprite character \"" << c << "\"\n";
		return _sprites["fonts"].copy(moveBy(QRect(8, 7, 7, 7), xDist, yDist, 7, 7, 3, 3));
	}
	else
	{
		std::cerr << "Cannot find sprite texture \"" << id << "\"\n";
		return QPixmap();
	}
}


QPixmap Sprites::getText(std::string text, int fill, QColor color)
{
	if (fill)
		while (text.size() != fill)
			text = ' ' + text;

	QPixmap collage(8 * int(text.size()), 7);
	QPainter painter(&collage);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, collage.width(), collage.height());

	for (int i = 0; i < text.size(); i++)
		if (text[i] != ' ')
			painter.drawPixmap(8 * i, 0, Sprites::instance()->getTexture(std::string("char-") + text[i]));

	painter.end();

	collage.setMask(collage.createMaskFromColor(QColor(4, 2, 4)));

	if (color != Qt::white)
		collage = replaceColor(collage, QColor(252, 254, 252), color);

	return collage;
}
