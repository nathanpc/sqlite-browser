#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>

#include "sqlhelper.h"
#include "queryfield.h"

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
		void on_treeView_clicked(const QModelIndex &index);

		void on_MainWindow_destroyed();

	private:
		Ui::MainWindow *ui;
		QueryField *queryField;
		QTableView *tableView;
		QHeaderView *horizontalHeader;

		SQLHelper sql;
		QStringList tables_list;

};

#endif // MAINWINDOW_H
