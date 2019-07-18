/*
	기능 : 고객 관리 구조체
	작성자 : 허준도
	작성일 : 2019-03-11
	버전 : 1.0
*/

#ifndef __cusInfo_H__

#define __cusInfo_H__

#define ID_LEN 10
#define NAME_LEN 30
#define PHONENUM_LEN 30

typedef struct __custInfo {
	struct __cusInfo *nextNode;
	struct __cusInfo *prevNode;

	char ID[ID_LEN];
	char name[NAME_LEN];
	char phoneNum[PHONENUM_LEN];
	int rentYear, rentMonth, rentDate;
} cusInfo;

#endif // !__cusInfo__


