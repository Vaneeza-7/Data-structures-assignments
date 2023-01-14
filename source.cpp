#include<iostream>
#include<string>
#include<stack>
#include<fstream>
#include"parsing.h"
#include"lru.h"

using namespace std;

int main() {

	Queue<string> priortyqueue;
	string files[7] = { "Test-7.txt", "Test-6.txt","Test-5.txt","Test-4.txt", "Test-3.txt", "Test-2.txt", "Test-1.txt" };
	string ref_files[7] = { "Test-1.txt", "Test-2.txt","Test-3.txt","Test-4.txt", "Test-5.txt", "Test-6.txt", "Test-7.txt" };
	int hits = 0, faults = 0;
	static int index;
	for (int i = 0; i < 7; i++)
	{
		priortyqueue.enqueue(files[i]);
		if (priortyqueue.getsize() == 4)
			break;
	}


	//   fstream input;
	   //input.open("Test1.txt");
	   //input.open("Test2.txt");
	   //input.open("Test3.txt");
	   //input.open("Test4.txt");
	   //input.open("Test5.txt");
	   //input.open("Test6.txt");
	   //input.open("Test7.txt");
	   //char c1, c2;
	   //int pror;
	   //for (int i = 0; i < 7; i++) {
	   //	while (input >> c1 >> c2) {
	   //		if (c1 >= char(48) && c1 <= char(57))
	   //			if (c2 >= char(48) && c2 <= char(57))
	   //			{
	   //				string temp1, temp2, str;
	   //				temp1 += c1;
	   //				temp2 += c2;
	   //				str = temp1 + temp2;
	   //				pror = stoi(str);
	   //				priority_queue[i] = pror;
	   //			}

	   //	}
	   //}
	   //---------------------LEAST RECENTLY USED ALGORITHM-----------//

		for (int i = 0; i < 7; i++)
		{
			tagparse(ref_files[i]);
			if (priortyqueue.contains(ref_files[i]))
			{
				hits++;
				//tagparse(ref_files[i]);
				priortyqueue.dequeue();
			}
			else
			{
				faults++;
				priortyqueue.dequeue();
				priortyqueue.enqueue(ref_files[i]);

			}

		}

    
cout << "Hits are: " << hits << endl;
cout << "Faults are: " << faults << endl;
//input.close();
	//output.close();
	string postfix = convertToPostfix("((A-(B+C))*D) $ (E+F)");
	cout << postfix<<endl;
	evalPost("A B C + - D * EF+ $");
	convertToPrefix(" a * b / (c + d) ^ f - g");
	
}