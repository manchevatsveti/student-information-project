#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void printMenu();

//main menu actions
void addingStudent(string fileName, string fn, string name, string countSubjects);
void deletingStudent(string facultyNumberToDelete, string fileName);
void sortStudents(int sortBy, int sortOrder, string fileName);
void printFile(string fileName);
void printMultipleFiles(int countGroups);

//utility functions
void writingInVectorBasedOnSortCriteria(string fileName, int sortBy, vector<string>& students);
void rewriteVector(vector<string>& students);
void writingInFileInAscendingOrder(vector<string>& students, string fileName);
void writingInFileInDescendingOrder(vector<string>& students, string fileName);
string fileNameGenerator(string groupNum);
void combineMultipleFilesInOne(int countGroups);

//validation functions
bool userInputValidation(string input);
bool isFnUnique(string fileName, string fn);
bool isGroupNumberValid(string group);
bool isSortCriteriaValid(int sortCriteria);

int main() {

	string sortBy, sortOrder, input, fn, name, countSubjects, countGroupsToPrint, student, group, fileName;
	bool isInputValid = false, validCountSubjects = false, validCountGroups = false, validGroupNumber = false, validFn = false, validSortCriteria = false;

	cout << "Group: " << endl;
	while (!validGroupNumber) {
		getline(cin, group);
		validGroupNumber = isGroupNumberValid(group);

		if (!validGroupNumber) {
			cout << "Invalid input. Please enter a number from 1 to 8." << endl;
		}
	}
	fileName = fileNameGenerator(group);

	printMenu();

	while (getline(cin, input)) {

		isInputValid = userInputValidation(input);

		if (!isInputValid) {
			cout << "Invalid input. Please enter a number from 1 to 6." << endl;
		}
		else {
			switch (stoi(input)) {
			case 1:
				cout << "Faculty number:" << endl;
				while (!validFn) {
					getline(cin, fn);
					validFn = isFnUnique(fileName, fn);

					if (!validFn) {
						cout << "This faculty number already exists. Please try again." << endl;
					}
				}
				validFn = false;

				cout << "Name of student:" << endl;
				getline(cin, name);
				cout << "Number of subjects studied: " << endl;
				while (!validCountSubjects) {
					getline(cin, countSubjects);
					if (stoi(countSubjects) < 1 || stoi(countSubjects) > 10) {
						cout << "Count should be between 1 and 10. Please try again!" << endl;
					}
					else {
						validCountSubjects = true;
					}
				}
				addingStudent(fileName, fn, name, countSubjects);
				break;
			case 2:
				cout << "Enter the faculty number of the student you want to delete: " << endl;
				getline(cin, fn);
				deletingStudent(fn, fileName);
				break;
			case 3:
				cout << "Sort by: " << endl << "1. Faculty number" << endl << "2. Average score" << endl;

				while (validSortCriteria != true) {
					getline(cin, sortBy);
					validSortCriteria = isSortCriteriaValid(stoi(sortBy));
					if (!validSortCriteria) {
						cout << "Choose between opion 1 and 2. Please try again!" << endl;
					}
				}
				validSortCriteria = false;

				cout << endl << "1. Ascending order" << endl << "2. Descending order" << endl;

				while (validSortCriteria != true) {
					getline(cin, sortOrder);
					validSortCriteria = isSortCriteriaValid(stoi(sortOrder));
					if (!validSortCriteria) {
						cout << "Choose between opion 1 and 2. Please try again!" << endl;
					}
				}
				validSortCriteria = false;

				sortStudents(stoi(sortBy), stoi(sortOrder), fileName);
				break;
			case 4:
				printFile(fileName);
				break;
			case 5:
				cout << "Number of groups to print: " << endl;
				while (validCountGroups != true) {
					getline(cin, countGroupsToPrint);
					if (stoi(countGroupsToPrint) < 1 || stoi(countGroupsToPrint) > 8) {
						cout << "Count should be between 1 and 8. Please try again!" << endl;
					}
					else {
						validCountGroups = true;
					}
				}
				printMultipleFiles(stoi(countGroupsToPrint));
				validCountGroups = false;
				break;
			case 6:
				return 0;
			}

			printMenu();
		}
	}
}

void printMenu() {
	cout << "Choose your option: " << endl;
	cout << "1. Add a student" << endl;
	cout << "2. Delete a student" << endl;
	cout << "3. Sort the students " << endl;
	cout << "4. Print group members " << endl;
	cout << "5. Print group members from multiple groups " << endl;
	cout << "6. Exit " << endl;

}

//main menu actions
void addingStudent(string fileName, string fn, string name, string countSubjects) {
	string tempGrade;
	fstream File;
	double sumGrades = 0, averageScore = 0;

	string* subjects = new string[stoi(countSubjects)];//creating an array with all the subjects
	int* grades = new int[stoi(countSubjects)];//creating an array with all the grades

	for (size_t i = 0; i < stoi(countSubjects); i++) {
		cout << "Subject " << i + 1 << ":" << endl;
		getline(cin, subjects[i]);

		cout << "Grade:" << endl;
		getline(cin, tempGrade);

		grades[i] = stoi(tempGrade);
		sumGrades += grades[i];//sum all grades
	}
	averageScore = sumGrades / stoi(countSubjects);//average score of all grades

	File.open(fileName, std::fstream::out | std::fstream::app);//writing in file
	File << fn << ":" << name;

	for (size_t i = 0; i < stoi(countSubjects); i++) {
		File << ":" << subjects[i] << "-" << grades[i];
	}
	File << "; average score /" << averageScore;
	File << endl;

	delete[] subjects;
	delete[] grades;

	File.close();
}

void deletingStudent(string facultyNumberToDelete, string fileName) {
	fstream File;
	string buffer, facultyNumber;
	bool isStudentDeleted = false;

	vector<string> students;

	File.open(fileName, std::fstream::in);

	if (File.is_open()) {
		while (getline(File, buffer) && buffer.size() > 0) {

			int i = 0;
			while (i < buffer.size() && buffer[i] != ':') {//looping through the array until ':', meaning that is the end of the faculty number, based on how we store the student's information

				facultyNumber += buffer[i++];

			}
			if (facultyNumber != facultyNumberToDelete) {//if the faculty number is not the one we want to delete, then we push this line from the file into the array
				students.push_back(buffer);
			}
			else if (facultyNumber == facultyNumberToDelete) {
				isStudentDeleted = true;
				cout << "The student was successfully deleted!" << endl;
			}
			facultyNumber.clear();//clearing the faculty number for the next student
		}
		if (!isStudentDeleted) {
			cout << "There is not a student with this faculty number in this group." << endl;
		}

		File.close();

		writingInFileInAscendingOrder(students, fileName);
	}
}

void sortStudents(int sortBy, int sortOrder, string fileName) {
	vector<string> students;

	writingInVectorBasedOnSortCriteria(fileName, sortBy, students);

	sort(students.begin(), students.end());

	if (sortBy == 2) {//if we sorted the vector based on average score, rewriting the elements, so when we write back in the file, the inforamtion is in its noramal order
		rewriteVector(students);
	}

	if (sortOrder == 1) {//ascending order
		writingInFileInAscendingOrder(students, fileName);
	}
	else if (sortOrder == 2) {//descending order
		writingInFileInDescendingOrder(students, fileName);
	}
}

void printFile(string fileName) {
	fstream File;
	string buffer, name, facultyNumber, averageScore;

	File.open(fileName, std::fstream::in);

	if (File.is_open()) {
		while (getline(File, buffer) && buffer.size() > 0) {

			int i = 0;
			while (i < buffer.size() && buffer[i] != ':') {
				facultyNumber += buffer[i++];
			}
			cout << "Fn: " << facultyNumber;
			i++; // in order to skip the ':'

			while (i < buffer.size() && buffer[i] != ':') {
				name += buffer[i++];
			}
			cout << " Student: " << name;
			i++;

			while (i < buffer.size() && buffer[i] != '/') {
				i++;
			}
			i++;
			while (i < buffer.size()) {
				averageScore += buffer[i++];
			}
			cout << " Average score: " << averageScore << endl;

			facultyNumber.clear();
			name.clear();
			averageScore.clear();
		}
	}
	File.close();
}

void printMultipleFiles(int countGroups) {
	string sortBy, sortOrder;

	combineMultipleFilesInOne(countGroups);

	cout << "Sort by: " << endl << "1. Faculty number" << endl << "2. Average score" << endl;
	getline(cin, sortBy);
	cout << endl << "1. Ascending order" << endl << "2. Descending order" << endl;
	getline(cin, sortOrder);
	sortStudents(stoi(sortBy), stoi(sortOrder), "bundle.txt");

	printFile("bundle.txt");
}

//utility functions
void writingInVectorBasedOnSortCriteria(string fileName, int sortBy, vector<string>& students) {
	fstream File;
	string buffer, averageScore, studentInfo;

	File.open(fileName, std::fstream::in);

	if (File.is_open()) {
		while (getline(File, buffer) && buffer.size() > 0) {
			if (sortBy == 1) {//by faculty number
				students.push_back(buffer);//because the faculty numbers are the first stored information for every student, we do not need to make any changes to sort the list
			}
			else if (sortBy == 2) {//by average score
				int i = 0;
				while (i < buffer.size() && buffer[i] != '/') {//until we get to the number that shows the average score

					studentInfo += buffer[i++];

				}
				i++;//skipping the '/'
				while (i < buffer.size()) {

					averageScore += buffer[i++];//storing the average score that stays at the end of every line in the file, in different string, so that we can paste it to the front and sort the elements based on it

				}
				students.push_back(averageScore + "//" + studentInfo);

				studentInfo.clear();
				averageScore.clear();
			}

		}
	}
	File.close();
}

void rewriteVector(vector<string>& students) {//rewriting the vector in its original format(average score is in the end of every line)
	string averageScore, studentInfo;

	for (int i = 0; i < students.size(); ++i)
	{
		int j = 0;
		while (j < students[i].size() && students[i][j] != '/') {
			averageScore += students[i][j];
			j++;

		}
		j += 2;
		while (j < students[i].size()) {
			studentInfo += students[i][j++];
		}
		students[i] = (studentInfo + "/" + averageScore);//returning the average score back to the end of the string
		studentInfo.clear();
		averageScore.clear();
	}
}

void writingInFileInAscendingOrder(vector<string>& students, string fileName) {
	fstream File;

	File.open(fileName, std::fstream::out);

	for (int i = 0; i < students.size(); ++i)
	{
		File << students[i] << endl;
	}

	File.close();
}

void writingInFileInDescendingOrder(vector<string>& students, string fileName) {
	fstream File;

	File.open(fileName, std::fstream::out);

	for (int i = students.size() - 1; i >= 0; i--)
	{
		File << students[i] << endl;
	}

	File.close();
}

string fileNameGenerator(string groupNum) {
	string fileName = "group_";
	fileName += groupNum;
	fileName += ".txt";

	return fileName;
}

void combineMultipleFilesInOne(int countGroups) {
	fstream File;
	string fileBundle = "bundle.txt", buffer;
	bool validGroupNumber = false;

	string* groups = new string[countGroups];//creating an array with all the grades

	for (size_t i = 0; i < countGroups; i++) {
		cout << "Group " << i + 1 << ":" << endl;

		while (!validGroupNumber) {
			getline(cin, groups[i]);
			validGroupNumber = isGroupNumberValid(groups[i]);

			if (!validGroupNumber) {
				cout << "Invalid input. Please enter a number from 1 to 8." << endl;
			}
		}
		validGroupNumber = false;

		File.open(fileBundle, std::fstream::out);

		for (size_t i = 0; i < countGroups; i++) {
			fstream FileTemp;
			FileTemp.open(fileNameGenerator(groups[i]), std::fstream::in);

			if (FileTemp.is_open()) {
				while (getline(FileTemp, buffer) && buffer.size() > 0) {
					File << buffer << endl;
				}
			}
			FileTemp.close();
		}
		File.close();
	}
}

//validation functions
bool userInputValidation(string input) {
	bool isValidInput = true;

	if (stoi(input) < 1 || stoi(input) > 6) {
		isValidInput = false;
	}
	return isValidInput;
}

bool isFnUnique(string fileName, string fn) {
	fstream File;
	string buffer, facultyNumber;
	bool isUnique = true;

	File.open(fileName, std::fstream::in);

	if (File.is_open()) {
		while (getline(File, buffer) && buffer.size() > 0) {

			int i = 0;
			while (i < buffer.size() && buffer[i] != ':') {
				facultyNumber += buffer[i++];
			}
			if (fn == facultyNumber) {
				isUnique = false;
				break;
			}
			facultyNumber.clear();
		}
	}
	File.close();
	return isUnique;
}

bool isGroupNumberValid(string group) {
	bool isValid = true;
	if (stoi(group) < 1 || stoi(group) > 8) {
		isValid = false;;
	}
	return isValid;
}

bool isSortCriteriaValid(int sortCriteria) {
	bool isValid = false;

	if (sortCriteria == 1 || sortCriteria == 2) {
		isValid = true;
	}

	return isValid;
}

