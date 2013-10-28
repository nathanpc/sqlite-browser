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
	}

	// Populate TreeView with the tables.
	vector<vector<QString> > tables = sql.query("SELECT name FROM sqlite_master WHERE type = 'table'", NULL);

	QStringList tables_list;
	QStringListModel *model = new QStringListModel();

	for (size_t i = 0; i < tables.size(); ++i) {
		tables_list.push_back(tables[0][i]);
	}

	model->setStringList(tables_list);
	ui->treeView->setModel(model);
}
