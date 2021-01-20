#pragma once
#define NUM1 128
#define NUM2 50
class CBook {
public:
	CBook() {}
	CBook(char* cName, char* cIsbn, char* cPrice, char* cAuthor);
	~CBook() {};//析构函数
public:
	char* GetName();//获取图书名称
	void SetName(char* cName);//设置图书名称

	char* GetIsbn();//获取图书ISBN编号
	void SetIsbn(char* cName);//设置Isbn编号

	char* GetPrice();//获取图书价格
	void SetPrice(char* cPrice);//设置Isbn编号

	char* GetAuthor();//获取作者姓名
	void SetAuthor(char* cName);//设置作者姓名
	//函数WriteData,DeleteData是类对象读写文件的函数，相当于操作数据库的接口
	void WriteData();
	void DeleteData(int iCount1);
	void GetBookFromFile(int iCount);



protected:
	char m_cName[NUM1];
	char m_cIsbn[NUM1];
	char m_cPrice[NUM2];
	char m_cAuthor[NUM2];
};

