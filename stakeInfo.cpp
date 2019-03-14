#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct Student
{
	int id,money;
	char name[10];
};
int main(){
	Student to_write;
	fstream sfile("stakeinfo.dat", ios::out | ios::binary);
	if(!sfile){
		cout<<"no corresponding file"<<endl;
		return 0;
	}
	while(cin>>to_write.id) {
		cin>>to_write.money>>to_write.name;
		sfile.write(reinterpret_cast<char *>(&to_write), sizeof(to_write));
	}
	sfile.close();

	Student to_read;
	fstream rfile("stakeinfo.dat", ios::in | ios::binary);
	cout << "allinfo" << endl;
	rfile.read(reinterpret_cast<char *>(&to_read), sizeof(to_read));
	while(!rfile.eof())
	{
		cout<<"Student id: "<< to_read.id << ";name: "<< to_read.name <<";\nmoney: " << to_read.money <<endl;
		rfile.read(reinterpret_cast<char *>(&to_read), sizeof(to_read));
	}
	rfile.close();
	return 0;
}