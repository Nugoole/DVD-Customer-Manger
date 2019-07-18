#include "common.h"
#include "cusInfoAccess.h"
#include "cusManager.h"
#include "screenOut.h"

void init_cus() {
	initialize_cusInfo();
}


void RegisterCustomer(void) {
	
	system("cls");


	//�Է¹��� ���� ������ ������
	char *cust_ID;
	char *cust_NAME;
	char *cust_PHONENUM;

	int end_flag = 0;
	//�Է¹��� ���� �Ҵ�
	cust_ID = (char *)malloc(10);
	cust_NAME = (char *)malloc(30);
	cust_PHONENUM = (char *)malloc(30);


	//���̵� Ȯ�� -> �ߺ��Ǹ� �ݺ�
	while (1) {
		system("cls");
		puts("------ȸ �� �� ��------");
		puts("ID�� �Է����ּ���.(��� : -1)");
		printf("ID : ");
		gets(cust_ID);
		if (!IsregistID(cust_ID))break;
		else if (!strcmp(cust_ID,"-1"))break;
		puts("�̹� �ִ� ���̵� �Դϴ�!");
		_sleep(700);
	}
	if (strcmp(cust_ID, "-1")) {
		puts("�̸��� �Է����ּ���.");
		printf("Name : ");
		gets(cust_NAME);

		puts("��ȭ��ȣ�� �Է����ּ���.");
		printf("PhoneNum : ");
		gets(cust_PHONENUM);

		//����� �Ҵ��� �Ǿ��ٸ� -> ������ ȣ���ؼ� �Է°� �ҷ���
		if (AddCusInfo(cust_ID, cust_NAME, cust_PHONENUM)) {
			system("cls");
			printf("<--------ȸ �� �� ��   �� �� ---------->\n\n");
			printf("%s ���� ȸ�������� ���ϵ帳�ϴ�.\n\n", GetCusPtrByID(cust_ID)->ID);
		}
		else
			printf("Error : Memory Allocation Failed\n");
	}
	puts("����Ϸ��� ���� Ű�� �����ʽÿ�");
	getchar();
	
	//�Ҵ� ����
	free(cust_ID);
	free(cust_NAME);
	free(cust_PHONENUM);


}




void SearchCusInfo(void) {

	system("cls");

	char *find_id;

	find_id = (char *)malloc(30);

	puts("<------ ȸ �� �� ��   �� �� ------->\n");
	puts("�˻��Ͻ� ȸ���� ID�� �Է����ּ���.");
	gets(find_id);


	//ID�� ���� ������ ������
	//
	//�ش� �����͸� SHOW�Լ��� �Է�
	//
	//SHOW�Լ��� �ش� ���� ���� ���� ���
	ShowCustomerInfo(GetCusPtrByID(find_id));

	puts("����Ϸ��� ���� Ű�� �����ʽÿ�");
	free(find_id);
	getchar();

}
