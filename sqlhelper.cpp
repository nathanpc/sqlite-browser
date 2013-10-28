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
 * @return SQLite return code.
 */
int SQLHelper::open_database(QString path) {
	const char *cpath = path.toStdString().c_str();
	return sqlite3_open(cpath, &db);
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

/**
 *	SQLite error message.
 *
 * @param sqlite_error Error code.
 * @return Error message.
 */
QString SQLHelper::sqlite_error_msg(int sqlite_error) {
	switch (sqlite_error) {
		case SQLITE_ERROR:
			return "SQLITE_ERROR: SQL error or missing database";
		case SQLITE_INTERNAL:
			return "SQLITE_INTERNAL: Internal logic error in SQLite";
		case SQLITE_PERM:
			return "SQLITE_PERM: Access permission denied";
		case SQLITE_ABORT:
			return "SQLITE_ABORT: Callback routine requested an abort";
		case SQLITE_BUSY:
			return "SQLITE_BUSY: The database file is locked";
		case SQLITE_LOCKED:
			return "SQLITE_LOCKED: A table in the database is locked";
		case SQLITE_NOMEM:
			return "SQLITE_NOMEM: A malloc() failed";
		case SQLITE_READONLY:
			return "SQLITE_READONLY: Attempt to write a readonly database";
		case SQLITE_INTERRUPT:
			return "SQLITE_INTERRUPT: Operation terminated by sqlite3_interrupt()";
		case SQLITE_IOERR:
			return "SQLITE_IOERR: Some kind of disk I/O error occurred";
		case SQLITE_CORRUPT:
			return "SQLITE_CORRUPT: The database disk image is malformed";
		case SQLITE_NOTFOUND:
			return "SQLITE_NOTFOUND: Unknown opcode in sqlite3_file_control()";
		case SQLITE_FULL:
			return "SQLITE_FULL: Insertion failed because database is full";
		case SQLITE_CANTOPEN:
			return "SQLITE_CANTOPEN: Unable to open the database file";
		case SQLITE_PROTOCOL:
			return "SQLITE_PROTOCOL: Database lock protocol error";
		case SQLITE_EMPTY:
			return "SQLITE_EMPTY: Database is empty";
		case SQLITE_SCHEMA:
			return "SQLITE_SCHEMA: The database schema changed";
		case SQLITE_TOOBIG:
			return "SQLITE_TOOBIG: String or BLOB exceeds size limit";
		case SQLITE_CONSTRAINT:
			return "SQLITE_CONSTRAINT: Abort due to constraint violation";
		case SQLITE_MISMATCH:
			return "SQLITE_MISMATCH: Data type mismatch";
		case SQLITE_MISUSE:
			return "SQLITE_MISUSE: Library used incorrectly";
		case SQLITE_NOLFS:
			return "SQLITE_NOLFS: Uses OS features not supported on host";
		case SQLITE_AUTH:
			return "SQLITE_AUTH: Authorization denied";
		case SQLITE_FORMAT:
			return "SQLITE_FORMAT: Auxiliary database format error";
		case SQLITE_RANGE:
			return "SQLITE_RANGE: Auxiliary database format error";
		case SQLITE_NOTADB:
			return "SQLITE_NOTADB: File opened that is not a database file";
	}
}
