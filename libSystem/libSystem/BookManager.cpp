#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include"Book.h"
#define CMD_COLS 80
#define CMD_LINES 25
using namespace std;
void SetScreenGrid();//������Ļ��ʾ������������
void ClearScreen();//�����Ļ��Ϣ
void SetSysCaption(const char* pText);//���ô��������
void ShowWelcome();//��ʾ��ӭ��Ϣ
void ShowRootMenu();//��ʾ�˵���Ϣ
void WaitView(int iCurPage);//�������ʱ�ȴ��û�����
void WaitUser();//�ȴ��û�����
void GuideInput();//ʹ�������ͼ����Ϣ
int GetSelect();//����û�ѡ��
long GetFileLength(ifstream& ifs);//��ȡ�ļ�����
void ViewData(int iSelPage);//������е�ͼ���¼
void DeleteBookFromFile();//���ļ��в���ͼ����Ϣ
void MainLoop();//��ѭ��
int main() {
	SetScreenGrid();
	SetSysCaption("ͼ�����ϵͳ");
	MainLoop();
	system("pause>nul");
	return 0;
}
void SetScreenGrid() {
	//���ô����С
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}
void SetSysCaption() {
	//���ô��ڱ���
	system("title Sample");
}
void ClearScreen() {
	system("cls");
}
void SetSysCaption(const char* pText) {
	char sysSetBuff[80];
	sprintf_s(sysSetBuff, "title %s", pText);
	system(sysSetBuff);
}
void ShowWelcome() {
	for (int i = 0; i < 10; i++) {
		cout << endl;
	}
	cout << setw(50);
	cout << "**********************" << endl;
	cout << setw(50);
	cout << "       ͼ�����ϵͳ     " << endl;
	cout << setw(50);
	cout << "**********************" << endl;
}
void ShowRootMenu() {
	cout << setw(43);
	cout << "1 ���ͼ��";
	cout << endl;
	cout << setw(43);
	cout << "2 ���ȫ��";
	cout << endl;
	cout << setw(43);
	cout << "3 ɾ��ͼ��";
	cout << endl;
	cout << endl;
	cout << setw(42);
	cout << "ѡ�������";
}
void WaitUser() {
	int iInputPage = 0;
	cout << "enter �������˵� q �˳�" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q') {
		system("exit");
	}
}
int GetSelect() {
	char buf[256];
	gets_s(buf);
	return atoi(buf);
}
void GuideInput() {
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	cout << "��������:" << endl;
	cin >> inName;
	cout << "����ISBN:" << endl;
	cin >> inIsbn;
	cout << "����۸�" << endl;
	cin >> inPrice;
	cout << "�������ߣ�" << endl;
	cin >> inAuthor;
	CBook book(inName, inIsbn, inPrice, inAuthor);
	book.WriteData();
	cout << "����ɹ�" << endl;
	WaitUser();
}
void MainLoop() {
	ShowWelcome();
	while (1) {
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch (GetSelect()) {
		case 1:
			ClearScreen();
			GuideInput();
			break;
		case 2:
			ClearScreen();
			ViewData(1);
			break;
		case 3:
			ClearScreen();
			DeleteBookFromFile();
			break;
		}
	}
}
void ViewData(int iSelPage = 1) {
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	bool bIndex = false;
	int iFileLength;
	iCurPage = iSelPage;
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	iFileLength = GetFileLength(ifile);
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);
	if (iDataCount >= 1) {
		bIndex = true;
	}
	iPage = iDataCount / 20 + 1;
	ClearScreen();
	cout << "���м�¼��" << iDataCount << " ";
	cout << "����ҳ����" << iPage << " ";
	cout << "��ǰҳ����" << iCurPage << "  ";
	cout << "��ʾ��һҳ n ���� m" << endl;
	cout << endl;
	cout << setw(5) << "���";
	cout << setw(22) << "����" << setw(22) << "ISBN";
	cout << setw(15) << "�۸�" << setw(15) << "����";
	cout << endl;
	try {
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		if (!ifile.fail()) {
			for (int i = 1; i < 21; i++) {
				memset(inName, 0, 128);
				memset(inIsbn, 0, 128);
				memset(inPrice, 0, 50);
				memset(inAuthor, 0, 50);
				if (bIndex) {
					cout << setw(3) << (iCurPage - 1) * 20 + i;
				}
				ifile.read(inName, NUM1);
				cout << setw(24) << inName;
				ifile.read(inIsbn, NUM1);
				cout << setw(22) << inIsbn;
				ifile.read(inPrice, NUM2);
				cout << setw(15) << inPrice;
				ifile.read(inAuthor, NUM2);
				cout << setw(15) << inAuthor;
				cout << endl;
				if (ifile.tellg() <= 0) {
					bIndex = false;
				}
				else {
					bIndex = true;
				}
			}

		}
		cout << "ѡ�������";
	}
	catch (...) {
		cout << "File exception" << endl;
		throw "File exception";
		ifile.close();
	}
	if (iCurPage < iPage) {
		iCurPage = iCurPage + 1;
		WaitView(iCurPage);
	}
	else {
		WaitView(iCurPage);
	}
	ifile.close();
}
long GetFileLength(ifstream& ifs) {
	long tmppos;
	long respos;
	tmppos = ifs.tellg();
	ifs.seekg(0, ios::end);
	respos = ifs.tellg();
	ifs.seekg(tmppos, ios::beg);
	return respos;
}
void DeleteBookFromFile() {
	int iDelCount;
	cout << "������ɾ����ţ�" << endl;
	cin >> iDelCount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelCount);
	cout << "ɾ������" << endl;
	WaitUser();
}
void WaitView(int iCurPage) {
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q') {
		system("exit");
	}
	if (buf[0] == 'm') {
		MainLoop();
	}
	if (buf[0] == 'n') {
		ViewData(iCurPage);
	}
}
