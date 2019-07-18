#include "common.h"
#include "cusInfoAccess.h"


//분할 컴파일에서 서로다른 c 파일에서 공용변수를 선언 할 때
//extern 을 사용한다.

//공유하지 않고 해당 c 파일 내에서만 사용하려면
//static 을 사용한다.


static cusInfo *customers = NULL;						//고객 정보 노드들(항상 마지막으로 등록된 고객을 가리킴)
static cusInfo *prevCusNode = NULL;						//이전 정보와 연결시키기 위해 마지막에서 한번 전의 고객을 가리킴
static cusInfo *CusNodeForSearch = NULL;				//검색을 위해 사용되는 포인터

FILE * cusInfo_file;



void initialize_cusInfo() {
	cusInfo_file = fopen("customer_Info.txt", "rt");

	char *temp[ID_LEN];

	if (NULL != cusInfo_file) {
		while (fscanf(cusInfo_file, "%s", temp) != EOF) {
			prevCusNode = customers;											//다음 노드의 작업을 위해 이전노드의 공간에 현재 노드를 저장

			customers = (cusInfo *)malloc(sizeof(cusInfo));

			strcpy(customers->ID, temp);
			fscanf(cusInfo_file, "%s", customers->name);
			fscanf(cusInfo_file, "%s", customers->phoneNum);

			//파일 불러올 때의 Linked List 구현 부분
			customers->prevNode = NULL;
			customers->nextNode = NULL;

			if (prevCusNode != NULL) {
				customers->prevNode = prevCusNode;								//현재 노드의 이전 노드 = 이전 노드
				prevCusNode->nextNode = customers;								//이전 노드의 다음 노드 = 현재 노드
			}
			customers->nextNode = NULL;											//현재 노드의 다음 노드는 NULL

			CusNodeForSearch = customers;
		}
		fclose(cusInfo_file);
	}
}



int AddCusInfo(char *ID, char *name, char * phoneNum) {


	prevCusNode = customers;													//다음 노드의 작업을 위해 이전노드의 공간에 현재 노드를 저장

	//고객 수에 대한 동적 메모리 할당 부분
	//
	//1명씩 입력할 때 마다 새로 1개를 생성해서 할당받음
	customers = (cusInfo *)malloc(sizeof(cusInfo));

	//고객 정보 저장
	strcpy(customers->ID, ID);
	strcpy(customers->name, name);
	strcpy(customers->phoneNum, phoneNum);

	//파일 불러올 때의 Linked List 구현 부분

	customers->nextNode = NULL;										//앞 뒤 노드 초기화
	customers->prevNode = NULL;

	if (prevCusNode != NULL) {
		customers->prevNode = prevCusNode;								//현재 노드의 이전 노드 = 이전 노드
		prevCusNode->nextNode = customers;								//이전 노드의 다음 노드 = 현재 노드
	}

	CusNodeForSearch = customers;

	//파일로 저장

	cusInfo_file = fopen("customer_Info.txt", "rt");

	if (NULL != cusInfo_file) {
		printf("고객 정보 존재\n");							
		cusInfo_file = fopen("customer_Info.txt", "a");		//파일을 계속 쓰기로 선언
	}
	else
	{
		printf("고객 정보 새로 생성\n");
		cusInfo_file = fopen("customer_Info.txt", "wt");	//파일을 새로 생성
	}


	//고객 정보 파일에 저장
	fprintf(cusInfo_file, "%s\t", customers->ID);
	fprintf(cusInfo_file, "%s\t", customers->name);
	fprintf(cusInfo_file, "%s\n", customers->phoneNum);

	fclose(cusInfo_file);

	return 1;
}


//고객 정보에 대한 메모리 할당 해제
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


//일치하는 ID가 있다면 해당 구조체 포인터를 반환
cusInfo * GetCusPtrByID(char * ID) {
	if (CusNodeForSearch != NULL) {
		//현재 노드의 ID가 일치하면 반환
		if (!strcmp(CusNodeForSearch->ID, ID)) {
			cusInfo * return_ptr = CusNodeForSearch;
			CusNodeForSearch = customers;
			return return_ptr;
		}
		else
		{	//다음 노드가 존재 x -> 검색 끝
			if (CusNodeForSearch->prevNode == NULL) {
				CusNodeForSearch = customers;
				return NULL;
			}
			else {
				CusNodeForSearch = CusNodeForSearch->prevNode;
				return GetCusPtrByID(ID);	//다음 노드로 검색 이동
			}
		}
	}
	else
		return NULL;
}


//이미 있는 ID인지 검색한 후 없다면 0을 반환
int IsregistID(char *ID) {
	if (CusNodeForSearch != NULL) {
		//현재 노드의 ID가 일치하면 반환
		if (!strcmp(CusNodeForSearch->ID, ID)) {
			cusInfo * return_ptr = CusNodeForSearch;
			CusNodeForSearch = customers;
			return 1;
		}
		else
		{	//다음 노드가 존재 x -> 검색 끝
			if (CusNodeForSearch->prevNode == NULL) {
				CusNodeForSearch = customers;
				return 0;
			}
			else {
				CusNodeForSearch = CusNodeForSearch->prevNode;
				return IsregistID(ID);	//다음 노드로 검색 이동
			}
		}
	}
	else
		return 0;
}