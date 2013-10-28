#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <vector>

#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
					   QMainWindow(parent),
					   ui(new Ui::MainWindow) {
	ui->setupUi(this);
}

MainWindow::~MainWindow() {
	delete ui;
}

/**
 * Populates the TableView.
 *
 * @param cols Collumn names.
 * @param rows Rows.
 */
void MainWindow::populate_table(vector<QString> cols, vector<vector<QString> > rows) {
	for (size_t row = 0; row < table.size(); ++row) {
		for (size_t col = 0; col < cols->size(); ++col) {
			//rows[row][col]
		}
	}
}

/**
 * Handles the database opening.
 */
void MainWindow::on_actionOpen_Database_triggered() {
	QString path = QFileDialog::getOpenFileName(this, tr("Open Database"), "",
												tr("SQLite Databases (*.db *.sqlite);;Files (*.*)"));

	// Open the database.
	int fail = sql.open_database(path);
	if (fail) {
		QMessageBox *alert = new QMessageBox(this);

		// TODO: Apply the "Error" dialog style.
		alert->setText("Error");
		alert->setInformativeText(sql.sqlite_error_msg(fail));
		alert->exec();
	} else {
		// Populate TreeView with the tables.
		vector<vector<QString> > tables = sql.query("SELECT name FROM sqlite_master WHERE type = 'table'", NULL);
		QStringListModel *model = new QStringListModel();

		for (size_t i = 0; i < tables.size(); ++i) {
			tables_list.push_back(tables[0][i]);
		}

		model->setStringList(tables_list);
		ui->treeView->setModel(model);
	}
}

/**
 * Selects a table to work with.
 *
 * @param index TreeView model index.
 */
void MainWindow::on_treeView_clicked(const QModelIndex &index) {
	// Dump the whole table into the TableView.
	vector<QString> *cols;
	vector<vector<QString> > table = sql.query("SELECT * FROM " + tables_list[index.row()], cols);

	populate_table(cols, table);
}
