#include <bits/stdc++.h>
using namespace std;

class name_age {
	public:
		string name;
		string age;
		
		void set_name_age(string tuple)
		{
			stringstream tuplestr(tuple);
			//string agestr;

			getline(tuplestr, name, ',');
			getline(tuplestr, age);
		}
};

class name_salary {
	public:
		string name;
		string salary;
		
		void set_name_salary(string tuple)
		{
			stringstream tuplestr(tuple);
			//string salarystr;

			getline(tuplestr, name, ',');
			getline(tuplestr, salary);
		}
};

string make_tuple(string name, string age, string salary)
{
	return name+ ',' + age + ',' + salary + '\n';
}

int main(){

	string buffer[2];
	name_age temp0;
	name_salary temp1;
	int current_block[2] = {};
	fstream block[12];
	ofstream output;

	output.open("./output1.csv");

	if(output.fail())
	{
		cout << "output file opening fail.\n";
	}

	/*********************************************************************************/
	
	for(int i = 0; i < 1000; i++){
		current_block[0] = 0;
		current_block[1] = 0;
		
		block[0].open("./name_age/" + to_string(i) + ".csv");
	       	block[1].open("./name_salary/" + to_string(i) + ".csv");	
			
		if (block[0].is_open()&&block[1].is_open()){
			while(1){
				block[0].clear();
				block[1].clear();
		
				getline(block[0], buffer[0]);
				temp0.set_name_age(buffer[0]);			
				getline(block[1], buffer[1]);
				temp1.set_name_salary(buffer[1]);
				
				if(temp0.name == temp1.name){
					
					output << make_tuple(temp0.name, temp0.age, temp1.salary);
					
					current_block[0]++;
				}
				else{
					current_block[1]++;
				}
			
				if(current_block[1] == 10 || current_block[0] == 10){
					block[0].close();
					block[1].close();
					break;
				}
			}
		}
	}

	/*********************************************************************************/


	output.close();
}
