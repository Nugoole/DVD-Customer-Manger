#include "common.h"
#include "dvdInfoAccess.h"
#include "cusInfoAccess.h"
#include "dvdManager.h"
#include "screenOut.h"

void init_dvdInfo() {
	initialize_dvdInfo();
}

void RegistDVD() {
	system("cls");


	//입력받을 값을 저장할 변수들
	char *dvd_ISBN;
	char *dvd_Title;
	int *dvd_Genre;

	int end_flag = 0;
	//입력받을 공간 할당
	dvd_ISBN = (char *)malloc(10);
	dvd_Title = (char *)malloc(30);
	dvd_Genre = (int *)malloc(sizeof(int));


	//아이디 확인 -> 중복되면 반복
	while (1) {
		system("cls");
		puts("<------D V D   등 록------>");
		puts("ISBN를 입력해주세요.(종료 : -1)");
		printf("ISBN : ");
		gets(dvd_ISBN);
		if (!IsRegistISBN(dvd_ISBN))break;
		if (!strcmp(dvd_ISBN, "-1"))break;
		puts("이미 있는 ISBN 입니다!");
		_sleep(700);
	}
	if (strcmp(dvd_ISBN, "-1")) {
		system("cls");
		puts("<------D V D   등 록------>");
		puts("타이틀을 입력해주세요.");
		printf("Title : ");
		gets(dvd_Title);

		system("cls");
		puts("<------D V D   등 록------>");
		puts("장르 번호를 골라주세요.");
		puts(" 1. 액션");
		puts(" 2. 코믹");
		puts(" 3. SF");
		puts(" 4. 로맨스");
		printf("Genre : ");
		while (1) {
			scanf("%d", dvd_Genre);
			rewind(stdin);
			if (*dvd_Genre < 5 && *dvd_Genre > 0)break;
			else
				printf("1~4를 골라주십시오.\n");
		}

		//제대로 할당이 되었다면 -> 포인터 호출해서 입력값 불러옴
		if (AddDVD_Info(dvd_ISBN, dvd_Title, dvd_Genre)) {
			system("cls");
			printf("<-------- D V D  등 록  성 공 ---------->\n\n");
			printf(" DVD가 등록되었습니다.\n\n\n");
		}
	}
	puts("계속하려면 엔터 키를 누르십시오");
	gets(dvd_Title);
	//할당 해제
	free(dvd_ISBN);
	free(dvd_Title);
	free(dvd_Genre);
}



void SearchDVDInfo() {

	system("cls");

	char *find_ISBN;

	find_ISBN = (char *)malloc(30);

	puts("<------ D V D   검 색 ------->");
	puts("검색하실 DVD의 ISBN를 입력해주세요.");
	gets(find_ISBN);

	ShowDVDInfo(GetDVDPtrByISBN(find_ISBN));

	puts("계속하려면 엔터 키를 누르십시오");
	gets(find_ISBN);


	free(find_ISBN);


}


void SearchCusBTWPeriod() {


	// 0번 배열 -Year , 1번 배열 - Month,  2번 배열- Date
	int periodFrom[3], periodTo[3];

	char search_Cus_ID[ID_LEN];


	system("cls");
	puts("<-----------대 여  고 객  검 색------------->");
	puts("");
	puts("검색 하실 기간을 입력해주세요.");

	//검색할 기간 입력 - From
	printf("<<언제 부터 >>\n");
	printf("Year  :  ");
	scanf("%d", &periodFrom[0]);
	rewind(stdin);
	printf("Month  :  ");
	scanf("%d", &periodFrom[1]);
	rewind(stdin);
	printf("Date  :  ");
	scanf("%d", &periodFrom[2]);
	rewind(stdin);


	//검색할 기간 입력 - To
	printf("<<언제 까지 >>\n");
	printf("Year  :  ");
	scanf("%d", &periodTo[0]);
	rewind(stdin);
	printf("Month  :  ");
	scanf("%d", &periodTo[1]);
	rewind(stdin);
	printf("Date  :  ");
	scanf("%d", &periodTo[2]);
	rewind(stdin);

	//검색할 아이디 입력
	printf("검색하시고 싶은 ID를 입력해주세요 : ");
	gets(search_Cus_ID);

	if (IsregistID(search_Cus_ID)) {
		ShowCusBTWPeriod(SearchCusInfoBTWperiod(periodFrom, periodTo, search_Cus_ID));
	}
	else {
		printf("등록되지 않은 ID입니다.\n");
		getchar();
		return;
	}
}


void RentDVDbyID() {

	//확인할 DVD의 ISBN을 입력받음
	char * temp_ISBN = (char *)malloc(ISBN_LEN);
	gets(temp_ISBN);

	if (IsRegistISBN(temp_ISBN)) {							//1차적으로 등록되어있는 DVD인지 확인
		if (!IsrentedDVD(temp_ISBN)) {						//등록이 되어있다면, 대여가능한지 확인
			printf("현재 대여가 가능합니다.\n\n");
			_sleep(1000);
		}
												
		else {
			printf("현재 대여중인 DVD입니다.\n\n");
			_sleep(1000);
			free(temp_ISBN);								//다른 함수로 넘어 갈 필요가 없으므로 할당 해제
			return;										
		}
	}
	else {
		printf("등록되어 있지 않은 DVD의 ISBN입니다.\n\n");		//등록되어 있지 않았던 경우
		getchar();
		free(temp_ISBN);
		return;
	}

	system("cls");

	puts("<--------------대 여 하 기--------------->");

	printf("아이디를 입력해주세요.\n\n");
	char *temp_ID = (char *)malloc(ID_LEN);
	int rentToday[3];

	gets(temp_ID);
	rewind(stdin);


	if (IsregistID(temp_ID)) {
		printf("오늘 날짜를 입력하여 주세요.\n\n");
		printf("Year  : ");
		scanf("%d", &rentToday[Year]);
		rewind(stdin);
		printf("Month : ");
		scanf("%d", &rentToday[Month]);
		rewind(stdin);
		printf("Date  : ");
		scanf("%d", &rentToday[Date]);
		rewind(stdin);
	}
	else
	{
		printf("등록되지 않은 ID입니다.\n");
		getchar();
		return;
	}

	if (RentDVD(temp_ID, temp_ISBN, rentToday)) {
		system("cls");

		printf("대여가 완료되었습니다.\n");

		free(temp_ISBN);
		free(temp_ID);
		printf("계속하려면 엔터키를 입력하세요");
		getchar();
	}
}


void returnDVDByISBN() {
	system("cls");
	puts("<-----------반 납-------------->");
	char * temp2_ISBN = (char *)malloc(ISBN_LEN);
	puts("\n반납하실 DVD의 ISBN을 입력하세요.");
	gets(temp2_ISBN);
	rewind(stdin);
	if (IsRegistISBN(temp2_ISBN)) {
		if (IsrentedDVD(temp2_ISBN)) {
			if (returnDVD(temp2_ISBN)) {
				printf("반납이 완료되었습니다.\n");
				free(temp2_ISBN);
				getchar();
			}
		}
		else
		{
			printf("대여한 DVD가 아닙니다.\n");
			free(temp2_ISBN);
			getchar();
		}

	}
	else
	{
		printf("존재하지 않는 ISBN입니다.\n");
		free(temp2_ISBN);
		getchar();
	}
}


void CheckRentHistoryByISBN() {
	system("cls");
	puts("<----------------대 여  내 역  확 인---------------->");
	puts("");
	puts("대여 내역을 확인 할 DVD의 ISBN을 입력하세요");
	char *temp3_ISBN = (char *)malloc(ISBN_LEN);
	gets(temp3_ISBN);
	if (IsRegistISBN(temp3_ISBN)) {
		dvdInfo *nowDvd = GetDVDPtrByISBN(temp3_ISBN);
		system("cls");
		puts("<----------------대 여  내 역  확 인---------------->");
		puts("");
		printf("  ID      이름      전화번호              대여날짜\n");
		while (nowDvd->rentedCus->prevNode !=NULL)
		{
			printf("%s     %s       %s           %d-%d-%d\n", nowDvd->rentedCus->ID, nowDvd->rentedCus->name, nowDvd->rentedCus->phoneNum, nowDvd->rentedCus->rentYear, nowDvd->rentedCus->rentMonth, nowDvd->rentedCus->rentDate);
			nowDvd->rentedCus = nowDvd->rentedCus->prevNode;
		}
		printf("%s     %s       %s           %d-%d-%d\n", nowDvd->rentedCus->ID, nowDvd->rentedCus->name, nowDvd->rentedCus->phoneNum, nowDvd->rentedCus->rentYear, nowDvd->rentedCus->rentMonth, nowDvd->rentedCus->rentDate);
		puts("");
		puts("");
	}
	else
		printf("등록 된 ISBN이 아닙니다.\n\n\n");

	free(temp3_ISBN);
	puts("계속하시려면 엔터 키를 눌러주세요");
	getchar();

}