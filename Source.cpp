#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>

class Student
{
private:
	std::string name;
	size_t size;
	int* grades;
public:
	Student(std::string name) : name(name), grades(nullptr), size(0) {}
	void addGrade(int grade)
	{
		int* tmp = new int[size + 1];
		for (int i = 0; i < size; i++)
		{
			tmp[i] = this->grades[i];
		}
		tmp[size] = grade;
		delete this->grades;
		this->grades = tmp;
		size++;
	}
	float getAvg()
	{
		if (grades == nullptr) return 0;
		int sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += grades[i];
		}
		return (float)sum / size;
	}
	std::string getGrades()
	{
		std::string str = "";
		for (int i = 0; i < size; i++)
		{
			str += std::to_string(grades[i]) + ", ";
		}
		//if (str != "") str.erase(str.length() - 2, str.length());
		return str;
	}
	std::string getName()
	{
		return name;
	}
	void setName(std::string name)
	{
		this->name = name;
	}
};

struct Node
{
	Student* stud;
	Node* next;

	Node(Student* stud, Node* next) : stud(stud), next(next) {}
};

class Group
{
private:
	Node* head;
public:
	Group()
	{
		this->head = nullptr;
	}
	void add(Student* newStudent)
	{
		if (this->head == nullptr)
		{
			this->head = new Node(newStudent, nullptr);
			return;
		}
		Node* iter = this->head;
		while (iter->next != nullptr)
		{
			iter = iter->next;
		}
		iter->next = new Node(newStudent, nullptr);
	}
	std::string getInfo()
	{
		if (this->head == nullptr) return "no students\n";
		std::string str = "";
		Node* iter = this->head;
		while (iter != nullptr)
		{
			str += iter->stud->getName() + ": " + iter->stud->getGrades() + "\n";
			iter = iter->next;
		}
		return str;
	}
	void save(const char* fileName)
	{
		std::ofstream out(fileName, std::ios::out);
		out << this->getInfo();
	}

	void load(const char* fileName)
	{
		std::ifstream in(fileName, std::ios::in);
		while (!in.eof())
		{
			std::string str;
			std::getline(in, str);
			if (str == "") continue;
			size_t pos = str.find(": ");
			std::string name = str.substr(0, pos);
			Student* newStudent = new Student(name);
			this->add(newStudent);

			std::string grades = str.substr(pos + 2);
			size_t left = 0, right = 0;
			while ((right = grades.find(", ", right + 1)) != std::string::npos)
			{
				newStudent->addGrade(std::stoi(grades.substr(left, right)));
				left = right + 2;
			}
		}
	}
};

int main()
{
	Group group1;
	Student* john = new Student("Johh");
	john->addGrade(10);
	john->addGrade(12);
	john->addGrade(8);
	group1.add(john);
	group1.add(new Student("Jake"));
	group1.add(new Student("James"));
	group1.save("data.txt");

	Group group2;
	group2.load("data.txt");
	std::cout << group2.getInfo();
}