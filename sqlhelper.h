#ifndef SQLHELPER_H
#define SQLHELPER_H

#include <QObject>
#include <vector>
#include <sqlite3.h>

class SQLHelper {
	public:
		sqlite3 *db;

		SQLHelper();
		virtual ~SQLHelper();

		int open_database(QString path);
		std::vector<std::vector<QString> > query(QString query, std::vector<QString> *col_names);
		QString sqlite_error_msg(int sqlite_error);
};

#endif // SQLHELPER_H
