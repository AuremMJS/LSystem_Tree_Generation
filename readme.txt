# University of Leeds 2019-2020
# COMP 582M1 Assignment 2
# Manigandan Rajan
# 201378895
#
# Tree using L-Systems
#

This is a program that generates a tree based on the grammer specified in ".Lsys" file

".Lsys" files should contain the grammer for a trunk and a branch as given in the following example:
	trunk: F(3.0f)[-30Branch][+30Branch]F(0.01f)[^40Branch][&40Branch]
	branch: F(1.0f)[-30Twig][+30Twig]F(1.0f)[-30Branch][+30Branch]F(1.0f)[^40Branch][&40Branch][-30Twig][+30Twig] 

To compile on the University Linux machines, you will need to use the following command:

[userid@machine Tree]$ module add qt/5.3.1
[userid@machine Tree]$ qmake -project QT+=opengl LIBS+=-lGLU CONFIG += c++11
[userid@machine Tree]$ qmake
[userid@machine Tree]$ make

To execute the program, pass the file name on the command line like below:

[userid@machine Tree]$ ./Tree Tree1.Lsys