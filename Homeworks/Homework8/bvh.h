#ifndef _BVH_H_
#define _BVH_H_


template <class T>
class Node{
	private:
		
	public:

};



template <class T>
class BVH{
	private:
		int size;
		int splitThreshold;
		int depthLimit;

		void statistics(bool print_tree, Node* n, const std::string &indent,
				int &node_count, int &max_depth,
				double &inner_node_area, double &leaf_node_area) const;
		void render_recolor(std::ostream &ostr, Node *n, const Color &color);

	public:
		BVH(int splitThreshold_, int depthLimit_): size(0), splitThreshold(splitThreshold_), depthLimit(depthLimit_){}

		//adding new elements to the tree
		void construct(const std::vector<T> & elements);
		void insert(const T & element);

		
		bool collision(const T & element);

		//prints
		void statistics(bool print_tree) const;
		void render_recolor(std::ostream &ostr) { render_recolor(ostr,root,Color(128,128,128)); }

};






#endif