#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

class Setting {
public:
	Setting();
	Setting(const Setting& h);						//Copy constructor
	Setting(string name, string key, string mail, int n1, int n2); //Parameter Constructor
	Setting& operator =(Setting& m);			//Assign operator
	virtual ~Setting();							//Destructor
	virtual void nhapThongTin();
	virtual void xuatThongTin();
	void print_user_data();						//Xuat thong tin chu xe


	/*---Getter---*/
	string getEmail();
	string getCarName();
	string getPersonalKey();
	int getODO();
	int getServiceRemind();
	/*---Setter---*/
	void setCarName(string data);
	void setEmail(string data1);
	void setPersonalKey(string data2);
	void setODO(int data3);
	void setServiceRemind(int data4);

	 bool operator < (const Setting& right);
	 bool operator > (const Setting& right);
	 bool operator == (const Setting& right);
	friend  bool operator==(const Setting& lhs, const Setting& rhs);
	friend  bool operator<(const Setting& lhs, const Setting& rhs);
	friend  bool operator>(const Setting& lhs, const Setting& rhs);

protected:
	string car_name;
	string personal_key; 	// Chuoi 8 ky tu so
	string email;			// email format abc@xyz.com
	int odo;
	int service_remind;
};


