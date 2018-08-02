#include "editorWindow.h"
#include <qwebengineview.h>
#include <DockWidget.h>
editorWindow::editorWindow(QString code, QString fileTitle,
	QString codeImplementationFile, QString ImplementationFileTitle,
	QWidget* parent)
	: QMainWindow(parent)
{

	setWindowTitle(fileTitle);
	setMinimumSize(1200, 700);

	addMenuBar();

	// ------File Widget

	dock = new DockWidget(this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
	dock->setMinimumWidth(950);

	fileWidget = new QWidget(this);
	tabs = new QTabWidget(dock);
	mainLayout = new QVBoxLayout;
	m_code = new TextEdit(code, dock);

	headerCode = new TextEdit(m_code->toPlainText());

	mainLayout->addWidget(m_code);

	fileWidget->setLayout(mainLayout);
	tabs->addTab(fileWidget, fileTitle);
	dock->setWidget(tabs);

	addDockWidget(Qt::RightDockWidgetArea, dock);

	//-------------------------------------------------
	fileWidget = new QWidget(this);
	tabs1 = new QTabWidget(dock);
	dock = new DockWidget(this);

	m_code = new TextEdit(codeImplementationFile, dock);

	cppCode = new TextEdit(m_code->toPlainText());

	mainLayout = new QVBoxLayout;

	mainLayout->addWidget(m_code);

	fileWidget->setLayout(mainLayout);
	tabs1->addTab(fileWidget, ImplementationFileTitle);
	dock->setWidget(tabs1);

	dock->setWidget(tabs1);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	//-------------------------------------------------------------

	dock = new DockWidget(this);
	treeWidget = new QTreeWidget(dock);
	treeWidget->setHeaderHidden(true);
	headerFiles = new QTreeWidgetItem(treeWidget);
	headerFiles->setIcon(0, QIcon("images/folder-icon.ico"));
	headerFiles->setText(0, tr("Header Files"));
	headerFileItem = new QTreeWidgetItem(headerFiles);
	headerFileItem->setText(0, fileTitle);
	headerFileItem->setIcon(0, QIcon("images/header.png"));

	cppFiles = new QTreeWidgetItem(treeWidget);
	cppFiles->setText(0, tr("Source Files"));
	cppFiles->setIcon(0, QIcon("images/folder-icon.ico"));

	cppFileItem = new QTreeWidgetItem(cppFiles);
	cppFileItem->setIcon(0, QIcon("images/cplusplus.ico"));
	

	cppFileItem->setText(0, ImplementationFileTitle);

	mainLayout = new QVBoxLayout;

	mainLayout->addWidget(treeWidget);
	fileWidget = new QWidget(this);
	fileWidget->setLayout(mainLayout);
	dock->setWidget(fileWidget);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	headerTitle = new QString(fileTitle);
	cppTitle = new QString(ImplementationFileTitle);

	connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(selectionnerFichier(QTreeWidgetItem*, int)));
}
void editorWindow::saveFile()
{
	QString headerFileName = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", *headerTitle, "Fichier d'en-tete C++ (*.h;*.hh;*.hpp;*.hxx;*.inl;*.ipp;*.tlh;*.tli)");
	QFile file(headerFileName);
	if (file.open(QIODevice::ReadWrite)) {
		QTextStream stream(&file);
		stream << headerCode->toPlainText() << endl;
	}
	QString CppFile = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", *cppTitle, "Fichier sources C++ (*.cc;*.c++;*.cxx;)");
	QFile file2(CppFile);
	if (file2.open(QIODevice::ReadWrite)) {
		QTextStream stream(&file2);
		stream << cppCode->toPlainText() << endl;
	}
}

void editorWindow::addMenuBar()
{
	QMenu* menu = new QMenu(this);
	menu = menuBar()->addMenu("Fichier");
	QAction* addFile = new QAction("Nouvelle classe");
	QAction* saveFile = new QAction("sauvegarder");
	menu->addAction(addFile);
	menu->addAction(saveFile);
	QObject::connect(saveFile, SIGNAL(triggered()), this, SLOT(saveFile()));
	QObject::connect(addFile, SIGNAL(triggered()), this, SLOT(addFileDialog()));
}

void editorWindow::addFileDialog()
{
	newClassDialog = new QDialog(this);

	formLayout = new QFormLayout;
	newClass = new QLineEdit();
	quitterDialog = new QPushButton("quitter");
	formLayout->addRow("Nouvelle classe : ", newClass);
	formLayout->addWidget(quitterDialog);
	newClassDialog->setLayout(formLayout);
	connect(quitterDialog, SIGNAL(clicked()), newClassDialog, SLOT(close()));

	connect(quitterDialog, SIGNAL(clicked()), this, SLOT(closeDialog()));

	newClassDialog->exec();
}

void editorWindow::closeDialog()
{
	newClassName = new QString(newClass->text());

	fileWidget = new QWidget;
	tabs1->addTab(fileWidget, *newClassName + ".cpp");
	QString code2 = "";

	m_code = new TextEdit(code2, dock);

	cppCode = new TextEdit(m_code->toPlainText());

	mainLayout = new QVBoxLayout;

	mainLayout->addWidget(m_code);

	fileWidget->setLayout(mainLayout);
	fileWidget = new QWidget;
	tabs->addTab(fileWidget, *newClassName + ".h");

	headerFileItem = new QTreeWidgetItem(headerFiles);
	headerFileItem->setText(0, *newClassName + ".h");
	QString code = "";

	m_code = new TextEdit(code, dock);

	cppCode = new TextEdit(m_code->toPlainText());

	mainLayout = new QVBoxLayout;

	mainLayout->addWidget(m_code);

	fileWidget->setLayout(mainLayout);

	cppFileItem = new QTreeWidgetItem(cppFiles);
	cppFileItem->setText(0, *newClassName + ".cpp");
	headerFileItem->setIcon(0, QIcon("images/header.png"));
	cppFileItem->setIcon(0, QIcon("images/cplusplus.ico"));

}

void editorWindow::selectionnerFichier(QTreeWidgetItem* item, int column)
{

	/*if (headerFileItem->isSelected() == true)
	{
	tabs->setCurrentIndex(0);
	}
	else if (cppFileItem->isSelected() == true) {
	tabs->setCurrentIndex(1);

	}*/

	for (int i = 0; i < cppFiles->childCount(); i++) {
		if (cppFiles->child(i)->isSelected()) {
			tabs1->setCurrentIndex(i);
		}
	}
	for (int g = 0; g < headerFiles->childCount(); g++) {

		if (headerFiles->child(g)->isSelected()) {
			tabs->setCurrentIndex(g);
		}
	}
}
