#include<stdio.h>
#include<math.h>

typedef struct _TREE
{
	char aData[32];
	struct TREE* LeftChild;
	struct TREE* RightSibling;	
}TREE;

void printTree(int depth, TREE* tree)
{
	for (int i = 0; i < depth; ++i)
		printf("---- ");
	printf("%s\t\t\t [%p]\t [%p]\t [%p]\n", tree->aData, tree, tree->LeftChild, tree->RightSibling);
	if (tree->LeftChild != NULL)
		printTree(depth + 1, (TREE*)tree->LeftChild);
	if (tree->RightSibling != NULL)
		printTree(depth, (TREE*)tree->RightSibling);
}

void appendChild(int nIndex, TREE* parent, TREE* child, int nCheck)
{	
	int checkFlag = nCheck;
	if (nIndex%2 == 0)
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
		if(checkFlag == 1)
			parent->RightSibling = child;
		else if (parent->LeftChild == NULL)
			parent->LeftChild = child;
		else
			appendChild(nIndex, parent->LeftChild, child, 1);			
	}
	
}

void Tree()
{
	TREE Root = { { "Root" }, NULL, NULL };
	TREE A = { { "Adat" }, NULL, NULL };
	TREE B = { { "Bdat" }, NULL, NULL };
	TREE C = { { "Cdat" }, NULL, NULL };
	TREE D = { { "Ddat" }, NULL, NULL };	
	TREE E = { { "Edat" }, NULL, NULL };
	TREE F = { { "Fdat" }, NULL, NULL };
	TREE G = { { "Gdat" }, NULL, NULL };
	TREE H = { { "Hdat" }, NULL, NULL };
	int i = 1;
	int nLevel = 0;
	appendChild(++i, &Root, &A, 0);
	appendChild(++i, &Root, &B, 0);
	appendChild(++i, &A, &C, 0);
	appendChild(++i, &A, &D, 0);
	appendChild(++i, &B, &E, 0);
	appendChild(++i, &B, &F, 0);
	appendChild(++i, &C, &G, 0);
	appendChild(++i, &C, &H, 0);
	printTree(0, &Root);
}