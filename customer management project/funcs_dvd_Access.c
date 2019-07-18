#include "common.h"
#include "cusInfoAccess.h"
#include "dvdInfoAccess.h"

static dvdInfo *dvds=NULL;          //DVD ����ü �迭
static dvdInfo *prevDvdNode = NULL;
static dvdInfo *DVDNodeforSearch = NULL;
static cusInfo *endRentNode = NULL;

int searched_cust_cnt = 0;			//screen_out ���� �ܺ� ������ ��

FILE * dvdInfo_file;
FILE * rentedInfo_file;


void initialize_rentedInfo(char * ISBN) {
	rentedInfo_file = fopen("rentedDVD_Info.txt", "rt");
	dvdInfo *temp_dvdInfo = GetDVDPtrByISBN(ISBN);  
	cusInfo *temp_rent = NULL;
	int *remove;
	char *temp[ISBN_LEN];
	


	if (rentedInfo_file != NULL) {
		while (fscanf(rentedInfo_file, "%s", temp) != EOF) {
			if (!strcmp(temp, ISBN)) {
				temp_rent = temp_dvdInfo->rentedCus;

				temp_dvdInfo->rentedCus = (cusInfo *)malloc(sizeof(cusInfo));

				fscanf(rentedInfo_file, "%s", temp);
				strcpy(temp_dvdInfo->rentedCus->ID, GetCusPtrByID(temp)->ID);
				strcpy(temp_dvdInfo->rentedCus->name, GetCusPtrByID(temp)->name);
				strcpy(temp_dvdInfo->rentedCus->phoneNum, GetCusPtrByID(temp)->phoneNum);
				fscanf(rentedInfo_file, "%d", &temp_dvdInfo->rentedCus->rentYear);
				fscanf(rentedInfo_file, "%d", &temp_dvdInfo->rentedCus->rentMonth);
				fscanf(rentedInfo_file, "%d", &temp_dvdInfo->rentedCus->rentDate);

				//���� ����ü������ ���Ḯ��Ʈ �Ϸ��� �ؿ� ����
				temp_dvdInfo->rentedCus->nextNode = NULL;
				temp_dvdInfo->rentedCus->prevNode = NULL;

				if (temp_rent != NULL) {
					temp_rent->nextNode = temp_dvdInfo->rentedCus;
					temp_dvdInfo->rentedCus->prevNode = temp_rent;
				}
			}
			else {
				remove = (int *)malloc(sizeof(int));
				fscanf(rentedInfo_file, "%s", temp);
				fscanf(rentedInfo_file, "%d", remove);
				fscanf(rentedInfo_file, "%d", remove);
				fscanf(rentedInfo_file, "%d", remove);
				free(remove);
			}
		}
		fclose(rentedInfo_file);
	}
}

void initialize_dvdInfo() {
	dvdInfo_file = fopen("DVD_Info.txt", "rt");

	char * temp[ISBN_LEN];

	if (dvdInfo_file != NULL) {
		while (fscanf(dvdInfo_file, "%s", temp) != EOF) {

			prevDvdNode = dvds;					//���� ����� �۾��� ���� ��������� ������ ���� ��带 ����

			//DVD�� ���� ���� �޸� �Ҵ�
			dvds = (dvdInfo *)malloc(sizeof(dvdInfo));


			if (dvds == NULL)return 0;
				
			strcpy(dvds->ISBN, temp);
			fscanf(dvdInfo_file, "%s", dvds->title);
			fscanf(dvdInfo_file, "%d", &dvds->genre);
			fscanf(dvdInfo_file, "%d", &dvds->rentFlag);
			fscanf(dvdInfo_file, "%d", &dvds->rentCnt);



			//DVD ����ü�� ���Ḯ��Ʈ ����***********

			dvds->nextNode = NULL;		// �� �� ��� �ʱ�ȭ
			dvds->prevNode = NULL;

			dvds->rentedCus = NULL;		//�뿩 ��� �ʱ�ȭ
			

			if (prevDvdNode != NULL) {
				prevDvdNode->nextNode = dvds;
				dvds->prevNode = prevDvdNode;
			}
			
			DVDNodeforSearch = dvds;

			//****************************************

			initialize_rentedInfo(dvds->ISBN);
		}
		fclose(dvdInfo_file);
	}
}

int AddDVD_Info(char *ISBN, char * title, int *genre) {
	
	prevDvdNode = dvds;					//���� ����� �۾��� ���� ��������� ������ ���� ��带 ����

	//DVD�� ���� ���� �޸� �Ҵ�
	//1���� ��ϵ� �� ���� ����
	dvds = (dvdInfo *)malloc(sizeof(dvdInfo));

	//�޸� �Ҵ� ���н� 0 ��ȯ
	if (dvds == NULL)return 0;

	//DVD�� ���� ���� ����
	strcpy(dvds->ISBN, ISBN);
	strcpy(dvds->title, title);
	dvds->genre = *genre;
	dvds->rentFlag = 0;
	dvds->rentCnt = 0;

	//DVD ����ü�� ���Ḯ��Ʈ ����
	
	dvds->nextNode = NULL;					//�� �� ��� �ʱ�ȭ
	dvds->prevNode = NULL;
	
	dvds->rentedCus = NULL;					//�뿩 ��� �ʱ�ȭ

	if (prevDvdNode != NULL) {
		prevDvdNode->nextNode = dvds;		//���� ����� ���� ��� = ���� ���
		dvds->prevNode = prevDvdNode;		//���� ����� ���� ��� = ���� ���
	}

	DVDNodeforSearch = dvds;

	//���� �ҷ�����
	dvdInfo_file = fopen("DVD_Info.txt", "rt");

	if (dvdInfo_file != NULL) {
		printf("DVD ���� �ҷ����� ����\n");
		dvdInfo_file = fopen("DVD_Info.txt", "a");
	}
	else
	{
		printf("DVD ���� ���� ����\n");
		dvdInfo_file = fopen("DVD_Info.txt", "wt");
	}

	fprintf(dvdInfo_file, "%s\t", dvds->ISBN);
	fprintf(dvdInfo_file, "%s\t", dvds->title);
	fprintf(dvdInfo_file, "%d\t", dvds->genre);
	fprintf(dvdInfo_file, "%d\t", dvds->rentFlag);
	fprintf(dvdInfo_file, "%d\n", dvds->rentCnt);

	fclose(dvdInfo_file);

	return 1;
	

}

//DVD�� ���� ���� �޸� �Ҵ� ����
void free_dvds() {
	cusInfo *temp;
	if (dvds != NULL) {												//DVD ������ �����ϸ� �����ϵ��� Ȯ��
		while (dvds->prevNode != NULL) {
			if (dvds->rentedCus != NULL) {							//�뿩 ������ �����ϸ� �����ϵ��� Ȯ��
				while (dvds->rentedCus->prevNode != NULL) {
					temp = dvds->rentedCus->prevNode;
					free(dvds->rentedCus);							//DVD ���� ���� �뿩 ���� ����
					dvds->rentedCus = temp;
				}

				free(dvds->rentedCus);								//�뿩 ���� ������ ��� ����
			}
			temp = dvds->prevNode;
			free(dvds);												//DVD ���� ����
			dvds = temp;
		}

		free(dvds);													//DVD ���� ������ ��� ����
	}
}


//ISBN�� ��ġ�ϴ� DVD�� ã���� �ش� ����ü ������ ��ȯ
dvdInfo *GetDVDPtrByISBN(char *ISBN) {
	if (DVDNodeforSearch != NULL) {
		//���� ����� ID�� ��ġ�ϸ� ��ȯ
		if (!strcmp(DVDNodeforSearch->ISBN, ISBN)) {
			cusInfo * return_ptr = DVDNodeforSearch;
			DVDNodeforSearch = dvds;
			return return_ptr;
		}
		else
		{	//���� ��尡 ���� x -> �˻� ��
			if (DVDNodeforSearch->prevNode == NULL) {
				DVDNodeforSearch = dvds;
				return NULL;
			}
			else {
				DVDNodeforSearch = DVDNodeforSearch->prevNode;
				return GetDVDPtrByISBN(ISBN);	//���� ���� �˻� �̵�
			}
		}
	}
	else
		return NULL;
}

//ISBN�� �ߺ����� �ʴ��� Ȯ�� �� ���ٸ� 0�� ��ȯ
int IsRegistISBN(char *ISBN) {
	if (DVDNodeforSearch != NULL) {
		//���� ����� ID�� ��ġ�ϸ� ��ȯ
		if (!strcmp(DVDNodeforSearch->ISBN, ISBN)) {
			cusInfo * return_ptr = DVDNodeforSearch;
			DVDNodeforSearch = dvds;
			return 1;
		}
		else
		{	//���� ��尡 ���� x -> �˻� ��
			if (DVDNodeforSearch->prevNode == NULL) {
				DVDNodeforSearch = dvds;
				return 0;
			}
			else {
				DVDNodeforSearch = DVDNodeforSearch->prevNode;
				return IsRegistISBN(ISBN);	//���� ���� �˻� �̵�
			}
		}
	}
	else
		return 0;
}

cusInfo ** SearchCusInfoBTWperiod(int *periodF, int *periodT, char * SearchID) {

	cusInfo **search_CusInfo = NULL;

	 searched_cust_cnt = 0;

	//��ȿ�� ���̵� �̶��

	while(1){		
		while(1){
			if (!strcmp(DVDNodeforSearch->rentedCus->ID, SearchID)) {																						//��ġ�ϴ� ����� �����ϸ�
				if (DVDNodeforSearch->rentedCus->rentYear <= periodT[Year] && DVDNodeforSearch->rentedCus->rentYear >= periodF[Year]) {						//���� ����						
					if (DVDNodeforSearch->rentedCus->rentMonth <= periodT[Month] && DVDNodeforSearch->rentedCus->rentMonth >= periodF[Month]) {				//�� ����
						if (DVDNodeforSearch->rentedCus->rentDate <= periodT[Date] && DVDNodeforSearch->rentedCus->rentDate >= periodF[Date]) {				//��¥ ���� �ִٸ�

							if (!searched_cust_cnt)search_CusInfo = (cusInfo **)malloc(++searched_cust_cnt * sizeof(cusInfo *));
							else
								search_CusInfo = (cusInfo **)realloc(search_CusInfo, ++searched_cust_cnt * sizeof(cusInfo *));

							*(search_CusInfo + searched_cust_cnt - 1) = (cusInfo *)malloc(sizeof(cusInfo));

							(*(search_CusInfo + searched_cust_cnt - 1))->rentYear = DVDNodeforSearch->rentedCus->rentYear;
							(*(search_CusInfo + searched_cust_cnt - 1))->rentMonth = DVDNodeforSearch->rentedCus->rentMonth;
							(*(search_CusInfo + searched_cust_cnt - 1))->rentDate = DVDNodeforSearch->rentedCus->rentDate;
							strcpy((*(search_CusInfo + searched_cust_cnt - 1))->ID, DVDNodeforSearch->ISBN);
							strcpy((*(search_CusInfo + searched_cust_cnt - 1))->name, DVDNodeforSearch->title);

							if (DVDNodeforSearch->rentedCus->prevNode != NULL)DVDNodeforSearch->rentedCus = DVDNodeforSearch->rentedCus->prevNode;
							else
								break;
						}
						else
							break;
					}
					else
						break;
				}
				else
					break;
			}
			else
				break;
			
		}
		
		while(DVDNodeforSearch->rentedCus->nextNode != NULL)DVDNodeforSearch->rentedCus = DVDNodeforSearch->rentedCus->nextNode;
		if (DVDNodeforSearch->prevNode != NULL)DVDNodeforSearch = DVDNodeforSearch->prevNode;
		else
			break;
	} 
	DVDNodeforSearch = dvds;
	
	return search_CusInfo;
}

int IsrentedDVD(char *ISBN) {
	if (GetDVDPtrByISBN(ISBN)->rentFlag)return 1;
	else
		return 0;

}

int RentDVD(char *inp_ID, char *inp_ISBN, int *Today) {

	cusInfo * nowCus = GetCusPtrByID(inp_ID);
	dvdInfo * nowDvd = GetDVDPtrByISBN(inp_ISBN);

	nowDvd->rentedCus = (cusInfo *)malloc(sizeof(cusInfo));

	strcpy(nowDvd->rentedCus->ID,nowCus->ID);
	strcpy(nowDvd->rentedCus->name, nowCus->name);
	strcpy(nowDvd->rentedCus->phoneNum, nowCus->phoneNum);
	nowDvd->rentedCus->rentYear = Today[Year];
	nowDvd->rentedCus->rentMonth = Today[Month];
	nowDvd->rentedCus->rentDate = Today[Date];
	nowDvd->rentFlag = 1;

	nowDvd->rentedCus->nextNode = NULL;
	nowDvd->rentedCus->prevNode = NULL;

	if (endRentNode != NULL) {
		nowDvd->rentedCus->prevNode = endRentNode;
		endRentNode->nextNode = nowDvd->rentedCus;
	}

	endRentNode = nowDvd->rentedCus;

	rentedInfo_file = fopen("rentedDVD_Info.txt", "rt");

	if (rentedInfo_file != NULL) {
		rentedInfo_file = fopen("rentedDVD_Info.txt", "a");
	}
	else
		rentedInfo_file = fopen("rentedDVD_Info.txt", "wt");

	fprintf(rentedInfo_file, "%s\t", inp_ISBN);
	fprintf(rentedInfo_file, "%s\t", nowCus->ID);
	fprintf(rentedInfo_file, "%d\t", nowDvd->rentedCus->rentYear);
	fprintf(rentedInfo_file, "%d\t", nowDvd->rentedCus->rentMonth);
	fprintf(rentedInfo_file, "%d\n", nowDvd->rentedCus->rentDate);

	fclose(rentedInfo_file);

	return 1;
}


int returnDVD(char *ISBN) {
	GetDVDPtrByISBN(ISBN)->rentFlag = 0;
	return 1;
}