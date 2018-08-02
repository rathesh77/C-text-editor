#include "TextEdit.h"

TextEdit::TextEdit(QWidget *parent)
	: QTextEdit(parent)
{
}

TextEdit::TextEdit(QString code, QWidget *parent)
	: QTextEdit(parent)
{
		QFont font = "Courier";

	this->setLineWrapMode(QTextEdit::NoWrap);
	this->setText(code);
	this->setFont(font);
}
TextEdit::TextEdit(QString text)
{
}
TextEdit::~TextEdit()
{
}
