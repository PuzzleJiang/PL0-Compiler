#ifndef MIDCODEPRODUECER_H_INCLUDED
#define MIDCODEPRODUECER_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#define MAX_LEX_LEN 30
#define MAX_VAR_NUM 20
using namespace std;


//***********************************Data***********************************
enum operationType
{
	NNN,
    ADD, SUB, MUL, DIVI, NEG,
    JMP, JG, JGE, JL, JLE, JE, JNE,
    ASS, CALL, RET, READ, WRITE, PUSH, POP, PUD, END, NOP
};
struct operandType
{
    int typeNum;  //���ͱ��1:���� 2:ָ����� 3:��ʱ���� 4:ֱ�ӷ��ʱ��� 5:�ַ��� 6:����/���� 7:����ֵ 7+i:֮ǰi���еı���
    int value;  //ֵ ����ֵ|ָ���ַ|��Ե�ַ
    int auxPara;  //������������������ʹ���ַ
    int auxParaValue;
};
struct midcodeType
{
    operationType op;
    operandType src1;
    operandType src2;
    operandType des;
};
extern int pc;
extern midcodeType midcodeTable[1000];


//*********************************Function*********************************
void gen(operationType op, operandType src1, operandType src2, operandType res);  //���м�����¼����Ԫʽ����
bool operandTypeEqual(operandType src1, operandType src2);


#endif // MIDCODEPRODUECER_H_INCLUDED
