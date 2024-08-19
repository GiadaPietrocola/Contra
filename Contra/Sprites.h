#pragma once

#include <QPixmap>
#include <map>

namespace Contra
{
	class Sprites;
}

class Contra::Sprites
{
private:

	std::map<std::string, QPixmap> _sprites;

	Sprites();

public:

	static Sprites* instance();

	QPixmap* getSprite(const std::string& id);
	void getAnimation(const std::string& id, QRect animOutput[]);
	QPixmap getTexture(const std::string& id);
	QPixmap getText(std::string text, int fill = 0, QColor color = Qt::white);
};