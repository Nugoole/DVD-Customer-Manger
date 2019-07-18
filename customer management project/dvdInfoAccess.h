
#ifndef __DVDINFOACCESS_H__
#define __DVDINFOACCESS_H__

#include "dvdInfo.h"

enum { Year, Month, Date };



/*
	기능   : DVD 정보 불러오기
	반환   : void
*/
void initialize_dvdInfo();


/*
	기능   : 해당 ISBN을 가진 DVD에 대해 대여정보를 불러옴
	반환   : void
*/
void initialize_rentedInfo(char * ISBN);



/*
	기능   : dvdInfo 저장공간 할당 및 구조체 배열에 저장
	반환   : 성공시 등록된 정보의 수,
			 실패시 0을 반환
*/
int AddDVD_Info(char *ISBN, char * title, int *genre);


/*
	기능   : dvd 관련 동적메모리 할당 한 내용을 해제
	반환   : void
*/
void free_dvds();


/*
	기능   : 해당 ISBN의 정보를 담고있는 변수의 포인터를 반환
	반환   : 등록되지 않은 ISBN인 경우 NULL포인터를 반환
*/
dvdInfo *GetDVDPtrByISBN(char *ISBN);

/*
	기능   : 기간 내에  dvd를 대여한 고객의 정보 검색
	반환   : cusInfo **
*/

cusInfo ** SearchCusInfoBTWperiod(int *periodF, int *periodT, char * SearchID);

/*
	기능   : 등록된 ISBN인지 체크
	반환   : 등록되었으면 1, 아니면 0을 반환
*/
int IsRegistISBN(char *ISBN);

/*
	기능   : 대여된 ISBN인지 체크
	반환   : 대여되었으면 1, 아니면 0을 반환
*/
int IsrentedDVD(char *ISBN);


/*
	기능   : 입력값에 대한  DVD를 대여
	반환   : 대여되었으면 1을 반환
*/
int RentDVD(char *inp_ID, char *inp_ISBN, int *Today);

/*
	기능   : 대여된 DVD를 반납함
	반환   : 반납완료되면 1을 반환
*/
int returnDVD(char *ISBN);

#endif // !__DVDINFOACCESS_H__
