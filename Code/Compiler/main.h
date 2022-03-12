#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "LexiconAnalysis.h"
#include "Error.h"
#include "SyntaxAnalysis.h"
#include "SymbolTableManage.h"
#include "MidcodeProduecer.h"
#include "FinalcodeProducer.h"
#include "Optimize.h"
#include "DAGAnalysis.h"
#include "DataFlowAnalysis.h"
#include "FinalcodeProducerOP.h"
#define MAX_LEX_LEN 30
#define MAX_VAR_NUM 20
using namespace std;


//***********************************Data***********************************
int cc;  //�л�����ָ��
int ll;  //�л���������
int lineNum;  //�к�
int number;  //����
int nowLevel;  //��ǰ�����
int pc;  //�м�����ָ�루ָ��ţ�
int pc1;
int symbolIndex;  //��ʶ����ָ��
int levelTableIndex;  //��α�ָ��
int valIndex;  //���ݴ洢��ָ��
int expressionType;  //��¼���ʽ����ֵ���� 0:integer 1:char
int strIndex;  //�ַ�������ָ��
int symbolLevel;  //��ʶ�����
int errorLineNum;  //��¼������ֵ�����
int blockNum;
int errorSum;
char ch;  //��ȡ�����ַ�
bool insertSign;  //�Ƿ�����־
bool ArrayOpen;
enum symbol symbol;  //��ŷ�������
operandType nop;  //����һ���������Ŀ�����
int valueMem[1000];  //���ݴ洢��
int funcOrder[100];
int block_in_num[100];
int block_out_num[100];
int block_def_num[100];
int block_use_num[100];
int block_begin[100];
int block_begin_op[100];
int jumpRelation[100][100];
char line[1000];  //�л�����
char token[256];  //��ŵ�ǰ�ַ�
char strTable[100][100];  //����ַ���
bool Bbegin[1000];
symbolType symbolTable[1000];  //��ʶ����
midcodeType midcodeTable[1000];  //��Ԫʽ-�м�����
midcodeType OPmidcodeTable[1000];
levelType levelTable[1000];  //��Ź��̻��ߺ�����ÿ�������Ϣ�ı��ò�κ���Ϊָ�룩
operandType block_in[100][100];
operandType block_out[100][100];
operandType block_def[100][100];
operandType block_use[100][100];
operandType block_mem[100][2];
ifstream fin;
ofstream fout;


//*********************************Function*********************************
void init();  //��ʼ��
void LexiconAnalysisTest();  //�ʷ������������
void symbolTableTest();  //���ű����ݲ���
void midcodeTest();  //�м�������


#endif // MAIN_H_INCLUDED
