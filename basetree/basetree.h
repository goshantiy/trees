#pragma once
template <class type> class baseTree//����� ������� ������
{

protected:

    class Node//����� ����
    {
    public:
        type data;//����(���� ����������)
        Node* left, * right;//��������� �� ������� � ������ �������
        explicit Node(type& key);//����������� ���� 
        explicit Node(Node& obj);//����������� �����������
        Node& operator = (Node& obj);//���������� ������������
    };

    static int height(Node*);//������
    Node* getRoot();
    void printTree(baseTree::Node* root, int spaces) const;//������ ������
    void ClearTree(baseTree::Node*& root);
    Node* root;//������
 public:
    baseTree();//�������������
    baseTree(baseTree<type>& obj);//�����������
    baseTree(type&);//����������� � ������
    bool isEmpty();//�������� �� �������
    int Height();//��� ������
    void Clear();//������� ������
    void print();//����� ������
    //����������� ������� ����������, ��������, ������ ����
    virtual bool AddNode(type&) = 0;
    virtual bool DelNode(type&) = 0;
    virtual bool FindNode(type&) = 0;
    virtual ~baseTree();

};


template<class type> baseTree<type>::Node::Node(type &key)//�������������
{
    data = key;
    right = left = nullptr;
}

template<class type> baseTree<type>::Node::Node(Node &obj)//�����������
{
    data = obj.data;
    right = left = nullptr;
    if (obj.left)
        left = new Node(*(obj.left));
    if (obj.right)
        right = new Node(*(obj.right));
}


template<class type> typename baseTree<type>::Node &baseTree<type>::Node::operator=(Node& obj)//���������� ������������
{
    data = obj.data;
    if (obj.left)//���� � ������� ���� ����� �������
    {
        if (left)//���� � ���� ���� ����� �������
        {
            delete left;//�������
            *left = *(obj.left);//������������� ������� �������
        }
        else
            left = new Node(*(obj.left));//���� � ���� ��� ������� �������
    }
    else
        if (left)//���� � ������� ��� ������� � � ���� ����
        {
            delete left;
            left = nullptr;
        }
    if (obj.right)//���� � ������� ���� ������ �������
    {
        if (right)//���� � ���� ���� ������ �������
        {
            delete right;//�������
            *right = *(obj.right);//������������� ������� �������
        }
        else
            right = new Node(*(obj.right));//���� � ���� ��� ������� �������
    }
    else
        if (right)//���� � ������� ��� ������� � � ���� ����
        {
            delete right;
            right = nullptr;
        }
    return *this;
}

template<class type> baseTree<type>::baseTree()//�������������
{
    root = nullptr;

}

template<class type> baseTree<type>::baseTree(baseTree<type>& obj)//����������� �����������
{
    root = new Node(obj.root);
 
}

template<class type> baseTree<type>::baseTree(type& key)//����������� � ������
{
    root = new Node(key);
}

template<class type> baseTree<type>::~baseTree()//����������
{
    ClearTree(root);
    delete root;
    root  = nullptr;
}

template<class type> bool baseTree<type>::isEmpty()//�������� �� �������
{
    if (root)
        return true;
    else
        return false;
}

template<class type> int baseTree<type>::Height()//����� ������ ������
{
    return height(this->root);
}

template<class type> void baseTree<type>::Clear()//�������
{
    ClearTree(root);
}



template<class type> void baseTree<type>::ClearTree(baseTree::Node*& Root)//������� ������
{
    if (Root)
    {
        ClearTree(Root->left); 
        ClearTree(Root->right);
        delete Root;
        Root = nullptr;
    }
}

template<class type> int baseTree<type>::height(Node* nd)//����� ������
{
    if (nd)
    {
        return (std::max(height(nd->left), height(nd->right)) + 1);//���������� ���� ������ 
    }
    return 0;
}

template<class type> typename baseTree<type>::Node* baseTree<type>::getRoot()//���������� ������
{
    return root;
}
template<class type> void baseTree<type>::printTree(baseTree::Node* nod, int spaces) const//����������� ����� ������
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