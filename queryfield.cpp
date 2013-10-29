#include "queryfield.h"

QueryField::QueryField(SQLHelper *sql) {
	this->setMaximumHeight(50);
	this->setToolTip("<html><head/><body><p>SQL Query</p></body></html>");

	this->sql = sql;
}

void QueryField::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Return){
		sql->view_query(this->toPlainText());
	} else {
		QPlainTextEdit::keyPressEvent(event);
	}
}
