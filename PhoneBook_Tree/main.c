#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct _USERDATA
{
	char szName[32];
	char szPhone[32];
	struct _USERDATA *LeftChild;
	struct _USERDATA *RightSibling;
}USERDATA;

void appendChild(int nIndex, USERDATA* parent, USERDATA* child, int nCheck)
{
	int checkFlag = nCheck;
	if (nIndex % 2 == 0)
	{
		if (parent->LeftChild == NULL)
			parent->LeftChild = child;
		else if (nIndex % 2 == 0 && parent->RightSibling == NULL)
			parent->RightSibling = child;
		else
			appendChild(nIndex, parent->LeftChild, child, 0);
	}
	else
	{
		if (checkFlag == 1)
			parent->RightSibling = child;
		else if (parent->LeftChild == NULL)
			parent->LeftChild = child;
		else
			appendChild(nIndex, parent->LeftChild, child, 1);
	}

}

void main()
{
	char szInput = '\0';
	printf("[1]Add\t[2]Search\t[3]Print All\t[4]Remove\t[0]Exit\n");
	USERDATA *pLastNode = NULL;
	USERDATA *pRoot = NULL;
	USERDATA *pTmpNode = NULL;
	FILE *fp = NULL;
	int nIndex = 1;
	int i = 0;

	if ((fp = fopen("phoneBook.dat", "rb")) == NULL)
	{
		printf("File is not open!\n");
	}
	else
	{
		USERDATA *pNode = NULL;
		char checkFileEOF = '\0'; //file eof check 1byte		
		
		while (!feof(fp))
		{			
			if (fread(&checkFileEOF, 1, 1, fp) == 0)
				break;
			else
				fseek(fp, -1, SEEK_CUR);

			pNode = (USERDATA*)malloc(sizeof(USERDATA));
			memset(pNode, 0, sizeof(USERDATA));
			fread(pNode, sizeof(char)*64, 1, fp);

			if (pRoot == NULL)
				pRoot = pNode;				
			else
				appendChild(++nIndex, pTmpNode, pNode, 0);

			if(i%2==0)
				pTmpNode = pNode;

			pLastNode = pNode;
			i++;
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
			USERDATA *pNode = NULL;
			pNode = (USERDATA*)malloc(sizeof(USERDATA));
			memset(pNode, 0, sizeof(USERDATA));
			printf("Input Name : ");
			scanf_s("%s", szName, sizeof(char) * 32);
			sprintf(pNode->szName, "%s", szName);
			printf("Input Phone Number : ");
			scanf_s("%s", szPhone, sizeof(char) * 32);
			sprintf(pNode->szPhone, "%s", szPhone);
			
			if (pRoot == NULL)
				pRoot = pNode;
			else
				appendChild(++nIndex, pTmpNode, pNode, 0);

			if (i % 2 == 0)
				pTmpNode = pNode;

			pLastNode = pNode;
			i++;

			getchar();
		}
		if (szInput == '2')
		{
			char szName[32] = { 0 };
			unsigned char ucSearchResultCheckFlag = 'F';
			USERDATA *pNode = pRoot;
			printf("Input Name : ");
			scanf_s("%s", szName, sizeof(char) * 32);
			while (pNode != NULL)
			{
				if (strcmp(pNode->szName, szName) == 0)
				{
					ucSearchResultCheckFlag = 'T';
					printf("[%p]\t %s\t %s\t [%p]\t [%p]\n", pNode, pNode->szName, pNode->szPhone, pNode->LeftChild, pNode->RightSibling);
					break;
				}
				else
				{
					if (pNode->LeftChild != NULL)
						pNode = pNode->LeftChild;
					else
						pNode = pNode->RightSibling;
				}
			}
			if (ucSearchResultCheckFlag == 'F')
				printf("Searching data is not found!\n");
			getchar();
		}
		if (szInput == '3')
		{
			USERDATA *pNode = pRoot;
			while (pNode != NULL)
			{
				printf("[%p]\t %s\t %s\t [%p]\t [%p]\n", pNode, pNode->szName, pNode->szPhone, pNode->LeftChild, pNode->RightSibling);
				if (pNode->LeftChild != NULL)
					pNode = pNode->LeftChild;
				else
					pNode = pNode->RightSibling;
			}
			if (pRoot == NULL)
				printf("Data is empty!\n");
			getchar();
		}
		if (szInput == '4')
		{
			char szName[32] = { 0 };
			USERDATA *pNode = pRoot;
			USERDATA *pPreNodeTmp = NULL;
			printf("Input Name : ");
			scanf_s("%s", szName, sizeof(char) * 32);
			while (pNode != NULL)
			{
				if (strcmp(pNode->szName, szName) == 0)
				{
					printf("[%p]\t %s\t %s\t [%p]\t [%p]\n", pNode, pNode->szName, pNode->szPhone, pNode->LeftChild, pNode->RightSibling);
					if (pNode->LeftChild == NULL && pNode->RightSibling==NULL)
					{
						//부모노드 찾기
						if (pPreNodeTmp->LeftChild == pNode)
							pPreNodeTmp->LeftChild = NULL;
						else if (pPreNodeTmp->RightSibling == pNode)
							pPreNodeTmp->RightSibling = NULL;

						free(pNode);
						break;
					}
					else
					{
						printf("end leaf node 가 아니거나 right sibling이 존재합니다.\n");
						break;
					}						
				}
				else
				{
					pPreNodeTmp = pNode;
					if (pNode->LeftChild != NULL)
						pNode = pNode->LeftChild;
					else
						pNode = pNode->RightSibling;
				}
			}
			getchar();
		}
		if (szInput == '0')
		{
			USERDATA *pNode = pRoot;
			USERDATA *pPreNodeTmp = NULL;

			fp = fopen("phoneBook.dat", "wb");
			if (fp == NULL)
				printf("file create Error!");

			//write file
			while (pNode != NULL)
			{
				fwrite(pNode, sizeof(char)*64, 1, fp);
				if (pNode->LeftChild != NULL)
					pNode = pNode->LeftChild;
				else
					pNode = pNode->RightSibling;
			}
			fclose(fp);

			pNode = pRoot;

			while (pNode != NULL)
			{
				pPreNodeTmp = pNode;
				if (pNode->LeftChild != NULL)
					pNode = pNode->LeftChild;
				else
					pNode = pNode->RightSibling;
				free(pPreNodeTmp);
			}
		}
	}
}