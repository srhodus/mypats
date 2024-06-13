// vim: tabstop=4 shiftwidth=4 noexpandtab
#include <QApplication>
#include "MainWindow.h"
#include "State.h"

State st;
History hs;

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	MainWindow window;
	window.show();
	return app.exec();
}
