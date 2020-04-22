// Include Statements
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <QGLWidget>
#include <string>
#include <fstream>
#include <iostream>
#include "openglwidget.h"
// Include Statements

using namespace std;

// Constructor
OpenGLWidget::OpenGLWidget(QWidget *parent)
	: QGLWidget(parent)
{
}

// Destructor
OpenGLWidget::~OpenGLWidget()
{
}

// Function to Draw Leaf
void OpenGLWidget::DrawLeaf(double r, int lats, int longs)
{
	// Set color to green
	glColor3f(0.0, 0.5, 0.0);

	// Create a quad
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	// Draw a sphere as a leaf
	gluSphere(quadratic, r, lats, longs);

	// Reset color to brown
	glColor3f(0.3, 0.13, 0.12);
}

// Function to draw a tapered cylinder for trunk or branch
void OpenGLWidget::DrawTaperedCylinder(double base, double top, double height)
{
	// Create a quad
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	// Draw cylinder
	gluCylinder(quadratic, base, top, height, 32, 1);
}

// Initialize OpenGL
void OpenGLWidget::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0, 0.0, 1.0, 1.0);
}
// Resize OpenGL
void OpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);

	// set projection matrix to be glOrtho based on zoom & window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// compute the aspect ratio of the widget
	float aspectRatio = (float)w / (float)h;

	// Set the projection matrix
	gluPerspective(90.0, aspectRatio, 2, 500);
}

// PainGL Function
void OpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the view matrix
	gluLookAt(0.0, 25, 100,   //position
		0, 0, -100.0,   //where we are looking
		0.0, 1.0, 0.0); //up vector

	glPushMatrix();
	glPushMatrix();

	glTranslatef(0.0, -30.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glPushMatrix();

	// Draw the tree
	DrawTree(8, 3.5, false);

	glPopMatrix();
	glPopMatrix();
}

// Function to parse grammer from Lsys file
void OpenGLWidget::ParseLSystem(const char *filename)
{
	// Open the Lsys file
	std::ifstream inputFile;
	inputFile.open(filename);

	if (!inputFile.is_open())
	{
		throw "Error opening file";
	}

	// Parse through each string in the file
	string tempString;
	while (!inputFile.eof())
	{
		// Read the grammer type
		inputFile >> tempString;

		// If the grammer is for trunk, store it in trunk grammer
		if (tempString == "trunk:")
			inputFile >> TrunkFormula;
		// If the grammer is for branch, store it in branch grammer
		else if (tempString == "branch:")
			inputFile >> BranchFormula;
	}
}

// Function to draw trunk or branch of tree
void OpenGLWidget::DrawTree(int depth, double radius, bool isBranch)
{
	// Set the matrix mode to model view 
	glMatrixMode(GL_MODELVIEW);

	// Check whether the depth is zero or the radius is too small
	if (depth == 0 || radius <= 0.2)
	{
		// Then draw the leaf and stop recursion
		DrawLeaf(1.0, 2, 2);
		return;
	}

	//  Set the grammer
	std::string grammer = TrunkFormula;
	if (isBranch)
		grammer = BranchFormula;

	// Set the color to brown
	glColor3f(0.3, 0.13, 0.12);

	// Parse the grammer
	for (int i = 0; grammer[i] != '\0'; i++)
	{
		// Grammer to grow the trunk or branch
		if (grammer[i] == 'F')
		{
			// Find the heigh of the cylinder
			int beginPos = grammer.find('(');
			int endPos = grammer.find(')');
			std::string valueStr = grammer.substr(beginPos + 1, endPos - beginPos - 1);
			float value = std::stof(valueStr);

			// Draw the cylinder
			DrawTaperedCylinder(radius, radius - 0.2, depth * value);
			radius -= 0.2;

			// Translate so that next branch grows from the top of this trunk or branch
			glTranslatef(0.0, 0.0, depth * value);
		}

		// Rotations specified within []
		else if (grammer[i] == '[')
		{
			// Push Matrix into stack
			glPushMatrix();
			float xrotation = 0, yrotation = 0, zrotation = 0;
			while (grammer[i] != ']')
			{
				// Clockwise Rotation around left vector
				if (grammer[i] == '&')
				{
					std::string valueStr = grammer.substr(i + 1, 3);
					xrotation = atoi(valueStr.c_str());
				}
				// Counter-clockwise Rotation around left vector
				if (grammer[i] == '^')
				{
					std::string valueStr = grammer.substr(i + 1, 3);
					xrotation = -atoi(valueStr.c_str());
				}
				// Clockwise Rotation around up vector
				if (grammer[i] == '+')
				{
					std::string valueStr = grammer.substr(i + 1, 3);
					yrotation = atoi(valueStr.c_str());
				}
				//Counter-clockwise Rotation around up vector
				if (grammer[i] == '-')
				{
					std::string valueStr = grammer.substr(i + 1, 3);
					yrotation = -atoi(valueStr.c_str());
				}
				//Clockwise Rotation around forward vector
				if (grammer[i] == '/')
				{
					std::string valueStr = grammer.substr(i + 1, 3);
					zrotation = atoi(valueStr.c_str());
				}
				//Counter - clockwise Rotation around forward vector
				if (grammer[i] == '\\')
				{
					std::string valueStr = grammer.substr(i + 1, 3);
					zrotation = -atoi(valueStr.c_str());
				}
				// If a branch or Twig appears in the grammer, do the rotations
				if (grammer[i] == 'B' || grammer[i] == 'T')
				{
					// Rotation around x,y,z axes
					glRotatef(xrotation, 1.0, 0.0, 0.0);
					glRotatef(yrotation, 0.0, 1.0, 0.0);
					glRotatef(zrotation, 0.0, 0.0, 1.0);

					// If a branch appears in the grammer, call the recursion
					if (grammer[i] == 'B')
					{
						std::string stringval = grammer.substr(i, 6);
						if (stringval == "Branch")
						{
							DrawTree(depth - 1, radius, true);
						}
						else
						{
							throw "Incorrect Grammer";
						}
					}
					// If a twig appears in the grammer, render a twig
					else
					{
						std::string stringval = grammer.substr(i, 4);
						if (stringval == "Twig")
						{
							DrawTaperedCylinder(0.4, 0.2, 1.0);
							DrawLeaf(1.0, 2, 2);
						}
						else
						{
							throw "Incorrect Formula";
						}
					}
				}
				i++;
			}
			// Pop matrix out of stack
			glPopMatrix();
		}
	}
}