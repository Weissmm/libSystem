#pragma once
#define NUM1 128
#define NUM2 50
class CBook {
public:
	CBook() {}
	CBook(char* cName, char* cIsbn, char* cPrice, char* cAuthor);
	~CBook() {};//��������
public:
	char* GetName();//��ȡͼ������
	void SetName(char* cName);//����ͼ������

	char* GetIsbn();//��ȡͼ��ISBN���
	void SetIsbn(char* cName);//����Isbn���

	char* GetPrice();//��ȡͼ��۸�
	void SetPrice(char* cPrice);//����Isbn���

	char* GetAuthor();//��ȡ��������
	void SetAuthor(char* cName);//������������
	//����WriteData,DeleteData��������д�ļ��ĺ������൱�ڲ������ݿ�Ľӿ�
	void WriteData();
	void DeleteData(int iCount1);
	void GetBookFromFile(int iCount);



protected:
	char m_cName[NUM1];
	char m_cIsbn[NUM1];
	char m_cPrice[NUM2];
	char m_cAuthor[NUM2];
};

