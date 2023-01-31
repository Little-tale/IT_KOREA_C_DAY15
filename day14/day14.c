#include "../../headers/structure.h"
// 백터 -> 묶음형 자료의 형태
// 리스트 -> 연결형 자료의 형태

// 큐 Que -> 선입 선출,FIFO 순서에 관한 자료구조
// 묶음형 즉 백터형 Que -> 순환큐
//			리스트형 Que -> 일반형

// 큐가 뭐야>? 일자형 데이터의 자료구조중 한개

// 리스트 방식
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
//	if (node->prev) //주소가 0이 아니라면 
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



// 묶음 방식




typedef struct Que {
	pDec datas; // 배열
	Dec size, input, output;//몇칸짜리인지 .
  // 넣을때와 뺄때의 인덱스가 필요하다.
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
//  이론상 문제가 없어보이지만 틀렸다. 왤까
//	단순한 이유다 내가 넣은데이터와 뺄데이터가있는데 빈공간의 데이터도 비교하게된다.
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


// 큐를 이용하여 최대 1000기ㅐ의 숫자를 입력라시오
// 입력에 실패(중복,최대)하면 더이상 입력을 하지말고
// 지금까지 입력한 모든수의 종합 및 평균과 최대값 및 최소값을 출력하시오
// 최대값 및 최소값을 함수를이용하여 기능을 구성하고 출력하시오.






// 숫자를 0 입력할때 까지 무한히 입력하다가
// 0을 입력하면 지금까지 입력한 모든수를 출력하는 프로그램을 작성하시오



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
	// 숫자를 0을 입력하기 까지 입력하고 최대 1000개 까지 저장이 가능하게 만드시오 
	// 저장 후 들어있는 모든 숫자의 총합과 평균을 출력하시오
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
	printf("\n총합 : %d 평균 %d\n", result,result/allcount);
	
	
	ReleaseQue(que);*/
	
	// 큐를 이용하여 최대 1000기ㅐ의 숫자를 입력라시오
// 입력에 실패(중복,최대)하면 더이상 입력을 하지말고
// 지금까지 입력한 모든수의 종합 및 평균과 최대값 및 최소값을 출력하시오
// 최대값 및 최소값을 함수를이용하여 기능을 구성하고 출력하시오.


	/*pQue newque = CreateQue(1000);
	Dec number = 1;
	while (1)
	{
		
		if (!InsertQueNotDuplicat(newque, Scan(" >>> "))) break;
	
	}*/

	




}