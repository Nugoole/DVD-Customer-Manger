
#ifndef __DVDINFOACCESS_H__
#define __DVDINFOACCESS_H__

#include "dvdInfo.h"

enum { Year, Month, Date };



/*
	���   : DVD ���� �ҷ�����
	��ȯ   : void
*/
void initialize_dvdInfo();


/*
	���   : �ش� ISBN�� ���� DVD�� ���� �뿩������ �ҷ���
	��ȯ   : void
*/
void initialize_rentedInfo(char * ISBN);



/*
	���   : dvdInfo ������� �Ҵ� �� ����ü �迭�� ����
	��ȯ   : ������ ��ϵ� ������ ��,
			 ���н� 0�� ��ȯ
*/
int AddDVD_Info(char *ISBN, char * title, int *genre);


/*
	���   : dvd ���� �����޸� �Ҵ� �� ������ ����
	��ȯ   : void
*/
void free_dvds();


/*
	���   : �ش� ISBN�� ������ ����ִ� ������ �����͸� ��ȯ
	��ȯ   : ��ϵ��� ���� ISBN�� ��� NULL�����͸� ��ȯ
*/
dvdInfo *GetDVDPtrByISBN(char *ISBN);

/*
	���   : �Ⱓ ����  dvd�� �뿩�� ���� ���� �˻�
	��ȯ   : cusInfo **
*/

cusInfo ** SearchCusInfoBTWperiod(int *periodF, int *periodT, char * SearchID);

/*
	���   : ��ϵ� ISBN���� üũ
	��ȯ   : ��ϵǾ����� 1, �ƴϸ� 0�� ��ȯ
*/
int IsRegistISBN(char *ISBN);

/*
	���   : �뿩�� ISBN���� üũ
	��ȯ   : �뿩�Ǿ����� 1, �ƴϸ� 0�� ��ȯ
*/
int IsrentedDVD(char *ISBN);


/*
	���   : �Է°��� ����  DVD�� �뿩
	��ȯ   : �뿩�Ǿ����� 1�� ��ȯ
*/
int RentDVD(char *inp_ID, char *inp_ISBN, int *Today);

/*
	���   : �뿩�� DVD�� �ݳ���
	��ȯ   : �ݳ��Ϸ�Ǹ� 1�� ��ȯ
*/
int returnDVD(char *ISBN);

#endif // !__DVDINFOACCESS_H__
