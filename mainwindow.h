#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "sqlhelper.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

		void populate_table(const std::vector<QString> cols, const std::vector<std::vector<QString> > rows);
		void sql_query(QString qry);

	private slots:
		void on_actionOpen_Database_triggered();
		void on_treeView_clicked(const QModelIndex &index);

		void on_MainWindow_destroyed();

	private:
		Ui::MainWindow *ui;
		SQLHelper sql;

		QStringList tables_list;
		QStandardItemModel *table_model;
};

#endif // MAINWINDOW_H
