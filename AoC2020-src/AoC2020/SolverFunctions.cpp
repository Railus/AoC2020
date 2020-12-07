#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <cstdlib>

typedef struct{
	int x;
	int y;
} Point;

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
					qDebug("Solution 1 : " + QString::number(solution1).toLatin1());
				}
				for (auto it3 = it2 + 1; it3 != allNumbers_vector.cend(); it3++) {
					if (*it + *it2 + *it3 == 2020) {
						solution2 = (*it) * (*it2) * (*it3); // Solution for day 2
						qDebug("Solution 2 : " + QString::number(solution2).toLatin1());
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
			qDebug("Solution 1 : " + QString::number(correctPassword_count[0]).toLatin1());
			qDebug("Solution 2 : " + QString::number(correctPassword_count[1]).toLatin1());
		}
		else {
			qDebug("File could not be opened!");
			return 0;
		}
	}

#define NUMBER_OF_SLOPES 5
	int solveDay3(const QString input) {
		QFile iFile(input + "Day3.txt");
		if (iFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream in(&iFile);
			int trees_count[NUMBER_OF_SLOPES] = {0,0,0,0,0};
			Point currentPosition[NUMBER_OF_SLOPES] = { {0,0},{0,0},{0,0},{0,0},{0,0} };
			Point slope[NUMBER_OF_SLOPES] = {	{1,1},
												{3,1},
												{5,1},
												{7,1},
												{1,2},
			};
			memset(currentPosition, 0, sizeof(Point)* NUMBER_OF_SLOPES);
			while (!in.atEnd()) {
				QString line = in.readLine();
				int positions_to_test = NUMBER_OF_SLOPES;
				if (currentPosition[0].y != currentPosition[NUMBER_OF_SLOPES-1].y) {
					positions_to_test = NUMBER_OF_SLOPES - 1;
				}
				for (int i = 0; i < positions_to_test; i++) {
					currentPosition[i].x %= line.length();
					if ('#' == line.at(currentPosition[i].x)) {
						trees_count[i]++;
					}
					currentPosition[i].x += slope[i].x;
					currentPosition[i].y += slope[i].y;
				}

			}
			int multiplied_trees = 1;
			for (int i = 0; i < NUMBER_OF_SLOPES; i++) {
				multiplied_trees *= trees_count[i];
			}
			qDebug("Solution 1 : " + QString::number(trees_count[1]).toLatin1());
			qDebug("Solution 2 : " + QString::number(multiplied_trees).toLatin1());
		}
		else {
			qDebug("File could not be opened!");
			return 0;
		}
	}

	int solveDay4(const QString input) {
		const int minHeight_cm = 150;
		const int maxHeight_cm = 193;
		const int minHeight_in = 59;
		const int maxHeight_in = 76;
		const int minimumMatches = 7;
		QFile iFile(input + "Day4.txt");
		if (iFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream in(&iFile);

			QVector<QRegularExpression> expressions;
			expressions.append(QRegularExpression("byr:(?<byr>(19[2-9][0-9])|(200[0-2]))"));
			expressions.append(QRegularExpression("iyr:(?<iyr>(201[0-9])|(2020))"));
			expressions.append(QRegularExpression("eyr:(?<eyr>(202[0-9])|(2030))"));
			expressions.append(QRegularExpression("hgt:(?<hgt>\\d+)(?<unit>\\S+)"));
			expressions.append(QRegularExpression("hcl:#(?<hcl>(\\d|[a-f]){6})"));
			expressions.append(QRegularExpression("ecl:(?<ecl>((amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth)))"));
			expressions.append(QRegularExpression("pid:(((?<pid>[0-9]{9})$)|([0-9]{9}\\s))"));
			QRegularExpressionMatch match;

			int valid_passports_count = 0;
			int match_count = 0;

			while (!in.atEnd()) {
				QString line = in.readLine();
				if (line.isEmpty()) {
					if (match_count >= minimumMatches) {
						valid_passports_count++;
					}
					match_count = 0;
				}
				for (auto i = expressions.cbegin(); i != expressions.cend(); i++) {
					match = i->match(line);
					if(match.hasMatch()){
						if (NULL != match.captured("hgt")) {
							int heightValue = match.captured("hgt").toInt();
							if ("cm" == match.captured("unit")) {
								if ((minHeight_cm <= heightValue) && (heightValue <= maxHeight_cm)) {
									match_count++;
								}
							}
							else if ("in" == match.captured("unit")) {
								if ((minHeight_in <= heightValue) && (heightValue <= maxHeight_in)) {
									match_count++;
								}
							}
						}
						else {
							match_count++;
						}
					}
				}
			}

			if (match_count == minimumMatches) {
				valid_passports_count++;
			}
			qDebug("Solution 2: " + QString::number(valid_passports_count).toLatin1());
		}
		else {
			qDebug("File could not be opened!");
			return 0;
		}
	}

	int convertBinaryToDecimal(int byteArray);
	bool IntLessThan(const int &v1, const int &v2);
	int solveDay5(const QString input) {
		QFile iFile(input + "Day5.txt");

		//int highestPossibleID = convertBinaryToDecimal(1111111) * 8 + convertBinaryToDecimal(111);
		QVector<int> allIDs;
		int highestID = 0;
		if (iFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream in(&iFile);

			while (!in.atEnd()) {
				QString line = in.readLine();

				line.replace("B","1");
				line.replace("F", "0");
				line.replace("L", "0");
				line.replace("R", "1");

				QString row_binary = line.left(7);
				QString column_binary = line.right(3);
				int row_decimal = convertBinaryToDecimal(row_binary.toInt());
				int column_decimal = convertBinaryToDecimal(column_binary.toInt());

				allIDs.push_back(row_decimal * 8 + column_decimal);

			}
			qSort(allIDs.begin(), allIDs.end(), IntLessThan);
			int mySeat = allIDs.first();
			for (auto i = allIDs.begin(); i != allIDs.end(); i++) {
				if (mySeat != *i) {
					break;
				}
				mySeat++;
			}
			int max = allIDs.last();
			qDebug("Solution 1: " + QString::number(max).toLatin1());
			qDebug("Solution 2: " + QString::number(mySeat).toLatin1());
		}
		else {
			qDebug("File could not be opened!");
			return 0;
		}
	}

	int convertBinaryToDecimal(int byteArray) {
		int decimalNumber = 0, i = 0, remainder;
		while (byteArray != 0)
		{
			remainder = byteArray % 10;
			byteArray /= 10;
			decimalNumber += remainder * pow(2, i);
			++i;
		}
		return decimalNumber;
	}

	bool IntLessThan(const int &v1, const int &v2)
	{
		return v1 < v2;
	}

	int solveDay6(const QString input) {

		QVector<QChar> anyYesOfOneGroup;
		QVector<QChar> everyYesOfOneGroup;
		QVector<int> numberOfAnyYesPerGroup;
		QVector<int> numberOfEveryYesPerGroup;
		QVector<QChar> onePersonsYesAnswers;

		QFile iFile(input + "Day6.txt");
		if (iFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream in(&iFile);
			while (!in.atEnd()) {
				QString line = in.readLine();

				bool firstEntry = anyYesOfOneGroup.isEmpty();
				onePersonsYesAnswers.clear();
				for (int i = 0; i < line.size(); i++) {
					QChar answer = line.at(i);
					if (!anyYesOfOneGroup.contains(answer)) {
						anyYesOfOneGroup.push_back(answer);
					}

					if (firstEntry) {
						everyYesOfOneGroup.push_back(answer);
					}
					else {
						onePersonsYesAnswers.push_back(answer);
					}
				}
				if(!firstEntry && !line.isEmpty()){
					QVector<QChar> duplicates;
					for (auto i = everyYesOfOneGroup.begin(); i != everyYesOfOneGroup.end(); i++) {
						if (onePersonsYesAnswers.contains(*i)) {
							duplicates.push_back(*i);
						}
					}
					everyYesOfOneGroup.clear();
					everyYesOfOneGroup = duplicates;
				}


				if (line.isEmpty()) {
					if (!anyYesOfOneGroup.isEmpty()) {
						numberOfAnyYesPerGroup.push_back(anyYesOfOneGroup.count());
						numberOfEveryYesPerGroup.push_back(everyYesOfOneGroup.count());
					}
					everyYesOfOneGroup.clear();
					anyYesOfOneGroup.clear();
				}
			}

			if (!anyYesOfOneGroup.isEmpty()) {
				numberOfAnyYesPerGroup.push_back(anyYesOfOneGroup.count());
				numberOfEveryYesPerGroup.push_back(everyYesOfOneGroup.count());
			}
		}
		else {
			qDebug("File could not be opened!");
			return 0;
		}

		int sum = 0;
		for (auto i = numberOfAnyYesPerGroup.cbegin(); i != numberOfAnyYesPerGroup.cend(); i++) {
			sum += *i;
		}
		qDebug("Solution 1: " + QString::number(sum).toLatin1());

		sum = 0;
		for (auto i = numberOfEveryYesPerGroup.cbegin(); i != numberOfEveryYesPerGroup.cend(); i++) {
			sum += *i;
		}
		qDebug("Solution 2: " + QString::number(sum).toLatin1());
	}
}