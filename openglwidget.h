#pragma once
// Include Statements
#include <QGLWidget>
#include <QMouseEvent>
// Include Statements

// Class OpenGLWidget to render the OpenGL Elements into the window
class OpenGLWidget : public QGLWidget
{
	Q_OBJECT


private:

// Grammer to construct the trunk
std::string TrunkFormula;

// Grammer to construct a branch
std::string BranchFormula;

public:

	// Constructor
	OpenGLWidget(QWidget *parent);

	// Destructor
	~OpenGLWidget();

	// Function to parse the grammer from file
	void ParseLSystem(const char* filename);


protected:

	// OpenGL functions
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	// Function to draw leaf
	void DrawLeaf(double r, int lats, int longs);

	// Function to draw a cylinder for trunk or a branch
	void DrawTaperedCylinder(double base,double top,double height);

	// Function to draw trunk or branch
	void DrawTree(int depth,double width,bool isBranch);
};
