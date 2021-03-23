#pragma once
#include "baseTree.h"
#include <stack>

template<class type> class randomTree : public baseTree<type>//класс случайно дерево, наследуем базовое 
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

template<class type> randomTree<type>::randomTree(type* arr, int n)//конструктор из массива
{
    if (arr)
    {
        for (int i = 0; i < n; i++)
            AddNode(arr[i]);
    }
}


template<class type>randomTree<type>& randomTree<type>::operator = (randomTree<type>& obj)//присваивание
{
    if (obj.root)//если правое дерево не пусто
    {
        if (baseTree<type>::root)//если есть левое дерево
            *baseTree<type>::root = *(obj.root);
        else//если левое пусто
            baseTree<type>::root = new typename randomTree<type>::Node(*(obj.root));
    }
    else
        if (baseTree<type>::root)//если правое дерево пусто
        {
            delete baseTree<type>::root;//очищаем память левого
            baseTree<type>::root = nullptr;//пустой указатель
        }
    return *this;
}

template<class type> bool randomTree<type>::AddNode(type& inf)//добавить узел
{
    typename baseTree<type>::Node** ptr = &(baseTree<type>::root);//указатель на корень
    while (*ptr)
    {
        if (rand() % 2)//ищем случайное место для узла
            ptr = &((*ptr)->left);
        else
            ptr = &((*ptr)->right);
    }
    (*ptr) = new typename randomTree<type>::Node(inf);//создаём узел
    if (*ptr)
        return true;//если создали
    return false;
}

template<class type> bool randomTree<type>::DelNode(type& inf)//удалить узел
{
    if (randomTree<type>::root)
    {
        typename randomTree<type>::Node** ptrNode = &(randomTree<type>::root);//указатель которым мы двигаемся
        std::stack<typename randomTree<type>::Node**> buf_nodes;//создаём стек в котором будем хранить указатели на правых потомков
        buf_nodes.push(nullptr);
        //в цикле while обходим дерево пока не дойдем до нужного элемента
        while (ptrNode && (*ptrNode)->data != inf)//пока не дошли до конца или до узла
        {
            if ((*ptrNode)->right)//если есть потомок справа
            {
                buf_nodes.push(&((*ptrNode)->right));//записываем его в стек
            }

            if ((*ptrNode)->left)//если есть потомок слева
            {
                ptrNode = &((*ptrNode)->left);//двигаемся влево
            }
            else //если нет потомка слева
            {
                ptrNode = buf_nodes.top();//передвигаем указатель на верхний элемент стека
                buf_nodes.pop();//удаляем верхний элемент стека
            }
        }

        if (ptrNode)//если нашли нужный узел
        {
            typename randomTree<type>::Node* ptr_lt = nullptr, * ptr_rt = nullptr;//создаем указатели для левого и правого потомков

            if ((*ptrNode)->left)//есть есть левый потомок 
                ptr_lt = (*ptrNode)->left;//записываем его в указатель
            if ((*ptrNode)->right)//если есть правый потомок
            {
                if (ptr_lt)//если есть и левый и правый потомок
                    ptr_rt = (*ptrNode)->right;//устанавливаем указатель на правого потомка
                else//если есть только правый
                    ptr_lt = (*ptrNode)->right;//устанавливаем указатель на правого потомка
            }

            delete (*ptrNode);//удаляем узел
            (*ptrNode) = ptr_lt;//левый становится на его место

            if (ptr_rt)//если есть правый
            {
                typename randomTree<type>::Node** ptr = &(randomTree<type>::root);//добавим его в рандомное место
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

template<class type> bool randomTree<type>::FindNode(type& inf)//поиск узла
{
    typename randomTree<type>::Node* pointer = randomTree<type>::root;
    std::stack<typename baseTree<type>::Node*> buffer;
    buffer.push(nullptr);
    //в цикле while обходим дерево пока не дойдем до нужного элемента или до конца
    while (pointer && pointer->data != inf)//пока не дошли до конца или до узла
    {
        if (pointer->right)//если есть правый потомок
        {
            buffer.push(pointer->right);//запишем в стек
        }
        if (pointer->left)//если есть левый потомок
        {
            pointer = (pointer->left);//идём влево
        }
        else//если нет левого потомка
        {
            pointer = buffer.top();//устанавливаем указатель на верхний элемент стека(последний правый потомок)
            buffer.pop();//удалим из стека этот указатль
        }
    }
    if (pointer)
    {
        return true;
    }
    return false;
}
template<class type>  type randomTree<type>::FindMax()//обходим дерево, ищем максимум
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
template<class type> type randomTree<type>::FindMin()//обходим дерево ищем минимум
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
