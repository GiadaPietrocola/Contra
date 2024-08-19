#include "MainWindow.h"
#include <QIcon>
#include <QResizeEvent>
#include <QVBoxLayout>


using namespace Contra;

MainWindow::MainWindow() : QWidget(0)
{
	_game = Game::instance();

	_layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	_layout->setSpacing(0);
	_layout->setContentsMargins(0, 0, 0, 0);
	_layout->addItem(new QSpacerItem(0, 0));
	_layout->addWidget(_game);
	_layout->addItem(new QSpacerItem(0, 0));
	setLayout(_layout);

	setStyleSheet("background-color: black;");

	resize(_game->aspectRatio() * 480, 480);

	setWindowIcon(QIcon(":/icons/icon.ico"));
	setWindowTitle("Contra [NES]");

}

void MainWindow::resizeEvent(QResizeEvent* evt)
{
	double thisAspectRatio = (double)evt->size().width() / evt->size().height();
	int widgetStretch, outerStretch;

	if (thisAspectRatio > _game->aspectRatio())
	{
		_layout->setDirection(QBoxLayout::LeftToRight);
		widgetStretch = height() * _game->aspectRatio();
		outerStretch = (width() - widgetStretch) / 2 + 0.5;
	}
	else
	{
		_layout->setDirection(QBoxLayout::TopToBottom);
		widgetStretch = width() * (1 / _game->aspectRatio());
		outerStretch = (height() - widgetStretch) / 2 + 0.5;
	}

	_layout->setStretch(0, outerStretch);
	_layout->setStretch(1, widgetStretch);
	_layout->setStretch(2, outerStretch);
}

void MainWindow::wheelEvent(QWheelEvent* evt)
{
	_game->wheelEvent(evt);
}