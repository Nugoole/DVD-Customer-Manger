

/*
	기능    : 콘솔출력을 위한 함수들의 선언.
	작성자  : 허준도
	작성일  : 2019-03-11
	Ver     : 1.0
*/


#include "cusInfo.h"
#include "dvdInfo.h"

#ifndef __SCROUT_H__
#define __SCROUT_H__

/*
	기능    : 타이틀 창을 출력
	반환    : void
*/
void ShowTitle(void);

/*
	기능    : 대여 창을 출력
	반환    : void
*/
void ShowRent(void);


/*
	기능    : 회원가입을 할 수 있는 창 출력
	반환    : void
*/
void ShowRegister(void);

/*
	기능    : 고객 정보를 출력
	반환    : void
*/
void ShowCustomerInfo(cusInfo * pCus);

/*
	기능    : DVD 정보를 출력
	반환    : void
*/
void ShowDVDInfo(dvdInfo *pDVD);

/*
	기능    : 장르 정보를 출력
	반환    : void
*/
void ShowGenre(int gen);

/*
	기능    : 기간 내에 대여고객 출력
	반환    : void
*/
void ShowCusBTWPeriod(cusInfo ** cusInfoBTWperiod);

#endif