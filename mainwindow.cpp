#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QFileDialog>
#include <QMessageBox>

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
	bool success = sql.open_database(path);

	if (!success) {
		QMessageBox *alert = new QMessageBox(this);

		// TODO: Apply the "Error" dialog style.
		alert->setText("Error");
		alert->setInformativeText("Couldn't open the database");
		alert->exec();
	}
}
