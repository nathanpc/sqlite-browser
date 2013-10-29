#ifndef QUERYFIELD_H
#define QUERYFIELD_H

#include <QObject>
#include <QPlainTextEdit>

#include "sqlhelper.h"

class QueryField : public QPlainTextEdit {
	Q_OBJECT

	private:
		SQLHelper *sql;

	public:
		explicit QueryField(SQLHelper *sql);

	protected:
		virtual void keyPressEvent(QKeyEvent *event);
};

#endif // QUERYFIELD_H
