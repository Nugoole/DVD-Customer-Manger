
#ifndef __MANAGER_H__
#define __MANAGER_H__


//*********************** 고 객 정 보****************************************

/*
	기능    :  회원가입 기능
	반환    :  void
*/
void RegisterCustomer(void);


/*
	기능    :  고객 정보 검색
	반환    :  void
*/

void SearchCusInfo(void);





//*********************** D V D  정 보 **************************************


/*
	 기능   : DVD 등록
	 반환   : void
*/
void RegistDVD();


/*
	기능    : DVD 정보 검색
	반환    : void
*/
void SearchDVDInfo();


/*
	기능    : DVD 대여
	반환    : void
*/
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


/*
	기능    : 대여한 DVD 반환
	반환    : void
*/
void returnDVDByISBN();





//**************************** 정 보   초 기 화*******************************

/*
	기능    : 고객,DVD. 대여 정보 파일에서 내용 불러오기
	반환    : void
*/
void init();
#endif // !__MANAGER_H__
