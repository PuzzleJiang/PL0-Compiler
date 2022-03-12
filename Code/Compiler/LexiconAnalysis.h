#ifndef LEXICONANALYSIS_H_INCLUDED
#define LEXICONANALYSIS_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "Error.h"
#define MAX_LEX_LEN 30
#define MAX_VAR_NUM 20
using namespace std;


//***********************************Data***********************************
enum symbol
{
    NUL, INTCON, CHARCON, IDENT,
    INTTK, CHARTK, STRTK, ARRAYTK, CONSTTK, VARTK, PROCEDURETK, FUNCTIONTK,
    BEGINTK, ENDTK, IFTK, THENTK, ELSETK, CASETK, OFTK, FORTK, TOTK, DOWNTK, DOTK, READTK, WRITETK,
    PLUS, MINUS, MULT, DIV, LSS, LEQ, GRE, GEQ, EQL, NEQ, ASSIGN, LPARENT, RPARENT, LBRACK, RBRACK, COLON, COMMA, SEMICN, PERIOD
};
extern ifstream fin;
extern char line[1000];
extern char token[256];
extern char ch;
extern int cc;
extern int ll;
extern int lineNum;
extern int number;
extern enum symbol symbol;


//*********************************Function*********************************
void getch();  //��ȡ��һ�ַ�
void getsym();  //�ʷ���������
void clearLine();  //����л�����
void clearToken();  //����ַ����������
void addToken();  //�������ַ������ַ��������
bool isSpace();  //�ж��Ƿ�Ϊ�ո�
bool isNewLine();  //�ж��Ƿ�Ϊ���з�
bool isTab();  //�ж��Ƿ�Ϊ�����
bool isLetter();  //�ж��Ƿ�Ϊ��ĸ
bool ifLetter(); //�ж��Ƿ�Ϊ��ĸ��ͬʱ�ٽ���ʶ����������ĸת����Сд
bool isDigit();  //�ж��Ƿ�Ϊ����
bool isStr();  //�ж��Ƿ����ַ���
int reserverWords();  //��ѯ�����ֱ�ȷ���������Ƿ�
int changeNumber();  //ת������


#endif // LEXICONANALYSIS_H_INCLUDED
