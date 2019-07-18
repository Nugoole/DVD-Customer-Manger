#include "common.h"
#include "screenOut.h"

extern int searched_cust_cnt;

void ShowRent(void) {
	system("cls");

	puts("<--------------�� �� �� ��--------------->");
	puts("");
	puts("�뿩�ϰ� ���� DVD�� ISBN�� �Է����ּ���");
}



void ShowTitle(void) {
	system("cls");

	puts("=================================================");
	puts("|    ����ʽÿ�~  � ���񽺸� ���Ͻó���?    |");
	puts("|                                                |");
	puts("|   1. �뿩   2.�ݳ�   3. ȸ������ ��   4. ����  |");
	puts("|                          DVD ���              |");
	puts("=================================================");

}

void ShowRegister() {

	system("cls");   //stdlib�� ����

	puts("------ �� �� -----");
	puts(" 1. �ű԰��� ");	
	puts(" 2. ȸ����ȸ");
	puts(" 3. DVD ���");
	puts(" 4. DVD ��ȸ");
	puts(" 5. DVD �뿩���� ��ȸ");
	puts(" 6. �Ⱓ �� �뿩 �� ��ȸ");
	puts(" 7. ���");
	puts("--------------------");

}




void ShowCustomerInfo(cusInfo *pCus) {

	system("cls");
	printf("<------ �� �� �� �� ------->\n\n");

	if (pCus == NULL) {
		puts("�ش� ID�� ���� ȸ���� �����ϴ�.");
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
	printf("<------ �� �� �� �� ------->\n\n");

	if (pDVD == NULL) {
		puts("�ش� ISBN�� ���� DVD�� �����ϴ�.");
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
	puts("<------------------�� �� �� ��-------------------->");
	puts("ISBN\t\tŸ��Ʋ            �뿩����");
	for(int i=0;i< searched_cust_cnt;i++){
		printf("%s\t\t%s            %d-%d-%d\n", cusInfoBTWperiod[i]->ID, cusInfoBTWperiod[i]->name, cusInfoBTWperiod[i]->rentYear, cusInfoBTWperiod[i]->rentMonth, cusInfoBTWperiod[i]->rentDate);
		free(*(cusInfoBTWperiod + i));				//ã�� ����� ��� �� �޸� �Ҵ� ����
	}

	free(cusInfoBTWperiod);								//ã�� ��� ��ü �޸� �Ҵ� ����

	getchar();
}