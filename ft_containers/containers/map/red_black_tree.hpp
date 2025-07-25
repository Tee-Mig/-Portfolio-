#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include "utils.hpp"
#include "MapIterator.hpp"
#include "MapReverseIterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> >,
				class NodeAlloc = std::allocator<Node<Key, T> >	>
	class RedBlackTree
	{
		public:
			typedef Key		key_type;
			typedef T		mapped_type;
			typedef	ft::pair<const key_type, mapped_type> pair_type;
			typedef	ft::pair<key_type, mapped_type> value_type;
			typedef	value_type &reference;
			typedef Alloc		allocator_pair;
			typedef NodeAlloc		allocator_node;
			typedef	Node<key_type, mapped_type>		node;
			typedef Node<key_type, mapped_type>*	nodePointer;
			typedef std::size_t size_type;
			typedef Compare		key_compare;
			typedef typename ft::MapIterator<key_type, mapped_type, false> iterator;
			typedef typename ft::MapIterator<key_type, mapped_type, true> const_iterator;
			typedef typename ft::MapReverseIterator<key_type, mapped_type, false> reverse_iterator;
			typedef typename ft::MapReverseIterator<key_type, mapped_type, true> const_reverse_iterator;

			RedBlackTree(const allocator_node &alloc = allocator_node(), const value_type &val = value_type(), const key_compare & comp = key_compare())
			: _alloc_node(alloc), _root(NULL), _begin(NULL), _end(NULL), _size(0), _comp(comp)
			{
				(void)val;
				// _end = _alloc_node.allocate(1);
				// node tmp(val, _end->parent, _end->left, _end->right, RED);
				// _alloc_node.construct(_end, tmp);
			}
			~RedBlackTree()
			{
				free_tree(_root);
				// _alloc_node.destroy(_end);
				// _alloc_node.deallocate(_end, 1);
			}

			void free_tree(nodePointer _root)
			{
				if (_root == NULL)
					return ;
				free_tree(_root->left);
				free_tree(_root->right);
				if (_root)
				{
					_alloc_node.destroy(_root);
					_alloc_node.deallocate(_root, 1);
				}
			}

			void display_tree()
			{
				display(_root);
			}

			void display(nodePointer elem)
			{
				(void)elem;
				if (_root == NULL)
				{
					return ;
				}
				if (elem)
				{
					if (elem->parent)
					{
						std::cout << elem->parent->_pair.first << " / " << elem->parent->_pair.second << "(";
						if (elem->parent->color == 0)
							std::cout << "red";
						else
							std::cout << "black";
						 std::cout << ")" << " -> ";
					}
					if (elem)
					{
						std::cout << elem->_pair.first << " / " << elem->_pair.second << "(";
						if (elem->color == 0)
							std::cout << "red";
						else
							std::cout << "black";
						std::cout << ")" << std::endl;
					}
					if (elem->left)
						display(elem->left);
					if (elem->right)
						display(elem->right);
				}
			}

			iterator begin()
			{
				iterator tmp(_begin, _end);
				tmp.getBegin(_size);
				return tmp;
			}
			iterator end()
			{
				iterator tmp(_begin, _end);
				tmp.getEnd();
				tmp.setIsEnd(1);
				return tmp;
			}

			const_iterator const_begin() const
			{
				const_iterator tmp(_begin, _end);
				tmp.getBegin(_size);
				return tmp;
			}
			const_iterator const_end() const
			{
				const_iterator tmp(_begin, _end);
				tmp.getEnd();
				tmp.setIsEnd(1);
				return tmp;
			}

			reverse_iterator rbegin()
			{
				reverse_iterator tmp(_begin, _end);
				tmp.getrBegin(_size);
				return tmp;
			}
			reverse_iterator rend()
			{
				reverse_iterator tmp(_begin, _end);
				tmp.getrEnd();
				tmp.setEnd(1);
				return tmp;
			}
			const_reverse_iterator const_rbegin() const
			{
				const_reverse_iterator tmp(_begin, _end);
				tmp.getrBegin(_size);
				return tmp;
			}
			const_reverse_iterator const_rend() const
			{
				const_reverse_iterator tmp(_begin, _end);
				tmp.getrEnd();
				tmp.setEnd(1);
				return tmp;
			}

			nodePointer search_key(key_type key_val)
			{
				
				if (_root == NULL)
				{
					return NULL;
				}
				nodePointer p;
				p = _root;
				int found = 0;
				while (p != NULL && found == 0)
				{
					if (p->_pair.first == key_val)
						found = 1;
					if (found == 0)
					{
						if (_comp(p->_pair.first, key_val))
							p = p->right;
						else
							p = p->left;
					}
				}
				if (found == 0)
					return NULL;
				else
					return p;
			}

			void deleteNode(const key_type key_val)
			{	
				if (_root == NULL)
				{
					return ;
				}
				nodePointer p = _root;
				nodePointer y, q;
				y = q = NULL;
				while (p != NULL)
				{
					if (p->_pair.first == key_val)
						break ;
					else
					{
						if (_comp(p->_pair.first, key_val))
							p = p->right;
						else
							p = p->left;
					}
				}
				if (p == NULL)
				{
					std::cout << "Element " << key_val << " not found" << std::endl;
					return ;
				}
				else
				{
					// std::cout << "element TEST ====== " << p->_pair.first << " | " << p->_pair.second << std::endl;
					// return ;

					// std::cout << "Deleted Element: " << p->_pair.first << std::endl;
					// std::cout << "Colour: ";

					// if(p->color == BLACK)
					// 	std::cout <<"Black" << std::endl;
					// else
					// 	std::cout <<"Red" << std::endl;

					// if(p->parent != NULL)
					// 	std::cout << "Parent: " << p->parent->_pair.first << std::endl;
					// else
					// 	std::cout << "There is no parent of the node." << std::endl;
					// if(p->right != NULL)
					// 	std::cout << "Right Child: " << p->right->_pair.first;
					// else
					// 	std::cout << "There is no right child of the node.  " << std::endl;
					// if(p->left != NULL)
					// 	std::cout << "Left Child: " << p->left->_pair.first;
					// else
					// 	std::cout << "There is no left child of the node.  " << std::endl;
					// std::cout << "Node Deleted." << std::endl;
					if (p->left == NULL || p->right == NULL)
					{
						y = p;
					}
					else
						y = successor(p);
					if (y->left != NULL)
						q = y->left;
					else
					{
						if (y->right != NULL)
							q = y->right;
						else
							q = NULL;
					}
					if (q != NULL)
						q->parent = y->parent;
					if (y->parent == NULL)
						_root = q;
					else
					{
						if (y == y->parent->left)
							y->parent->left = q;
						else
							y->parent->right = q;
					}
					if (y != p)
					{
						p->color = y->color;
						p->_pair = y->_pair;
					}
					if (y->color == BLACK)
						delfix(q);
					// if (y == _begin)
					// 	_begin = successor(_begin);
					// if (y == _end)
					// 	_end = predecessor(_end);
					update_begin_end();
					_alloc_node.destroy(y);
					_alloc_node.deallocate(y, 1);
					_size--;
				}
				// if (_root)
				// 	_root->color=BLACK;
			}

			void delfix(nodePointer _node)
			{
				nodePointer s;
				if (_node != NULL)
				{
					while(_node != _root && _node->color == BLACK)
					{
						if(_node->parent->left == _node)
						{
							s = _node->parent->right;
							if(s->color == RED)
							{
								s->color = BLACK;
								_node->parent->color = RED;
								rotateLeft(_node->parent);
								s = _node->parent->right;
							}
							if(s->right && s->right->color == BLACK && s->left && s->left->color == BLACK)
							{
								_node->color = RED;
								_node = _node->parent;
							}
							else
							{
								if (s->right)
								{
									if(s->right->color ==  BLACK)
									{
										// s->left->color == BLACK;
										s->color = RED;
										rotateRight(s);
										s = _node->parent->right;
									}
									s->color = _node->parent->color;
									_node->parent->color = BLACK;
									s->right->color = BLACK;
									rotateLeft(_node->parent);
								}
								_node = _root;
							}
						}
						else
						{
							s = _node->parent->left;
							if(s->color == RED)
							{
									s->color = BLACK;
									_node->parent->color = RED;
									rotateRight(_node->parent);
									s = _node->parent->left;
							}
							if(s->left && s->left->color == BLACK && s->right && s->right->color == BLACK)
							{
								s->color = RED;
								_node = _node->parent;
							}
							else
							{
								if (s->left)
								{
									if(s->left->color == BLACK)
									{
										s->right->color = BLACK;
										s->color = RED;
										rotateLeft(s);
										s = _node->parent->left;
									}
									s->color = _node->parent->color;
									_node->parent->color = BLACK;
									s->left->color = BLACK;
									rotateRight(_node->parent);
								}
								_node = _root;
							}
						}
						_node->color = BLACK;
						_root->color = BLACK;
					}
				// _node->color = BLACK;
				}
			}

			nodePointer successor(nodePointer node)
			{
				nodePointer y = NULL;
				if (node->left != NULL)
				{
					y = node->left;
					while (y->right != NULL)
						y = y->right;
				}
				else
				{
					y = node->right;
					while (y->left != NULL)
						y = y->left;
				}
				return y;
			}

			nodePointer predecessor(nodePointer node)
			{
				nodePointer y = NULL;
				if (node->right != NULL)
				{
					y = node->right;
					while (y->left != NULL)
						y = y->left;
				}
				else
				{
					y = node->left;
					while (y->right != NULL)
						y = y->right;
				}
				return y;
			}

			nodePointer search_pair(const value_type &_pair)
			{
				node key2(_pair);
				nodePointer key = &key2;
				
				if (_root == NULL)
				{
					// std::cout << "Empty tree" << std::endl;
					return NULL;
				}
				nodePointer p;
				p = _root;
				int found = 0;
				while (p != NULL && found == 0)
				{
					if (p->_pair.first == key->_pair.first)
						found = 1;
					if (found == 0)
					{
						if (_comp(p->_pair.first, key->_pair.first))
							p = p->right;
						else
							p = p->left;
					}
				}
				if (found == 0)
					return NULL;
				else
					return p;
			}

			nodePointer insert(const value_type &_pair)
			{
				nodePointer val_exists = search_pair(_pair);
				if (val_exists != NULL)
				{
					std::cout << "key already exists" << std::endl;
					return val_exists;
				}

				nodePointer root_tmp, it;
				nodePointer new_node = _alloc_node.allocate(1);
				_alloc_node.construct(new_node, node(_pair));
				(void)it;
				(void)root_tmp;
				_size++;
				if (_root == NULL)
				{
					new_node->color = BLACK;
					_root = new_node;
					_begin = _root;
					_end = _root;
				}
				else
				{
					root_tmp = _root;
					it = NULL;
					while (root_tmp != NULL)
					{
						it = root_tmp;
						if (_comp(_pair.first, root_tmp->_pair.first))
							root_tmp = root_tmp->left;
						else
							root_tmp = root_tmp->right;
					}
					new_node->parent = it;
					if (_comp(it->_pair.first, _pair.first))
						it->right = new_node;
					else
						it->left = new_node;
					
					insert_fix(new_node);
					// update_begin_end();
					// std::cout << "new node = " << new_node->_pair.first << std::endl;
					if (_comp(new_node->_pair.first, _begin->_pair.first))
					{
						// std::cout << "nouveau begin qui est: " << new_node->_pair.first << std::endl;
						// std::cout << "nouvrau begin! ancien: " << _begin->_pair.first << std::endl;
						_begin = new_node;
					}
					if (_comp(_end->_pair.first, new_node->_pair.first))
					{
						// std::cout << "nouveau end qui est: " << new_node->_pair.first << std::endl;
						// std::cout << "nouvrau end! ancien: " << _end->_pair.first << std::endl;
						_end = new_node;
					}
				}
				return (new_node);
			}

			void update_begin_end()
			{
				if (_root == NULL)
				{
					_begin = NULL;
					_end = NULL;
					return ;
				}
				nodePointer root_tmp(_root);
				while (root_tmp->left != NULL)
					root_tmp = root_tmp->left;
				_begin = root_tmp;
				nodePointer root_tmp2(_root);
				while (root_tmp2->right != NULL)
					root_tmp2 = root_tmp2->right;
				_end = root_tmp2;
			}

			nodePointer getLeftMost(nodePointer _node)
			{
				while (_node->left != NULL)
					_node = _node->left;
				return _node;
			}

			nodePointer getRightMost(nodePointer _node)
			{
				while (_node->right != NULL)
					_node = _node->right;
				return _node;
			}

			void rotateLeft(nodePointer pt)
			{
				if (pt == NULL)
					return ;
				nodePointer pt_right = pt->right;

				pt->right = pt_right->left;

				if (pt->right != NULL)
					pt->right->parent = pt;
				
				pt_right->parent = pt->parent;

				if (pt->parent == NULL)
					_root = pt_right;
				else if (pt == pt->parent->left)
					pt->parent->left = pt_right;
				else
					pt->parent->right = pt_right;

				pt_right->left = pt;
				pt->parent = pt_right;
			}

			void rotateRight(nodePointer pt)
			{
				if (pt == NULL)
					return ;
				nodePointer pt_left = pt->left;

				pt->left = pt_left->right;

				if (pt->left != NULL)
					pt->left->parent = pt;
				
				pt_left->parent = pt->parent;

				if (pt->parent == NULL)
					_root = pt_left;
				else if (pt == pt->parent->left)
					pt->parent->left = pt_left;
				else
					pt->parent->right = pt_left;

				pt_left->right = pt;
				pt->parent = pt_left;
			}

			void swap_color(nodePointer node1, nodePointer node2)
			{
				if (node1 == NULL || node2 == NULL)
					return ;
				bool tmp = node1->color;
				node1->color = node2->color;
				node2->color = tmp;
			}

			void insert_fix(nodePointer node)
			{
				while (node != _root && node->parent->color == RED && node->color != BLACK)
				{
					nodePointer grand_parent;
					if (node->parent->parent)
						grand_parent = node->parent->parent;
					else
						grand_parent = NULL;
					nodePointer parent;
					if (node->parent)
						parent = node->parent;
					else
						parent = NULL;

					if (grand_parent && parent == grand_parent->left)
					{
						nodePointer uncle = grand_parent->right;
						if (uncle != NULL && uncle->color == RED)
						{
							parent->color = BLACK;
							uncle->color = BLACK;
							grand_parent->color = RED;
							node = grand_parent;
						}
						else
						{
							if (node == parent->right)
							{
								rotateLeft(parent);
								node = parent;
                    			parent = node->parent;
							}
							rotateRight(grand_parent);
							swap_color(parent, grand_parent);
							// bool tmp = parent->color;
							// parent->color = grand_parent->color;
							// grand_parent->color = tmp;
							node = parent;
						}
					}
					else
					{
						nodePointer uncle;
						if (grand_parent)
							 uncle = grand_parent->left;
						else
							uncle = NULL;
						if (uncle != NULL && uncle->color == RED)
						{
							parent->color = BLACK;
							uncle->color = BLACK;
							grand_parent->color = RED;
							node = grand_parent;
						}
						else
						{
							if (node == parent->left)
							{
								rotateRight(parent);
								node = parent;
								parent = node->parent;
							}
							rotateLeft(grand_parent);
							swap_color(parent, grand_parent);
							// bool tmp = parent->color;
							// parent->color = grand_parent->color;
							// grand_parent->color = tmp;
							node = parent;
						}
					}
				}
				_root->color = BLACK;
			}

			void swap(RedBlackTree& x)
			{
				(void)x;
				allocator_node		tmp_alloc_node = x._alloc_node;
				nodePointer			tmp_root = x._root;
				nodePointer			tmp_begin = x._begin;
				nodePointer			tmp_end = x._end;
				size_type			tmp_size = x._size;
				key_compare			tmp_comp = x._comp;

				x._alloc_node = _alloc_node;
				x._root = _root;
				x._begin = _begin;
				x._end = _end;
				x._size = _size;
				x._comp = _comp;

				_alloc_node = tmp_alloc_node;
				_root = tmp_root;
				_begin = tmp_begin;
				_end = tmp_end;
				_size = tmp_size;
				_comp = tmp_comp;

				
			}

			nodePointer get_root() const { return _root; }
			void		set_root(nodePointer root) { _root = root; }
			size_type	get_size() const { return _size; }
			void		set_size(size_type size) { _size = size; }
			size_type	max_size() const { return _alloc_node.max_size(); }
			void set_root_to_null() { _root = NULL; }
			nodePointer getBegin() const { return _begin; }
			nodePointer getEnd() const { return _end; }

			private:
				allocator_node		_alloc_node;
				nodePointer			_root;
				nodePointer			_begin;
				nodePointer			_end;
				size_type			_size;
				key_compare			_comp;
	};
}

#endif