#pragma once
template <class type> class baseTree//класс базовое дерево
{

protected:

    class Node//класс узел
    {
    public:
        type data;//ключ(поле информации)
        Node* left, * right;//указатели на правого и левого потомка
        explicit Node(type& key);//конструктор узла 
        explicit Node(Node& obj);//конструктор копирования
        Node& operator = (Node& obj);//перегрузка присваивания
    };

    static int height(Node*);//высота
    Node* getRoot();
    void printTree(baseTree::Node* root, int spaces) const;//печать дерева
    void ClearTree(baseTree::Node*& root);
    Node* root;//корень
 public:
    baseTree();//инициализация
    baseTree(baseTree<type>& obj);//копирование
    baseTree(type&);//конструктор с ключем
    bool isEmpty();//проверка на пустоту
    int Height();//вес дерева
    void Clear();//очистка дерева
    void print();//вывод дерева
    //виртуальные функции добавления, удаления, поиска узла
    virtual bool AddNode(type&) = 0;
    virtual bool DelNode(type&) = 0;
    virtual bool FindNode(type&) = 0;
    virtual ~baseTree();

};


template<class type> baseTree<type>::Node::Node(type &key)//инициализация
{
    data = key;
    right = left = nullptr;
}

template<class type> baseTree<type>::Node::Node(Node &obj)//копирование
{
    data = obj.data;
    right = left = nullptr;
    if (obj.left)
        left = new Node(*(obj.left));
    if (obj.right)
        right = new Node(*(obj.right));
}


template<class type> typename baseTree<type>::Node &baseTree<type>::Node::operator=(Node& obj)//перегрузка присваивания
{
    data = obj.data;
    if (obj.left)//если у обьекта есть левый потомок
    {
        if (left)//если у узла есть левый потомок
        {
            delete left;//удаляем
            *left = *(obj.left);//устанавливаем потомок обьекта
        }
        else
            left = new Node(*(obj.left));//если у узла нет потомка создаем
    }
    else
        if (left)//если у обьекта нет потомка а у узла есть
        {
            delete left;
            left = nullptr;
        }
    if (obj.right)//если у обьекта есть правый потомок
    {
        if (right)//если у узла есть правый потомок
        {
            delete right;//удаляем
            *right = *(obj.right);//устанавливаем потомок обьекта
        }
        else
            right = new Node(*(obj.right));//если у узла нет потомка создаем
    }
    else
        if (right)//если у обьекта нет потомка а у узла есть
        {
            delete right;
            right = nullptr;
        }
    return *this;
}

template<class type> baseTree<type>::baseTree()//инициализация
{
    root = nullptr;

}

template<class type> baseTree<type>::baseTree(baseTree<type>& obj)//конструктор копирования
{
    root = new Node(obj.root);
 
}

template<class type> baseTree<type>::baseTree(type& key)//конструктор с ключем
{
    root = new Node(key);
}

template<class type> baseTree<type>::~baseTree()//деструктор
{
    ClearTree(root);
    delete root;
    root  = nullptr;
}

template<class type> bool baseTree<type>::isEmpty()//проверка на пустоту
{
    if (root)
        return true;
    else
        return false;
}

template<class type> int baseTree<type>::Height()//поиск высоты дерева
{
    return height(this->root);
}

template<class type> void baseTree<type>::Clear()//очистка
{
    ClearTree(root);
}



template<class type> void baseTree<type>::ClearTree(baseTree::Node*& Root)//очистка дерева
{
    if (Root)
    {
        ClearTree(Root->left); 
        ClearTree(Root->right);
        delete Root;
        Root = nullptr;
    }
}

template<class type> int baseTree<type>::height(Node* nd)//поиск высоты
{
    if (nd)
    {
        return (std::max(height(nd->left), height(nd->right)) + 1);//рекурсивно ищем высоту 
    }
    return 0;
}

template<class type> typename baseTree<type>::Node* baseTree<type>::getRoot()//возвращает корень
{
    return root;
}
template<class type> void baseTree<type>::printTree(baseTree::Node* nod, int spaces) const//рекурсивный вывод дерева
{
    while (nod)
    {
        printTree(nod->right, spaces + 5);

        for (int i = 1; i < spaces; ++i)
            std::cout << ' ';

        std::cout << nod->data << std::endl;

        nod = nod->left;
        spaces += 5;
    }
}
template<class type> void baseTree<type>::print()
{
    printTree(root, 1);
}