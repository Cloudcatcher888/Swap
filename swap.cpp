#include<iostream>	
#include<list>
#include<queue>
using namespace std;

typedef char TElemType;

typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode;

typedef BiTNode* BiTree;

void CreateBiTree_Rec(BiTree &T)
{
	TElemType ch;
	cin >> ch;
	if (ch == '#')T = NULL;
	else
	{
		T = new BiTNode;
		CreateBiTree_Rec(T->lchild);
		CreateBiTree_Rec(T->rchild);
		T->data = ch;
	}
}

void InOrder_Rec(BiTree T)
{
	if (T)
	{
		InOrder_Rec(T->lchild);
		cout << T->data;
		InOrder_Rec(T->rchild);

	}
}
int Leafs_Rec(BiTree T)
{
	static int i = 0;
	if (!T)return 0;
	if (T)
	{
		i++;
		Leafs_Rec(T->lchild);
		Leafs_Rec(T->rchild);
	}
	return i;

}

int Leafs_Rec1(BiTree T)
{
	int l_Leafs, r_Leafs;
	if (!T)return 0;
	else
	{
		if (!T->lchild && !T->rchild)
			return 1;
		else
		{
			l_Leafs = Leafs_Rec1(T->lchild);
			r_Leafs = Leafs_Rec1(T->rchild);
			return r_Leafs + l_Leafs;
		}
	}
}

int BiTreeDepth_Rec(BiTree T)
{
	int l_Depth, r_Depth;
	if (T)
	{
		l_Depth = BiTreeDepth_Rec(T->lchild);
		r_Depth = BiTreeDepth_Rec(T->rchild);
		if (r_Depth >= l_Depth)return r_Depth + 1;
		else return l_Depth + 1;
	}
	else return 0;
}

void swap(BiTree &tree)
{
	if (tree != NULL)
	{
		BiTree temp ;//是一个指针
		if (tree->lchild != NULL || tree->rchild != NULL)
		{
			temp=tree->lchild;
			tree->lchild = tree->rchild;
			tree->rchild = temp;
		}
		swap(tree->lchild);
		swap(tree->rchild);
	}
}

int calc_degree2(BiTree T)
{
	static int i = 0;
	if (T->lchild != NULL&&T->rchild != NULL)i++;
	if (T->lchild != NULL)
	{
		calc_degree2(T->lchild);
	}
	if (T->rchild != NULL)
	{
		calc_degree2(T->rchild);
	}
	return i;
}

void depthTaverse(BiTree T)
{
	queue<BiTNode,list<BiTNode> > queue;
	queue.push(*T);
	while (!queue.empty())
	{
		*T = queue.front();
		queue.pop();
		if (T->lchild != NULL)queue.push(*(T->lchild));
		if (T->rchild != NULL)queue.push(*(T->rchild));
		cout << T->data;
	}

}

bool Tequal(BiTree T1, BiTree T2)
{
	bool tequal,flag1=true,flag2=true;
	if (T1->data == T2->data&&T1!=NULL&&T2!=NULL)
	{
		if (T1->lchild != NULL&&T2->lchild != NULL)
		{
			flag1=Tequal(T1->lchild, T2->lchild);
		}
		else if (T1->lchild == NULL&&T2->lchild == NULL)flag1 = true;
		if (T1->rchild != NULL&&T2->rchild != NULL)
		{
			flag2 = Tequal(T1->rchild, T2->rchild);
		}
		else if (T1->rchild == NULL&&T2->rchild == NULL)flag1 = true;
	}
	return flag1&&flag2;
}

void main()
{
	BiTree T;
	int k;
	cout << "请按要求（前序序列建立）输入您所要输入的字符串：\n";
	CreateBiTree_Rec(T);
	cout << "中序递归遍历输出为：\n";
	InOrder_Rec(T);
	cout << endl;
	cout << "交换后为：\n";
	swap(T);
	InOrder_Rec(T);
	cout<<calc_degree2(T);
	depthTaverse(T);
	cout<<Tequal(T, T);
	cin >> k;
}