
#ifndef __MANAGER_H__
#define __MANAGER_H__


//*********************** �� �� �� ��****************************************

/*
	���    :  ȸ������ ���
	��ȯ    :  void
*/
void RegisterCustomer(void);


/*
	���    :  �� ���� �˻�
	��ȯ    :  void
*/

void SearchCusInfo(void);





//*********************** D V D  �� �� **************************************


/*
	 ���   : DVD ���
	 ��ȯ   : void
*/
void RegistDVD();


/*
	���    : DVD ���� �˻�
	��ȯ    : void
*/
void SearchDVDInfo();


/*
	���    : DVD �뿩
	��ȯ    : void
*/
void RentDVDbyID();


/*
	���    : �Ⱓ �� �뿩 �� �˻�
	��ȯ    : void
*/
void SearchCusBTWPeriod(void);


/*
	���    : �뿩��� ���� ���
	��ȯ    : void
*/
void CheckRentHistoryByISBN();


/*
	���    : �뿩�� DVD ��ȯ
	��ȯ    : void
*/
void returnDVDByISBN();





//**************************** �� ��   �� �� ȭ*******************************

/*
	���    : ��,DVD. �뿩 ���� ���Ͽ��� ���� �ҷ�����
	��ȯ    : void
*/
void init();
#endif // !__MANAGER_H__
