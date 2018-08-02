#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include <qwebengineview.h>
#include "DockWidget.h"
#include "TextEdit.h"

class editorWindow : public QMainWindow {
	Q_OBJECT

public:
	editorWindow(QString code, QString fileTitle,
		QString codeImplementationFile, QString ImplementationFileTitle, QWidget* parent = Q_NULLPTR);
	void addMenuBar();

private:
	DockWidget* dock;
	QTextEdit* m_code;
	QTabWidget* tabs;
	QTabWidget* tabs1;
	QWidget* fileWidget;
	QListWidget *listWidget;
	QString *headerTitle;
	QString *cppTitle;
	QTextEdit *cppCode;
	QTextEdit *headerCode;
	QTreeWidget *treeWidget;
	QTreeWidgetItem *headerFiles;
	QTreeWidgetItem *cppFiles;
	QTreeWidgetItem *cppFileItem;
	QTreeWidgetItem *headerFileItem;
	QDialog *newClassDialog;
	QFormLayout *formLayout;
	QLineEdit *newClass;
	QString *newClassName;
	QPushButton *quitterDialog;
	QVBoxLayout *mainLayout;
	QFont *font2;

public slots:
	void saveFile();
	void addFileDialog();
	void closeDialog();
	void selectionnerFichier(QTreeWidgetItem *item, int column);
};
