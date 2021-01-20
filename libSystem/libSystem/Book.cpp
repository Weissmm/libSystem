﻿
#include"Book.h"
#include<string>
#include<fstream>
#include<iostream>
#include<ostream>
using namespace std;
CBook::CBook(char* cName, char* cIsbn, char* cPrice, char* cAuthor) {
	//构造函数
	strncpy_s(m_cName, cName, NUM1);
	strncpy_s(m_cIsbn, cIsbn, NUM1);
	strncpy_s(m_cPrice, cPrice, NUM2);
	strncpy_s(m_cAuthor, cAuthor, NUM2);

}
char* CBook::GetName() {
	return m_cName;
}
void CBook::SetName(char* cName) {
	strncpy_s(m_cName, cName, NUM1);
}
char* CBook::GetIsbn() {
	return m_cIsbn;
}
void CBook::SetIsbn(char* cIsbn) {
	strncpy_s(m_cIsbn, cIsbn, NUM1);
}
char* CBook::GetPrice() {
	return m_cPrice;
}
void CBook::SetPrice(char* cPrice) {
	strncpy_s(m_cPrice, cPrice, NUM2);
}
char* CBook::GetAuthor() {
	return m_cAuthor;
}
void CBook::SetAuthor(char* cAuthor) {
	strncpy_s(m_cAuthor, cAuthor, NUM2);
}

//成员函数WirteData主要实现将图书对象写入到文件中
void CBook::WriteData() {
	ofstream ofile;
	ofile.open("book.dat", ios::binary | ios::app);
	try {
		ofile.write(m_cName, NUM1);
		ofile.write(m_cIsbn, NUM1);
		ofile.write(m_cPrice, NUM2);
		ofile.write(m_cAuthor, NUM2);
	}
	catch (...) {
		throw("file error occurred!");
		ofile.close();
	}
	ofile.close();
}
//成员函数GetBookFromFile能够实现从文件中读取数据来构建对象
void CBook::GetBookFromFile(int iCount) {
	char cName[NUM1];
	char cIsbn[NUM1];
	char cPrice[NUM2];
	char cAuthor[NUM2];
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	try {
		//通过接口读取多少字节
		ifile.seekg(iCount * (NUM1 + NUM1 + NUM2 + NUM2), ios::binary);
		ifile.read(cName, NUM1);
		if (ifile.tellg() > 0) {
			strncpy_s(m_cName, cName, NUM1);
		}

		ifile.read(cIsbn, NUM1);
		if (ifile.tellg() > 0) {
			strncpy_s(m_cIsbn, cIsbn, NUM1);
		}

		ifile.read(cPrice, NUM2);
		if (ifile.tellg() > 0) {
			strncpy_s(m_cPrice, cPrice, NUM2);
		}

		ifile.read(cAuthor, NUM2);
		if (ifile.tellg() > 0) {
			strncpy_s(m_cAuthor, cAuthor, NUM2);
		}
	}
	catch (...) {
		throw("file error occurred!");
		ifile.close();
	}
	ifile.close();
}
void CBook::DeleteData(int iCount) {
	long respos;
	int iDataCount = 0;
	fstream file;
	fstream tmpfile;
	ofstream ofile;
	char cTempBuf[NUM1 + NUM1 + NUM2 + NUM2];
	file.open("book.dat", ios::binary | ios::in | ios::out);
	tmpfile.open("temp.dat", ios::binary | ios::in | ios::out | ios::trunc);
	file.seekg(0, ios::end);
	respos = file.tellg();
	iDataCount = respos / (NUM1 + NUM1 + NUM2 + NUM2);
	if (iCount<0 && iCount>iDataCount) {
		throw "input error";
	}
	else {
		file.seekg((iCount) * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		for (int j = 0; j != (iDataCount - iCount); j++) {
			memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);
			file.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
			tmpfile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
		}
		file.close();
		tmpfile.seekg(0, ios::beg);
		ofile.open("book.dat");
		ofile.seekp((iCount - 1) * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		for (int i = 0; i < (iDataCount - iCount); i++) {
			memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);
			tmpfile.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
			ofile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
		}
	}
	tmpfile.close();
	ofile.close();
	remove("temp.dat");
}
