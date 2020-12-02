#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>

namespace SolverFunctions{
	int solveDay1(const QString input) {
		int solution1 = 0;
		int solution2 = 0;
		QVector<int> allNumbers_vector;

		QFile iFile(input + "Day1.txt");
		if (iFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream in(&iFile);
			while (!in.atEnd()) {
				allNumbers_vector.append(in.readLine().toInt());
			}
		}
		else {
			qDebug("File could not be opened!");
			return 0;
		}

		// Find solutions
		for (auto it = allNumbers_vector.cbegin(); it != allNumbers_vector.cend(); it++) {
			for (auto it2 = it + 1; it2 != allNumbers_vector.cend(); it2++) {
				if (*it + *it2 == 2020) {
					solution1 = (*it) * (*it2); // Solution for day 2
					qDebug("Solution 1 :" + QString::number(solution1).toLatin1());
				}
				for (auto it3 = it2 + 1; it3 != allNumbers_vector.cend(); it3++) {
					if (*it + *it2 + *it3 == 2020) {
						solution2 = (*it) * (*it2) * (*it3); // Solution for day 2
						qDebug("Solution 2 :" + QString::number(solution2).toLatin1());
					}
				}
			}
		}
	}
	}