// Include Statements
#include <QtWidgets/QApplication>
#include <iostream>
#include "Tree.h"
// Include Statements

// Main Function
int main(int argc, char *argv[])
{
	// Check for inline argument count
	if (argc < 2)
	{
		std::cout << "Usage: ./Tree filename";
		return -1;
	}
	// Start the QT application
	QApplication a(argc, argv);

	// Initialize the Tree Window
	Tree w;
	
	// Parse the input file for grammer
	w.ParseLsysFile(argv[1]);

	// Show the window
	w.show();
	return a.exec();
}
