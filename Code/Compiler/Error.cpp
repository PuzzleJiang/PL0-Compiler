#include "Error.h"

void Error(int errorNum)
{
	cout << line << endl;
	cout << "��" << lineNum << "��,";
	cout << "����ԭ��";
	switch (errorNum)
	{
	case 1:
		cout << "�ַ�ȱ�� '" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != COMMA)
		{
			getsym();
		}
		break;
	case 2:
		cout << "�Ƿ��ַ�" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != COMMA)
		{
			getsym();
		}
		break;
	case 3:
		cout << "�ַ���ȱ�� \"" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 4:
		cout << "����δ�� . ����" << endl;
		errorSum++;
		break;
	case 5:
		cout << "��" << line << "֮ǰȱ�� ;" << endl;
		errorSum++;
		break;
	case 6:
		cout << "ȱ�� ;" << endl;
		errorSum++;
		break;
	case 7:
		cout << "�ظ����壬���ű����ʧ��" << endl;
		errorSum++;
		break;
	case 8:
		cout << "���鶨���������Ͳ��Ϸ�" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 9:
		cout << "ȱ�ٱ����� of" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 10:
		cout << "ȱ�� ]" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 11:
		cout << "���鳤�����ʹ���" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 12:
		cout << "ȱ�� [" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 13:
		cout << "ȱ�ٱ����� array" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 14:
		cout << "ȱ�� :" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 15:
		cout << "������ֵ���Ų��Ϸ����� :=" << endl;
		errorSum++;
		break;
	case 16:
		cout << "�����������Ͳ��Ϸ�" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != COMMA)
		{
			getsym();
		}
		break;
	case 17:
		cout << "������ֵ���Ų��Ϸ�" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != COMMA)
		{
			getsym();
		}
		break;
	case 18:
		cout << "��ʶ�����岻�Ϸ�" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 19:
		cout << "����δ�� ; ����" << endl;
		errorSum++;
		break;
	case 20:
		cout << "����δ�� ; ����" << endl;
		errorSum++;
		break;
	case 21:
		cout << "�����������Ͳ��Ϸ�" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != VARTK && symbol != BEGINTK)
		{
			getsym();
		}
		break;
	case 22:
		cout << "ȱ�ٱ����� end" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != FUNCTIONTK && symbol != PROCEDURETK)
		{
			getsym();
		}
		break;
	case 23:
		cout << "ȱ�ٱ����� begin" << endl;
		errorSum++;
		while (symbol != ENDTK)
		{
			getsym();
		}
		getsym();
		break;
	case 24:
		cout << "���Ϸ����" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != ENDTK)
		{
			getsym();
		}
		break;
	case 25:
		cout << "��ֵ����ʶ�����Ͳ��Ϸ�" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 26:
		cout << "ȱ�� :=" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 27:
		cout << "ȱ�ٱ����� then" << endl;
		errorSum++;
		while (symbol != ELSETK && symbol != ENDTK) 
		{
			getsym();
		}
		break;
	case 28:
		cout << "ȱ�ٱ����� if" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != THENTK && symbol != ELSETK)
		{
			getsym();
		}
		break;
	case 29:
		cout << "case������Ԫ�ر��г������Ͳ��Ϸ�" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 30:
		cout << "ȱ�ٱ����� case" << endl;
		errorSum++;
		while (symbol != ENDTK)
		{
			getsym();
		}
		break;
	case 31:
		cout << "��ѯ���ű�ʧ�ܣ�δ����" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 32:
		cout << "ȱ�� )" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 33 :
		cout << "ȱ�� (" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 34:
		cout << "ȱ�ٱ����� read" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 35:
		cout << "ȱ�ٱ����� write" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 36:
		cout << "ȱ�ٱ����� downto �� to" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 37:
		cout << "ȱ�ٱ����� do" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 38:
		cout << "ȱ�ٱ����� for" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 39:
		cout << "var���ͺͲ������Ͳ�ƥ�䣬��Ҫʹ�ñ���" << endl;
		errorSum++;
		break;
	case 40:
		cout << "�������ȱ�� , �� ;" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 41:
		cout << "�����������Ͷ��岻�Ϸ�" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 42:
		cout << "�����������Ͷ��岻�Ϸ�" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 43:
		cout << "����������ƥ��" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 44:
		cout << "��������Ϊ0�����ù��̻����޲���" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 45:
		cout << "��������Ϊ0����Ӧ������" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 46:
		cout << "�������Ͳ��Ϸ�" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 47:
		cout << "write����ʽ���Ϸ�" << endl;
		errorSum++;
		while (symbol != RPARENT && symbol != SEMICN)
		{
			getsym();
		}
		break;
	default:
		break;
	}
}
