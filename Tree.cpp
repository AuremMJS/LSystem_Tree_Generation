// Include Statements
#include "Tree.h"
// Include Statements

// Constructor
Tree::Tree(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

// Function to parse the grammer from file
void Tree::ParseLsysFile(const char* filename)
{
	ui.openGLWidget->ParseLSystem(filename);
}