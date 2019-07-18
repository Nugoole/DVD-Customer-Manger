

#ifndef __DVDMANAGER_H__
#define __DVDMANAGER_H__
/*
	기능 : 해당 DVD가 현재 대여중인지 체크
	반환 : 대여가능이면 1, 아니면 0을 반환
*/


void init_dvdInfo();

void RegistDVD();

void SearchDVDInfo();

void RentDVDbyID();
/*
	기능    : 기간 내 대여 고객 검색
	반환    : void
*/
void SearchCusBTWPeriod(void);


/*
	기능    : 대여기록 정보 출력
	반환    : void
*/
void CheckRentHistoryByISBN();


void returnDVDByISBN();
#endif // !__DVDMANAGER_H__