#include<memory>

using namespace std;
template <typename T>
struct StackNode_
{
    T data;
    StackNode_ * prev;
    StackNode_()
    {
        prev=nullptr;
    }
};

//TΪ�洢��������ͣ�AllocΪ��������Ĭ��ʹ��std::allocator���������
template <typename T,typename Alloc=std::allocator<T> >
class StackAlloc
{

public:
    typedef StackNode_<T> Node;
    typedef typename Alloc::template rebind<Node>::other allocator;

    //Ĭ�Ϲ���
    StackAlloc(){
        head_=nullptr;
    }

    ~StackAlloc(){
        clear();
    }

    bool empty(){
        return (head_==nullptr);
    }

    void clear(); //�ͷ�ջ�е������ڴ�

    void push(T element);

    T pop();

    T top(){
        return (head_->data);
    }

private:
    allocator allocator_;
    Node* head_;

};




template <typename T,typename Alloc>
void StackAlloc<T,Alloc>::clear(){
    Node * curr=head_;
    //�����ջ

    while(curr != 0){
        Node * tmp=curr->prev;
        //���������ٽ��л����ڴ�
        allocator_.destroy(curr);
        allocator_.deallocate(curr,1);
        curr = tmp;
    }
    head_=nullptr;

}

template<typename T,typename Alloc>
void StackAlloc<T,Alloc>::push(T element){
    //�ȷ����ڴ�
    Node * newNode=allocator_.allocate(1);
    //Ȼ������乹�캯��
    allocator_.construct(newNode,Node() );

    //��ջ����
    newNode->data =element;
    newNode->prev=head_;
    head_=newNode;

}

//��ջ��
template<typename T,typename Alloc>
T StackAlloc<T,Alloc>::pop(){
    T result =head_->data;
    Node * tmp=head_->prev;
    //�ȵ������������������ͷ��ڴ�
    allocator_.destroy(head_);
    allocator_.deallocate(head_,1);
    head_=tmp;
    return result;
}