#ifndef NODE_LIST_H
#define NODE_LIST_H

template <typename T>
class NodeList {
private:
    struct Node {
        T elem;                     /// value
        Node* prev;                 /// pointer to the previous node
        Node* next;                 /// pointer to the next node
    };
public:
    class Iterator {                /// position in the list
    public:
        Iterator();                 /// default constructor
        Iterator(Node* u);          /// create an Iterator from given Node
        Iterator(const Iterator& u);/// copy constructor
        Iterator& operator =(const Iterator& p);

        T& operator*();             /// get the value on this position

        bool operator ==(const Iterator& p) const; /// check if this operator and p are on the same position
        bool operator !=(const Iterator& p) const;

        /// prefix overloaders
        Iterator& operator--();     /// prefix decrement
        Iterator& operator++();     /// prefix increment

        ///postfix overloaders
        Iterator operator --(int);  /// postfix decrement
        Iterator operator ++(int);  /// postfix increment

        friend class NodeList;  /// allow NodeList to access even the
                                /// private members of class Iterator
    private:
        Node* v;                /// address of the node
        void copy(const Iterator& u);
    };
public:
    NodeList();                 /// default constructor
    ~NodeList();                /// destructor
    int size() const;           /// get size
    bool empty() const;         /// check if empty

    Iterator begin() const;     /// get the first position
    Iterator end() const;       /// get the last position

    /// Insertion functions
    void insert(const Iterator& pos, const T& el);  /// insert an element 'el'
                                                    /// before position 'pos'
    void insert_front(const T& el);                 /// insert just after 'header'
    void insert_back(const T& el);                  /// insert just before 'trailer'

    /// Erase functions
    void erase(const Iterator& pos);                /// erase the node on position 'pos'
    void erase_front();                             /// erase the node after 'header'
    void erase_back();                              /// erase the node before 'trailer'

private:
    int n;              /// count of nodes
    Node* header;       /// head node of the list
    Node* trailer;      /// tail node of the list
};

template <typename T>
NodeList<T>::Iterator::Iterator() {
    v = new Node;
} /// default constructor of Iterator

template <typename T>
NodeList<T>::Iterator::Iterator(Node* u) {
    v = u;
} /// construct an Iterator from given Node u

template <typename T>
NodeList<T>::Iterator::Iterator(const Iterator& u) {
    copy(u);
} /// copy constructor

template <typename T>
typename NodeList<T>::Iterator& NodeList<T>::Iterator::operator =(const Iterator& u) {
    copy(u);
    return *this;
} /// assignment operator

template <typename T>
void NodeList<T>::Iterator::copy(const Iterator& u) {
    v = u.v;
}

template <typename T>
T& NodeList<T>::Iterator::operator *() {
    return v->elem;
} /// get the value of this position

template <typename T>
typename NodeList<T>::Iterator& NodeList<T>::Iterator::operator --() {
    v = v->prev;
    return *this;
} /// prefix decrement

template <typename T>
typename NodeList<T>::Iterator& NodeList<T>::Iterator::operator ++() {
    v = v->next;
    return *this;
} /// prefix increment

template <typename T>
typename NodeList<T>::Iterator NodeList<T>::Iterator::operator --(int) {
    Iterator r = *this;
    --*this;

    return r;
} /// postfix decrement

template <typename T>
typename NodeList<T>::Iterator NodeList<T>::Iterator::operator ++(int) {
    Iterator r = *this;
    ++*this;

    return r;
} /// postfix decrement

template <typename T>
bool NodeList<T>::Iterator::operator ==(const Iterator& p) const {
    return p.v == v;
}

template <typename T>
bool NodeList<T>::Iterator::operator !=(const Iterator& p) const {
    return p.v != v;
}


template <typename T>
NodeList<T>::NodeList() {
    n = 0;
    header = new Node;
    trailer = new Node;

    /// link the head to the tail and vice-versa
    header->next = trailer;
    trailer->prev = header;
} /// default constructor

template <typename T>
NodeList<T>::~NodeList() {
    /// destruct the list
    while(!empty()) {
        erase_back();
    }
} /// destructor

template <typename T>
int NodeList<T>::size() const {
    return n;
} /// get size

template <typename T>
bool NodeList<T>::empty() const {
    return size() == 0;
} /// check if empty

template <typename T>
typename NodeList<T>::Iterator NodeList<T>::begin() const {
    return Iterator(header->next);
} /// get the first position

template <typename T>
typename NodeList<T>::Iterator NodeList<T>::end() const {
    return Iterator(trailer);
} /// get the last position

template <typename T>
void NodeList<T>::insert(const Iterator& pos, const T& el) {
    Node* w = pos.v;    /// node on position 'pos'
    Node* u = w->prev;  /// node before w

    Node* v = new Node; /// new node
    v->elem = el;       /// assign the value to the new node
    v->next = w; w->prev = v;
    v->prev = u; u->next = v;

    n++;
} /// insert an element 'el' before position 'pos'

template <typename T>
void NodeList<T>::insert_front(const T& el) {
    insert(begin(), el);
} /// insert just after 'header'

template <typename T>
void NodeList<T>::insert_back(const T& el) {
    insert(end(), el);
} /// insert just before 'trailer'

template <typename T>
void NodeList<T>::erase(const Iterator& pos) {
    Node* v = pos.v;    /// node to be deleted
    Node* w = v->next;
    Node* u = v->prev;

    u->next = w;
    w->prev = u;

    delete v;           /// destructing the node
    n--;
}/// erase the node on position 'pos'

template <typename T>
void NodeList<T>::erase_front(){
    erase(begin());
} /// erase the node after 'header'

template <typename T>
void NodeList<T>::erase_back(){
    erase(--end());
} /// erase the node before 'trailer'

#endif // NODE_LIST_H


/*
#ifndef NODE_LIST_H
#define NODE_LIST_H

template <typename T>
class NodeList {
private:

    struct Node{
        T elem; /// the value
        Node* prev; /// pointer to previous node
        Node* next; /// pointer to next node
    };
public:
    class Iterator { /// position in the list
    public:
        Iterator(); /// default constructor
        Iterator(Node* u); /// crate Iterator from given Node
        T& operator* (); /// get the value on this position

        bool operator ==(const Iterator& p) const;
        bool operator !=(const Iterator& p) const;


        /// prefix overloaders
        Iterator operator--(int); /// prefix decrement
        Iterator operator++(int); /// prefix increment

        friend class NodeList; /// allow NodeList to access even the private members of the class Iterator
    private:
        Node* v;  /// address of the node
    };

public:
    NodeList();     /// default constructor
    ~NodeList(); /// destructor
    int size() const; /// get size
    bool empty() const; /// check if empty

    Iterator begin()  const; /// get the first position
    Iterator end() const; ///   get the last position

    void insert(const Iterator& pos, const T& el); ///  insert an element 'el' before position 'pos'
    void insert_front(const T& el); /// insert just after 'header'
    void insert_back(const T& el);  /// insert just before 'tailer'

    /// erase function
    void erase(const Iterator& pos); /// erase the node on position 'pos'
    void erase_front(); /// erase the node after 'header'
    void erase_back(); /// erase the node before 'tailer'
private:
    int n;  /// count of nodes
    Node* header;   /// head node of the list
    Node* tailer; /// tail node of the list

};

template <typename T>
NodeList<T>::Iterator::Iterator(){

    v = new Node;
    /// default constructor of Iterator
}

template <typename T>
NodeList<T>::Iterator::Iterator(Node* u){

    v = u;
    /// construct an Iterator from given Node u
}

template <typename T>
T& NodeList<T>::Iterator::operator*(){

    return v->elem;
    /// get the value of the position
}


template <typename T>
typename NodeList<T>::Iterator NodeList<T>::Iterator::operator --() {
    v = v->prev;
    return *this;

    /// prefix decrement
}

template <typename T>
typename NodeList<T>::Iterator NodeList<T>::Iterator::operator++(){

    v = v->next;
    return *this;

    /// prefix increment
}

template <typename T>
bool NodeList<T>::Iterator::operator ==(const Iterator& p) const{

    return p.v == v;

}

template <typename T>
bool NodeList<T>::Iterator::operator !=(const Iterator& p) const{

    return p.v != v;

}

template <typename T>
NodeList<T>::NodeList(){
    n = 0;
    header = new Node;
    tailer = new Node;

    /// link the head to the tail and vice-versa
    header->next = tailer;
    tailer->prev = header;

    /// a default constructor
}

template <typename T>
NodeList<T>::~NodeList(){
    while(!empty()){

        erase_back();

    }
    /// destructor
}

template <typename T>
int NodeList<T>::size() const{
    return n;
    /// get size
}

template <typename T>
bool NodeList<T>::empty() const {

    return size() == 0;
    /// check if empty
}

template <typename T>
typename NodeList<T>::Iterator NodeList<T>::begin() const{

    return Iterator(tailer);

    /// get the last position
}

template <typename T>
typename NodeList<T>::Iterator NodeList<T>::end() const{

    return Iterator(header->next);

    /// get the first position
}

template <typename T>
void NodeList<T>::insert(const Iterator& pos, const T& el){

    Node* w = pos.v;    /// node on position 'pos'
    Node* u = w->prev;  /// node before w

    Node* v = new Node; /// new node
    v->elem = el;   /// assign the value to the new node
    v->next = w; w->prev = v;
    w->prev = u; u->next = v;
    /// insert an element 'el' before position 'pos'
}

template <typename T>
void NodeList<T>::insert_front(const T& el){

    insert(begin(), el);

    /// insert just after 'header'
}

template <typename T>
void NodeList<T>::insert_back(const T& el){

    insert(end(), el);
    /// insert just before 'tailer'
}

template <typename T>
void NodeList<T>::erase(const Iterator& pos){

    Node* v = pos.v; /// node to be deleted
    Node* w = v->next;
    Node* u = v->prev;

    u->next = w;
    w->prev = u;

    delete v; /// destructing the node
    n--;
}

template <typename T>
void NodeList<T>::erase_front(){

    erase(begin());
    /// erase the node after 'header'
}

template <typename T>
void NodeList<T>::erase_back(){

    erase(--end());
    /// erase the node before 'tailer'
}

#endif // NODE_LIST_H
*/

