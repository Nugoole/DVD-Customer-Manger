

#ifndef __DVDMANAGER_H__
#define __DVDMANAGER_H__
/*
	��� : �ش� DVD�� ���� �뿩������ üũ
	��ȯ : �뿩�����̸� 1, �ƴϸ� 0�� ��ȯ
*/


void init_dvdInfo();

void RegistDVD();

void SearchDVDInfo();

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


void returnDVDByISBN();
#endif // !__DVDMANAGER_H__