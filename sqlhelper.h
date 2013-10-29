#ifndef SQLHELPER_H
#define SQLHELPER_H

#include <QObject>
#include <vector>
#include <sqlite3.h>
#include <QStandardItemModel>
#include <QTableView>

class SQLHelper {
	private:
		sqlite3 *db;
		QTableView *tableView;

		QStandardItemModel *table_model;

	public:
		SQLHelper();
		virtual ~SQLHelper();

		int open_database(QString path);
		std::vector<std::vector<QString> > query(QString query, std::vector<QString> *col_names);
		QString sqlite_error_msg(int sqlite_error);

		void setTableView(QTableView *tableView);
		void populate_table(const std::vector<QString> cols, const std::vector<std::vector<QString> > rows);
		void view_query(QString qry);
};

#endif // SQLHELPER_H
