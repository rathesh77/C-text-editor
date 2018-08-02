#pragma once

#include <QTextEdit>

class TextEdit : public QTextEdit
{
	Q_OBJECT

public:
	TextEdit(QWidget *parent);
	TextEdit(QString code,QWidget *parent);
	TextEdit(QString text);
	~TextEdit();
};
