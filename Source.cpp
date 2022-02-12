#include<iostream>
#include<fstream>
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
		str.erase(str.length() - 1, str.length());//delete \n
		return str;
	}
	void save(const char* fileName)
	{
		std::ofstream out(fileName, std::ios::out);
		out << this->getInfo();
	}

	void load(const char* fileName)
	{
		std::ifstream file(fileName, std::ios::in);
		std::string str;
		while (std::getline(file,str))
		{
			std::string name(str, 0, str.find(':'));
			Student* newStudent = new Student(name);
			this->add(newStudent);

			str = str.substr(str.find(':') + 1);
			size_t left = 0, right = 0;
			while (true)
			{
				right = str.find(',', left);
				if(right == std::string::npos) break;
				std::string grade(str, left, right);
				newStudent->addGrade(stoi(grade));
				left = right + 1;
			} 
		}
	}
};

int main()
{
	Group group1;
	Student* john = new Student("John");
	john->addGrade(10);
	john->addGrade(12);
	john->addGrade(8);
	group1.add(john);
	Student* jake = new Student("jake");
	jake->addGrade(9);
	group1.add(jake);
	group1.add(new Student("James"));
	group1.save("data.txt");

	Group group2;
	group2.load("data.txt");
	std::cout << group2.getInfo();
}