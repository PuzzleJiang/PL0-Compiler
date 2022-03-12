#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "LexiconAnalysis.h"
#define MAX_LEX_LEN 30
#define MAX_VAR_NUM 20
using namespace std;


//***********************************Data***********************************
extern int lineNum;
extern int cc;
extern int errorSum;
extern char line[1000];

//*********************************Function*********************************
void Error(int errorNum);  //���ݴ�����������Ӧ�Ĵ�����Ϣ


#endif // ERROR_H_INCLUDED
