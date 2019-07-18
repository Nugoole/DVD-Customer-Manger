#include "common.h"
#include "cusInfoAccess.h"
#include "dvdInfoAccess.h"

static dvdInfo *dvds=NULL;          //DVD 구조체 배열
static dvdInfo *prevDvdNode = NULL;
static dvdInfo *DVDNodeforSearch = NULL;
static cusInfo *endRentNode = NULL;

int searched_cust_cnt = 0;			//screen_out 에서 외부 참조를 함

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

				//내부 구조체에서도 연결리스트 하려면 밑에 설정
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

			prevDvdNode = dvds;					//다음 노드의 작업을 위해 이전노드의 공간에 현재 노드를 저장

			//DVD에 대한 동적 메모리 할당
			dvds = (dvdInfo *)malloc(sizeof(dvdInfo));


			if (dvds == NULL)return 0;
				
			strcpy(dvds->ISBN, temp);
			fscanf(dvdInfo_file, "%s", dvds->title);
			fscanf(dvdInfo_file, "%d", &dvds->genre);
			fscanf(dvdInfo_file, "%d", &dvds->rentFlag);
			fscanf(dvdInfo_file, "%d", &dvds->rentCnt);



			//DVD 구조체의 연결리스트 설정***********

			dvds->nextNode = NULL;		// 앞 뒤 노드 초기화
			dvds->prevNode = NULL;

			dvds->rentedCus = NULL;		//대여 목록 초기화
			

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
	
	prevDvdNode = dvds;					//다음 노드의 작업을 위해 이전노드의 공간에 현재 노드를 저장

	//DVD에 대한 동적 메모리 할당
	//1개씩 등록될 때 마다 생성
	dvds = (dvdInfo *)malloc(sizeof(dvdInfo));

	//메모리 할당 실패시 0 반환
	if (dvds == NULL)return 0;

	//DVD에 대한 정보 저장
	strcpy(dvds->ISBN, ISBN);
	strcpy(dvds->title, title);
	dvds->genre = *genre;
	dvds->rentFlag = 0;
	dvds->rentCnt = 0;

	//DVD 구조체의 연결리스트 설정
	
	dvds->nextNode = NULL;					//앞 뒤 노드 초기화
	dvds->prevNode = NULL;
	
	dvds->rentedCus = NULL;					//대여 목록 초기화

	if (prevDvdNode != NULL) {
		prevDvdNode->nextNode = dvds;		//현재 노드의 이전 노드 = 이전 노드
		dvds->prevNode = prevDvdNode;		//이전 노드의 다음 노드 = 현재 노드
	}

	DVDNodeforSearch = dvds;

	//파일 불러오기
	dvdInfo_file = fopen("DVD_Info.txt", "rt");

	if (dvdInfo_file != NULL) {
		printf("DVD 정보 불러오기 성공\n");
		dvdInfo_file = fopen("DVD_Info.txt", "a");
	}
	else
	{
		printf("DVD 정보 새로 생성\n");
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

//DVD에 대한 동적 메모리 할당 해제
void free_dvds() {
	cusInfo *temp;
	if (dvds != NULL) {												//DVD 정보가 존재하면 해제하도록 확인
		while (dvds->prevNode != NULL) {
			if (dvds->rentedCus != NULL) {							//대여 정보가 존재하면 해제하도록 확인
				while (dvds->rentedCus->prevNode != NULL) {
					temp = dvds->rentedCus->prevNode;
					free(dvds->rentedCus);							//DVD 정보 내의 대여 정보 해제
					dvds->rentedCus = temp;
				}

				free(dvds->rentedCus);								//대여 정보 마지막 노드 해제
			}
			temp = dvds->prevNode;
			free(dvds);												//DVD 정보 해제
			dvds = temp;
		}

		free(dvds);													//DVD 정보 마지막 노드 해제
	}
}


//ISBN이 일치하는 DVD를 찾으면 해당 구조체 포인터 반환
dvdInfo *GetDVDPtrByISBN(char *ISBN) {
	if (DVDNodeforSearch != NULL) {
		//현재 노드의 ID가 일치하면 반환
		if (!strcmp(DVDNodeforSearch->ISBN, ISBN)) {
			cusInfo * return_ptr = DVDNodeforSearch;
			DVDNodeforSearch = dvds;
			return return_ptr;
		}
		else
		{	//다음 노드가 존재 x -> 검색 끝
			if (DVDNodeforSearch->prevNode == NULL) {
				DVDNodeforSearch = dvds;
				return NULL;
			}
			else {
				DVDNodeforSearch = DVDNodeforSearch->prevNode;
				return GetDVDPtrByISBN(ISBN);	//다음 노드로 검색 이동
			}
		}
	}
	else
		return NULL;
}

//ISBN이 중복되지 않는지 확인 후 없다면 0을 반환
int IsRegistISBN(char *ISBN) {
	if (DVDNodeforSearch != NULL) {
		//현재 노드의 ID가 일치하면 반환
		if (!strcmp(DVDNodeforSearch->ISBN, ISBN)) {
			cusInfo * return_ptr = DVDNodeforSearch;
			DVDNodeforSearch = dvds;
			return 1;
		}
		else
		{	//다음 노드가 존재 x -> 검색 끝
			if (DVDNodeforSearch->prevNode == NULL) {
				DVDNodeforSearch = dvds;
				return 0;
			}
			else {
				DVDNodeforSearch = DVDNodeforSearch->prevNode;
				return IsRegistISBN(ISBN);	//다음 노드로 검색 이동
			}
		}
	}
	else
		return 0;
}

cusInfo ** SearchCusInfoBTWperiod(int *periodF, int *periodT, char * SearchID) {

	cusInfo **search_CusInfo = NULL;

	 searched_cust_cnt = 0;

	//유효한 아이디 이라면

	while(1){		
		while(1){
			if (!strcmp(DVDNodeforSearch->rentedCus->ID, SearchID)) {																						//일치하는 사람이 존재하면
				if (DVDNodeforSearch->rentedCus->rentYear <= periodT[Year] && DVDNodeforSearch->rentedCus->rentYear >= periodF[Year]) {						//연도 내에						
					if (DVDNodeforSearch->rentedCus->rentMonth <= periodT[Month] && DVDNodeforSearch->rentedCus->rentMonth >= periodF[Month]) {				//월 내에
						if (DVDNodeforSearch->rentedCus->rentDate <= periodT[Date] && DVDNodeforSearch->rentedCus->rentDate >= periodF[Date]) {				//날짜 내에 있다면

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