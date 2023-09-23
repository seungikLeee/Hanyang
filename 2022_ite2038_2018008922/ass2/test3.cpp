#include <bits/stdc++.h>
using namespace std;

class name_grade {
	public:
		string student_name;
		int korean;
		int math;
		int english;
		int science;
		int social;
		int history;

		void set_grade(string tuple)
		{
			stringstream tuplestr(tuple);
			string tempstr;

			getline(tuplestr, student_name, ',');

			getline(tuplestr, tempstr, ',');
			korean = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			math = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			english = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			science = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			social = stoi(tempstr);
			
			getline(tuplestr, tempstr);
			history = stoi(tempstr);
		}
};

class name_number{
	public :
		string student_name;
		string student_number;

		void set_number(string tuple)
		{
			stringstream tuplestr(tuple);
//			string tempstr;


			getline(tuplestr, student_name, ',');
			getline(tuplestr, student_number, ',');
		}
};

string make_tuple(string name, string number)
{
	string ret = "";

	ret += name+ "," + number +"\n";

	return ret;
}

int main(){

	string buffer[2];
	name_grade temp0;
	name_grade temp1;
	name_number temp2;
	fstream block[12];
	ofstream output;

	output.open("./output3.csv");

	if(output.fail())
	{
		cout << "output file opening fail.\n";
	}

	/*********************************************************************/
	block[2].open("./buckets/2.csv");
	block[3].open("./buckets/0.csv");
        
	for(int i = 0; i < 1000; i++){
                block[0].open("./name_grade1/" + to_string(i) + ".csv");
                
                if (block[0].is_open()){
                       while(1){
                                block[0].clear();

                                getline(block[0], buffer[0]);
                            	
                                if(buffer[0].length() == 0){
                                        block[0].close();
                                        break;
                                }

				temp0.set_grade(buffer[0]);
				
                                for(int j = 0; j < 1000; j++){
					block[1].open("./name_grade2/"  + to_string(j) + ".csv");

                                        if (block[1].is_open()){
                                                while(1){
                                                        block[1].clear();

                                                        getline(block[1], buffer[1]);
                                                       
                                                        if(buffer[1].length() == 0){
                                                                block[1].close();
                                                                break;
                                                        }

							temp1.set_grade(buffer[1]);
							
                                                        if(temp0.student_name == temp1.student_name){
								int count = 0;
								if (temp0.korean > temp1.korean){
									count++;
								}
								if (temp0.math > temp1.math){
                                                                        count++;
                                                                }
                                                                if (temp0.english > temp1.english){
                                                                        count++;
                                                                }
                                                                if (temp0.science > temp1.science){
                                                                        count++;
                                                                }
                                                                if (temp0.social > temp1.social){
                                                                        count++;
                                                                }
                                                                if (temp0.history > temp1.history){
                                                                        count++;
                                                                }
								
								if(count>=2){
									block[2] << temp0.student_name + "\n";							
								}
								else{
									block[3] << temp0.student_name + "\n";
								}

                                                        }


						}
					}
				}
		       }

		}
	}
	
	block[2].close();
	block[3].close();

	block[0].open("./buckets/2.csv");
	
	if(block[0].is_open()){
		while(1){
			block[0].clear();

			getline(block[0], buffer[0]);
			
			if(buffer[0].length()==0){
				block[0].close();
				break;
			}

			for(int k=0; k < 1000; k++){
				block[1].open("./name_number/" + to_string(k) + ".csv");
				
				if(block[1].is_open()){
					while(1){
						block[1].clear();

						getline(block[1], buffer[1]);
						
						if(buffer[1].length() == 0){
							block[1].close();
							break;
						}

						temp2.set_number(buffer[1]);


						if(buffer[0] == temp2.student_name){
							output << make_tuple(temp2.student_name, temp2. student_number);
						}
					}
				}
			}

		}
	}


	/*********************************************************************/


	output.close();

	
}



