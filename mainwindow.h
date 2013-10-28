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

		void populate_table(vector<QString> cols, vector<vector<QString> > rows);

	private slots:
		void on_actionOpen_Database_triggered();

		void on_treeView_clicked(const QModelIndex &index);

	private:
		Ui::MainWindow *ui;
		SQLHelper sql;

		QStringList tables_list;
};

#endif // MAINWINDOW_H
