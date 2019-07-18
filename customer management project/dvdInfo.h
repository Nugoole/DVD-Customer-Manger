

#ifndef __DVDINFO_H__
#define __DVDINFO_H__

#include "cusInfo.h"

#define ISBN_LEN 30
#define TITLE_LEN 30


enum {ACTION = 1, COMIC, SF, ROMANTIC};


typedef struct __dvdInfo {
	struct __dvdInfo *nextNode;
	struct __dvdInfo *prevNode;

	char ISBN[ISBN_LEN];
	char title[TITLE_LEN];
	int genre;
	int rentFlag;
	int rentCnt;
	cusInfo *rentedCus;
}dvdInfo;

#endif // !__DVDINFO_H__

