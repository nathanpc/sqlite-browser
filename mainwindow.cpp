#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <vector>

#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>
#include <QStandardItem>
#include <QStandardItemModel>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
					   QMainWindow(parent),
					   ui(new Ui::MainWindow) {
	ui->setupUi(this);
	table_model = NULL;
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
void MainWindow::populate_table(const vector<QString> cols, const vector<vector<QString> > rows) {
	// Create the model.
	table_model = new QStandardItemModel(rows.size(), cols.size(), this);
	bool populated_cols = false;

	// Populate the model.
	for (size_t row = 0; row < rows.size(); ++row) {
		for (size_t col = 0; col < cols.size(); ++col) {
			if (!populated_cols) {
				table_model->setHorizontalHeaderItem(col, new QStandardItem(cols[col]));
			}

			table_model->setItem(row, col, new QStandardItem(rows[row][col]));
		}

		populated_cols = true;
	}

	// Set the model.
	ui->tableView->setModel(table_model);
}

/**
 * Execute a SQL query and show its result in the TableView.
 *
 * @param qry A SQL query.
 */
void MainWindow::sql_query(QString qry) {
	vector<QString> cols;
	vector<vector<QString> > table = sql.query(qry, &cols);

	populate_table(cols, table);
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
		QMessageBox::critical(this, "Error", sql.sqlite_error_msg(fail));
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
	sql_query("SELECT * FROM " + tables_list[index.row()]);
}

/**
 * Window close event handler.
 */
void MainWindow::on_MainWindow_destroyed() {
	// TODO: Save the splitter sizes.
}
