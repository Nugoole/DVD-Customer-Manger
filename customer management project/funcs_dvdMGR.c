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


	//�Է¹��� ���� ������ ������
	char *dvd_ISBN;
	char *dvd_Title;
	int *dvd_Genre;

	int end_flag = 0;
	//�Է¹��� ���� �Ҵ�
	dvd_ISBN = (char *)malloc(10);
	dvd_Title = (char *)malloc(30);
	dvd_Genre = (int *)malloc(sizeof(int));


	//���̵� Ȯ�� -> �ߺ��Ǹ� �ݺ�
	while (1) {
		system("cls");
		puts("<------D V D   �� ��------>");
		puts("ISBN�� �Է����ּ���.(���� : -1)");
		printf("ISBN : ");
		gets(dvd_ISBN);
		if (!IsRegistISBN(dvd_ISBN))break;
		if (!strcmp(dvd_ISBN, "-1"))break;
		puts("�̹� �ִ� ISBN �Դϴ�!");
		_sleep(700);
	}
	if (strcmp(dvd_ISBN, "-1")) {
		system("cls");
		puts("<------D V D   �� ��------>");
		puts("Ÿ��Ʋ�� �Է����ּ���.");
		printf("Title : ");
		gets(dvd_Title);

		system("cls");
		puts("<------D V D   �� ��------>");
		puts("�帣 ��ȣ�� ����ּ���.");
		puts(" 1. �׼�");
		puts(" 2. �ڹ�");
		puts(" 3. SF");
		puts(" 4. �θǽ�");
		printf("Genre : ");
		while (1) {
			scanf("%d", dvd_Genre);
			rewind(stdin);
			if (*dvd_Genre < 5 && *dvd_Genre > 0)break;
			else
				printf("1~4�� ����ֽʽÿ�.\n");
		}

		//����� �Ҵ��� �Ǿ��ٸ� -> ������ ȣ���ؼ� �Է°� �ҷ���
		if (AddDVD_Info(dvd_ISBN, dvd_Title, dvd_Genre)) {
			system("cls");
			printf("<-------- D V D  �� ��  �� �� ---------->\n\n");
			printf(" DVD�� ��ϵǾ����ϴ�.\n\n\n");
		}
	}
	puts("����Ϸ��� ���� Ű�� �����ʽÿ�");
	gets(dvd_Title);
	//�Ҵ� ����
	free(dvd_ISBN);
	free(dvd_Title);
	free(dvd_Genre);
}



void SearchDVDInfo() {

	system("cls");

	char *find_ISBN;

	find_ISBN = (char *)malloc(30);

	puts("<------ D V D   �� �� ------->");
	puts("�˻��Ͻ� DVD�� ISBN�� �Է����ּ���.");
	gets(find_ISBN);

	ShowDVDInfo(GetDVDPtrByISBN(find_ISBN));

	puts("����Ϸ��� ���� Ű�� �����ʽÿ�");
	gets(find_ISBN);


	free(find_ISBN);


}


void SearchCusBTWPeriod() {


	// 0�� �迭 -Year , 1�� �迭 - Month,  2�� �迭- Date
	int periodFrom[3], periodTo[3];

	char search_Cus_ID[ID_LEN];


	system("cls");
	puts("<-----------�� ��  �� ��  �� ��------------->");
	puts("");
	puts("�˻� �Ͻ� �Ⱓ�� �Է����ּ���.");

	//�˻��� �Ⱓ �Է� - From
	printf("<<���� ���� >>\n");
	printf("Year  :  ");
	scanf("%d", &periodFrom[0]);
	rewind(stdin);
	printf("Month  :  ");
	scanf("%d", &periodFrom[1]);
	rewind(stdin);
	printf("Date  :  ");
	scanf("%d", &periodFrom[2]);
	rewind(stdin);


	//�˻��� �Ⱓ �Է� - To
	printf("<<���� ���� >>\n");
	printf("Year  :  ");
	scanf("%d", &periodTo[0]);
	rewind(stdin);
	printf("Month  :  ");
	scanf("%d", &periodTo[1]);
	rewind(stdin);
	printf("Date  :  ");
	scanf("%d", &periodTo[2]);
	rewind(stdin);

	//�˻��� ���̵� �Է�
	printf("�˻��Ͻð� ���� ID�� �Է����ּ��� : ");
	gets(search_Cus_ID);

	if (IsregistID(search_Cus_ID)) {
		ShowCusBTWPeriod(SearchCusInfoBTWperiod(periodFrom, periodTo, search_Cus_ID));
	}
	else {
		printf("��ϵ��� ���� ID�Դϴ�.\n");
		getchar();
		return;
	}
}


void RentDVDbyID() {

	//Ȯ���� DVD�� ISBN�� �Է¹���
	char * temp_ISBN = (char *)malloc(ISBN_LEN);
	gets(temp_ISBN);

	if (IsRegistISBN(temp_ISBN)) {							//1�������� ��ϵǾ��ִ� DVD���� Ȯ��
		if (!IsrentedDVD(temp_ISBN)) {						//����� �Ǿ��ִٸ�, �뿩�������� Ȯ��
			printf("���� �뿩�� �����մϴ�.\n\n");
			_sleep(1000);
		}
												
		else {
			printf("���� �뿩���� DVD�Դϴ�.\n\n");
			_sleep(1000);
			free(temp_ISBN);								//�ٸ� �Լ��� �Ѿ� �� �ʿ䰡 �����Ƿ� �Ҵ� ����
			return;										
		}
	}
	else {
		printf("��ϵǾ� ���� ���� DVD�� ISBN�Դϴ�.\n\n");		//��ϵǾ� ���� �ʾҴ� ���
		getchar();
		free(temp_ISBN);
		return;
	}

	system("cls");

	puts("<--------------�� �� �� ��--------------->");

	printf("���̵� �Է����ּ���.\n\n");
	char *temp_ID = (char *)malloc(ID_LEN);
	int rentToday[3];

	gets(temp_ID);
	rewind(stdin);


	if (IsregistID(temp_ID)) {
		printf("���� ��¥�� �Է��Ͽ� �ּ���.\n\n");
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
		printf("��ϵ��� ���� ID�Դϴ�.\n");
		getchar();
		return;
	}

	if (RentDVD(temp_ID, temp_ISBN, rentToday)) {
		system("cls");

		printf("�뿩�� �Ϸ�Ǿ����ϴ�.\n");

		free(temp_ISBN);
		free(temp_ID);
		printf("����Ϸ��� ����Ű�� �Է��ϼ���");
		getchar();
	}
}


void returnDVDByISBN() {
	system("cls");
	puts("<-----------�� ��-------------->");
	char * temp2_ISBN = (char *)malloc(ISBN_LEN);
	puts("\n�ݳ��Ͻ� DVD�� ISBN�� �Է��ϼ���.");
	gets(temp2_ISBN);
	rewind(stdin);
	if (IsRegistISBN(temp2_ISBN)) {
		if (IsrentedDVD(temp2_ISBN)) {
			if (returnDVD(temp2_ISBN)) {
				printf("�ݳ��� �Ϸ�Ǿ����ϴ�.\n");
				free(temp2_ISBN);
				getchar();
			}
		}
		else
		{
			printf("�뿩�� DVD�� �ƴմϴ�.\n");
			free(temp2_ISBN);
			getchar();
		}

	}
	else
	{
		printf("�������� �ʴ� ISBN�Դϴ�.\n");
		free(temp2_ISBN);
		getchar();
	}
}


void CheckRentHistoryByISBN() {
	system("cls");
	puts("<----------------�� ��  �� ��  Ȯ ��---------------->");
	puts("");
	puts("�뿩 ������ Ȯ�� �� DVD�� ISBN�� �Է��ϼ���");
	char *temp3_ISBN = (char *)malloc(ISBN_LEN);
	gets(temp3_ISBN);
	if (IsRegistISBN(temp3_ISBN)) {
		dvdInfo *nowDvd = GetDVDPtrByISBN(temp3_ISBN);
		system("cls");
		puts("<----------------�� ��  �� ��  Ȯ ��---------------->");
		puts("");
		printf("  ID      �̸�      ��ȭ��ȣ              �뿩��¥\n");
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
		printf("��� �� ISBN�� �ƴմϴ�.\n\n\n");

	free(temp3_ISBN);
	puts("����Ͻ÷��� ���� Ű�� �����ּ���");
	getchar();

}