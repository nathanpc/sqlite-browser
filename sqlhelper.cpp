/**
 *	sqlhelper.h
 *	SQL helper library.
 *
 *	@author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <QObject>
#include <iostream>
#include <vector>
#include <sqlite3.h>

#include "sqlhelper.h"

using namespace std;

SQLHelper::SQLHelper() {
	sqlite3_initialize();
	db = NULL;
}

SQLHelper::~SQLHelper() {
	if (db) {
		sqlite3_close(db);
		sqlite3_shutdown();
	}
}

/**
 * Open the database.
 *
 * @param path A SQLite database path.
 */
bool SQLHelper::open_database(QString path) {
	const char *cpath = path.toStdString().c_str();

	if (sqlite3_open(cpath, &db) != SQLITE_OK) {
		return false;
	}

	return true;
}

/**
 * Query something from the database.
 *
 * @param query A SQL query string.
 * @return A vector of string vectors with the results.
 */
vector<vector<QString> > SQLHelper::query(QString query) {
	sqlite3_stmt *statement;
	vector<vector<QString> > results;

	// Check if the query was successful.
	if (sqlite3_prepare_v2(db, query.toStdString().c_str(), -1, &statement, 0) == SQLITE_OK) {
		// Get the amount of columns.
		int cols = sqlite3_column_count(statement);

		while (true) {
			// Check if there's a row.
			if (sqlite3_step(statement) == SQLITE_ROW) {
				vector<QString> values;

				// Iterate over each column.
				for (int col = 0; col < cols; ++col) {
					QString value;
					char *cval = (char *)sqlite3_column_text(statement, col);

					// Prevents storing NULL into a std::string, which causes a crash.
					if (cval) {
						value = QString(cval);
					}

					values.push_back(value);
				}

				results.push_back(values);
			} else {
				break;
			}
		}

		// Finalize the query to prevent memory leaks.
		sqlite3_finalize(statement);
	}

	string error = sqlite3_errmsg(db);
	if (error != "not an error") {
		cout << "Error at \"" << query.toStdString() << "\": " << error << endl;
		exit(EXIT_FAILURE);
	}

	return results;
}
