#include <windows.h>
#include <QApplication>
#include <QSettings>
#include <QFileDialog>
#include <vector>
#include <sstream>
#include <iterator>
#include "main.h"
#include <stdio.h>
#include <iostream>
#include <qfile.h>
#include <QTextStream>
#include <QVector>
#include "SolverFunctions.h"

const QString inputDirectory = QString("C:/Users/simon/Documents/Git Ordner/AoC2020/AoC2020-src/AoC2020/PuzzleInput/");

int main(int argc, char *argv[])
{
	SolverFunctions::solveDay1(inputDirectory);
}
