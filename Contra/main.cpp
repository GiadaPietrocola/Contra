#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	(new Contra::MainWindow())->show();

	return app.exec();
}