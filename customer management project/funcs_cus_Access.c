#include "common.h"
#include "cusInfoAccess.h"


//���� �����Ͽ��� ���δٸ� c ���Ͽ��� ���뺯���� ���� �� ��
//extern �� ����Ѵ�.

//�������� �ʰ� �ش� c ���� �������� ����Ϸ���
//static �� ����Ѵ�.


static cusInfo *customers = NULL;						//�� ���� ����(�׻� ���������� ��ϵ� ���� ����Ŵ)
static cusInfo *prevCusNode = NULL;						//���� ������ �����Ű�� ���� ���������� �ѹ� ���� ���� ����Ŵ
static cusInfo *CusNodeForSearch = NULL;				//�˻��� ���� ���Ǵ� ������

FILE * cusInfo_file;



void initialize_cusInfo() {
	cusInfo_file = fopen("customer_Info.txt", "rt");

	char *temp[ID_LEN];

	if (NULL != cusInfo_file) {
		while (fscanf(cusInfo_file, "%s", temp) != EOF) {
			prevCusNode = customers;											//���� ����� �۾��� ���� ��������� ������ ���� ��带 ����

			customers = (cusInfo *)malloc(sizeof(cusInfo));

			strcpy(customers->ID, temp);
			fscanf(cusInfo_file, "%s", customers->name);
			fscanf(cusInfo_file, "%s", customers->phoneNum);

			//���� �ҷ��� ���� Linked List ���� �κ�
			customers->prevNode = NULL;
			customers->nextNode = NULL;

			if (prevCusNode != NULL) {
				customers->prevNode = prevCusNode;								//���� ����� ���� ��� = ���� ���
				prevCusNode->nextNode = customers;								//���� ����� ���� ��� = ���� ���
			}
			customers->nextNode = NULL;											//���� ����� ���� ���� NULL

			CusNodeForSearch = customers;
		}
		fclose(cusInfo_file);
	}
}



int AddCusInfo(char *ID, char *name, char * phoneNum) {


	prevCusNode = customers;													//���� ����� �۾��� ���� ��������� ������ ���� ��带 ����

	//�� ���� ���� ���� �޸� �Ҵ� �κ�
	//
	//1�� �Է��� �� ���� ���� 1���� �����ؼ� �Ҵ����
	customers = (cusInfo *)malloc(sizeof(cusInfo));

	//�� ���� ����
	strcpy(customers->ID, ID);
	strcpy(customers->name, name);
	strcpy(customers->phoneNum, phoneNum);

	//���� �ҷ��� ���� Linked List ���� �κ�

	customers->nextNode = NULL;										//�� �� ��� �ʱ�ȭ
	customers->prevNode = NULL;

	if (prevCusNode != NULL) {
		customers->prevNode = prevCusNode;								//���� ����� ���� ��� = ���� ���
		prevCusNode->nextNode = customers;								//���� ����� ���� ��� = ���� ���
	}

	CusNodeForSearch = customers;

	//���Ϸ� ����

	cusInfo_file = fopen("customer_Info.txt", "rt");

	if (NULL != cusInfo_file) {
		printf("�� ���� ����\n");							
		cusInfo_file = fopen("customer_Info.txt", "a");		//������ ��� ����� ����
	}
	else
	{
		printf("�� ���� ���� ����\n");
		cusInfo_file = fopen("customer_Info.txt", "wt");	//������ ���� ����
	}


	//�� ���� ���Ͽ� ����
	fprintf(cusInfo_file, "%s\t", customers->ID);
	fprintf(cusInfo_file, "%s\t", customers->name);
	fprintf(cusInfo_file, "%s\n", customers->phoneNum);

	fclose(cusInfo_file);

	return 1;
}


//�� ������ ���� �޸� �Ҵ� ����
void free_cus() {
	if (customers != NULL) {
		while (customers->prevNode != NULL) {
			cusInfo *temp = customers->prevNode;
			free(customers);
			customers = temp;
		}

		free(customers);
	}
}


//��ġ�ϴ� ID�� �ִٸ� �ش� ����ü �����͸� ��ȯ
cusInfo * GetCusPtrByID(char * ID) {
	if (CusNodeForSearch != NULL) {
		//���� ����� ID�� ��ġ�ϸ� ��ȯ
		if (!strcmp(CusNodeForSearch->ID, ID)) {
			cusInfo * return_ptr = CusNodeForSearch;
			CusNodeForSearch = customers;
			return return_ptr;
		}
		else
		{	//���� ��尡 ���� x -> �˻� ��
			if (CusNodeForSearch->prevNode == NULL) {
				CusNodeForSearch = customers;
				return NULL;
			}
			else {
				CusNodeForSearch = CusNodeForSearch->prevNode;
				return GetCusPtrByID(ID);	//���� ���� �˻� �̵�
			}
		}
	}
	else
		return NULL;
}


//�̹� �ִ� ID���� �˻��� �� ���ٸ� 0�� ��ȯ
int IsregistID(char *ID) {
	if (CusNodeForSearch != NULL) {
		//���� ����� ID�� ��ġ�ϸ� ��ȯ
		if (!strcmp(CusNodeForSearch->ID, ID)) {
			cusInfo * return_ptr = CusNodeForSearch;
			CusNodeForSearch = customers;
			return 1;
		}
		else
		{	//���� ��尡 ���� x -> �˻� ��
			if (CusNodeForSearch->prevNode == NULL) {
				CusNodeForSearch = customers;
				return 0;
			}
			else {
				CusNodeForSearch = CusNodeForSearch->prevNode;
				return IsregistID(ID);	//���� ���� �˻� �̵�
			}
		}
	}
	else
		return 0;
}