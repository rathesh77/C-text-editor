#pragma once

#include <QDockWidget>

class DockWidget : public QDockWidget
{
	Q_OBJECT

public:
	DockWidget(QWidget *parent);
	~DockWidget();
};
