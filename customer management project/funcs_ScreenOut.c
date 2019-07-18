#include "common.h"
#include "screenOut.h"

extern int searched_cust_cnt;

void ShowRent(void) {
	system("cls");

	puts("<--------------대 여 하 기--------------->");
	puts("");
	puts("대여하고 싶은 DVD의 ISBN을 입력해주세요");
}



void ShowTitle(void) {
	system("cls");

	puts("=================================================");
	puts("|    어서오십시오~  어떤 서비스를 원하시나요?    |");
	puts("|                                                |");
	puts("|   1. 대여   2.반납   3. 회원가입 및   4. 종료  |");
	puts("|                          DVD 등록              |");
	puts("=================================================");

}

void ShowRegister() {

	system("cls");   //stdlib에 존재

	puts("------ 메 뉴 -----");
	puts(" 1. 신규가입 ");	
	puts(" 2. 회원조회");
	puts(" 3. DVD 등록");
	puts(" 4. DVD 조회");
	puts(" 5. DVD 대여내역 조회");
	puts(" 6. 기간 내 대여 고객 조회");
	puts(" 7. 취소");
	puts("--------------------");

}




void ShowCustomerInfo(cusInfo *pCus) {

	system("cls");
	printf("<------ 검 색 결 과 ------->\n\n");

	if (pCus == NULL) {
		puts("해당 ID를 가진 회원이 없습니다.");
	}
	else {
		puts("-------------------");
		printf(" ID : %s \n", pCus->ID);
		printf(" Name : %s\n", pCus->name);
		printf(" PhoneNum : %s\n", pCus->phoneNum);
		puts("-------------------");
	}
}



void ShowGenre(int gen) {
	if (gen == ACTION)printf(" Genre : ACTION\n");
	else if (gen == COMIC)printf(" Genre : COMIC\n");
	else if (gen == SF)printf(" Genre : SF\n");
	else if (gen == ROMANTIC)printf(" Genre : ROMANTIC\n");
	else printf(" Genre : Unknown\n");
}



void ShowDVDInfo(dvdInfo *pDVD) {
	system("cls");
	printf("<------ 검 색 결 과 ------->\n\n");

	if (pDVD == NULL) {
		puts("해당 ISBN을 가진 DVD가 없습니다.");
	}
	else {
		printf(" ISBN : %s \n", pDVD->ISBN);
		printf(" Title : %s\n", pDVD->title);
		ShowGenre(pDVD->genre);
		puts("-------------------");
	}
}


void ShowCusBTWPeriod(cusInfo ** cusInfoBTWperiod) {
	system("cls");
	puts("<------------------검 색 결 과-------------------->");
	puts("ISBN\t\t타이틀            대여일자");
	for(int i=0;i< searched_cust_cnt;i++){
		printf("%s\t\t%s            %d-%d-%d\n", cusInfoBTWperiod[i]->ID, cusInfoBTWperiod[i]->name, cusInfoBTWperiod[i]->rentYear, cusInfoBTWperiod[i]->rentMonth, cusInfoBTWperiod[i]->rentDate);
		free(*(cusInfoBTWperiod + i));				//찾은 목록은 출력 후 메모리 할당 해제
	}

	free(cusInfoBTWperiod);								//찾은 목록 전체 메모리 할당 해제

	getchar();
}