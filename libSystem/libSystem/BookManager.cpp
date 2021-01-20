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
void SetScreenGrid();//设置屏幕显示的行数和列数
void ClearScreen();//清除屏幕信息
void SetSysCaption(const char* pText);//设置窗体标题栏
void ShowWelcome();//显示欢迎信息
void ShowRootMenu();//显示菜单信息
void WaitView(int iCurPage);//浏览数据时等待用户操作
void WaitUser();//等待用户操作
void GuideInput();//使用向导添加图书信息
int GetSelect();//获得用户选择
long GetFileLength(ifstream& ifs);//获取文件长度
void ViewData(int iSelPage);//浏览所有的图书记录
void DeleteBookFromFile();//在文件中产生图书信息
void MainLoop();//主循环
int main() {
	SetScreenGrid();
	SetSysCaption("图书管理系统");
	MainLoop();
	system("pause>nul");
	return 0;
}
void SetScreenGrid() {
	//设置窗体大小
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}
void SetSysCaption() {
	//设置窗口标题
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
	cout << "       图书管理系统     " << endl;
	cout << setw(50);
	cout << "**********************" << endl;
}
void ShowRootMenu() {
	cout << setw(43);
	cout << "1 添加图书";
	cout << endl;
	cout << setw(43);
	cout << "2 浏览全部";
	cout << endl;
	cout << setw(43);
	cout << "3 删除图书";
	cout << endl;
	cout << endl;
	cout << setw(42);
	cout << "选择操作：";
}
void WaitUser() {
	int iInputPage = 0;
	cout << "enter 返回主菜单 q 退出" << endl;
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
	cout << "输入书名:" << endl;
	cin >> inName;
	cout << "输入ISBN:" << endl;
	cin >> inIsbn;
	cout << "输入价格：" << endl;
	cin >> inPrice;
	cout << "输入作者：" << endl;
	cin >> inAuthor;
	CBook book(inName, inIsbn, inPrice, inAuthor);
	book.WriteData();
	cout << "保存成功" << endl;
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
	cout << "共有记录：" << iDataCount << " ";
	cout << "共有页数：" << iPage << " ";
	cout << "当前页数：" << iCurPage << "  ";
	cout << "显示下一页 n 返回 m" << endl;
	cout << endl;
	cout << setw(5) << "序号";
	cout << setw(22) << "书名" << setw(22) << "ISBN";
	cout << setw(15) << "价格" << setw(15) << "作者";
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
		cout << "选择操作：";
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
	cout << "请输入删除编号：" << endl;
	cin >> iDelCount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelCount);
	cout << "删除结束" << endl;
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
