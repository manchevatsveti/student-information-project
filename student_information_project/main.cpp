/**
*
* Solution to course project # 05
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Tsvetelina Mancheva
* @idnumber 0MI0600239
* @compiler GCC 
*
* <main code file>
*
*/


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
void printMultipleFiles(int countGroups, string* groups, string sortBy, string sortOrder);

//utility functions
void writingInVectorBasedOnSortCriteria(string fileName, int sortBy, vector<string>& students);
void rewriteVector(vector<string>& students);
void writingInFileInAscendingOrder(vector<string>& students, string fileName);
void writingInFileInDescendingOrder(vector<string>& students, string fileName);
string fileNameGenerator(string groupNum);
void combineMultipleFilesInOne(int countGroups, string* groups);

//validation functions
bool isGroupNumberValid(string group);
bool userInputValidation(string input);
bool isFnUnique(string fileName, string fn);
bool isCountSubjectsValid(string countSubjects);
bool isSortCriteriaValid(int sortCriteria);
bool isGradeValid(string grade);
bool isNumber(string s);

int main() {
	string sortBy, sortOrder, input, fn, name, countSubjects, countGroupsToPrint, student, group, fileName;
	bool validGroupNumber = false, isInputValid = false, validFn = false, validCountSubjects = false, validSortCriteria = false;
	bool validInteger = false;
	string* groups;

	cout << "Group: " << endl;

	while (!validGroupNumber) {
		getline(cin, group);
		validInteger = isNumber(group);

		if (!validInteger) {
			cout << "Invalid input. Please enter a number from 1 to 8." << endl;
		}
		else {
			validGroupNumber = isGroupNumberValid(group);

			if (!validGroupNumber) {
				cout << "Invalid input. Please enter a number from 1 to 8." << endl;
			}
		}
	}
	validInteger = false;
	validGroupNumber = false;
	fileName = fileNameGenerator(group);

	printMenu();

	while (getline(cin, input)) {
		validInteger = isNumber(input);
		if (!validInteger) {
			cout << "Invalid input. Please enter a number from 1 to 6." << endl;
		}else{
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

					validInteger = false;
					while (!validCountSubjects) {
						getline(cin, countSubjects);
						validInteger = isNumber(countSubjects);

						if (!validInteger) {
							cout << "Invalid input. Please enter a number from 1 to 10." << endl;
						}
						else {
							validCountSubjects = isCountSubjectsValid(countSubjects);
							if (!validCountSubjects) {
								cout << "Count should be between 1 and 10. Please try again!" << endl;
							}
						}
					}
					validInteger = false;
					validCountSubjects = false;
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
						validInteger = isNumber(sortBy);

						if (!validInteger) {
							cout << "Choose between option 1 and 2. Please try again!" << endl;
						}
						else {
							validSortCriteria = isSortCriteriaValid(stoi(sortBy));
							if (!validSortCriteria) {
								cout << "Choose between option 1 and 2. Please try again!" << endl;
							}
						}
					}
					validInteger = false;
					validSortCriteria = false;

					cout << endl << "1. Ascending order" << endl << "2. Descending order" << endl;

					while (validSortCriteria != true) {
						getline(cin, sortOrder);
						validInteger = isNumber(sortOrder);

						if (!validInteger) {
							cout << "Choose between option 1 and 2. Please try again!" << endl;
						}
						else {
							validSortCriteria = isSortCriteriaValid(stoi(sortOrder));
							if (!validSortCriteria) {
								cout << "Choose between option 1 and 2. Please try again!" << endl;
							}
						}
					}
					validInteger = false;
					validSortCriteria = false;

					sortStudents(stoi(sortBy), stoi(sortOrder), fileName);
					break;
				case 4:
					printFile(fileName);
					break;
				case 5:
					cout << "Number of groups to print: " << endl;
					while (!validGroupNumber) {
						getline(cin, countGroupsToPrint);
						validInteger = isNumber(countGroupsToPrint);

						if (!validInteger) {
							cout << "Invalid input. Please enter a number from 1 to 8." << endl;
						}
						else {
							validGroupNumber = isGroupNumberValid(countGroupsToPrint);

							if (!validGroupNumber) {
								cout << "Invalid input. Please enter a number from 1 to 8." << endl;
							}
						}
					}
					validInteger = false;
					validGroupNumber = false;

					groups = new string[stoi(countGroupsToPrint)];//creating an array with all the groups

					cout << "Please enter the " << stoi(countGroupsToPrint) << " groups to be printed:" << endl;

					for (size_t i = 0; i < stoi(countGroupsToPrint); i++) {
						while (!validGroupNumber) {
							getline(cin, groups[i]);
							validInteger = isNumber(groups[i]);

							if (!validInteger) {
								cout << "Invalid input. Please enter a number from 1 to 8." << endl;
							}
							else {
								validGroupNumber = isGroupNumberValid(groups[i]);

								if (!validGroupNumber) {
									cout << "Invalid input. Please enter a number from 1 to 8." << endl;
								}
							}
						}
						validInteger = false;
						validGroupNumber = false;
					}

					cout << "Sort by: " << endl << "1. Faculty number" << endl << "2. Average score" << endl;
					while (validSortCriteria != true) {
						getline(cin, sortBy);
						validInteger = isNumber(sortBy);

						if (!validInteger) {
							cout << "Choose between option 1 and 2. Please try again!" << endl;
						}
						else {
							validSortCriteria = isSortCriteriaValid(stoi(sortBy));
							if (!validSortCriteria) {
								cout << "Choose between option 1 and 2. Please try again!" << endl;
							}
						}
					}
					validInteger = false;
					validSortCriteria = false;

					cout << endl << "1. Ascending order" << endl << "2. Descending order" << endl;
					while (validSortCriteria != true) {
						getline(cin, sortOrder);
						validInteger = isNumber(sortOrder);

						if (!validInteger) {
							cout << "Choose between option 1 and 2. Please try again!" << endl;
						}
						else {
							validSortCriteria = isSortCriteriaValid(stoi(sortOrder));
							if (!validSortCriteria) {
								cout << "Choose between option 1 and 2. Please try again!" << endl;
							}
						}
					}
					validInteger = false;
					validSortCriteria = false;

					printMultipleFiles(stoi(countGroupsToPrint), groups, sortBy, sortOrder);
					delete[] groups;
					break;
				case 6:
					return 0;
				}

				printMenu();
			}
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
	bool validGrade = false, validSubject=true, validInteger=false;

	string* subjects = new string[stoi(countSubjects)];//creating an array with all the subjects
	int* grades = new int[stoi(countSubjects)];//creating an array with all the grades

	for (size_t i = 0; i < stoi(countSubjects); i++) {
		validSubject = true;

		cout << "Subject " << i + 1 << ":" << endl;
		getline(cin, subjects[i]);

		transform(subjects[i].begin(), subjects[i].end(), subjects[i].begin(), ::toupper);

		for (size_t j = 0; j < i; j++) {
			transform(subjects[j].begin(), subjects[j].end(), subjects[j].begin(), ::toupper);
			if (subjects[j]==subjects[i]) {
				cout << "This subject already exists. Please enter a new one! " << endl;
				validSubject = false;
				i--;
			}
		}

		if (validSubject) {
			cout << "Grade:" << endl;
			while (!validGrade) {
				getline(cin, tempGrade);
				validInteger = isNumber(tempGrade);

				if (!validInteger) {
					cout << "Invalid input. Please enter a number from 2 to 6." << endl;
				}
				else {
					validGrade = isGradeValid(tempGrade);

					if (!validGrade) {
						cout << "Invalid input. Please enter a number from 2 to 6." << endl;
					}
				}
			}
			validInteger = false;
			validGrade = false;

			grades[i] = stoi(tempGrade);
			sumGrades += grades[i];//sum all grades
		}
		
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

void printMultipleFiles(int countGroups, string* groups, string sortBy, string sortOrder) {
	string fileBundle = "bundle.txt";

	combineMultipleFilesInOne(countGroups, groups);
	sortStudents(stoi(sortBy), stoi(sortOrder), fileBundle);
	printFile(fileBundle);
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

void combineMultipleFilesInOne(int countGroups, string* groups) {
	fstream File;
	string fileBundle = "bundle.txt", buffer;

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

//validation functions
bool isGroupNumberValid(string group) {
	bool isValid = true;
	if (stoi(group) < 1 || stoi(group) > 8) {
		isValid = false;;
	}
	return isValid;
}

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

bool isCountSubjectsValid(string countSubjects) {
	bool isValid = true;
	if (stoi(countSubjects) < 1 || stoi(countSubjects) > 10) {
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

bool isGradeValid(string grade) {
	bool isValid = true;
	if (stoi(grade) < 2 || stoi(grade) > 6) {
		isValid = false;;
	}
	return isValid;
}

bool isNumber(string s) {
	bool isInt = true;
	if (s.size() == 0) {
		isInt=false;
	}
	for (int i = 0; i < s.size(); i++) {
		if (!((s[i] >= '0' && s[i] <= '9'))) {
			isInt = false;
		}
	}
	return isInt;
}