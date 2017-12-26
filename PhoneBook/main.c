#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct _USERDATA
{
	char szName[32];
	char szPhone[32];
	struct _USERDATA *pNext;
}USERDATA;

void main()
{
	char szInput = '\0';
	printf("[1]Add\t[2]Search\t[3]Print All\t[4]Remove\t[0]Exit\n");	
	USERDATA *pPreNode = NULL;
	USERDATA *pInit = NULL;
	FILE *fp = NULL;
	
	if ((fp = fopen("phoneBook.dat", "rb")) == NULL)
	{
		printf("File is not open!\n");
	}		
	else
	{
		USERDATA *pNode = NULL;
		char checkFileEOF = '\0'; //file eof check 1byte

		//read file
		while (!feof(fp))
		{
			pNode = (USERDATA*)malloc(sizeof(USERDATA));
			memset(pNode, 0, sizeof(USERDATA));
			fread(pNode, sizeof(USERDATA), 1, fp);
			if (pInit == NULL)
				pInit = pNode;
			else
				pPreNode->pNext = pNode;
			pPreNode = pNode;
			
			if (fread(&checkFileEOF, 1, 1, fp) == 0)
				break;
			else
				fseek(fp, -1, SEEK_CUR);			
		}

		fclose(fp);
	}


	while (szInput != '0')
	{
		putchar(':');
		szInput = getchar();
		if (szInput == '1')
		{
			char szName[32] = { 0 };
			char szPhone[32] = { 0 };
			USERDATA *userData = NULL;
			userData = (USERDATA*)malloc(sizeof(USERDATA));
			memset(userData, 0, sizeof(USERDATA));
			printf("Input Name : ");
			scanf_s("%s", szName, sizeof(char) * 32);
			sprintf(userData->szName, "%s", szName);
			printf("Input Phone Number : ");
			scanf_s("%s", szPhone, sizeof(char) * 32);
			sprintf(userData->szPhone, "%s", szPhone);
			if (pPreNode == NULL)
				userData->pNext = NULL;
			else
				pPreNode->pNext = userData;
			pPreNode = userData;
			if (pInit == NULL)
				pInit = userData;
			getchar();
		}
		if (szInput == '2')
		{
			char szName[32] = { 0 };
			USERDATA *pNode = pInit;
			printf("Input Name : ");
			scanf_s("%s", szName, sizeof(char) * 32);
			while (pNode != NULL) 
			{
				if (strcmp(pNode->szName, szName) == 0)
				{
					printf("[%p]\t %s\t %s\t [%p]\n", pNode, pNode->szName, pNode->szPhone, pNode->pNext);
					break;
				}
				else
				{
					pNode = pNode->pNext;
				}
			}
			getchar();
		}
		if (szInput == '3')
		{
			USERDATA *pNode = pInit;
			while (pNode != NULL)
			{
				printf("[%p]\t %s\t %s\t [%p]\n", pNode, pNode->szName, pNode->szPhone, pNode->pNext);
				pNode = pNode->pNext;				
			} 
			getchar();
		}
		if (szInput == '4')
		{	
			char szName[32] = { 0 };
			USERDATA *pNode = pInit;
			USERDATA *pPreNode = NULL;
			printf("Input Name : ");
			scanf_s("%s", szName, sizeof(char) * 32);
			while (pNode != NULL)
			{
				if (strcmp(pNode->szName, szName) == 0)
				{
					printf("[%p]\t %s\t %s\t [%p]\n", pNode, pNode->szName, pNode->szPhone, pNode->pNext);
					if (pPreNode != NULL)
						pPreNode->pNext = pNode->pNext;
					free(pNode);
					break;
				}
				else
				{
					pPreNode = pNode;
					pNode = pNode->pNext;
				}
			} 
			getchar();
		}
		if (szInput == '0')
		{
			USERDATA *pNode = pInit;
			USERDATA *pPreNode = NULL;

			fp = fopen("phoneBook.dat", "wb");
			if (fp == NULL)
				printf("file create Error!");

			//write file
			while (pNode != NULL)
			{
				fwrite(pNode, sizeof(USERDATA), 1, fp);
				pNode = pNode->pNext;
			}
			fclose(fp);

			pNode = pInit;

			while (pNode != NULL)
			{
				if (pNode->pNext == NULL)
				{
					free(pNode);
					break;
				}					
				else
				{
					pPreNode = pNode;
					pNode = pNode->pNext;
					free(pPreNode);
				}
			}
		}
	}
}