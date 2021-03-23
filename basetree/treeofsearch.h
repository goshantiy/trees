#pragma once
#include "basetree.h"
template<class type> class searchTree :public baseTree<type>//����� ������ ������, ��������� ������� ������
{
public:

    searchTree();
    searchTree(searchTree<type>&);
    searchTree(type&);
    searchTree(type*, int);

    searchTree<type>& operator = (searchTree<type>&);

    virtual bool AddNode(type&);
    virtual bool DelNode(type&);
    virtual bool FindNode(type&);

private:
typename searchTree<type>::Node** SearchNode(type&, typename searchTree<type>::Node*&);
};

template<class type> searchTree<type>::searchTree() : searchTree<type>::baseTree()
{
}

template<class type> searchTree<type>::searchTree(searchTree& obj) : searchTree<type>::baseTree(obj)
{
}

template<class type> searchTree<type>::searchTree(type& inf) : searchTree<type>::baseTree(inf)
{
}

template<class type> searchTree<type>::searchTree(type* arr, int n)//����������� �� ������� ����������� n
{
    baseTree<type>::root = nullptr;
    if (arr)
    {
        for (int i = 0; i < n; i++)
            AddNode(arr[i]);
    }
}

template<class type> searchTree<type>& searchTree<type>::operator = (searchTree<type>& obj)//������������
{
    if (obj.root)//�������� �����
    {//���� ������ �� ������
        if (baseTree<type>::root)//���� ����� �� ������ 
            *baseTree<type>::root = *(obj.root);
        else//���� ������
            baseTree<type>::root = new typename searchTree<type>::Node(*(obj.root));
    }
    else//���� ������ ������ ������
        if (baseTree<type>::root)
        {
            delete baseTree<type>::root;//������� ������
            baseTree<type>::root = nullptr;//������ ���������
        }

    return *this;
}

template<class type> bool searchTree<type>::AddNode(type& key)//�������� ����
{
    typename searchTree<type>::Node** ptr = &(baseTree<type>::root);//��������� �� ������
    while (*ptr)
    {
        if ((*ptr)->data > key)//���� ����������� ���� ������ �����
            ptr = &((*ptr)->left);
        else
            ptr = &((*ptr)->right);//����� ������
    }
    *ptr = new typename searchTree<type>::Node(key);//������� ����
    if (*ptr)
        return true;
    return false;
}

template<class type> bool searchTree<type>::DelNode(type& inf)
{
    typename searchTree<type>::Node* ptr, ** parent, * replace;
    ptr = nullptr;
    replace = nullptr;
    parent = SearchNode(inf, ptr);
    if (ptr)  //���� ���� ������
    {
        if (!ptr->left)//��������� ������ �������
            replace = ptr->right;
        else
            if (!ptr->right)//��������� �������
                replace = ptr->left;
            else
            {
                typename searchTree<type>::Node* rep_parent = ptr;
                replace = ptr->left;
                while (replace->right) //���� ���� ��� ������ (� ����� ��������� ����� ������ ����)
                {
                    rep_parent= replace;
                    replace = replace->right;
                }
                if (ptr != rep_parent)//���� ��������� �� ��� �����������, �� �������������� ���������
                {
                    rep_parent->right = replace->left;
                    replace->left = ptr->left;
                }
                replace->right = ptr->right;
            }
        *parent = replace;
        ptr->left = ptr->right = nullptr;
        delete ptr;
        return true;
    }
    return false;
}


template<class type> bool searchTree<type>::FindNode(type& inf)//����� ����
{
    typename searchTree<type>::Node* ptr = baseTree<type>::root;//���������

    while (ptr && ptr->data != inf)//���� �� ����� ��� �� ����� �� �����
    {
        if (ptr->data > inf)//���� ����� ������ ����� �� � ����� ���������
            ptr = ptr->left;
        else//����� � ������
            ptr = ptr->right;
    }

    if (!ptr)
        return false;
    return true;
}


template<class type> typename searchTree<type>::Node** searchTree<type>::SearchNode(type& inf, typename searchTree<type>::Node*& found_node)
{//����� ���� � ��������
    typename searchTree<type>::Node** parent_node = &(baseTree<type>::root);//��������� �� ��������
    found_node = baseTree<type>::root;//���������
    while (found_node && found_node->data != inf)//���� �� ����� ��� �� ����� �� �����
    {
        if (found_node->data > inf)//���� ����� ������ ����� �� � ����� ���������
        {
            parent_node = &(found_node->left);
            found_node = found_node->left;
        }
        else//����� � ������
        {
            parent_node = &(found_node->right);
            found_node = found_node->right;
        }
    }

    if (!found_node)
        parent_node = nullptr;

    return parent_node;
}

