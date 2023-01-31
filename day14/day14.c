#include "../../headers/structure.h"
// ���� -> ������ �ڷ��� ����
// ����Ʈ -> ������ �ڷ��� ����

// ť Que -> ���� ����,FIFO ������ ���� �ڷᱸ��
// ������ �� ������ Que -> ��ȯť
//			����Ʈ�� Que -> �Ϲ���

// ť�� ����>? ������ �������� �ڷᱸ���� �Ѱ�

// ����Ʈ ���
//typedef struct Node {
//	Dec data;
//	struct Node* prev;
//	struct Node* next;
//}Node,*pNode;
//
//typedef struct Que {
//
//	pNode root, end;
//
//
//}Que,*pQue;
//
//
//pQue CreateQueue()
//{
//	pQue que = Allocation(sizeof(Que));
//	return que;
//}
//
//Void ReleaseQue(pQue this)
//{
//	pNode now = this->root;
//	pNode rem;
//	while (now != 0)
//	{
//		rem = now;
//		now = now->next;
//		free(rem);
//	}
//	free(this);
//}
//
//Void insertQue(pQue this, Dec number)
//{
//	pNode node = Allocation(sizeof(Node));
//	node->data = number;
//
//	if (this->root)
//	{
//		node->next = this->root;
//		this->root->prev = node;
//		this->root = node;
//	}
//	else {
//		this->root = node;
//		this->end = node;
//	}
//}
//
//Dec PopQue(pQue this)
//{
//	pNode node = this->end;
//	if (node == 0)
//	{
//		return 0;
//		
//	}
//	if (node->prev) //�ּҰ� 0�� �ƴ϶�� 
//	{
//		node->prev->next = 0;
//	}
//	else
//		this->root = 0;
//	this->end = node->prev;
//	Dec result = node->data;
//	free(node);
//	return result;
//}



// ���� ���




typedef struct Que {
	pDec datas; // �迭
	Dec size, input, output;//��ĭ¥������ .
  // �������� ������ �ε����� �ʿ��ϴ�.
}Que,*pQue;


pQue CreateQue(Dec size)
{
	pQue que = Allocation(sizeof(Que));
	que->datas= Allocation(sizeof(Que));
	que->size = size;
	return que;

}

Void ReleaseQue(pQue this)
{
	free(this->datas);
	free(this);
}

Dec isFull(pQue this)
{
	if ((this->input + 1) % this->size == this->output)return RESULT_OK;
	return RESULT_CANCEL;
}
Dec isEmpty(pQue this)
{
	if (this->input == this->output)return RESULT_OK;
	return  RESULT_CANCEL;
}


Dec InsertQue(pQue this, Dec data)
{
	if ((this->input + 1) % this->size == this->output) return RESULT_CANCEL;
	this->datas[this->input] = data;
	this->input = (this->input + 1) % this->size;
	return RESULT_OK;

}
Dec PopQue(pQue this)
{
	if (this->output == this->input)return RESULT_CANCEL;
	Dec index = this->output;
	this->output = (this->output + 1) % this->size;
	return this->datas[index];
}


Dec LastInsertCheckQue(pQue this)
{
	if (this->input == this->output) return RESULT_CANCEL;
	return this->datas[(this->input + this->size - 1) % this->size];
}
Dec FirstInsertCheckQue(pQue this)
{
	if (this->input == this->output) return RESULT_CANCEL;
	return this->datas[this->output];
}

//Dec DuplicateCheckQue(pQue this, Dec duplicate)
//{
//	for (Dec i = 0; i < this->size; ++i)
//	{
//		if (this->datas[i] == duplicate) return RESULT_OK;
//	}
//	return RESULT_CANCEL;
//  �̷л� ������ ��������� Ʋ�ȴ�. �ͱ�
//	�ܼ��� ������ ���� ���������Ϳ� �������Ͱ��ִµ� ������� �����͵� ���ϰԵȴ�.
//}
Dec DuplicateCheckQue(pQue this, Dec duplicate)
{
	for (Dec i = this->output; i != this->input ; i = (i +1)%this->size)
	{
		if (this->datas[i] == duplicate) return RESULT_OK;
	}
	return RESULT_CANCEL;
}

Void InsertQueNotDuplicat(pQue this, Dec data)
{
	if (DuplicateCheckQue(this, data)) return RESULT_CANCEL;
	return InsertQue(this, data);
}


// ť�� �̿��Ͽ� �ִ� 1000����� ���ڸ� �Է¶�ÿ�
// �Է¿� ����(�ߺ�,�ִ�)�ϸ� ���̻� �Է��� ��������
// ���ݱ��� �Է��� ������ ���� �� ��հ� �ִ밪 �� �ּҰ��� ����Ͻÿ�
// �ִ밪 �� �ּҰ��� �Լ����̿��Ͽ� ����� �����ϰ� ����Ͻÿ�.






// ���ڸ� 0 �Է��Ҷ� ���� ������ �Է��ϴٰ�
// 0�� �Է��ϸ� ���ݱ��� �Է��� ������ ����ϴ� ���α׷��� �ۼ��Ͻÿ�



Void thisduflicate(pQue this, pQue other)
{
	DuplicateCheckQue(this, (other + 1));
}

Dec TotalQue(pQue this)
{
	Dec total = 0;
	for (Dec i = this->output; i != this->input; i = (i + 1) % this->size)
	{
		total += this->datas[i];
	}
	return total;
}

Dec CountQue(pQue this)
{
	Dec total = 0;
	for (Dec i = this->output; i != this->input; i = (i + 1) % this->size)
	{
		total += 1;
	}
	return total;
}


Dec whatQueMAX(pQue this)
{
	if (this->input == this->output)return RESULT_CANCEL;
	Dec large = this->datas[this->output];
	for (Dec i = this->output; i != this->input; i = (i + 1) % this->size)
	{
		large = (large < this->datas[i] ? this->datas[i] : large);
	}
	return large;
}

Dec SmallQue(pQue this)
{
	if (this->input == this->output)return RESULT_CANCEL;
	Dec large = this->datas[this->output];
	for (Dec i = this->output; i != this->input; i = (i + 1) % this->size)
	{
		large = (large > this->datas[i] ? this->datas[i] : large);
	}
	return large;
}



Void main()
{
	/*pQue que = CreateQueue();
	
	for (Dec i = 1; i < 11; ++i)
	insertQue(que, i);
		
	for (Dec i = 0; i < 10; ++i)
		printf("%d > ", PopQue(que));
	

	pQue que2 = CreateQueue();

	Dec select = 0;
	Dec count = 0;
	Dec count2 = 0;
	while (1)
	{
		select = Scan(" >>> ");
		if (select == 0) break;
		insertQue(que2, select);
	}
	while (select = PopQue(que2)) {
		printf("%d > ", select);
	}*/
	// ReleaseQue(que2);
	// ReleaseQue(que);
	// ���ڸ� 0�� �Է��ϱ� ���� �Է��ϰ� �ִ� 1000�� ���� ������ �����ϰ� ����ÿ� 
	// ���� �� ����ִ� ��� ������ ���հ� ����� ����Ͻÿ�
	//pQue que = CreateQue(1000);
	/*for (Dec i = 1; i <= 40; ++i)
	{
		InsertQue(que, i);

	}*/
	/*Dec Number;
	while (Number = PopQue(que)) {
		printf("%d > ", Number);
	}*/
	/*pQue que = CreateQue(1000);
	Dec select = 1;
	while (1)
	{
		select = Scan(" >>> ");
		if (select == 0) break;
		InsertQue(que, select);
	}

	

	Dec count , allcount =0;
	Dec result = 0;
	while (count = PopQue(que)) {
		result += PopQue(que);
		printf("%d > ", count);
		++allcount;
	}
	printf("\n���� : %d ��� %d\n", result,result/allcount);
	
	
	ReleaseQue(que);*/
	
	// ť�� �̿��Ͽ� �ִ� 1000����� ���ڸ� �Է¶�ÿ�
// �Է¿� ����(�ߺ�,�ִ�)�ϸ� ���̻� �Է��� ��������
// ���ݱ��� �Է��� ������ ���� �� ��հ� �ִ밪 �� �ּҰ��� ����Ͻÿ�
// �ִ밪 �� �ּҰ��� �Լ����̿��Ͽ� ����� �����ϰ� ����Ͻÿ�.


	/*pQue newque = CreateQue(1000);
	Dec number = 1;
	while (1)
	{
		
		if (!InsertQueNotDuplicat(newque, Scan(" >>> "))) break;
	
	}*/

	




}