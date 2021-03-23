#pragma once
#include "baseTree.h"
#include <stack>

template<class type> class randomTree : public baseTree<type>//����� �������� ������, ��������� ������� 
{
public:
    randomTree();
    randomTree(randomTree<type>&);
    randomTree(type&);
    randomTree(type*, int);
    randomTree<type>& operator = (randomTree<type>&);
    virtual bool AddNode(type&);
    virtual bool DelNode(type&);
    bool FindNode(type&);
    type FindMax();
    type FindMin();
};

template<class type> randomTree<type>::randomTree() : randomTree<type>::baseTree()
{}

template<class type> randomTree<type>::randomTree(randomTree& obj) : randomTree<type>::baseTree(obj)
{}

template<class type> randomTree<type>::randomTree(type& inf) : randomTree<type>::baseTree(inf)
{}

template<class type> randomTree<type>::randomTree(type* arr, int n)//����������� �� �������
{
    if (arr)
    {
        for (int i = 0; i < n; i++)
            AddNode(arr[i]);
    }
}


template<class type>randomTree<type>& randomTree<type>::operator = (randomTree<type>& obj)//������������
{
    if (obj.root)//���� ������ ������ �� �����
    {
        if (baseTree<type>::root)//���� ���� ����� ������
            *baseTree<type>::root = *(obj.root);
        else//���� ����� �����
            baseTree<type>::root = new typename randomTree<type>::Node(*(obj.root));
    }
    else
        if (baseTree<type>::root)//���� ������ ������ �����
        {
            delete baseTree<type>::root;//������� ������ ������
            baseTree<type>::root = nullptr;//������ ���������
        }
    return *this;
}

template<class type> bool randomTree<type>::AddNode(type& inf)//�������� ����
{
    typename baseTree<type>::Node** ptr = &(baseTree<type>::root);//��������� �� ������
    while (*ptr)
    {
        if (rand() % 2)//���� ��������� ����� ��� ����
            ptr = &((*ptr)->left);
        else
            ptr = &((*ptr)->right);
    }
    (*ptr) = new typename randomTree<type>::Node(inf);//������ ����
    if (*ptr)
        return true;//���� �������
    return false;
}

template<class type> bool randomTree<type>::DelNode(type& inf)//������� ����
{
    if (randomTree<type>::root)
    {
        typename randomTree<type>::Node** ptrNode = &(randomTree<type>::root);//��������� ������� �� ���������
        std::stack<typename randomTree<type>::Node**> buf_nodes;//������ ���� � ������� ����� ������� ��������� �� ������ ��������
        buf_nodes.push(nullptr);
        //� ����� while ������� ������ ���� �� ������ �� ������� ��������
        while (ptrNode && (*ptrNode)->data != inf)//���� �� ����� �� ����� ��� �� ����
        {
            if ((*ptrNode)->right)//���� ���� ������� ������
            {
                buf_nodes.push(&((*ptrNode)->right));//���������� ��� � ����
            }

            if ((*ptrNode)->left)//���� ���� ������� �����
            {
                ptrNode = &((*ptrNode)->left);//��������� �����
            }
            else //���� ��� ������� �����
            {
                ptrNode = buf_nodes.top();//����������� ��������� �� ������� ������� �����
                buf_nodes.pop();//������� ������� ������� �����
            }
        }

        if (ptrNode)//���� ����� ������ ����
        {
            typename randomTree<type>::Node* ptr_lt = nullptr, * ptr_rt = nullptr;//������� ��������� ��� ������ � ������� ��������

            if ((*ptrNode)->left)//���� ���� ����� ������� 
                ptr_lt = (*ptrNode)->left;//���������� ��� � ���������
            if ((*ptrNode)->right)//���� ���� ������ �������
            {
                if (ptr_lt)//���� ���� � ����� � ������ �������
                    ptr_rt = (*ptrNode)->right;//������������� ��������� �� ������� �������
                else//���� ���� ������ ������
                    ptr_lt = (*ptrNode)->right;//������������� ��������� �� ������� �������
            }

            delete (*ptrNode);//������� ����
            (*ptrNode) = ptr_lt;//����� ���������� �� ��� �����

            if (ptr_rt)//���� ���� ������
            {
                typename randomTree<type>::Node** ptr = &(randomTree<type>::root);//������� ��� � ��������� �����
                while (*ptr)                                                      
                {
                    if (rand() % 2)
                        ptr = &((*ptr)->left);
                    else
                        ptr = &((*ptr)->right);
                }
                (*ptr) = ptr_rt;
            }

            return true;
        }
    }
    return false;
}

template<class type> bool randomTree<type>::FindNode(type& inf)//����� ����
{
    typename randomTree<type>::Node* pointer = randomTree<type>::root;
    std::stack<typename baseTree<type>::Node*> buffer;
    buffer.push(nullptr);
    //� ����� while ������� ������ ���� �� ������ �� ������� �������� ��� �� �����
    while (pointer && pointer->data != inf)//���� �� ����� �� ����� ��� �� ����
    {
        if (pointer->right)//���� ���� ������ �������
        {
            buffer.push(pointer->right);//������� � ����
        }
        if (pointer->left)//���� ���� ����� �������
        {
            pointer = (pointer->left);//��� �����
        }
        else//���� ��� ������ �������
        {
            pointer = buffer.top();//������������� ��������� �� ������� ������� �����(��������� ������ �������)
            buffer.pop();//������ �� ����� ���� ��������
        }
    }
    if (pointer)
    {
        return true;
    }
    return false;
}
template<class type>  type randomTree<type>::FindMax()//������� ������, ���� ��������
{
    typename randomTree<type>::Node* pointer = randomTree<type>::root;
    std::stack<typename baseTree<type>::Node*> buffer;
    buffer.push(nullptr);
    type MAX;
    MAX = randomTree<type>::root->data;

    while (pointer)
    {
        if (MAX < pointer->data)
        {
            MAX = pointer->data;
        }
        if (pointer->right)
        {
            buffer.push(pointer->right);
        }
        if (pointer->left)
        {
            pointer = (pointer->left);
                    }
        else
        {
            pointer = buffer.top();
            buffer.pop();
        }
    }
    return MAX;
}
template<class type> type randomTree<type>::FindMin()//������� ������ ���� �������
{
    typename randomTree<type>::Node* pointer = randomTree<type>::root;
    std::stack<typename baseTree<type>::Node*> buffer;
    buffer.push(nullptr);
    type MIN;
    MIN = randomTree<type>::root->data;

    while (pointer)
    {
        if (pointer)
        {
            if (MIN > pointer->data)
            {
                MIN = pointer->data;
            }
        if (pointer->right)
        {
            buffer.push(pointer->right);
        }
        if (pointer->left)
        {
            pointer = (pointer->left);

        }
        else
        {

            pointer = buffer.top();
            buffer.pop();
        }

        }
    }
    return MIN;
}
