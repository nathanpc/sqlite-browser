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

		bool open_database(QString path);
		std::vector<std::vector<QString> > query(QString query);
};

#endif // SQLHELPER_H
