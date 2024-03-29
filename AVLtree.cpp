#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

template <class A> class Node
{
private:
	A data;
	Node <A> * l, * r;
	int h; 
public:
	template <class T> friend class AVLTree;
	Node() : data(0), l(NULL), r(NULL), h(0) {}
	Node (const A i =0) : data(i), l(NULL), r(NULL), h(0) {}
	Node (const Node & x): data(x.data), l(x.l), r(x.r), h(x.h) {}
	/*~Node()
	{
		if (l)	delete l;
		if (r) delete r;
	}*/
};


template<class T> class AVLTree
{
public:
	AVLTree() : root(NULL) {}
	void Insert(const  T key)
	{
		root = _insert(root, key);
	}
	
	void Display()
	{
		_display(root);
	}
	
	void Delete()
	{
		_delete(root);
	}
	
	void ViewLevels()
    {
        for (int i = 0; i < _height(root); i++)
        {
            viewTreeLevel(i,root);
            cout << endl;
        }
    }
	
	Node <T> * Find(AVLTree t,int key)
	{
		
		return _find(t.root, key);
	}
	
	
	
	
	

private:
	Node<T> * root;
	
	int _height(const Node <T> * pNode)
	{
		//t++;
		return pNode ? pNode->h : 0;
	}
	
	int _balance(const Node <T> * pNode)
	{
		return pNode ? (pNode->l? pNode->l->h:0) - (pNode->r? pNode->r->h:0) : 0;
	}
	
	Node <T> * _l_rotation(Node <T> * pNode)
	{
		Node <T> * tmpNode = pNode->r;
		pNode->r = tmpNode->l;
		tmpNode->l = pNode;
		pNode->h = max(_height(pNode->l),_height(pNode->r))+1;
		tmpNode->h = max(_height(tmpNode->l),_height(tmpNode->r))+1;
		return tmpNode;
	}
	
	Node <T> * _r_rotation(Node <T> * pNode)
	{
		Node <T> * tmpNode = pNode->l;
		pNode->l = tmpNode->r;
		tmpNode->r = pNode;
		pNode->h = max(_height(pNode->l),_height(pNode->r))+1;
		tmpNode->h = max(_height(tmpNode->l),_height(tmpNode->r))+1;
		return tmpNode;
	}
	
	Node <T> * _R_rotation(Node <T> * pNode)
	{
		Node <T> * tmpNode = pNode->l;
		pNode->l = _l_rotation(tmpNode);
		return _r_rotation(pNode);
	}
	
	Node <T> * _L_rotation(Node <T> * pNode)
	{
		Node <T> * tmpNode = pNode->r;
		pNode->r = _r_rotation(tmpNode);
		return _l_rotation(pNode);
	}
	
	Node <T> * _balancing(Node <T> * pNode)
	{
		int b_factor = _balance(pNode);
		if (b_factor > 1)
		{
			if (_balance(pNode->l) >= 0) pNode = _r_rotation(pNode);
			else pNode = _R_rotation(pNode);
		}
		else
		{
			if (b_factor < -1)
			{
				if (_balance(pNode->r) <= 0) pNode = _l_rotation(pNode);
				else pNode = _L_rotation(pNode);
			}
		}
		return pNode;
	}
	
	Node <T> * _insert(Node <T> * pNode, const  T key)
	{
		if (!pNode) return new Node<T>(key);
		else if (key < pNode->data)
		{
			pNode->l = _insert(pNode->l, key);
			pNode = _balancing(pNode);
		}
		else if (key > pNode->data)
		{
			pNode->r = _insert(pNode->r, key);
			pNode = _balancing(pNode);
		}
		else
		{
			//Already existed
			return 0;
		}
		pNode->h = max(_height(pNode->l),_height(pNode->r))+1;
		return pNode;
	}
	
	void _display(Node <T> * pNode)
	{
		if (!pNode) return;
		_display(pNode->l);
		cout << pNode->data << ' ';
		_display(pNode->r);
	}
	
	/*	void _delete(Node <T> * pNode)
	{
		if (!pNode) return;
		if(pNode->l != NULL)
		{
			_delete(pNode->l);
		}
		if(pNode->r != NULL)
		{
			_delete(pNode->r);
		}
		delete pNode;
		//_remove(pNode, pNode->data);
	}*/
	
	void _delete(Node <T> * pNode)
	{
		if(pNode != NULL)
		{
			if(pNode -> l != NULL)
			{
				_delete(pNode -> l);
			}
			if(pNode -> r != NULL)
			{
				_delete(pNode -> r);
			}
			delete pNode;
		} 
	}
	
	Node <T> * _find_min(const Node < T> * pNode)
	{
		return pNode->l ? _find_min(pNode->l) : pNode;
	}
	
	Node <T> * _find_max(const Node < T> * pNode)
	{
		return pNode->r ? _find_max(pNode->r) : pNode;
	}
	
	Node <T> * _find(Node <T> * pNode, const  T key)
	{
		if (pNode == NULL) return NULL;
		else if (pNode->data == key) return pNode;
		else return pNode->data > key ? _find(pNode->l, key) : _find(pNode->r, key);
	}
	
	void _remove(Node <T> * pNode, const  T key)
	{
		Node<T> * tmpNode = _find(pNode, key);
		if (tmpNode == NULL) return pNode;
		else
		{
			if (tmpNode->l && tmpNode->r)
			{
				//Left and right subtree
				Node<T> * maxTmpNode = _find_min(tmpNode);
				tmpNode->data = maxTmpNode->data;
				delete maxTmpNode;
			}
			else
			{
				if (tmpNode->l)
				{
					//only left subtree
					Node<T> * leftTmpNode = tmpNode->l;
					tmpNode->data = leftTmpNode->data;
					tmpNode->l = leftTmpNode->l;
					tmpNode->r = leftTmpNode->r;
					delete leftTmpNode;

				}
				else
				{
					if (tmpNode->r)
					{
						//only right subtree
						Node<T> * rightTmpNode = tmpNode->r;
						tmpNode->data = rightTmpNode->data;
						tmpNode->l = rightTmpNode->l;
						tmpNode->r = rightTmpNode->r;
						delete rightTmpNode;
					}
					else
					{
						//no subtree
						delete tmpNode;
					}


				}
			}
		}
	}
	
	void viewTreeLevel(int i, const Node<T> * pNode)
    {
        if (i == 0) cout << pNode->data << ' ';
        else
        {
            if (pNode->l) viewTreeLevel(i - 1, pNode->l);
            if (pNode->r) viewTreeLevel(i - 1, pNode->r);
        }
    }
};



int main()
{
	AVLTree<int> t;
    t.Insert(42);
    for(int i = 0; i < 10; ++i)
        t.Insert(i);
    t.ViewLevels();
	cout<<t.Find(t, 42)<<endl;
	
	//t.ViewLevels();
	t.Delete();
	//t.ViewLevels();
}
