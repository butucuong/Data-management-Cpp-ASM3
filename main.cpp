#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include<regex>
#include<utility>
#include <ctype.h>

#include "General.h"
#include "Display.h"
#include "Sound.h"
#include "CommonInfo.h"
vector<Setting> DATA;
vector<Display> display;
vector<Sound> sound;
vector<General> general;


using namespace std;
int g_totalindex{};
int dispCnt{}, soundCnt{}, generalCnt = 0;

vector<CommonInfo> timezoneList;
vector<CommonInfo> languageList;

void NhapThongTinCaiDat();
void XuatThongTinCaiDat();

void XuatThongTinCaiDat_Sound();
void XuatThongTinCaiDat_General();
void XuatThongTinCaiDat_Display();
void XuatTatCaThongTinCaiDat();

void NhapThongTinCaiDat_Sound();
void NhapThongTinCaiDat_General();
void NhapThongTinCaiDat_Display();

void downloadTimeZone();
void downloadLanguage();

void readfromfileSetting();								//Doc du lieu tu file Setting.txt
void writetofileSetting();								//Ghi du lieu vao file Setting.txt

void sortTimezone();									//Sap xep Timezone
void sortLanguage();									//Sap xep Language
int menu();
void showList(vector<CommonInfo>);						



void sort_object(int);									//1:sorted by PersonalKey - 2:sorted by CarName

void sort_vector(vector<CommonInfo>& v, int a);
bool cmpnum(CommonInfo obj1,CommonInfo obj2);
bool cmpalpha(CommonInfo obj1,CommonInfo obj2);

void sort_vectorS(vector<Setting>&, int a);
bool cmpnumS(Setting obj1, Setting obj2);
bool cmpalphaS(Setting obj1, Setting obj2);

void sort_vectorSo(vector<Sound>&, int a);
bool cmpnumSo(Sound obj1, Sound obj2);
bool cmpalphaSo(Sound obj1, Sound obj2);

void sort_vectorD(vector<Display>&, int a);
bool cmpnumD(Display obj1, Display obj2);
bool cmpalphaD(Display obj1, Display obj2);

void sort_vectorG(vector<General>&, int a);
bool cmpnumG(General obj1, General obj2);
bool cmpalphaG(General obj1, General obj2);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {
	downloadLanguage();
	downloadTimeZone();
	
	

	char decision = 'c';								//Tiep tuc nha du lieu cho xe tiep theo hay khong
	bool flag{ false };									//Flag cho while

	readfromfileSetting();

	while (flag != true) {
		decision = 'c';

		cout << "There is (are) " << g_totalindex + 1 << " car(s) in the system." << endl;
		cout << "Will you import another user? (y/n) :";//Goi y chon tao doi tuong moi
		cin >> decision;
		if (toupper(decision) == 'Y') {
			g_totalindex++;
			cin.ignore(1);
			system("cls");

			cout << "Car number: " << g_totalindex + 1 << endl;

			Setting data;

			data.nhapThongTin();

			Display DIS(data, 1, 1, 1);											//default parameter
			Sound SND(data, 1, 1, 1, 1);										//default parameter
			General GEN(data, "(GMT-12:00)", "Mandarin (entire branch)");			//default parameter
			DATA.push_back(data);
			display.push_back(DIS);
			sound.push_back(SND);
			general.push_back(GEN);
			cout << "\n-----------------------" << endl;
			DATA[g_totalindex].xuatThongTin();

		}
		else {
			if (toupper(decision) == 'N') {

				menu();

				flag = true;
			}
			else {
				cout << "Unknown selection." << endl;
				continue;

			}
		}
	}




	return 0;
}

int menu() {
	int selection{};									//Chon che do
	bool flag{ false };									//Flag cho vong lap while

	while (flag != true) {
		system("cls");

		cout << "--- SELECT MENU ---\n";
		cout << "1. Input setting information" << endl;
		cout << "2. Print setting information" << endl;
		cout << "3. Exit\nYour seclection: ";

		cin >> selection;
		try {
			switch (selection) {							//Switch-case nhu menu
			case 1:
				NhapThongTinCaiDat();
				break;
			case 2:
				XuatThongTinCaiDat();
				break;
			case 3:

				cout << "\nGood bye.";
				cout << endl;
				system("pause");
				flag = true;
				break;
			default:
				cout << "Unknown selection. Please try again!!!" << endl;
				system("pause");
			}
		}
		catch (...) {
			cerr << "Unknown selection!!! Please try again.";
			continue;
		}
	}return selection;
}

void NhapThongTinCaiDat() {
	int choose{};										//Chon xe de cai dat thong tin Display/Sound/General
	int selection{};									//Chon chuc nang 
	bool flag{ false }, flagbis{ false };				//Flag cho while 


	while (flag != true) {
		system("cls");

		cout << "--- SELECT MENU ---" << endl;
		cout << "1. Display setting " << endl;
		cout << "2. Sound setting " << endl;
		cout << "3. General setting" << endl;
		cout << "0. Back\nYour selection: ";

		cin >> selection;

		try {
			switch (selection) {
			case 1:																//Nhap thong tin cho Display
				system("cls");
				cout << " --- Ban nhap thong tin Display --- " << endl;			//Xuat thong bao da chon Input Display
				while (flagbis != true) {
					cout << "Car index: ";
					cin >> dispCnt;												//So nhap tu ban phim
					dispCnt--;													//So duoc luu trong mang
					cout << endl;
					if (dispCnt <= g_totalindex) {								//So chon phai nho hon so xe trong du lieu	

						NhapThongTinCaiDat_Display();						//Ham Input Display
						break;
					}
					else {														//Neu so lon hon thi xuat thong bao va yeu cau nhap lai
						cout << "There are no user's data in the memory. There are (is) " << g_totalindex + 1 << " User(s) in the memory. Try another!! " << endl;
					}
				}
				break;

			case 2:
				system("cls");
				cout << " --- Ban nhap thong tin Sound --- " << endl;			//Xuat thong bao da chon Input Sound
				while (flagbis != true) {
					cout << "Car index: ";
					cin >> soundCnt;											//So nhap tu ban phim
					soundCnt--;													//So duoc luu trong mang
					cout << endl;
					if (soundCnt <= g_totalindex) {								//So chon phai nho hon so xe trong du lieu

						NhapThongTinCaiDat_Sound();							//Ham Input Sound
						break;
					}
					else {
						cout << "There are no user's data in the memory. There are (is) " << g_totalindex + 1 << " User(s) in the memory. Try another!! " << endl;
					}
				}
				break;

			case 3:
				system("cls");
				cout << " --- Ban nhap thong tin General --- " << endl;
				while (flagbis != true) {
					cout << "Car index: ";
					cin >> generalCnt;											//So nhap tu ban phim				
					generalCnt--;												//So duoc luu trong mang
					cout << endl;
					if (generalCnt <= g_totalindex) {							//So chon phai nho hon so xe trong du lieu

						NhapThongTinCaiDat_General();						//Ham Input General
						break;
					}
					else {
						cout << "There are no user's data in the memory. There are (is) " << g_totalindex + 1 << " User(s) in the memory. Try another!! " << endl;
					}
				}
				break;
			case 0:
				system("cls");
				flag = true;
				break;

			default:
				cout << "Unknown selection. Please try again!!!" << endl;
				system("pause");
				continue;
			}
		}
		catch (...) {
			cerr << "Unknown selection. Please try again!!";
			system("pause");
			continue;
		}
	}
}

void NhapThongTinCaiDat_Sound()
{
	char continues = 'c';
	bool flag{false}, flagys{false};
	while (flag != true) {
		flagys = false;

		system("cls");
		cin.clear();
		cin.ignore(100, '\n');
		cout << "--- Input Sound setting ---\n";
		cout << "Car index: " << soundCnt + 1 << endl;

		sound[soundCnt].print_user_data();															//Xuat du lieu User
		if (sound[soundCnt].get_call_level() == 1 && sound[soundCnt].get_media_level() == 1 && sound[soundCnt].get_navi_level() == 1 && sound[soundCnt].get_notification_level() == 1) {											//Neu du lieu Sound chua ton tai
			cout << "\t->This is car, data will be appended to your list." << endl;
			sound[soundCnt].nhapThongTin();														//Nhap thong tin
		}
		else {
			cout << "\t->This car already existed, data will be overwriten.";
			sound[soundCnt].xuatThongTin();														//Xuat thong tin
		}
		if (soundCnt < g_totalindex) {															//Xe duoc chon de nhap phai co trong du lieu nguoi dung
			while (flagys != true) {
				cout << "\nWill input for Car " << soundCnt + 2 << " ? (y/n): ";					//Goi y nhap tiep
				cin >> continues;
				if (toupper(continues) == 'N') {
					flag = true;																	//Flag true neu say no
					flagys = true;
					cin.clear();
					cin.ignore(100, '\n');
				}
				if (toupper(continues) == 'Y')
				{
					soundCnt++;
					flagys = true;
				}

			}
		}
		else {
			cout << "The data are fully imported!!! " << endl;									//Khi du lieu duoc nhap het cho cac xe thi khong goi y nua
			flag = true;																		//Ket thuc vong lap
		}

		system("pause");
	}
}

void NhapThongTinCaiDat_General()
{
	char continues = 'c';
	bool flag{ false }, flagys{ false };
	while (flag != true) {
		flagys = false;
		system("cls");
		cin.clear();
		cin.ignore(100, '\n');
		cout << "--- Input General setting ---\n";
		cout << "Car index: " << generalCnt + 1 << endl;
		general[generalCnt].print_user_data();
		if (general[generalCnt].get_language() == "Mandarin (entire branch)" && general[generalCnt].get_timeZone() == "(GMT-12:00)") {		//Kiem tra xem da nhap chua

			cout << "\n\t->This is car, data will be append to the list." << endl;
			sortLanguage();
			sortTimezone();
			general[generalCnt].nhapThongTin();
		}
		else {
			cout << "\n\t->This car already existed, data will be overwriten.";
			general[generalCnt].xuatThongTin();
		}
		if (generalCnt < g_totalindex) {																//Xuat thong bao nhap tiep hay khong
			while (flagys != true)
			{


				cout << "\nWill input for Car " << generalCnt + 2 << " ? (y/n): ";
				cin >> continues;
				if (toupper(continues) == 'N') {
					flag = true;
					flagys = true;
					cin.clear();
					cin.ignore(100, '\n');
				}
				if (toupper(continues) == 'Y')
				{
					generalCnt++;
					flagys = true;
				}
			}
		}
		else {
			cout << "The data are fully imported!!! " << endl;											//Neu nhap het cho cac xe se xuat thong bao nay
			flag = true;																				//Ket thuc vong lap cua ham
		}
	}
	system("pause");
}

void NhapThongTinCaiDat_Display()
{
	char continues = 'c';
	bool flag{ false }, flagyn{ false };
	while (flag != true) {
		flagyn = false;
		cin.clear();
		cin.ignore(100, '\n');
		system("cls");

		cout << "--- Input Display setting ---\n";
		cout << "Car index: " << dispCnt + 1 << endl;
		display[dispCnt].print_user_data();
		if (display[dispCnt].get_light_level() == 1 && display[dispCnt].get_screen_light_level() == 1 && display[dispCnt].get_taplo_light_level() == 1) {

			cout << "\n\t->This is car, data will be appended to your list." << endl;
			display[dispCnt].nhapThongTin();

		}
		else {
			cout << "\n\t->This car already existed, data will be overwriten.";
			display[dispCnt].xuatThongTin();
		}
		if (dispCnt < g_totalindex) {
			while (flagyn != true) {
				cout << "\nWill input for Car " << dispCnt + 2 << " ? (y/n): ";
				cin >> continues;

				if (toupper(continues) == 'N') {
					flag = true;
					flagyn = true;
					cin.clear();
					cin.ignore(100, '\n');
				}
				if (toupper(continues) == 'Y')
				{
					dispCnt++;
					flagyn = true;

				}
			}
		}
		else {
			cout << "\nThe data are fully imported!!! " << endl;
			flag = true;
		}

		system("pause");
	}
}

void XuatThongTinCaiDat() {
	int selection{};											//Chon che do xuat
																//Chon phuong thuc de sap xep 
	bool flag{ false };

	while (flag != true) {
		system("cls");
		cout << "--- SELECT MENU ---\n";
		cout << "1. Print Display setting information\n";
		cout << "2. Print Sound setting information\n";
		cout << "3. Print General setting information\n";
		cout << "4. Print all setting information\n";
		cout << "0. Back\nYour selection: ";
		cin >> selection;
		

		writetofileSetting();
		system("cls");

		switch (selection) {
		case 1:
			cout << "--- Display setting ---\n";
			XuatThongTinCaiDat_Display();					//Ham xuat thong tin cai dat Display
			break;
		case 2:
			cout << "--- Sound setting ---\n";
			XuatThongTinCaiDat_Sound();						//Ham xuat thong tin cai dat Sound
			break;
		case 3:
			cout << "--- General setting ---\n";
			XuatThongTinCaiDat_General();					//Ham xuat thong tin cai dat General
			break;
		case 4:
			cout << "--- All setting ---\n";					//Ham xuat thong tin tat cacai dat 

			XuatTatCaThongTinCaiDat();
			break;
		case 0:													//Ket thuc Ham Xuat Thong Tin Cai Dat
			system("cls");
			flag = true;
			break;
		default:
			cout << "Illegal choice, please input again!!";
			system("pause");
		}
	}


}


void downloadTimeZone() {
	ifstream f;													//Doi tuong cua ifstream de mo file	
	CommonInfo obj[32];											//Mang  doi tuong
	f.open("timezones.txt");									//Lenh mo file
	if (!f) {													//Neu mo khong thanh cong
		cerr << "Can't open timezones.txt file!" << endl;
		return;

	}
	else {
		try {													//Exception Handle neu khong doc thanh cong file
			for (int i = 0; i < 32; i++) {						//Neu doc duoc 
				cout << flush;									//Vi input la string nen xoa bo nho dem
				obj[i].doc(f);									//Ham Friend doc duoc dinh nghia trong Class CommonInfo
				timezoneList.push_back(obj[i]);					//Them vao vector

			}
			cout << "The TimeZoneList download process is successfull.\n";
		}
		catch (...) {
			cerr << "Can't read this file !" << endl;

			return;
		}
	}
	f.close();
}

void downloadLanguage() {
	ifstream f;													//Doi tuong cua ifstream de mo file	
	CommonInfo objl[30];										//Mang  doi tuong
	f.open("languages.txt");									//Lenh mo file
	if (f.fail()) {												//Neu mo khong thanh cong
		cerr << "Can't open the languages.txt file!";
		return;

	}
	else {
		try {													//Exception Handle neu khong doc thanh cong file
			for (int i = 0; i < 30; i++) {						//Neu doc duoc 
				cout << flush;									//Vi input la string nen xoa bo nho dem
				objl[i].doc(f);
				languageList.push_back(objl[i]);				//Them vao vector
			}
			cout << "The LanguageList download process is successfull.\n";
		}
		catch (...) {
			cerr << "Can't read the language.txt file!";
			return;
		}
	}
	f.close();
}

void XuatThongTinCaiDat_Sound() {
	char choose{};
	bool flag{ false };
	size_t i = 0;
	//do {							//Kiem tra xem co xe nao chua Input hay khong, neu co xuat thong bao

	//	if (sound[i].get_call_level() == 0 && sound[i].get_media_level() == 0 && sound[i].get_navi_level() == 0 && sound[i].get_notification_level() == 0) {
	//		cout << "Empty data\n";
	//		cout << "Car number " << i + 1 << " need to be imported data, please input again before choose printing.\n";
	//		system("pause");
	//		return;
	//	}
	//	i++;
	//} while (i <= g_totalindex);

	while (flag != true) {

		cout << "Sorting data by :\n1. Personal Key\n2. Car Name\n";
		cout << "Your choice: ";
		cin >> choose;
		
		if (choose == '1') {
			sort_vectorSo(sound, 1);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
		}
		else if (choose == '2') {
			sort_vectorSo(sound, 2);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
		}
		else {
			cout << "Illegal choice, please try again.\n";
			system("pause");
			continue;

		}
	}
	cout << endl;
	cout << setw(20) << left << "Owner name" << setw(25) << left << "Email" << setw(20) << left << "Key number" << setw(20) << left << "ODO number" << setw(20) << left << "Remind service" << setw(20) << left << "Media" << setw(20) << left << "Call" << setw(20) << left << "Navigation" << setw(20) << left << "Notification" << endl;							//Format String
	i = 0;
	do
	{

		cout << setw(20) << left << sound[i].getCarName() << setw(25) << left << sound[i].getEmail() << setw(20) << left << sound[i].getPersonalKey() << setw(20) << left << sound[i].getODO() << setw(20) << left << sound[i].getServiceRemind() << setw(20) << left << sound[i].get_media_level() << setw(20) << left << sound[i].get_call_level() << setw(20) << left << sound[i].get_navi_level() << setw(20) << left << sound[i].get_notification_level() << endl;
		i++;
	} while (i <= g_totalindex);
	system("pause");
}

void XuatThongTinCaiDat_General() {
	bool flag{ false };
	char choose{};
	size_t i = 0;
	//do {													//Kiem tra xem con xe nao chua Input hay khong, neu co thi yeu cau nhap
	//	if (general[i].get_language() == "" && general[i].get_timeZone() == "") {
	//		cout << "Lack of data\n";
	//		cout << "Car number " << i + 1 << " need to be imported data, please input again before choose printing.\n";
	//		system("pause");
	//		return;
	//	}
	//	i++;
	//} while (i <= g_totalindex);

	while (flag != true) {

		cout << "Sorting data by :\n1. Personal Key\n2. Car Name\n";
		cout << "Your choice";
		cin >> choose;
		if (choose == '1') {
			sort_vectorG(general, 1);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
		}
		else if (choose == '2') {
			sort_vectorG(general, 2);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
		}
		else {
			cout << "Illegal choice, please try again.\n";
			system("pause");
			continue;

		}
	}
	cout << endl;
	cout << setw(20) << left << "Owner name" << setw(25) << left << "Email" << setw(20) << left << "Key number" << setw(20) << left << "ODO number" << setw(20) << left << "Remind service" << setw(15) << left << "TimeZone" << setw(30) << left << "Language" << endl;
	i = 0;
	do {
		cout << setw(20) << left << general[i].getCarName() << setw(25) << left << general[i].getEmail() << setw(20) << left << general[i].getPersonalKey() << setw(20) << left << general[i].getODO() << setw(20) << left << general[i].getServiceRemind() << setw(15) << left << general[i].get_timeZone() << setw(30) << left << general[i].get_language() << endl;
		i++;
	} while (i <= g_totalindex);
	system("pause");
}

void XuatThongTinCaiDat_Display() {
	bool flag{ false };
	char choose{};
	size_t i = 0;
	/*do {

		if (display[i].get_light_level() == 0 && display[i].get_screen_light_level() == 0 && display[i].get_taplo_light_level() == 0) {
			cout << "Lack of data\n";
			cout << "Car number " << i + 1 << " need to be imported data, please input again before choose printing.\n";
			system("pause");
			return;
		}
		i++;
	} while (i <= g_totalindex);*/

	while (flag != true) {
		
		cout << "Sorting data by :\n1. Personal Key\n2. Car Name\n";
		cout << "Your choice: ";
		cin >> choose;
		if (choose == '1') {
			sort_vectorD(display,1);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
		}
		else if (choose == '2') {
			sort_vectorD(display,2);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
		}
		else {
			cout << "Illegal choice, please try again.\n";
			system("pause");
			continue;

		}
	}
	cout << endl;
	cout << setw(20) << left << "Owner name" << setw(25) << left << "Email" << setw(20) << left << "Key number" << setw(20) << left << "ODO number" << setw(20) << left << "Remind service" << setw(20) << left << "Light level" << setw(20) << left << "Taplo light level" << setw(20) << left << "Screen light level" << endl;
	i = 0;
	do
	{
		cout << setw(20) << left << display[i].getCarName() << setw(25) << left << display[i].getEmail() << setw(20) << left << display[i].getPersonalKey() << setw(20) << left << display[i].getODO() << setw(20) << left << display[i].getServiceRemind() << setw(20) << left << display[i].get_light_level() << setw(20) << left << display[i].get_taplo_light_level() << setw(20) << left << display[i].get_screen_light_level() << endl;
		i++;
	} while (i <= g_totalindex);
	system("pause");
}

void XuatTatCaThongTinCaiDat() {

	char c = 'c';
	char c_indx[10];
	int indx{};
	bool flagys{ false }, coinsisive{false};
	cout << endl << endl;
	size_t i = 0;
	bool flag{ false };
	char choose{};
	//do {				//Kiem tra tat ca cac thong tin Display/Sound/General cua tat ca cac xe
	//	if ((display[i].get_light_level() == 0 && display[i].get_screen_light_level() == 0 && display[i].get_taplo_light_level() == 0) || (general[i].get_language() == "" && general[i].get_timeZone() == "") || (sound[i].get_call_level() == 0 && sound[i].get_media_level() == 0 && sound[i].get_navi_level() == 0 && sound[i].get_notification_level() == 0)) {
	//		cout << "Lack of data\n";
	//		cout << "Car number " << i + 1 << " need to be imported data, please input again before choose printing.\n";
	//		system("pause");
	//		return;
	//	}i++;
	//} while (i <= g_totalindex);


	while (flag != true) {

		cout << "Sorting data by :\n1. Personal Key\n2. Car Name\nYour choice: ";
		cin >> choose;
		if (choose == '1') {
			sort_object(1);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
		}
		else if (choose == '2') {
			sort_object(2);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
		}
		else {
			cout << "Illegal choice, please try again.\n";
			system("pause");
			continue;

		}
	}

	writetofileSetting();
	cout << endl;
	for (int k = 0; k <= g_totalindex; k++) {
		cout << setw(5) << left << k + 1 << setw(20) << left << "Owner name" << setw(25) << left << "Email" << setw(20) << left << "Key number" << setw(20) << left << "ODO number" << setw(20) << left << "Remind service (km)" << endl;
		cout << setw(5) << " " << setw(20) << left << display[k].getCarName() << setw(25) << left << display[k].getEmail() << setw(20) << left << display[k].getPersonalKey() << setw(20) << left << display[k].getODO() << setw(20) << left << display[k].getServiceRemind() << endl;

		//------------------------------------------------------------------------

		cout << setw(5) << " " << setw(20) << left << "Display: " << setw(15) << left << "Light" << setw(15) << left << "Screen Light" << setw(15) << left << "Taplo Light" << endl;
		cout << setw(5) << " " << setw(20) << left << " " << setw(15) << left << display[k].get_light_level() << setw(15) << left << display[k].get_screen_light_level() << setw(15) << left << display[k].get_taplo_light_level() << endl;

		//------------------------------------------------------------------------

		cout << setw(5) << " " << setw(20) << left << "Sound: " << setw(15) << left << "Media" << setw(15) << left << "Call" << setw(15) << left << "Navigation" << setw(15) << left << "Notification" << endl;
		cout << setw(5) << " " << setw(20) << left << " " << setw(15) << left << sound[k].get_media_level() << setw(15) << left << sound[k].get_call_level() << setw(15) << left << sound[k].get_navi_level() << setw(15) << left << sound[k].get_notification_level() << endl;

		//------------------------------------------------------------------------

		cout << setw(5) << " " << setw(20) << left << "General: " << setw(15) << left << "Timezone" << setw(15) << left << "Language" << endl;
		cout << setw(5) << " " << setw(20) << left << "  " << setw(15) << left << general[k].get_timeZone() << setw(15) << left << general[k].get_language() << endl << endl;
	}

	while (flagys != true) {
		coinsisive = false;
		flagys = false;
		cout << "\nWould you like to update user data? [yes/no]" << endl;
	
		cin >> c;
		if (toupper(c) == 'Y') {
			cout << "Which car: ";
			cin >> c_indx;
			if (isdigit(c_indx[0])) {
				indx = atoi(c_indx);
				--indx;
				cout << "Car index:" << indx + 1 << endl;
				cin.ignore(1);
				Setting updateCar;
				
				updateCar.nhapThongTin();

				for (int i = 0; i <= g_totalindex; i++) {
					if (updateCar == DATA[i]) {
						coinsisive = true;

					}
				}
				if (coinsisive) {
					continue;
				}
				DATA[indx] = updateCar;
				display[indx].setCarName(updateCar.getCarName());
				display[indx].setPersonalKey(updateCar.getPersonalKey());
				display[indx].setServiceRemind(updateCar.getServiceRemind());
				display[indx].setEmail(updateCar.getEmail());
				display[indx].setODO(updateCar.getODO());

				sound[indx].setCarName(updateCar.getCarName());
				sound[indx].setPersonalKey(updateCar.getPersonalKey());
				sound[indx].setServiceRemind(updateCar.getServiceRemind());
				sound[indx].setEmail(updateCar.getEmail());
				sound[indx].setODO(updateCar.getODO());

				general[indx].setCarName(updateCar.getCarName());
				general[indx].setPersonalKey(updateCar.getPersonalKey());
				general[indx].setServiceRemind(updateCar.getServiceRemind());
				general[indx].setEmail(updateCar.getEmail());
				general[indx].setODO(updateCar.getODO());

			}
			else {
				cout << "\nIllegal choice. Could you try again?";
				cin.clear();
				cin.ignore(100, '\n');
			}


		}
		if (toupper(c) == 'N') {
			
			cin.clear();
			cin.ignore(100, '\n');
			flagys = true;
		}


	}
	system("pause");
}
void readfromfileSetting() {
	ifstream f;
	string begin_word;
	string string_word, string_num;
	int num{};
	f.open("Setting.txt", ios::in);
	if (f.fail()) {
		cerr << "Can't open the Setting.txt file to read!";
		return;
	}
	else {
		try {

			f.seekg(0, ios::end);
			size_t size = f.tellg();
			if (size == 0) {
				cout << "Ready to write on file.";
				system("cls");

				cout << "Car number: " << g_totalindex + 1 << endl;

				Setting data;

				data.nhapThongTin();

				Display DIS(data, 1, 1, 1);											//default parameter
				Sound SND(data, 1, 1, 1, 1);										//default parameter
				General GEN(data, "(GMT-12:00)", "Mandarin (entire branch)");			//default parameter
				DATA.push_back(data);
				display.push_back(DIS);
				sound.push_back(SND);
				general.push_back(GEN);
				cout << "\n-----------------------" << endl;
				DATA[g_totalindex].xuatThongTin();

			}
			else {
				f.seekg(0);
				while (!f.eof()) {
					Setting data;
					DATA.push_back(data);
					f >> begin_word;
					f.seekg(3, 1);
					getline(f, string_word, '/');
					DATA[g_totalindex].setCarName(string_word);

					getline(f, string_word, '/');
					DATA[g_totalindex].setEmail(string_word);

					getline(f, string_word, '/');
					DATA[g_totalindex].setPersonalKey(string_word);

					getline(f, string_num, '/');
					num = stoi(string_num);
					DATA[g_totalindex].setODO(num);

					getline(f, string_num, 'S');
					num = stoi(string_num);

					DATA[g_totalindex].setServiceRemind(num);


					getline(f, begin_word, ':');
					f.seekg(4, 1);

					Sound SND((DATA[g_totalindex]), 0, 0, 0, 0);
					sound.push_back(SND);
					getline(f, string_num, '/');
					num = stoi(string_num);
					sound[g_totalindex].set_media_level(num);

					getline(f, string_num, '/');
					num = stoi(string_num);
					sound[g_totalindex].set_call_level(num);

					getline(f, string_num, '/');
					num = stoi(string_num);
					sound[g_totalindex].set_navi_level(num);

					getline(f, string_num, 'D');
					num = stoi(string_num);
					sound[g_totalindex].set_notification_level(num);

					Display DIS((DATA[g_totalindex]), 0, 0, 0);
					display.push_back(DIS);
					getline(f, begin_word, ':');
					f.seekg(2, 1);

					getline(f, string_num, '/');
					num = stoi(string_num);
					display[g_totalindex].set_light_level(num);

					getline(f, string_num, '/');
					num = stoi(string_num);
					display[g_totalindex].set_screen_light_level(num);

					getline(f, string_num, 'G');
					num = stoi(string_num);
					display[g_totalindex].set_taplo_light_level(num);


					General GEN((DATA[g_totalindex]), "", "");
					general.push_back(GEN);


					getline(f, begin_word, ':');
					f.seekg(2, 1);
					getline(f, string_word, '/');
					general[g_totalindex].set_timeZone(string_word);

					getline(f, string_word);
					general[g_totalindex].set_language(string_word);
					f.ignore(1);
					g_totalindex++;
				}
				g_totalindex--;
			}
			return;
		}
		catch (...) {
			cerr << "Can't read the Setting.txt file.";
			system("pause");
			return;
		}
	}
	f.close();
}
void writetofileSetting() {
	ofstream f;
	f.open("Setting.txt", ios_base::out | ios_base::trunc);
	if (f.fail()) {
		cerr << "Can't open the Setting.txt file to read!";
		return;
	}
	else {
		try {
			for (int i = 0; i <= g_totalindex; i++) {
				f << setw(10) << left << "Common:" << setw(20) << display[i].getCarName() << "/" << setw(25) << display[i].getEmail() << "/" << setw(8) << display[i].getPersonalKey() << "/" << setw(7) << display[i].getODO() << "/" << setw(7) << display[i].getServiceRemind() << " " << setw(10) << left << "Sound:" << setw(2) << sound[i].get_media_level() << "/" << setw(2) << sound[i].get_call_level() << "/" << setw(2) << sound[i].get_navi_level() << "/" << setw(2) << sound[i].get_notification_level() << " " << setw(10) << left << "Display:" << setw(2) << display[i].get_light_level() << "/" << setw(2) << display[i].get_screen_light_level() << "/" << setw(2) << display[i].get_taplo_light_level() << " " << setw(10) << left << "General: " << setw(11) << general[i].get_timeZone() << "/" << setw(20) << general[i].get_language() << endl;
			}
			cout << "Completed to write the data into file." << endl;
		}
		catch (...) {
			cerr << "Can't read the Setting.txt file.";
			return;
		}
	}
	f.close();

}

void sortTimezone() {
	char a('c');
	bool flag = false;
	cout << "\nSorting Timezone list by:";
	cout << "\n1. Index\n2. Alphabet\n0. Leave it alone.\n";

	while (flag != true) {
		flag = false;
		cout << "Your choice: ";
		cin >> a;
		switch (a) {
		case '0':
			cout << "\nNo change in your list.\n";
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
			break;
		case '1': 
			cout << "\nTimezone list was sorted by GMT Index.\n";
			sort_vector(timezoneList, 1);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
			break;
		case '2':
			cout << "Timezone list was sorted by Alphabet.\n";
			sort_vector(timezoneList, 2);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
			break;

		default:
			cout << "Illegal input, please try again." << endl;

			break;
		}
	}

}

void sortLanguage() {
	char a('c');
	bool flag = false;
	cout << "\nSorting Language list by:";
	cout << "\n1. Index\n2. Alphabet\n0. Leave it alone.\n";
	while (flag != true) {
		flag = false;
		cout << "Your choice: ";
		cin >> a;
		switch (a) {
			
		case '0':
			cout << "\nNo change in your list.\n";
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
			break;
		case '2':
			cout << "Language list was sorted by Alphabet.\n";
			sort_vector(languageList, 2);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
			break;
		case '1':
			cout<< "Language list was sorted by Index.\n";
			sort_vector(languageList, 1);
			cin.clear();
			cin.ignore(100, '\n');
			flag = true;
			break;
		default:
			cout << "Illegal input, please try again." << endl;

			break;
		}
	}

}

void showList(vector<CommonInfo>a) {
	vector<CommonInfo>::iterator it;
	for (it = a.begin(); it != a.end(); ++it) {
		cout << it->getNumber() << " " << it->getName() << endl;
	}
}



void sort_object(int a)
{	//case 1: sort by PersonalKey
	//case 2: sort by Name

	
	switch (a) {
	case 1:
		sort_vectorD(display, 1);
		sort_vectorG(general, 1);
		sort_vectorS(DATA, 1);
		sort_vectorSo(sound, 1);

		break;
	case 2:
		sort_vectorD(display, 2);
		sort_vectorG(general, 2);
		sort_vectorS(DATA, 2);
		sort_vectorSo(sound, 2);
		break;
	}
}

//sort TimeZoneList and LanguageList
void sort_vector(vector<CommonInfo>& v, int a) {
	// a=1: sortbyNumber
	// a=2: sortbyName




	switch (a) {

	case 1:
		sort(v.begin(), v.end(), cmpnum);
		break;

	case 2:
		sort(v.begin(), v.end(), cmpalpha);
		break;
	}
}

 bool cmpalpha(CommonInfo obj1,CommonInfo obj2)
	 {
		 return operator<(obj1, obj2);
	 }

 bool cmpnum( CommonInfo obj1,CommonInfo obj2) {
	
		 return obj1 < obj2;
	 }
 

 //Sort Setting object
void sort_vectorS(vector<Setting>& k, int a) {
	// a=1: sortbyNumber
	// a=2: sortbyName




	switch (a) {

	case 1:
		sort(k.begin(), k.end(), cmpnumS);
		break;

	case 2:
		sort(k.begin(), k.end(), cmpalphaS);
		break;
	}
}
 bool cmpalphaS(Setting obj1, Setting obj2)
 {
	 return operator<(obj1, obj2);
 }

 bool cmpnumS(Setting obj1, Setting obj2) {

	 return obj1 < obj2;
 }


 void sort_vectorD(vector<Display>& k, int a) {
	 // a=1: sortbyNumber
	 // a=2: sortbyName




	 switch (a) {

	 case 1:
		 sort(k.begin(), k.end(), cmpnumD);
		 break;

	 case 2:
		 sort(k.begin(), k.end(), cmpalphaD);
		 break;
	 }
 }
 bool cmpalphaD(Display obj1, Display obj2)
 {
	 return operator<(obj1, obj2);
 }

 bool cmpnumD(Display obj1, Display obj2) {

	 return obj1 < obj2;
 }


 //sort Sound object
 void sort_vectorSo(vector<Sound>& k, int a) {
	 // a=1: sortbyNumber
	 // a=2: sortbyName




	 switch (a) {

	 case 1:
		 sort(k.begin(), k.end(), cmpnumSo);
		 break;

	 case 2:
		 sort(k.begin(), k.end(), cmpalphaSo);
		 break;
	 }
 }
 bool cmpalphaSo(Sound obj1, Sound obj2)
 {
	 return operator<(obj1, obj2);
 }

 bool cmpnumSo(Sound obj1, Sound obj2) {

	 return obj1 < obj2;
 }

 //Sort General object
 void sort_vectorG(vector<General>& k, int a) {
	 // a=1: sortbyNumber
	 // a=2: sortbyName




	 switch (a) {

	 case 1:
		 sort(k.begin(), k.end(), cmpnumG);
		 break;

	 case 2:
		 sort(k.begin(), k.end(), cmpalphaG);
		 break;
	 }
 }
 bool cmpalphaG(General obj1, General obj2)
 {
	 return operator<(obj1, obj2);
 }

 bool cmpnumG(General obj1, General obj2) {

	 return obj1 < obj2;
 }



