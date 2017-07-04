


int CreateBiTree(BiTree *T)
{
	*T = (BiTNode *)malloc(sizeof(BiTNode));
	if (*T==NULL)
	{
		printf("memery malloc failure !\n");
		return -1;
	}

	printf("enter data to create node:\n");

	scanf("%c",&((*T)->item));

	if((*T)->item=='#'){
		*T=NULL;
	}
	if(*T){
		printf("创建左子树:\n");
		CreateBiTree( &((*T)->lChild) );
		printf("创建右子树:\n");
		CreateBiTree( &((*T)->rChild) );
	}
	return 0;
}


int main(int argc, char const *argv[])
{
	/* code */
	BiTree binaryTree;

	printf("创建二叉树，输入\"空格\"创建空节点（先序方式建立二叉树）:\n");
	binaryTree =  CreateBiTree();
	if(binaryTree==NULL){
		printf("创建空的二叉树\n");
	}

	printf("前序遍历:\n");
	PreOrderTraverse(binaryTree);
	printf("\n\n");
	return 0;
}


