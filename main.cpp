#include<iostream>
#include<cassert>
#include<ctime>

#include"StackAlloc.hpp"
#include"MemoryPool.hpp"
using namespace std;

//����Ԫ�ظ���
#define ELEMS 100000

//�ظ�����
#define REPS 100


int main()
{
    clock_t start;
    //ʹ��stlĬ�Ϸ�����
    StackAlloc<int,std::allocator<int> > stackDefault;
    start=clock();
    for(int i=0;i<REPS;i++)
    {
        assert(stackDefault.empty() );
        for(int j=0;j<ELEMS;j++)
        {
            stackDefault.push(j);
        }

        for(int j=0;j<ELEMS;j++)
        {
            stackDefault.pop();
        }

    }
    //ʹ��CLOCKS_PER_SEC���������е����ڵ�cpuת��������
    cout<<"Default time :"<<( ( (double)clock()-start  )/CLOCKS_PER_SEC)<<endl;


    // ���ڲ���ʹ���ڴ��
    StackAlloc<int, MemoryPool<int> > stackPool;
    start = clock();
    for (int j = 0; j < REPS; j++) {
        assert(stackPool.empty());
        for (int i = 0; i < ELEMS; i++)
            stackPool.push(i);
        for (int i = 0; i < ELEMS; i++)
            stackPool.pop();
    }
    cout << "MemoryPool Allocator Time: ";
    cout << (((double)clock() - start) / CLOCKS_PER_SEC) << endl;




    

    return 0;
}
