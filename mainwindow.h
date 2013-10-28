#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sqlhelper.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		void on_actionOpen_Database_triggered();

	private:
		Ui::MainWindow *ui;
		SQLHelper sql;
};

#endif // MAINWINDOW_H
