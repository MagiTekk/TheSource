#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "VirtualityChallenge.h"
using namespace std;


VirtualityChallenge::VirtualityChallenge()
{
}


VirtualityChallenge::~VirtualityChallenge()
{
}

int global_prof_cur_id = 1;
int global_student_cur_id = 1;

class Person
{
private:
	string name = "";
	unsigned int age = 0;

public:
	Person() {}

	virtual void getdata()
	{
		cin >> name >> age;
	}

	virtual void putdata()
	{
		cout << name << " " << age << " ";
	}
};

class Professor : public Person
{
private:
	unsigned int publications = 0;
	int cur_id = global_prof_cur_id;

public:
	Professor() : Person() { global_prof_cur_id++; }

	virtual void getdata() override
	{
		Person::getdata();
		cin >> publications;
	}

	virtual void putdata() override
	{
		Person::putdata();
		cout << publications << " " << cur_id << endl;
	}

};

class Student : public Person
{
private:
	vector<int> marks;
	int cur_id = global_student_cur_id;

public:
	Student() : Person() { global_student_cur_id++; }

	virtual void getdata() override
	{
		Person::getdata();
		for (int i = 0; i < 6; ++i)
		{
			int singleMark = 0;
			cin >> singleMark;
			marks.push_back(singleMark);
		}
	}

	virtual void putdata() override
	{
		Person::putdata();
		int sum = 0;
		for (auto element : marks)
		{
			sum += element;
		}
		cout << sum << " " << cur_id << endl;
	}

};

void VirtualityChallenge::Execute()
{
	int n;
	int val;
	cin >> n; //The number of objects that is going to be created.
	std::vector<Person> per(n);

	for (int i = 0; i < n; i++) {
		
		cin >> val;

		if (val == 1) {
			Professor prof;
			per.push_back(prof);
		}
		else
		{
			Student stu;
			per.push_back(stu);
		}

		per.at(i).getdata(); // Get the data from the user.
	}

	for (int i = 0; i < n; i++)
		per.at(i).putdata(); // Print the required output for each object.

}
