#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "queryfield.h"

#include <iostream>
#include <vector>

#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTableView>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
					   QMainWindow(parent),
					   ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// Setup the Query field.
	queryField = new QueryField(&sql);
	ui->splitter->addWidget(queryField);

	// Setup the table.
	tableView = new QTableView();
	horizontalHeader = tableView->horizontalHeader();
	horizontalHeader->setSortIndicatorShown(true);
	horizontalHeader->setCascadingSectionResizes(true);
	ui->splitter->addWidget(tableView);

	sql.setTableView(tableView);
}

MainWindow::~MainWindow() {
	delete ui;
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
	sql.view_query("SELECT * FROM " + tables_list[index.row()]);
}

/**
 * Window close event handler.
 */
void MainWindow::on_MainWindow_destroyed() {
	// TODO: Save the splitter sizes.
}
