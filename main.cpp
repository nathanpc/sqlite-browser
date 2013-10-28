#include "mainwindow.h"
#include <QApplication>
#include "sqlhelper.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	MainWindow window;
	//SQLHelper *sql;

	//window.sql = sql;
	window.show();

	return app.exec();
}
