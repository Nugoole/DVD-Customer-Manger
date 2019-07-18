#include "common.h"
#include "cusInfoAccess.h"
#include "cusManager.h"
#include "screenOut.h"

void init_cus() {
	initialize_cusInfo();
}


void RegisterCustomer(void) {
	
	system("cls");


	//입력받을 값을 저장할 변수들
	char *cust_ID;
	char *cust_NAME;
	char *cust_PHONENUM;

	int end_flag = 0;
	//입력받을 공간 할당
	cust_ID = (char *)malloc(10);
	cust_NAME = (char *)malloc(30);
	cust_PHONENUM = (char *)malloc(30);


	//아이디 확인 -> 중복되면 반복
	while (1) {
		system("cls");
		puts("------회 원 가 입------");
		puts("ID를 입력해주세요.(취소 : -1)");
		printf("ID : ");
		gets(cust_ID);
		if (!IsregistID(cust_ID))break;
		else if (!strcmp(cust_ID,"-1"))break;
		puts("이미 있는 아이디 입니다!");
		_sleep(700);
	}
	if (strcmp(cust_ID, "-1")) {
		puts("이름을 입력해주세요.");
		printf("Name : ");
		gets(cust_NAME);

		puts("전화번호를 입력해주세요.");
		printf("PhoneNum : ");
		gets(cust_PHONENUM);

		//제대로 할당이 되었다면 -> 포인터 호출해서 입력값 불러옴
		if (AddCusInfo(cust_ID, cust_NAME, cust_PHONENUM)) {
			system("cls");
			printf("<--------회 원 가 입   성 공 ---------->\n\n");
			printf("%s 님의 회원가입을 축하드립니다.\n\n", GetCusPtrByID(cust_ID)->ID);
		}
		else
			printf("Error : Memory Allocation Failed\n");
	}
	puts("계속하려면 엔터 키를 누르십시오");
	getchar();
	
	//할당 해제
	free(cust_ID);
	free(cust_NAME);
	free(cust_PHONENUM);


}




void SearchCusInfo(void) {

	system("cls");

	char *find_id;

	find_id = (char *)malloc(30);

	puts("<------ 회 원 정 보   검 색 ------->\n");
	puts("검색하실 회원의 ID를 입력해주세요.");
	gets(find_id);


	//ID에 대한 포인터 가져옴
	//
	//해당 포인터를 SHOW함수에 입력
	//
	//SHOW함수가 해당 고객에 대한 정보 출력
	ShowCustomerInfo(GetCusPtrByID(find_id));

	puts("계속하려면 엔터 키를 누르십시오");
	free(find_id);
	getchar();

}
