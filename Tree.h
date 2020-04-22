#pragma once

// Include Statements
#include <QtWidgets/QMainWindow>
#include "ui_Tree.h"
// Include Statements

// QT Window to render the tree
class Tree : public QMainWindow
{
	Q_OBJECT

public:
	// Constructor
	Tree(QWidget *parent = Q_NULLPTR);

	// Function to parse the grammer from file
	void ParseLsysFile(const char* filename);
private:
	Ui::TreeClass ui;
};
