#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//DO NOT ADD ANY CONSTANTS OR FUNCTIONS TO ANY CLASS

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
  Node(const T& data); //Node Constructor - Assume each quan
  pair<T,int>& GetData(); //Node Data Getter
  void SetData( const pair<T,int>& ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  pair <T,int> m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
  m_data = make_pair(data,1);
  m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
	m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
 public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
	 LL();
  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
	 ~LL();
  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
	 LL(const LL&);
  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
	 LL<T>& operator= (const LL& linkList);
  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
	 Node<T>* Find(const T& data);
  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
	 void Insert(const T& data);
  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node. 
  // Postconditions: Removes first node with passed value (in first)
	 void RemoveAt(const T&);
  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL 
	 void Display();
  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
	 int GetSize();
  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const LL<U>& linkList);
  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T, int>& operator[] (int x);//Overloaded [] operator to pull data from LL
private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in queue
};
//*****************************************************************
	//Implement LL here
	  // Name: LL() (Linked List) - Default Constructor
	  // Desc: Used to build a new linked list
	  // Preconditions: None
	  // Postconditions: Creates a new linked list where m_head points to nullptr
	template <class T>
	LL<T>::LL() {
		m_head = nullptr;
		m_size = 0;
	}
	// Name: ~LL() - Destructor
	// Desc: Used to destruct a LL
	// Preconditions: There is an existing LL with at least one node
	// Postconditions: A LL is deallocated (including dynamically allocated nodes)
	//                 to have no memory leaks!
	template <class T>
	LL<T>::~LL() {
		Node<T>* curr = m_head;
		Node<T>* prev = m_head;
		while (curr != nullptr) {
			prev = curr;
			curr = curr->GetNext();
			delete prev;
			prev = nullptr;
		}
	}
	// Name: LL (Copy Constructor)
	// Desc: Creates a copy of existing LL
	//       Requires a LL - REQUIRED to be implemented even if not used
	// Preconditions: Source LL exists
	// Postconditions: Copy of source LL
	template <class T>
	LL<T>::LL(const LL& linkList) {
		Node<T> *curr = linkList.m_head;

		while (curr != nullptr) {
			for (int i = 0; i < curr->GetData().second; i++) {
				Insert(curr->GetData().first);
			}
			curr = curr->GetNext();
		}
	}
	// Name: operator= (Overloaded Assignment Operator)
	// Desc: Makes two LL of the same type have identical number of nodes and values
	// Preconditions: Requires two linked lists of the same templated type
	//                REQUIRED to be implemented even if not used
	// Postconditions: Two idenetical LL
	template <class T>
	LL<T>& LL<T>::operator= (const LL& linkList) {
		Node<T>* curr = linkList.m_head;

		while (curr != nullptr) {
			for (int i = 0; i < curr->GetData().second; i++) {
				Insert(curr->GetData().first);
			}
			curr = curr->GetNext();
		}
		return *this;
	}
	// Name: Find
	// Desc: Iterates through LL and returns node if data found
	// Preconditions: LL Populated
	// Postconditions: Returns nullptr if not found OR Node pointer if found
	template <class T>
	Node<T>* LL<T>::Find(const T& data) {
		Node<T>* temp = m_head;

		while (temp != nullptr) {
			if (temp->GetData().first == data) {
				return temp;
			}
			temp = temp->GetNext();
		}
		return nullptr;

	}
	// Name: Insert
	// Desc: Either inserts a node to the linked list OR increments frequency of first
	//       Takes in data. If "first" (of pair) NOT in list, adds node
	//       If "first" (of pair) is already in list, increments quantity
	//       Inserts "first" in order with no duplicates
	// Preconditions: Requires a LL.
	// Postconditions: Node inserted in LL based on first value (or quantity incremented)
	template <class T>
	void LL<T>::Insert(const T& data) {
		Node<T>* curr = m_head;
		Node<T>* prev = m_head;
		Node<T>* find = nullptr;
		Node<T>* newNode = new Node<T>(data);
		pair <T, int> tempData = make_pair(data, 1);
		bool check = false;

		//if LL is empty
		if (m_head != nullptr) {
			//if LL had more than one element
				//find is Node class or nullptr
				find = Find(data);
				//if find exists
				if (find != nullptr) {
					tempData = find->GetData();
					tempData.second++;
					find->SetData(tempData);
				}
				else {
					//if LL has one element
					if (m_size == 1) {
						if (data < curr->GetData().first) {
							newNode->SetNext(curr);
							m_head = newNode;
							m_size++;
						}
						else {
							curr->SetNext(newNode);
							newNode->SetNext(nullptr);
							m_size++;
						}
					}
					else {
						//loops through entire linked list
						while ((curr != nullptr) && (!check)) {
							//if data is not greater than the next data
							if (!(data > curr->GetData().first)){
								//if the current node is the first
								if (curr == m_head) {
									newNode->SetNext(curr);
									m_head = newNode;
									check = true;
									m_size++;
								}
								else {
									prev->SetNext(newNode);
									newNode->SetNext(curr);
									check = true;
									m_size++;
								}
							}
							//if the data is greater than all data in LL
							else if (curr->GetNext() == nullptr) {
								curr->SetNext(newNode);
								check = true;
								m_size++;
							}
							prev = curr;
							curr = curr->GetNext();
						}
					}
				}
		}
		else {
			m_head = newNode;
			m_size++;
		}
	}
	// Name: RemoveAt
	// Desc: Removes a node at a particular position based on data passed (matches first)
	// Preconditions: LL with at least one node. 
	// Postconditions: Removes first node with passed value (in first)
	template <class T>
	void LL<T>::RemoveAt(const T& data) {
		Node<T> *curr = m_head;
		Node<T> *prev = m_head;
		bool found = false;
		
		while ((curr != nullptr) && !(found)) {
			if (curr->GetData().first == data) {
				if (curr == m_head) {
					prev = curr;
					m_head = curr->GetNext();
					delete prev;
					found = true;
					m_size--;
				}
				else {
					prev->SetNext(curr->GetNext());
					delete curr;
					found = true;
					m_size--;
				}
			}
			else {
				prev = curr;
				curr = curr->GetNext();
			}

		}
	}
	// Name: Display
	// Desc: Display all nodes in linked list
	// Preconditions: Outputs the LL
	// Postconditions: Displays the pair in each node of LL 
	template <class T>
	void LL<T>::Display() {
		cout << *this;
		cout << "END" << endl;
	}
	// Name: GetSize
	// Desc: Returns the size of the LL
	// Preconditions: Requires a LL
	// Postconditions: Returns m_size
	template <class T>
	int LL<T>::GetSize() {
		return m_size;
	}
	// Name: operator<< (Overloaded << operator)
	// Desc: Returns the ostream of the data in each node
	// Preconditions: Requires a LL
	// Postconditions: Returns an ostream with the data from each node on different line
	template <class U>
	ostream& operator<<(ostream& output, const LL<U>& linkList) {
		Node<U>* curr = linkList.m_head;

		while (curr != nullptr) {
			output << curr->GetData().first << ": " << curr->GetData().second << endl;
			curr = curr->GetNext();
		}
		return output;
	}
	// Name: Overloaded [] operator
	// Desc: When passed an integer, returns the data at that location
	// Precondition: Existing LL
	// Postcondition: Returns pair from LL using []
	template <class T>
	pair<T, int>& LL<T>::operator[] (int x) {
		Node<T>* curr = m_head;
		for (int i = 0; i < x; i++) {
			curr = curr->GetNext();
		}
		return curr->GetData();
	}//Overloaded [] operator to pull data from LL
