#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

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

	int solveDay2(const QString input) {
		QFile iFile(input + "Day2.txt");
		if (iFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream in(&iFile);
			QRegularExpression re("(?<min>\\d+)-(?<max>\\d+)\\s(?<symbol>\\S):\\s(?<password>\\S+)");
			QRegularExpressionMatch match;
			int correctPassword_count[2] = {0,0};
			while (!in.atEnd()) {
				QString line = in.readLine();
				match = re.match(line);
				int min = match.captured("min").toInt();
				int max = match.captured("max").toInt();
				QString symbol = match.captured("symbol");
				QString password = match.captured("password");
				int count = password.count(symbol);

				if ((min <= password.count(symbol)) && (password.count(symbol) <= max)) {
					correctPassword_count[0]++;
				}
				QChar testing = password.at(min-1);
				if (symbol == password.at(min-1) ^ symbol == password.at(max-1)) {
					correctPassword_count[1]++;
				}
			}
			qDebug("Solution 1 :" + QString::number(correctPassword_count[0]).toLatin1());
			qDebug("Solution 2 :" + QString::number(correctPassword_count[1]).toLatin1());
		}
		else {
			qDebug("File could not be opened!");
			return 0;
		}
	}
}