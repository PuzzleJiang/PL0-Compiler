#include "SyntaxAnalysis.h"

void program()
{
    getsym();
    block();
    if (symbol == PERIOD)
    {
        gen(END, nop, nop, nop);
		//cout << "This is a program." << endl;
    }
    else
    {
        Error(4);
    }
}

void block()
{
    if (symbol == CONSTTK)
    {
        getsym();
        constDeclaration();
        while (symbol == COMMA)
        {
            getsym();
            constDeclaration();
        }
        if (symbol != SEMICN)
        {
            Error(5);
        }
		else
		{
			getsym();
		}
    }
    if (symbol == VARTK)
    {
		getsym();
        while (symbol == IDENT)
        {
            varDeclaration();
            if (symbol != SEMICN)
            {
                Error(5);
            }
			else
			{
				getsym();
			}
        }
    }
    while ((symbol == FUNCTIONTK) || (symbol == PROCEDURETK))
    {
        if (symbol == FUNCTIONTK)
        {
            funcDeclaration();
			//cout << "This is a function declaration." << endl;
        }
        else
        {
            procDeclaration();
			//cout << "This is a procedure declaration." << endl;
        }
    }
	levelTable[nowLevel].entranceAddress = pc;
	compoundStatement();
	gen(RET, nop, nop, nop);
	levelTable[nowLevel].exitAddress = pc;
}

void varDeclaration()
{
	int tempIndex = valIndex;
	int varNum = 0;
	char tempName[MAX_VAR_NUM][MAX_LEX_LEN];

	while (symbol == IDENT)
	{
		strcpy(tempName[varNum], token);
		varNum++;
		getsym();
		if (symbol == COLON)
		{
			break;
		}
		if (symbol != COMMA)
		{
			break;
		}
		getsym();
	}
	if (symbol == COLON)
	{
		getsym();
		if (symbol == INTTK)
		{
			for (int i = 0; i < varNum; i++)
			{
				symbolType tempItem;

				strcpy(tempItem.name, tempName[i]);
				tempItem.kind = Variable;
				tempItem.dataType = Integer;
				valueMem[valIndex] = 0;
				tempItem.address = valIndex;
				tempItem.length = 0;
				tempItem.level = symbolLevel;
				insertSign = insertSymbolTable(tempItem);
				if (insertSign)
				{
					valIndex++;
					levelTable[nowLevel].varNum++;
					//cout << "This is an int var declaration." << endl;
				}
				else
				{
					Error(7);
				}
			}
			getsym();
		}
		else if (symbol == CHARTK)
		{
			for (int i = 0; i < varNum; i++)
			{
				symbolType tempItem;

				strcpy(tempItem.name, tempName[i]);
				tempItem.kind = Variable;
				tempItem.dataType = Char;
				valueMem[valIndex] = 0;
				tempItem.address = valIndex;
				tempItem.length = 0;
				tempItem.level = symbolLevel;
				insertSign = insertSymbolTable(tempItem);
				if (insertSign)
				{
					valIndex++;
					levelTable[nowLevel].varNum++;
					//cout << "This is a char var declaration." << endl;
				}
				else
				{
					Error(7);
				}
			}
			getsym();
		}
		else if (symbol == ARRAYTK)
		{
			getsym();
			if (symbol == LBRACK)
			{
				getsym();
				if (symbol == INTCON)
				{
					int tempNum = number;

					getsym();
					if (symbol == RBRACK)
					{
						getsym();
						if (symbol == OFTK)
						{
							getsym();
							if (symbol == INTTK)
							{
								for (int i = 0; i < varNum; i++)
								{
									symbolType tempItem;

									strcpy(tempItem.name, tempName[i]);
									tempItem.kind = Variable;
									tempItem.dataType = Integer;
									tempItem.address = valIndex;
									tempItem.length = tempNum;
									tempItem.level = symbolLevel;
									insertSign = insertSymbolTable(tempItem);
									if (insertSign)
									{
										for (int j = 0; j < tempNum; j++)
										{
											valueMem[valIndex] = 0;
											valIndex++;
										}
										levelTable[nowLevel].varNum++;
										//cout << "This is an int var array declaration." << endl;
									}
									else
									{
										Error(7);
									}
								}
								getsym();
							}
							else if (symbol == CHARTK)
							{
								for (int i = 0; i < varNum; i++)
								{
									symbolType tempItem;

									strcpy(tempItem.name, tempName[i]);
									tempItem.kind = Variable;
									tempItem.dataType = Char;
									tempItem.address = valIndex;
									tempItem.length = tempNum;
									tempItem.level = symbolLevel;
									insertSign = insertSymbolTable(tempItem);
									if (insertSign)
									{
										for (int j = 0; j < tempNum; j++)
										{
											valueMem[valIndex] = 0;
											valIndex++;
										}
										levelTable[nowLevel].varNum++;
										//cout << "This is a char var array declaration." << endl;
									}
									else
									{
										Error(7);
									}
								}
								getsym();
							}
							else
							{
								Error(8);
							}
						}
						else
						{
							Error(9);
						}
					}
					else
					{
						Error(10);
					}
				}
				else
				{
					Error(11);
				}
			}
			else
			{
				Error(12);
			}
		}
		else
		{
			Error(42);
		}
	}
	else
	{
		Error(14);
	}
	//getsym();
}

void constDeclaration()
{
	if (symbol == IDENT)
	{
		char tempName[MAX_LEX_LEN];

		strcpy(tempName, token);
		getsym();
		if ((symbol == EQL) || (symbol == ASSIGN))
		{
			if (symbol == ASSIGN)
			{
				Error(15);
			}
			getsym();
			if ((symbol == PLUS) || (symbol == MINUS) || (symbol == INTCON))
			{
				int sign = 1;

				if (symbol == MINUS)
				{
					sign = -1;
					getsym();
				}
				else if (symbol == PLUS)
				{
					sign = 1;
					getsym();
				}
				symbolType tempItem;

				strcpy(tempItem.name, tempName);
				tempItem.kind = Constant;
				tempItem.dataType = Integer;
				valueMem[valIndex] = number * sign;
				tempItem.address = valIndex;
				tempItem.length = 0;
				tempItem.level = symbolLevel;
				insertSign = insertSymbolTable(tempItem);
				if (insertSign)
				{
					valIndex++;
					levelTable[nowLevel].constNum++;
					//cout << "This is an int constant declaration." << endl;
					getsym();
				}
				else
				{
					Error(7);
				}
			}
			else if (symbol == CHARCON)
			{
				symbolType tempItem;

				strcpy(tempItem.name, tempName);
				tempItem.kind = Constant;
				tempItem.dataType = Char;
				valueMem[valIndex] = (int) token[0];  //ת����ASCIIֵ����
				tempItem.address = valIndex;
				tempItem.length = 0;
				tempItem.level = symbolLevel;
				insertSign = insertSymbolTable(tempItem);
				if (insertSign)
				{
					valIndex++;
					levelTable[nowLevel].constNum++;
					//cout << "This is a char constant declaration." << endl;
					getsym();
				}
				else
				{
					Error(7);
				}
			}
			else
			{
				Error(16);
			}
		}
		else
		{
			Error(17);
		}
	}
	else
	{
		Error(18);
	}
	//getsym();
}

void funcDeclaration()
{
	if (symbol == FUNCTIONTK)
	{
		getsym();
		funcHead();
		if (symbol == SEMICN)
		{
			getsym();
		}
		block();
		if (symbol != SEMICN)
		{
			Error(19);
		}
		else
		{
			getsym();
		}
		symbolLevel--;
		nowLevel = levelTable[nowLevel].outNum;  //��Ƕ�ײ���лָ�
	}
}

void procDeclaration()
{
	if (symbol == PROCEDURETK)
	{
		getsym();
		procHead();
		if (symbol == SEMICN)
		{
			getsym();
		}
		block();
		if (symbol != SEMICN)
		{
			Error(20);
		}
		else
		{
			getsym();
		}
		symbolLevel--;
		nowLevel = levelTable[nowLevel].outNum;  //��Ƕ�ײ���лָ�
	}
}

void funcHead()
{
	if (symbol == IDENT)
	{
		int tempIndex;
		symbolType tempItem;

		strcpy(tempItem.name, token);
		tempItem.kind = Function;
		tempItem.dataType = Nop;
		tempItem.length = 0;
		tempItem.address = pc;
		tempItem.level = symbolLevel;
		tempIndex = symbolIndex;  //��¼������ʶ���ڷ��ű��е�λ�ã����ں�����������
		insertSign = insertSymbolTable(tempItem);
		if (!insertSign)
		{
			Error(7);
		}
		symbolLevel++;
		getsym();

		levelType tempLevel;

		//��ʼ��tempLevel,Ϊ��ѯ׼��
		tempLevel.constNum = 0;
		tempLevel.varNum = 0;
		tempLevel.paraNum = 0;
		tempLevel.profuncNum = 0;

		strcpy(tempLevel.name, tempItem.name);
		levelTable[nowLevel].profuncNum++;
		tempLevel.outNum = nowLevel;
		tempLevel.levelNum = levelTable[nowLevel].levelNum + 1;
		//nowLevel++;
		tempLevel.paraNum = arguement();
		tempLevel.varNum = 0;
		tempLevel.constNum = 0;
		tempLevel.symbolAddress = symbolIndex;  //��¼���������һ��������λ�á�����add(n:integer;ch:char):integer,���¼����ch�ڷ��ű��еĺ�һλ�á�������Ҳ���ں�������ͷ����һ���֣�
		tempLevel.entranceAddress = pc;
		tempLevel.kind = Function;
		insertLevelTable(tempLevel);

		if (tempLevel.paraNum != 0 && symbol == RPARENT)
		{
			getsym();
		}
		if (symbol == COLON)
		{
			getsym();
			if (symbol == INTTK)
			{
				symbolTable[tempIndex].dataType = Integer;  //�������������ͻ���

				getsym();
				if (symbol != SEMICN)
				{
					Error(5);
				}
				//cout << "This is an int function head." << endl;
			}
			else if (symbol == CHARTK)
			{
				symbolTable[tempIndex].dataType = Char;  //�������������ͻ���

				getsym();
				if (symbol != SEMICN)
				{
					Error(5);
				}
				//cout << "This is a char function head." << endl;
			}
			else
			{
				Error(21);
			}
		}
		else
		{
			if (symbol != SEMICN)
			{
				Error(14);
			}
		}
	}
	else
	{
		Error(18);
	}
}

void procHead()
{
	if (symbol == IDENT)
	{
		symbolType tempItem;

		strcpy(tempItem.name, token);
		tempItem.kind = Procedure;
		tempItem.dataType = Nop;
		tempItem.length = 0;
		tempItem.address = pc;
		tempItem.level = symbolLevel;
		insertSign = insertSymbolTable(tempItem);
		if (!insertSign)
		{
			Error(7);
		}
		getsym();
		symbolLevel++;
		levelType tempLevel;

		//��ʼ��tempLevel,Ϊ��ѯ׼��
		tempLevel.constNum = 0;
		tempLevel.varNum = 0;
		tempLevel.paraNum = 0;
		tempLevel.profuncNum = 0;

		strcpy(tempLevel.name, tempItem.name);
		levelTable[nowLevel].profuncNum++;
		tempLevel.outNum = nowLevel;
		tempLevel.levelNum = levelTable[nowLevel].levelNum + 1;
		//nowLevel++;
		if (symbol == LPARENT)
		{
			tempLevel.paraNum = arguement();
			getsym();
		}
		else
		{
			tempLevel.paraNum = 0;
		}

		tempLevel.varNum = 0;
		tempLevel.constNum = 0;
		tempLevel.symbolAddress = symbolIndex;  //�˴�ԭ��ͬfuncHead
		tempLevel.entranceAddress = pc;
		tempLevel.kind = Procedure;
		insertLevelTable(tempLevel);

		if (symbol != SEMICN)
		{
			Error(5);
		}
		//cout << "This is a procedure head." << endl;
	}
	else
	{
		Error(18);
	}
}

void compoundStatement()
{
	if (symbol == BEGINTK)
	{
		getsym();
		statement();
		while (symbol == SEMICN)
		{
			getsym();
			statement();
		}
		if (symbol != ENDTK)
		{
			Error(22);
		}
		//cout << "This is a compound statement." << endl;
		if (symbol == ENDTK)
		{
			getsym();
		}
	}
	else
	{
		Error(23);
	}
}

void statement()
{
	if (symbol == IDENT)
	{
		findAns tempFind = findTable(token);

		if ((tempFind.typeNum == 4) && (levelTable[tempFind.value].kind == Procedure))  //���̵������
		{
			callStatement();
			if (symbol == RPARENT)
			{
				getsym();
			}
			//���޲�������')'
		}
		else
		{
			assignStatement();
		}
	}
	else if (symbol == IFTK)
	{
		ifStatement();
	}
	else if (symbol == CASETK)
	{
		caseStatement();
	}
	else if (symbol == FORTK)
	{
		forStatement();
	}
	else if (symbol == BEGINTK)
	{
		compoundStatement();
	}
	else if (symbol == READTK)
	{
		readStatement();
	}
	else if (symbol == WRITETK)
	{
		writeStatement();
	}
	else if (symbol == ENDTK || symbol == SEMICN || symbol == ELSETK)  //�����
	{

	}
	else
	{
		Error(24);
	}
}

void assignStatement()
{
	operandType src1, des;

	if (symbol == IDENT)
	{
		findAns tempFind = findTable(token);

		if (tempFind.typeNum == 3)  //����
		{
			getsym();
			if (symbol == LBRACK)
			{
				getsym();

				operandType src1;

				src1 = expression();
				if (src1.typeNum != 3)  //����ʱ����
				{
					operandType temp;

					temp.typeNum = 3;
					temp.value = valIndex;  //Ϊ��ʱ�������ٴ洢�ռ�
					temp.auxPara = 0;
					temp.auxParaValue = 0;
					valIndex++;
					gen(ASS, src1, nop, temp);
					src1 = temp;
				}
				if (symbol == RBRACK)
				{
					if (tempFind.level != 0)  //���ǿ���ֱ�ӷ��ʵ��������
					{
						des.typeNum = 7 + tempFind.level;  //��i����Է��ʵ�
					}
					else
					{
						des.typeNum = 4;
					}
					des.value = tempFind.value;  //������������ƫ�Ƶ�ַ
					des.auxPara = src1.typeNum;
					des.auxParaValue = src1.value;  //����������¼���Ǵ�������С����ʱ��������Ϣ
				}
				else
				{
					Error(10);
				}
			}
			else
			{
				Error(12);
			}
		}
		else if (tempFind.typeNum == 2)  //����
		{
			if (tempFind.level != 0)
			{
				des.typeNum = 7 + tempFind.level;  //��i��ı���
			}
			else
			{
				des.typeNum = 4;  //ֱ�ӷ��ʵı���
			}
			des.value = tempFind.value;
			des.auxPara = 0;  //ʹ�ø����������ֱ��������
			des.auxParaValue = 0;
		}
		else if (tempFind.typeNum == 5)  //����
		{
			if (tempFind.level != 0)
			{
				des.typeNum = 7 + tempFind.level;
			}
			else
			{
				des.typeNum = 4;
			}
			des.value = tempFind.value;
			des.auxPara = 1;  //ʹ�ø����������ֱ��������
			des.auxParaValue = 0;
		}
		else if (tempFind.typeNum == 4)  //������ֵ
		{
			des.typeNum = 7;
			des.value = 0;
			des.auxPara = 0;
			des.auxParaValue = 0;
		}
		else
		{
			Error(25);
		}
		getsym();
		if (symbol == ASSIGN)
		{
			getsym();
			src1 = expression();
			gen(ASS, src1, nop, des);
			//cout << "This is an assign statement." << endl;
		}
		else
		{
			Error(26);
		}
	}
	else
	{
		Error(18);
	}
}

void ifStatement()
{
	operandType src1, src2, des;
	operationType op;

	des.typeNum = 2;  //ָ����ڣ�label��
	des.value = 0;
	des.auxPara = 0;
	des.auxParaValue = 0;
	if (symbol == IFTK)
	{
		getsym();
		src1 = expression();

		switch (symbol)  //����symbolѡ�������
		{
		case LSS:
			op = JGE;
			break;
		case LEQ:
			op = JG;
			break;
		case GRE:
			op = JLE;
			break;
		case GEQ:
			op = JL;
			break;
		case EQL:
			op = JNE;
			break;
		case NEQ:
			op = JE;
			break;
		default:
			op = NOP;
			break;
		}
		getsym();
		src2 = expression();

		int tempPC1;  //��¼���ɵ���������λ�ã�Ϊ���������ת��ַ��׼��

		tempPC1 = pc;
		gen(op, src1, src2, des);  //�˴�����Ԫʽ�м���������ʵ��д��c�����෴����Ϊ�˴�����Ԫʽ����Ϊ����������ת������c������������������ִ�У�������������ת
		if (symbol == THENTK)
		{
			getsym();
			statement();
			if (symbol == ELSETK)
			{
				int tempPC2;

				tempPC2 = pc;
				gen(JMP, nop, nop, des);
				midcodeTable[tempPC1].des.value = pc;  //����ǰ��ת�ĵ�ַ���������䴦
				getsym();
				statement();
				midcodeTable[tempPC2].des.value = pc;  //��if�������ĵ�ַ����
			}
			else
			{
				midcodeTable[tempPC1].des.value = pc;  //��else����������ַ����
			}
			//cout << "This is an if statement." << endl;
		}
		else
		{
			Error(27);
		}
	}
	else
	{
		Error(28);
	}
}

void caseStatement()
{
	int sign = 1, tempPC;
	operandType src1, src2, des;

	des.typeNum = 2;  //ָ����ڣ�label��
	des.auxPara = 0;
	des.auxParaValue = 0;
	if (symbol == CASETK)
	{
		getsym();
		src1 = expression();
		if (src1.typeNum != 3)
		{
			operandType temp;

			temp.typeNum = 3;
			temp.value = valIndex;
			temp.auxPara = 0;
			temp.auxParaValue = 0;
			valIndex++;
			gen(ASS, src1, nop, temp);
			src1 = temp;
		}

		if (symbol == OFTK)
		{
			getsym();

			if (symbol == PLUS || symbol == MINUS || symbol == INTCON)
			{
				if (symbol == PLUS)
				{
					sign = 1;
					getsym();
				}
				else if (symbol == MINUS)
				{
					sign = -1;
					getsym();
				}
				getsym();
				src2.typeNum = 1;
				src2.value = sign * number;
				src2.auxPara = 0;
				src2.auxParaValue = 0;
				if (symbol == COLON)
				{
					operandType target;

					target.typeNum = 2;
					target.auxPara = 0;
					target.auxParaValue = 0;
					tempPC = pc;
					gen(JNE, src1, src2, target);
					getsym();
					statement();
					//getsym();
					midcodeTable[tempPC].des.value = pc;
				}
				else
				{
					Error(14);

				}
			}
			else if (symbol == CHARCON)
			{
				src2.typeNum = 1;
				src2.value = (int)token[0];
				src2.auxPara = 1;
				src2.auxParaValue = 0;
				getsym();
				if (symbol == COLON)
				{
					operandType target;

					target.typeNum = 2;
					target.auxPara = 0;
					target.auxParaValue = 0;
					tempPC = pc;
					gen(JNE, src1, src2, target);
					getsym();
					statement();
					//getsym();
					midcodeTable[tempPC].des.value = pc;
				}
				else
				{
					Error(14);
				}
			}
			else
			{
				Error(29);
			}

			while (symbol == SEMICN)
			{
				getsym();
				sign = 1;
				if (symbol == PLUS || symbol == MINUS || symbol == INTCON)
				{
					if (symbol == PLUS)
					{
						sign = 1;
						getsym();
					}
					else if (symbol == MINUS)
					{
						sign = -1;
						getsym();
					}
					getsym();
					src2.typeNum = 1;
					src2.value = sign * number;
					src2.auxPara = 0;
					src2.auxParaValue = 0;
					if (symbol == COLON)
					{
						operandType target;

						target.typeNum = 2;
						target.auxPara = 0;
						target.auxParaValue = 0;
						tempPC = pc;
						gen(JNE, src1, src2, target);
						getsym();
						statement();
						//getsym();
						midcodeTable[tempPC].des.value = pc;
					}
					else
					{
						Error(14);

					}
				}
				else if (symbol == CHARCON)
				{
					src2.typeNum = 1;
					src2.value = (int) token[0];
					src2.auxPara = 1;
					src2.auxParaValue = 0;
					getsym();
					if (symbol == COLON)
					{
						operandType target;

						target.typeNum = 2;
						target.auxPara = 0;
						target.auxParaValue = 0;
						tempPC = pc;
						gen(JNE, src1, src2, target);
						getsym();
						statement();
						//getsym();
						midcodeTable[tempPC].des.value = pc;
					}
					else
					{
						Error(14);
					}
				}
				else
				{
					Error(29);
				}
			}
			if (symbol == ENDTK)
			{
				//cout << "This is a case statement." << endl;
				getsym();
			}
			else
			{
				Error(22);
			}
		}
		else
		{
			Error(9);
		}
	}
	else
	{
		Error(30);
	}
}

void readStatement()
{
	if (symbol == READTK)
	{
		getsym();
		if (symbol == LPARENT)
		{
			do
			{
				getsym();
				if (symbol == IDENT)
				{
					findAns tempFind = findTable(token);

					if (tempFind.typeNum == 0)
					{
						Error(31);
					}
					else
					{
						operandType src1, src2;

						if (tempFind.level != 0)
						{
							src1.typeNum = 7 + tempFind.level;
						}
						else
						{
							src1.typeNum = 4;
						}
						if (tempFind.typeNum == 5)
						{
							src1.auxPara = 1;  //����������¼����һ������
						}
						else
						{
							src1.auxPara = 0;
						}
						src1.auxParaValue = 0;
						src1.value = tempFind.value;
						src2.typeNum = 1;  //src2��¼�������� 1:char 2:integer
						src2.auxPara = 0;
						src2.auxParaValue = 0;
						if (symbolTable[tempFind.symbolTableIndex].dataType == Char)
						{
							src2.value = 1;
						}
						else
						{
							src2.value = 2;
						}
						gen(READ, src2, nop, src1);
						getsym();
					}
				}
				else
				{
					Error(18);
				}
			} while (symbol == COMMA);
			if (symbol != RPARENT)
			{
				Error(32);
			}
			else
			{
				//cout << "This is a read statement." << endl;
				getsym();
			}
		}
		else
		{
			Error(33);
		}
	}
	else
	{
		Error(34);
	}
}

void writeStatement()
{
	operandType src1;

	if (symbol == WRITETK)
	{
		getsym();
		if (symbol == LPARENT)
		{
			getsym();
			if (symbol == STRTK)
			{
				strcpy(strTable[strIndex], token);
				src1.typeNum = 5;
				src1.value = strIndex;  //��¼���ַ�����ά�����е�λ��
				src1.auxPara = 0;
				src1.auxParaValue = 0;
				strIndex++;
				gen(WRITE, src1, nop, nop);
				getsym();
				if (symbol == COMMA)
				{
					getsym();
					src1 = expression2();
					if (expressionType == 1)
					{
						operandType src2;

						src2.typeNum = 1;  //src2��Ϊ����������src1�����ͣ�1�����ַ�����
						gen(WRITE, src1, src2, nop);
					}
					else
					{
						gen(WRITE, src1, nop, nop);
					}
				}
				if (symbol == RPARENT)
				{
					getsym();
					//cout << "This is a write statement." << endl;
				}
				else
				{
					Error(47);
				}
			}
			else
			{
				src1 = expression2();
				if (expressionType == 1)
				{
					operandType src2;

					src2.typeNum = 1;
					gen(WRITE, src1, src2, nop);
				}
				else
				{
					gen(WRITE, src1, nop, nop);
				}
				if (symbol == RPARENT)
				{
					getsym();
					//cout << "This is a write statement." << endl;
				}
				else
				{
					Error(47);
				}
			}
		}
		else
		{
			Error(33);
		}
	}
	else
	{
		Error(35);
	}
}

void forStatement()
{
	operandType src1, src2, des;
	operandType path, pc1, pc2;
	int sign, tempPC;

	path.typeNum = 1;  //����Ϊ1
	path.value = 1;
	path.auxPara = 0;
	path.auxParaValue = 0;

	if (symbol == FORTK)
	{
		getsym();
		if (symbol == IDENT)
		{
			findAns tempFind = findTable(token);

			if ((tempFind.typeNum == 2) || (tempFind.typeNum == 5))
			{
				getsym();
				if (tempFind.typeNum == 2)
				{
					des.auxPara = 0;
				}
				else
				{
					des.auxPara = 1;  //����������¼Ϊ����
				}
				if (tempFind.level != 0)  //�ж��Ƿ�Ϊ����ֱ�ӷ��ʵı���
				{
					des.typeNum = 7 + tempFind.level;
				}
				else
				{
					des.typeNum = 4;
				}

				des.value = tempFind.value;
				des.auxParaValue = 0;
				if (symbol == ASSIGN)
				{
					getsym();
					src1 = expression();
					gen(ASS, src1, nop, des);
					if (symbol == TOTK)
					{
						sign = 1;
					}
					else if (symbol == DOWNTK)
					{
						sign = -1;
					}
					else
					{
						Error(36);
					}
					if (symbol == TOTK || symbol == DOWNTK)
					{
						getsym();
						src2 = expression();
						pc1.typeNum = 2;  //ָ�����
						pc1.value = pc;
						pc1.auxPara = 0;
						pc1.auxParaValue = 0;
						pc2.typeNum = 2;
						pc2.auxPara = 0;
						pc2.auxParaValue = 0;
						if (symbol == DOTK)
						{
							if (sign == 1)
							{
								gen(JG, des, src2, pc2);
							}
							else
							{
								gen(JL, des, src2, pc2);
							}

							getsym();
							statement();

							tempPC = pc;
							gen(JE, des, src2, pc2);
							if (sign == 1)
							{
								gen(ADD, des, path, des);
							}
							else
							{
								gen(SUB, des, path, des);
							}
							gen(JMP, nop, nop, pc1);
							midcodeTable[pc1.value].des.value = pc;
							midcodeTable[tempPC].des.value = pc;  //��Ż���
						    //cout << "This is a for statement." << endl;
						}
						else
						{
							Error(37);
						}
					}
				}
				else
				{
					Error(26);
				}
			}
		}
		else
		{
			Error(18);
		}
	}
	else
	{
		Error(38);
	}
}

operandType callStatement()
{
	operandType src1, des;
	operandType operandArray[100];  //����ջ
	findAns tempFind;
	levelType tempLevel;
	int tempValue;
	int operandArrayIndex = 0;

	tempFind = findTable(token);
	tempValue = tempFind.value;
	tempLevel = levelTable[tempFind.value];
	operandArrayIndex = 0;

	if (tempLevel.paraNum != 0)  //����������Ϊ0
	{
		getsym();
		if (symbol == LPARENT)
		{
			for (int j = tempLevel.symbolAddress - tempLevel.paraNum; j < tempLevel.symbolAddress; j++)
			{
				getsym();
				operandArray[operandArrayIndex] = expression2();
				if (symbolTable[j].kind == Varparam)
				{
					src1.typeNum = 1;  //src1��¼��������
					if ((operandArray[operandArrayIndex].typeNum == 1) || (operandArray[operandArrayIndex].typeNum == 3))
					{
						Error(39);  //var���ͺͲ������Ͳ�ƥ�䣬��Ҫʹ�ñ���
					}
				}
				else
				{
					src1.typeNum = 0;
				}
				operandArrayIndex++;
				if ((symbol != COMMA) && (symbol != RPARENT))
				{
					Error(40);
				}
			}  //��ѭ�����ڽ�����������������У�ͬʱ�жϲ��������Ƿ�ƥ��
			//cout << "This is a call statement." << endl;
			if (symbol != RPARENT)
			{
				if (symbol == COMMA)
				{
					Error(43);
				}
				else
				{
					Error(2);
				}
			}

			operandArrayIndex = 0;
			for (int j = tempLevel.symbolAddress - tempLevel.paraNum; j < tempLevel.symbolAddress; j++)
			{
				if (symbolTable[j].kind == Varparam)
				{
					src1.typeNum = 1;  //src1��¼��������
				}
				else
				{
					src1.typeNum = 0;
				}
				gen(PUSH, operandArray[operandArrayIndex], src1, nop);  //���������ѹ��ջ
				operandArrayIndex++;
			}  //��ѭ�����������м����
		}
	}
	else  //��������Ϊ0
	{
		getsym();
		//cout << "This is a call statement." << endl;
		if (symbol == LPARENT)
		{
			Error(44);
		}
	}
	if (levelTable[nowLevel].levelNum >= tempLevel.levelNum)
	{
		for (int k = 1; k <= tempLevel.levelNum; k++)
		{
			des.typeNum = 1;
			des.value = k;
			des.auxPara = 0;
			des.auxParaValue = 0;
			gen(PUD, des, nop, nop);
		}
	}
	else
	{
		for (int k = levelTable[nowLevel].levelNum; k > 0; k--)
		{
			des.typeNum = 1;
			des.value = k;
			des.auxPara = 0;
			des.auxParaValue = 0;
			gen(PUD, des, nop, nop);
		}
		des.value = 0;
		gen(PUD, des, nop, nop);
	}
	gen(PUSH, nop, nop, nop);
	des.typeNum = 2;
	des.value = tempValue;
	des.auxPara = 0;
	des.auxParaValue = 0;
	gen(CALL, des, nop, nop);
	src1.typeNum = 3;
	src1.value = valIndex;
	src1.auxPara = 0;
	src1.auxParaValue = 0;
	valIndex++;
	if (levelTable[tempValue].kind == Function)
	{
		gen(POP, nop, nop, src1);
	}

	return src1;
}

operandType expression()
{
	operandType src1, src2, des;
	int sign = 1;

	des.typeNum = 3;  //��ʱ����
	des.value = valIndex;
	des.auxPara = 0;
	des.auxParaValue = 0;
	valIndex++;
	expressionType = 0;

	if ((symbol == PLUS) || (symbol == MINUS))
	{
		if (symbol == PLUS)
		{
			sign = 1;
		}
		else
		{
			sign = -1;
		}
		getsym();
	}

	src1 = term();
	if (sign == -1)
	{
		gen(NEG, src1, nop, des);
	}
	else
	{
		gen(ASS, src1, nop, des);
	}

	while ((symbol == PLUS) || (symbol == MINUS))
	{
		if (symbol == PLUS)
		{
			sign = 1;
		}
		else
		{
			sign = -1;
		}
		getsym();

		src1 = term();
		if (sign == 1)
		{
			gen(ADD, src1, des, des);
		}
		else
		{
			gen(SUB, des, src1, des);
		}
	}
	return des;
}

operandType expression2()
{
	operandType src1, src2, des;
	int sign = 1;
	bool tag = false;

	expressionType = 0;

	if ((symbol == PLUS) || (symbol == MINUS))
	{
		if (symbol == PLUS)
		{
			sign = 1;
		}
		else
		{
			sign = -1;
		}
		getsym();
	}

	src1 = term();
	src2 = src1;

	if (sign == -1)
	{
		gen(NEG, src1, nop, des);
		tag = true;
	}

	while ((symbol == PLUS) || (symbol == MINUS))
	{
		if (!tag)
		{
			tag = true;
			des.typeNum = 3;
			des.value = valIndex;
			des.auxPara = 0;
			des.auxParaValue = 0;
			valIndex++;
			gen(ASS, src1, nop, des);
			expressionType = 0;
		}
		if (symbol == PLUS)
		{
			sign = 1;
		}
		else
		{
			sign = -1;
		}
		getsym();

		src1 = term();
		if (sign == 1)
		{
			gen(ADD, src1, des, des);
		}
		else
		{
			gen(SUB, des, src1, des);
		}
	}
	if (!tag)
	{
		return src2;
	}
	else
	{
		return des;
	}
}

operandType term()
{
	int sign = 1;
	bool tag = false;
	operandType src1, des;

	des = factor();
	if (symbol != SEMICN)
	{
		getsym();
	}
	while ((symbol == MULT) || (symbol == DIV))
	{
		if (!tag)
		{
			tag = true;
			src1 = des;
			des.typeNum = 3;
			des.value = valIndex;
			des.auxPara = 0;
			des.auxParaValue = 0;
			valIndex++;
			gen(ASS, src1, nop, des);
			expressionType = 0;
		}
		if (symbol == MULT)
		{
			sign = 1;
		}
		else if (symbol == DIV)
		{
			sign = -1;
		}
		getsym();
		src1 = factor();
		if (sign == 1)
		{
			gen(MUL, src1, des, des);
		}
		else
		{
			gen(DIVI, des, src1, des);
		}
		getsym();
	}
	return des;
}

operandType factor()
{
	operandType src1, des;

	des = nop;
	if (symbol == IDENT)
	{
		findAns tempFind = findTable(token);

		if (tempFind.typeNum == 0)
		{
			Error(31);
		}
		else
		{
			if (tempFind.typeNum != 3)
			{
				if (tempFind.typeNum == 4)  //��������
				{
					des = callStatement();
				}
				else if (tempFind.typeNum == 1)  //����
				{
					des.typeNum = 1;
					des.value = tempFind.value;
					des.auxPara = 0;
					des.auxParaValue = 0;
				}
				else  //�������߲�������
				{
					if (tempFind.level != 0)
					{
						des.typeNum = 7 + tempFind.level;
					}
					else
					{
						des.typeNum = 4;
					}
					des.value = tempFind.value;
					if (tempFind.typeNum == 5)  //����
					{
						des.auxPara = 1;  //�����������Ϊ1�������ǲ�������
						des.auxParaValue = 0;
					}
					else
					{
						des.auxPara = 0;  //�����������Ϊ0�������Ǳ�������
						des.auxParaValue = 0;
					}
				}
			}
			else  //<����> ::= <��ʶ��>'['<���ʽ>']'
			{
				getsym();
				if (symbol == LBRACK)
				{
					getsym();
					src1 = expression();

					if (src1.typeNum != 3)
					{
						operandType temp;

						temp.typeNum = 3;
						temp.value = valIndex;
						temp.auxPara = 0;
						temp.auxParaValue = 0;
						valIndex++;
						gen(ASS, src1, nop, temp);
						src1 = temp;
					}
					if (symbol == RBRACK)
					{
						if (tempFind.level != 0)
						{
							des.typeNum = 7 + tempFind.level;
						}
						else
						{
							des.typeNum = 4;
						}
						des.value = tempFind.value;
						des.auxPara = src1.typeNum;  //����������¼�����С����Ϣ
						des.auxParaValue = src1.value;
					}
					else
					{
						Error(10);
					}
				}
				else
				{
					Error(12);
				}
			}
		}
		if (tempFind.typeNum == 0)
		{
			Error(31);
		}
		else
		{
			if (symbolTable[tempFind.symbolTableIndex].dataType == Char)
			{
				expressionType = 1;  //��¼��������Ϊchar����1
			}
		}
	}
	else if (symbol == INTCON)
	{
		des.typeNum = 1;
		des.value = number;
		des.auxPara = 0;
		des.auxParaValue = 0;
	}
	else if (symbol == LPARENT)
	{
		getsym();
		src1 = expression();
		if (symbol == RPARENT)
		{
			des = src1;
		}
		else
		{
			Error(32);
		}
	}
	else
	{
		Error(46);
	}
	return des;
}

int arguement()
{
	int argNum = 0;

	if (symbol == LPARENT)
	{
		getsym();
		if (symbol == RPARENT)
		{
			Error(45);
		}
		argNum += argSegment();
		getsym();
		while (symbol == SEMICN)
		{
			getsym();
			argNum += argSegment();
			getsym();
			if (symbol != SEMICN)
			{
				break;
			}
		}
		if (symbol != RPARENT)
		{
			Error(32);
		}
	}
	else
	{
		argNum = 0;
	}
	return argNum;
}

int argSegment()
{
	int argNum = 0;
	int len = 0;
	Kind argKind = Param;
	char tempName[MAX_VAR_NUM][MAX_LEX_LEN];

	if (symbol == VARTK)
	{
		getsym();
		argKind = Varparam;
	}

	while (symbol == IDENT)
	{
		strcpy(tempName[len], token);
		len++;
		getsym();
		if (symbol == COLON)
		{
			break;
		}
		if (symbol != COMMA)
		{
			break;
		}
		getsym();
	}

	if (symbol == COLON)
	{
		getsym();
		if (symbol == INTTK)
		{
			for (int i = 0; i < len; i++)
			{
				symbolType tempItem;

				strcpy(tempItem.name, tempName[i]);
				tempItem.kind = argKind;
				tempItem.dataType = Integer;
				valueMem[valIndex] = 0;
				tempItem.address = valIndex;
				tempItem.length = 0;
				tempItem.level = symbolLevel;
				insertSign = insertSymbolTable(tempItem);
				if (insertSign)
				{
					valIndex++;
					argNum++;
				}
				else
				{
					Error(7);
				}
			}
		}
		else if (symbol == CHARTK)
		{
			for (int i = 0; i < len; i++)
			{
				symbolType tempItem;

				strcpy(tempItem.name, tempName[i]);
				tempItem.kind = argKind;
				tempItem.dataType = Char;
				valueMem[valIndex] = 0;
				tempItem.address = valIndex;
				tempItem.length = 0;
				tempItem.level = symbolLevel;
				insertSign = insertSymbolTable(tempItem);
				if (insertSign)
				{
					valIndex++;
					argNum++;
				}
				else
				{
					Error(7);
				}
			}
		}
		else
		{
			Error(41);
		}
	}
	else
	{
		Error(14);
	}
	return argNum;
}
