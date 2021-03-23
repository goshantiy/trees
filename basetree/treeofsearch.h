#pragma once
#include "basetree.h"
template<class type> class searchTree :public baseTree<type>//класс дерево поиска, наследуем базовое дерево
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

template<class type> searchTree<type>::searchTree(type* arr, int n)//конструктор из массива размерности n
{
    baseTree<type>::root = nullptr;
    if (arr)
    {
        for (int i = 0; i < n; i++)
            AddNode(arr[i]);
    }
}

template<class type> searchTree<type>& searchTree<type>::operator = (searchTree<type>& obj)//присваивание
{
    if (obj.root)//проверка корня
    {//если дерево не пустое
        if (baseTree<type>::root)//если левое не пустое 
            *baseTree<type>::root = *(obj.root);
        else//если пустое
            baseTree<type>::root = new typename searchTree<type>::Node(*(obj.root));
    }
    else//если дерево справа пустое
        if (baseTree<type>::root)
        {
            delete baseTree<type>::root;//очищаем память
            baseTree<type>::root = nullptr;//пустой указатель
        }

    return *this;
}

template<class type> bool searchTree<type>::AddNode(type& key)//добавить узел
{
    typename searchTree<type>::Node** ptr = &(baseTree<type>::root);//указатель на корень
    while (*ptr)
    {
        if ((*ptr)->data > key)//если вставляемый ключ больше влево
            ptr = &((*ptr)->left);
        else
            ptr = &((*ptr)->right);//иначе вправо
    }
    *ptr = new typename searchTree<type>::Node(key);//создаем узел
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
    if (ptr)  //если есть дерево
    {
        if (!ptr->left)//проверяем левого потомка
            replace = ptr->right;
        else
            if (!ptr->right)//проверяем правого
                replace = ptr->left;
            else
            {
                typename searchTree<type>::Node* rep_parent = ptr;
                replace = ptr->left;
                while (replace->right) //ищем узел для замены (в левом поддереве самый правый узел)
                {
                    rep_parent= replace;
                    replace = replace->right;
                }
                if (ptr != rep_parent)//если удаляемый не сын замещаемого, то переобозначаем указатели
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


template<class type> bool searchTree<type>::FindNode(type& inf)//поиск узла
{
    typename searchTree<type>::Node* ptr = baseTree<type>::root;//указатель

    while (ptr && ptr->data != inf)//пока не нашли или не дошли до конца
    {
        if (ptr->data > inf)//если число больше ключа то в левое поддерево
            ptr = ptr->left;
        else//иначе в правое
            ptr = ptr->right;
    }

    if (!ptr)
        return false;
    return true;
}


template<class type> typename searchTree<type>::Node** searchTree<type>::SearchNode(type& inf, typename searchTree<type>::Node*& found_node)
{//поиск узла и родителя
    typename searchTree<type>::Node** parent_node = &(baseTree<type>::root);//указатель на родителя
    found_node = baseTree<type>::root;//указатель
    while (found_node && found_node->data != inf)//пока не нашли или не дошли до конца
    {
        if (found_node->data > inf)//если число больше ключа то в левое поддерево
        {
            parent_node = &(found_node->left);
            found_node = found_node->left;
        }
        else//иначе в правое
        {
            parent_node = &(found_node->right);
            found_node = found_node->right;
        }
    }

    if (!found_node)
        parent_node = nullptr;

    return parent_node;
}

