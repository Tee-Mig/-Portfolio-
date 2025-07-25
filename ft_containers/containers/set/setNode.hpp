#ifndef SET_NODE_HPP
#define SET_NODE_HPP

namespace ft
{
	template <class T>
	struct SetNode
	{
		T			_pair;
		bool		color;
		SetNode		*left;
		SetNode		*right;
		SetNode		*parent;

		SetNode()
		: _pair(), color(RED), left(NULL), right(NULL), parent(NULL) {}

		virtual ~SetNode() {}

		SetNode(T val, SetNode *_parent = NULL,
				SetNode *_left = NULL, SetNode *_right = NULL, bool _color = RED)
		: _pair(val), color(_color), left(_left), right(_right), parent(_parent) {}

		SetNode(const SetNode& cp)
		: _pair(cp._pair), color(cp.color), left(cp.left), right(cp.right),
			parent(cp.parent) {}

		bool isOnLeft() { return this == parent->left; }

		SetNode *sibling()
		{
			if (parent == NULL)
				return NULL;
		
			if (isOnLeft())
				return parent->right;
		
			return parent->left;
  		}
	};
}

#endif