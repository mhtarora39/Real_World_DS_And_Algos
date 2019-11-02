#include "Graph.hpp"

// class test {
//   public:
//   test() {

//   }
  
//   test(const test& t) {
//     std::cout<<"Copy COTR" << std::endl;
//   }

// };

//  #include <vector>
// #include <map>
// #include <string>
// #include <iostream>

// template <typename T>
// struct OptionParams {
//     OptionParams(int level, int name, bool is_flag, T value) : level_(level), 
//             name_(name), is_flag_(is_flag), value_(value) {}
    
//     int level_;
//     int name_;
//     bool is_flag_;
//     T value_;
// };

// template <typename T>
// std::vector<OptionParams<T>> Options = {
//     {OptionParams<int>(1, 2, 0, 3)},
//     {OptionParams<int>(1, 2, 1, 1)}
// };
// template<typename T>
// class A {
// public:
// A(){};
// virtual T getName() =0;
// };

// template<typename T>
// class B : public A<T> {
//   T data;
//   public:
//   B(){
//     data =100;
//   };

//   T getName() {
//     return data;
//   }

// };

// template<class ItemType>
// class ListInterface
// {
// public:
//    /** Virtual destructor allows concrete implementations to clean up
//    heap memory when the List is discarded. */
  
//    virtual ~ListInterface() {}

//    /** Sees whether this list is empty.
//     @return True if the list is empty; otherwise returns false. */

//    virtual bool isEmpty() const = 0;

//    /** Gets the current number of entries in this list.
//     @return The integer number of entries currently in the list. */

//    virtual int getLength() const = 0;

//    /** Inserts an entry into this list at a given position.
//     @pre  None.
//     @post  If 1 <= position <= getLength() + 1 and the insertion is
//    successful, newEntry is at the given position in the list, and
//    other entries are renumbered accordingly.
//     @param newPosition  The list position at which to insert newEntry.
//     @param newEntry  The entry to insert into the list.
//     @throw  PrecondViolatedExcep if insertion cannot be performed. */

//    virtual void insert(int newPosition, const ItemType& newEntry) /* 
// throw(PrecondViolatedExcep) */ = 0;

//     /** Removes the entry at a given position from this list.
//     @pre  None.
//     @post  If 1 <= position <= getLength() and the removal is successful,
//    the entry at the given position in the list is removed, and other
//    items are renumbered accordingly.
//     @param position  The list position of the entry to remove.
//     @throw  PrecondViolatedExcep if removal cannot be performed. */

//    virtual void remove(int position) /* throw(PrecondViolatedExcep) */ = 0;

//    /** Removes all entries from this list.
//     @post  List contains no entries and the count of items is 0. */

//   virtual void clear() = 0;

//     /** Gets the entry at the given position in this list.
//     @pre  1 <= position <= getLength().
//     @post  The desired entry has been returned.
//     @param position  The list position of the desired entry.
//     @throw  PrecondViolatedExcep if no such entry exists. */

//    virtual ItemType getEntry(int position) const /* 
//    throw(PrecondViolatedExcep) */ = 0;

//    /** Replaces the entry at the given position in this list.
//     @pre  1 <= position <= getLength().
//     @post  The entry at the given position is newEntry.
//     @param position  The list position of the entry to replace.
//     @param newEntry  The replacement entry.
//     @throw  PrecondViolatedExcep if no such entry exists. */

//    virtual void setEntry(int position, const ItemType& newEntry) /* 
// throw(PrecondViolatedExcep) */ = 0;

// };




// template <typename ItemType>
// class LinkedList: public ListInterface<ItemType>
// {
// public:
//     LinkedList();
//     void addFront(ItemType* entry);

//     bool isEmpty() const;
//     int getLength () const;
//     void insert(int newPosition, const ItemType &newEntry);
//     void remove (int position);
//     void clear();
//     ItemType getEntry(int position) const;
//     void setEntry (int position, const ItemType& newEntry);


// private:
//     ItemType* m_front;
// };
// template <typename ItemType>
// LinkedList<ItemType>::LinkedList()
// {
//     m_front = nullptr;
// }

// template <typename ItemType>
// void LinkedList<ItemType>::addFront(ItemType *entry){}

// template <typename ItemType>
// bool LinkedList<ItemType>::isEmpty() const {}

// template <typename ItemType>
// int LinkedList<ItemType>::getLength() const{}

// template <typename ItemType>
// void LinkedList<ItemType>::insert(int newPosition, const ItemType &newEntry){}

// template <typename ItemType>
// void LinkedList<ItemType>::remove(int position){}

// template <typename ItemType>
// void LinkedList<ItemType>::clear() {}

// template <typename ItemType>
// ItemType LinkedList<ItemType>::getEntry(int position) const {}


// template <typename ItemType>
// void LinkedList<ItemType>::setEntry(int position, const ItemType &newEntry){}
class A {
  public:
  A() {
    std::cout << "New " << std::endl;
  }

  ~A() {
    std::cout << "DLT" << std::endl;
  }
};


int main()
{

  std::shared_ptr<A> a = std::make_shared<A>();
  
  a.reset(new A());

  GraphFactory<int> obj;
  obj.BuildGraph(1, 1, 2);
  obj.BuildGraph(2, 1, 6);
  //6  1 10,  10  1  11
  obj.BuildGraph(6, 3, 10);
  obj.BuildGraph(2, 1, 11);
  obj.BuildGraph(10, 1, 11);
   
  auto list = obj.GetAllNodes();
  GraphAlgo<int> algoObj(list);
  
  auto nodes = algoObj.DijkstraShortestPath();

  
  for(auto item: nodes) {
    std::cout << item.GetData() <<std::endl;
  }



 return 0;
}