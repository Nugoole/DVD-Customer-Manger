/*
	���   : �� ���� ���� �� ���� �Լ����� ����.
	�ۼ��� : ���ص�
	�ۼ��� : 2019-03-11
	Ver    : 1.0
*/

#ifndef __cusInfoAccess_H__
#define __cusInfoAccess_H__


#include "cusInfo.h"



/*
	���   : cusInfo ���� �ҷ�����
	��ȯ   : void
*/
void initialize_cusInfo();

/*
	���   : cusInfo �Ҵ� �� ����
	��ȯ   : ���� �� ��ϵ� ������ ����,
			 ���� �� 0�� ��ȯ.
*/
int AddCusInfo(char *ID, char *name, char * phoneNum);

/*
	��� : �ش� �� ID�� ������ ������ �ִ� 
		   �����͸� ��ȯ.

	��ȯ : ��� �ȵ� ID�� ��� NULL������ ��ȯ.
*/

cusInfo * GetCusPtrByID(char * ID);

/*
	���    : ���Ե� ID���� üũ
	��ȯ    : ���ԵǾ����� 1, �ƴϸ� 0�� ��ȯ
*/

int IsregistID(char *ID);

/*
	���   : �� ���� �����޸� �Ҵ� �� ������ ����
	��ȯ   : void
*/
void free_cus();

#endif //!_cusInfoAccess_H__
