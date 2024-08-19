#include <QWidget>
#include <QBoxLayout>
#include "Game.h"

namespace Contra
{
	class MainWindow;
}

class Contra::MainWindow : public QWidget
{
private:

	Game* _game;
	QBoxLayout* _layout;

public:

	MainWindow();

	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void wheelEvent(QWheelEvent* event) override;
};