

/*
	���    : �ܼ������ ���� �Լ����� ����.
	�ۼ���  : ���ص�
	�ۼ���  : 2019-03-11
	Ver     : 1.0
*/


#include "cusInfo.h"
#include "dvdInfo.h"

#ifndef __SCROUT_H__
#define __SCROUT_H__

/*
	���    : Ÿ��Ʋ â�� ���
	��ȯ    : void
*/
void ShowTitle(void);

/*
	���    : �뿩 â�� ���
	��ȯ    : void
*/
void ShowRent(void);


/*
	���    : ȸ�������� �� �� �ִ� â ���
	��ȯ    : void
*/
void ShowRegister(void);

/*
	���    : �� ������ ���
	��ȯ    : void
*/
void ShowCustomerInfo(cusInfo * pCus);

/*
	���    : DVD ������ ���
	��ȯ    : void
*/
void ShowDVDInfo(dvdInfo *pDVD);

/*
	���    : �帣 ������ ���
	��ȯ    : void
*/
void ShowGenre(int gen);

/*
	���    : �Ⱓ ���� �뿩�� ���
	��ȯ    : void
*/
void ShowCusBTWPeriod(cusInfo ** cusInfoBTWperiod);

#endif