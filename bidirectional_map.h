# include <iostream>
# include <utility>
# include <cassert>
# include <string>
# include <vector> 
# include <utility>
# include <algorithm>
# include <cstdlib>

template <class DataType, class LinkType> 
class Node{
public:
	Node(): left(NULL), right(NULL), parent(NULL), link(NULL) {}
	Node(const DataType& init): data(init), left(NULL), right(NULL), parent(NULL), link(NULL) {}
	DataType data;
	Node<LinkType, DataType>* link;
    Node* left;
    Node* right; 
    Node* parent;
};

template <class KeyType, class ValueType> class bidirectional_map;
template <class DataType, class LinkType> class key_iter;
template <class DataType, class LinkType> class value_iter;

template <class DataType, class LinkType>
class key_iter{
public:
	key_iter(): ptr_(NULL), map_(NULL) {}
	key_iter(Node<DataType, LinkType>* p, const bidirectional_map<DataType, LinkType>* m): ptr_(p), map_(m) {}
	key_iter(const key_iter& old): ptr_(old.ptr_), map_(old.map_) {}
	~key_iter() {}
	//operator
	key_iter& operator=(const key_iter& old){ptr_=old.ptr_; map_=old.map_; return *this;}
    const std::pair<DataType, LinkType> operator* () const {return std::pair<DataType, LinkType>(ptr_->data, ptr_->link->data);}
    Node<DataType, LinkType>* getptr() const {return ptr_;}
    value_iter<LinkType, DataType> follow_link() const {return value_iter<LinkType, DataType>(ptr_->link, map_);} 
    friend bool operator ==(const key_iter& itr1, const key_iter itr2) {return (itr1.ptr_==itr2.ptr_ && itr1.map_==itr2.map_);}
    friend bool operator !=(const key_iter& itr1, const key_iter itr2) {return (itr1.ptr_!=itr2.ptr_ || itr1.map_!=itr2.map_);}
    //increment and decrement operators
    
    key_iter<DataType, LinkType> & operator++(){
    	if (ptr_->right!=NULL){
    		ptr_=ptr_->right;
    		while(ptr_->left!=NULL){
    			ptr_=ptr_->left;
    		}
    	}
    	else{
    		while(ptr_->parent!=NULL && ptr_->parent->right==ptr_){
    			ptr_=ptr_->parent;
    		}
    		ptr_=ptr_->parent;
    	}
    	return *this;
    } 
    key_iter<DataType, LinkType> operator++(int){
    	key_iter<DataType, LinkType> temp(*this);
    	++(*this);
    	return temp;
    }
    key_iter<DataType, LinkType> & operator--(){
    	if (ptr_==NULL){
    		assert(map_!=NULL);
    		ptr_=map_->key_root;
    		while(ptr_->right!=NULL){
    			ptr_=ptr_->right;
    		}
    	}
    	else if (ptr_->left!=NULL){
    		ptr_=ptr_->left;
    		while(ptr_->right!=NULL){
    			ptr_=ptr_->right;
    		}
    	}
    	else {
    		while(ptr_->parent!=NULL && ptr_->parent->left==ptr_){
    			ptr_=ptr_->parent;
    		}
    		ptr_=ptr_->parent;
    	}
    	return *this;
    }
    key_iter<DataType, LinkType> operator--(int){
    	key_iter<DataType, LinkType> temp(*this);
    	--(*this);
    	return temp;
    }

private:
	Node<DataType, LinkType>* ptr_;
	const bidirectional_map<DataType, LinkType>* map_;
};

template <class DataType, class LinkType>
class value_iter{
public:
	value_iter(): ptr_(NULL), map_(NULL) {}
	value_iter(Node<DataType, LinkType>* p, const bidirectional_map<LinkType, DataType>* m): ptr_(p), map_(m) {}
	value_iter(const value_iter& old): ptr_(old.ptr_), map_(old.map_) {}
	~value_iter() {}
	//operator
	value_iter& operator=(const value_iter& old){ptr_=old.ptr_; map_=old.map_; return *this;}
    const std::pair<DataType, LinkType> operator* () const {return std::pair<DataType, LinkType>(ptr_->data, ptr_->link->data);}
    Node<DataType, LinkType>* getptr() const {return ptr_;}
    key_iter<LinkType, DataType> follow_link() const {return key_iter<LinkType, DataType>(ptr_->link, map_);} 
    friend bool operator==(const value_iter& itr1, const value_iter& itr2) {
    	return (itr1.ptr_==itr2.ptr_ && itr1.map_==itr2.map_);
    }
    friend bool operator!=(const value_iter& itr1, const value_iter& itr2) {
    	return (itr1.ptr_!=itr2.ptr_ || itr1.map_!=itr2.map_);
    }
    //increment and decrement operators
    value_iter<DataType, LinkType> & operator++(){
    	if (ptr_->right!=NULL){
    		ptr_=ptr_->right;
    		while(ptr_->left!=NULL){
    			ptr_=ptr_->left;
    		}
    	}
    	else{
    		while(ptr_->parent!=NULL && ptr_->parent->right==ptr_){
    			ptr_=ptr_->parent;
    		}
    		ptr_=ptr_->parent;
    	}
    	return *this;
    } 
    value_iter<DataType, LinkType> operator++(int){
    	value_iter<DataType, LinkType> temp(*this);
    	++(*this);
    	return temp;
    }
    value_iter<DataType, LinkType> & operator--(){
    	if (ptr_==NULL){
    		assert(map_!=NULL);
    		ptr_=map_->value_root;
    		while(ptr_->right!=NULL){
    			ptr_=ptr_->right;
    		}
    	}
    	else if (ptr_->left!=NULL){
    		ptr_=ptr_->left;
    		while(ptr_->right!=NULL){
    			ptr_=ptr_->right;
    		}
    	}
    	else {
    		while(ptr_->parent!=NULL && ptr_->parent->left==ptr_){
    			ptr_=ptr_->parent;
    		}
    		ptr_=ptr_->parent;
    	}
    	return *this;
    }
    value_iter<DataType, LinkType> operator--(int){
    	value_iter<DataType, LinkType> temp(*this);
    	--(*this);
    	return temp;
    }
private:
	Node<DataType, LinkType>* ptr_;
	const bidirectional_map<LinkType, DataType>* map_;
};
//bidirectional map class
template <class KeyType, class ValueType>
class bidirectional_map {
public:
	bidirectional_map() : key_root(NULL), value_root(NULL), size_(0) {}
	bidirectional_map(const bidirectional_map& old): size_(old.size_) {
		key_root=this->copy_tree(old.key_root, NULL);
		value_root=this->copy_tree(old.value_root, NULL);
		link_two_tree(key_root, value_root, old.key_root);
	}
	~bidirectional_map() {this->destroy_tree(key_root); this->destroy_tree(value_root); key_root=NULL; value_root=NULL;}
	bidirectional_map& operator=(const bidirectional_map& old) {
		if(&old!=this){
		  this->destroy_tree(key_root);
		  this->destroy_tree(value_root);
		  key_root=this->copy_tree(old.key_root, NULL);
		  value_root=this->copy_tree(old.value_root, NULL);
		  link_two_tree(key_root, value_root, old.key_root);
		  size_=old.size_;
	    }
	return *this;
	}

	typedef key_iter<KeyType, ValueType> key_iterator;
	typedef value_iter<ValueType, KeyType> value_iterator;
	typedef Node<KeyType, ValueType> key_node;
	typedef Node<ValueType, KeyType> value_node;
	friend class key_iter<KeyType, ValueType>;
	friend class value_iter<ValueType, KeyType>;

	int size() const {return size_;}

	bool operator==(const bidirectional_map<KeyType, ValueType>& old) {
		return old.key_root==this->key_root && old.value_root==this->value_root;
	}

	key_iterator find(const KeyType& key) const {
		return find(key, key_root);
	}

	value_iterator find(const ValueType& value) const {
		return find(value, value_root);
	}

	std::pair<key_iterator, bool> insert(const std::pair<KeyType, ValueType>& pair){
		return insert(pair, key_root, NULL, value_root, NULL);
	}

	int erase(const KeyType& key){
		return erase(key, key_root, value_root);
	}

	friend std::ostream& operator<< (std::ostream& ostr, const bidirectional_map<KeyType, ValueType>& map) {
		map.print_in_order(ostr, map.key_root);
		map.print_in_order(ostr, map.value_root);
		return ostr;
	}

	void print(std::ostream& ostr) const{
		print_as_sideways_tree(ostr, key_root, 0);
		print_as_sideways_tree(ostr, value_root, 0);
	}

	key_iterator key_begin(){
		if(!key_root) return key_iterator(NULL, this);
		key_node* p=key_root;
		while (p->left) p=p->left;
		return key_iterator(p, this);
	}

	value_iterator value_begin(){
		if(!value_root) return value_iterator(NULL, this);
		value_node* p=value_root;
		while (p->left) p=p->left;
		return value_iterator(p, this);
	}

	key_iterator key_end(){
		return key_iterator(NULL, this);
	}

	value_iterator value_end(){
		return value_iterator(NULL, this);
	}

	ValueType& operator[] (const KeyType& key){
    	key_iterator ki=find(key);
        assert(ki!=this->key_end());
        return ki.getptr()->link->data;
    }
    KeyType& operator[] (const ValueType& value){
    	value_iterator vi=find(value);
        assert(vi!=this->value_end());
        return vi.getptr()->link->data;
    }


private:
	Node<KeyType, ValueType>* key_root;
	Node<ValueType, KeyType>* value_root;
	int size_; 

	//private helper function
	void destroy_tree(key_node* p){
		if (p==NULL) return;
		destroy_tree(p->right);
		destroy_tree(p->left);
		delete p;
	}

	void destroy_tree(value_node* p){
		if (p==NULL) return;
		destroy_tree(p->right);
		destroy_tree(p->left);
		delete p;
	}

	Node<KeyType, ValueType>* copy_tree(const Node<KeyType, 
		ValueType>*& old_key_root, Node<KeyType, ValueType>* the_parent) {
		if (old_key_root==NULL) return NULL;
		Node<KeyType, ValueType>* key_tree= new Node<KeyType, ValueType>;
		key_tree->data=old_key_root->data;
		key_tree->left=copy_tree(old_key_root->left, key_tree);
		key_tree->right=copy_tree(old_key_root->right, key_tree);
		key_tree->parent=the_parent;
		return key_tree;
	}

	Node<ValueType, KeyType>* copy_tree(const value_node*& old_value_root, value_node* the_parent) {
		if (old_value_root==NULL) return NULL;
		Node<ValueType, KeyType>* value_tree=new Node<ValueType, KeyType>;
		value_tree->data=old_value_root->data;
		//value_tree->link=old_value_root->link;
		value_tree->left=copy_tree(old_value_root->left, value_tree);
		value_tree->right=copy_tree(old_value_root->right, value_tree);
		value_tree->parent=the_parent;
		return value_tree;
	}

	key_iterator find(const KeyType& key, key_node* p) const {
		if (p==NULL) return key_iterator(NULL, this);
		if (p->data == key) return key_iterator(p, this);
		else if (p->data < key) return find(key, p->right);
		else return find(key, p->left);
	}

	value_iterator find(const ValueType& value, value_node* p) const {
		if (p==NULL) return value_iterator(NULL, this);
		if (p->data == value) return value_iterator(p, this);
		else if (p->data < value) return find(value, p->right);
		else return find(value, p->left);
	}

    void link_two_tree(Node<KeyType, ValueType>*& key_root, Node<ValueType, KeyType>*& value_root, 
    	const Node<KeyType, ValueType>*& old_key_root){
    	if (old_key_root!=NULL) {
    	    key_iterator ki=find(old_key_root->data, key_root);
    	    value_iterator vi=find(old_key_root->link->data, value_root);
    	    ki.ptr_->link=vi.ptr_;
    	    vi.ptr_->link=ki.ptr_;
            link_two_tree(key_root, value_root, old_key_root->left);
            link_two_tree(key_root, value_root, old_key_root->right);
        }
    }

	std::pair<key_iterator, bool> insert(const std::pair<KeyType, ValueType>& pair, key_node*& key_root, 
		key_node* key_parent, value_node*& value_root, value_node* value_parent){
		if(key_root==NULL){
			key_root=new key_node(pair.first);
			value_node* vi=new value_node(pair.second);
			key_root->link=vi;
			vi->link=key_root;
			key_root->parent=key_parent;
            size_++;
            insert_value(vi, value_root, value_parent);
			return std::pair<key_iterator, bool>(key_iterator(key_root, this), true);
		}
		else if (key_root->data < pair.first){
			return insert(pair, key_root->right, key_root, value_root, value_parent);
		}
		else if (key_root->data > pair.first){
			return insert(pair, key_root->left, key_root, value_root, value_parent);
		}
		else
			return std::pair<key_iterator, bool>(key_iterator(key_root, this), false);
	}

	void insert_value(value_node*& vi, value_node*& p, value_node* value_parent){
		if(p==NULL){
			p=vi;
			vi->parent=value_parent;
		}
		else if(vi->data < p->data){
			insert_value(vi, p->left, p);
		}
		else if (vi->data > p->data){
			insert_value(vi, p->right, p);
		}
		else 
			std::cerr <<"duplicated value."<<std::endl;
	}

	int erase(const KeyType& key, key_node*& p, value_node*& value_root){
		if(p==NULL) return 0;
		std::cout << key << std::endl;
		if(key < p->data){
			return erase(key, p->left, value_root);
		}
		if(key > p->data){
			return erase(key, p->right, value_root);
		}
		assert (p->data==key);
		if (p->left==NULL && p->right==NULL){
			erase_value(p->link->data, value_root);
			std::cout <<"aha " << p->link->data << std::endl;
			delete p;
			p = NULL;
			size_--;
		}
		else if (p->left==NULL){
			key_node* q=p;
			erase_value(p->link->data, value_root);
			p=p->right;
			p->parent=q->parent;
			delete q;
			size_--;
		}
		else if (p->right==NULL){
			key_node* q=p;
			erase_value(p->link->data, value_root);
			p=p->left;
			p->parent=q->parent;
			delete q;
			size_--;
		}
		else{
			key_node* q=p->left;
			while(q->right!=NULL) q=q->right;
			p->data=q->data;
			int check = erase(q->data, p->left, value_root);
			assert(check==1);
		}
		//std::cout << p->data << std::endl;
		return 1;
	
	}

	void erase_value(const ValueType& value, value_node*& p){
		assert(p!=NULL);
		std::cout << value <<std::endl;
		if (value < p->data){
			erase_value(value, p->left);
			return;
		}
		if(value > p->data){
			erase_value(value, p->right);
			return;
		}
        std::cout << "found" << std::endl;
		if (p->left==NULL && p->right==NULL){
			std::cout << "leaf" << std::endl;
			delete p;
			p=NULL;
		}
		else if (p->right==NULL){
			value_node* q=p;
			p=p->left;
			p->parent=q->parent;
			delete q;
		}
		else if (p->left==NULL){
			value_node* q=p;
			p=p->right;
			p->parent=q->parent;
			delete q;
		}
		else{
			value_node* q=p->left;
			while(q->right!=NULL) q=q->right;
			p->data=q->data;
			erase_value(q->data, p->left);
		}

	}

	void print_in_order(std::ostream& ostr, const key_node*& p){
		if(p!=NULL){
			print_in_order(p->left);
			ostr << p->data <<"\n";
			print_in_order(p->right);
		}
	}

	void print_in_order(std::ostream& ostr, const value_node*& p){
		if(p!=NULL){
			print_in_order(p->left);
			ostr << p->data <<"\n";
			print_in_order(p->right);
		}
	}

    void print_as_sideways_tree(std::ostream& ostr, const key_node* p, int depth) const {
    	if(p!=NULL){
    		print_as_sideways_tree(ostr, p->right, depth+1);
    		for (int i=0; i<depth; i++) ostr << "    ";
    		ostr << p->data << "\n";
    	    print_as_sideways_tree(ostr, p->left, depth+1);
    	}
    }

    void print_as_sideways_tree(std::ostream& ostr, const value_node* p, int depth) const {
    	if(p!=NULL){
    		print_as_sideways_tree(ostr, p->right, depth+1);
    		for (int i=0; i<depth; i++) ostr << "    ";
    		ostr << p->data << "\n";
    	    print_as_sideways_tree(ostr, p->left, depth+1);
    	}
    }

};




