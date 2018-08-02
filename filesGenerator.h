#pragma once
#include <QtWidgets>

class filesGenerator : public QWidget {
	Q_OBJECT

public:
	filesGenerator(QWidget* parent = Q_NULLPTR);
	~filesGenerator();

private:
	QLineEdit * m_nom;
	QLineEdit* m_classeMere;
	QCheckBox* m_protections;
	QCheckBox* m_constructeur;
	QCheckBox* m_destructeur;
	//QCheckBox *commentaire;
	QLineEdit* m_auteur;
	//QLineEdit *m_date;
	QTextEdit* m_role;
	QPushButton* m_generer;

public slots:
	void openDialog();
};
