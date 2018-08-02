#include "filesGenerator.h"
#include <QtWidgets>
#include "editorWindow.h"
filesGenerator::filesGenerator(QWidget* parent)
	: QWidget(parent)
{
	setWindowTitle("Generateur de classe C++");
	m_nom = new QLineEdit(this);
	m_classeMere = new QLineEdit(this);
	m_protections = new QCheckBox("Proteger le &header contre les multiples inclusions", this);
	m_constructeur = new QCheckBox("Generer un constructeur par defaut", this);
	m_destructeur = new QCheckBox("Generer un destructeur", this);
	m_auteur = new QLineEdit(this);
	m_role = new QTextEdit(this);
	m_generer = new QPushButton("Generer");

	QFormLayout* form = new QFormLayout;
	form->addRow("Nom :", m_nom);
	form->addRow("Classe mere :", m_classeMere);
	form->addWidget(m_protections);
	form->addWidget(m_constructeur);
	form->addWidget(m_destructeur);
	//VerticalLayout->addWidget(commentaire);
	form->addRow("Auteur :", m_auteur);
	//VerticalLayout->addWidget(m_date);
	form->addRow("Role de la classe :", m_role);
	form->addWidget(m_generer);

	this->setLayout(form);

	QObject::connect(m_generer, SIGNAL(clicked()), this, SLOT(openDialog()));
}

void filesGenerator::openDialog()
{
	if (m_nom->text().isEmpty() || m_classeMere->text().isEmpty() || m_auteur->text().isEmpty()) {
		QMessageBox::warning(this, "Attention", "Tous les champs sont obligatoires exceptes les cases !");
	}
	else {

		QString codeHeaderFile;
		QString codeImplementationFile;
		if (m_protections->isChecked()) {
			codeHeaderFile = "/* <br/>auteur : " + m_auteur->text() + " <br/>date de creation : "
				+ QDate::currentDate().toString() + "<br/><br/> Role : " + m_role->toPlainText() + " <br/>*/<br/><br/>ifndef HEADER_" +
				m_nom->text().toUpper() + "<br/>#define HEADER_" + m_nom->text().toUpper() + "<br/><br/>class " + m_nom->text() + " : public " 
				+ m_classeMere->text() + "<br/>{<br/>public:<br/>" + m_nom->text() + "()<br/><br/><br/>private:<br/><br/><br/>}<br/><br/>#endif";
		}
		else {
			codeHeaderFile = "/* <br/>auteur : " + m_auteur->text() + " <br/>date de creation : "
				+ QDate::currentDate().toString() + "<br/><br/> Role : " + m_role->toPlainText() + " <br/>*/<br/><br/>"
				"class "
				+ m_nom->text() + " : public " + m_classeMere->text() + "<br/>{<br/>public:<br/>" + m_nom->text() + "()<br/><br/><br/>private:<br/><br/><br/>}";
		}

		QString fileTitleHeaderFile = m_nom->text() + ".h";
		QString ImplementationFileTitle = m_nom->text() + ".cpp";
		codeImplementationFile = "#include '" + fileTitleHeaderFile + "'<br/><br/>" + m_nom->text() + "::" + m_nom->text()
			+ "(){<br/><br/>}";

		editorWindow* f = new editorWindow(codeHeaderFile, fileTitleHeaderFile, codeImplementationFile, ImplementationFileTitle, this);
	
		f->show();
	}
}

filesGenerator::~filesGenerator()
{
}

