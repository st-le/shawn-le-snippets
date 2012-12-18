
#include <stdlib.h>
#include <stdio.h>

//using namespace std;

void main()
{


	struct contact {
		short int age;
		short int height; 
		unsigned int weight;
	};

	typedef struct {
		short int age;
		short int height; 
		unsigned int weight;
	} person;

	struct contact sonle; 
	contact kimha;

	kimha.age = 5;

	person thaoanh;

	person* anhduy;
	anhduy->age = 10;  // cannot use struct pointer like this

	thaoanh.age = 3;

	//sonle.name = "Le Trung Son";
	sonle.age = 10;

	printf("age = %d",sonle.age);
	printf("age = %d",kimha.age);
	printf("age = %d",thaoanh.age);
//	cout << "hello world!" << endl;
	getchar();

}