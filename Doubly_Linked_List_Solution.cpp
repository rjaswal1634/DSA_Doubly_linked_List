#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;
/**
 * Represents a node in a doubly linked list.
 * @param <T> The type of data stored in the node.
 */
template<typename T>
  struct Node
  {
    T data;
    Node* next;
    Node* prev;
  };

template<typename T>
class DoublyLinkedList
{
  private:
    Node<T>* head;
    Node<T>* tail;
    int count;

  
    /**
      this method creates and returns a new node
     * @param d Node value
     * @return New node
     */
    Node<T>* createNewNode(T d)
    {
      Node<T> *newNode = new Node<T>;
      newNode->prev = nullptr;
      newNode->data = d;
      newNode->next = nullptr;
      return newNode;
    }
    // delete the node pointed at by the prevNode
    /**
     * Deletes the node after the specified node.
     * @param prevNode Pointer to the node before the node to be deleted.
     * @return True if deletion is successful, false otherwise.
     */
    bool deleteAfter(Node<T>* prevNode)
    {
      if (prevNode == nullptr || prevNode->next == nullptr)
      {
        return false;
      }
      Node<T>* temp = prevNode->next;
      prevNode->next = temp->next;
      if (temp->next != nullptr)
      {
        temp->next->prev = prevNode;
      }
      delete temp;
      count--;
      return true;
    }
    /**
     * Inserts a new node with the given value after the specified node.
     * @param prevNode Pointer to the node after which the new node should be inserted.
     * @param value The value for the new node.
     */
    void insertAfter(Node<T>* prevNode, T value)
    {
      if (prevNode == nullptr)
      {
        return;
      }
      Node<T>* newNode = createNewNode(value);
      newNode->next = prevNode->next;
      newNode->prev = prevNode;
      if (prevNode->next != nullptr)
      {
        prevNode->next->prev = newNode;
      }
      prevNode->next = newNode;
      count++;
    }

  public:
    // Default Constructor
    DoublyLinkedList()
    {
      head = nullptr;
      tail = nullptr;
      count = 0;
    }

    // Copy Constructor
    /** Copy constructor for DoublyLinkedList.
     * @param otherList The list to be copied.
     */
    DoublyLinkedList(const DoublyLinkedList<T>& otherList)
    {
      head = nullptr;
      tail = nullptr;
      count = 0;
      Node<T>* currentNode = otherList.head;
      while (currentNode != nullptr)
      {
        push_back(currentNode->data);
        currentNode = currentNode->next;
      }
    }

    // Destructor
    ~DoublyLinkedList()
    {
      Node<T>* current = head;
      while (current != nullptr)
      {
        Node<T>* next = current->next;
        delete current;
        current = next;
      }
      head = nullptr;
      tail = nullptr;
      count = 0;
    }
    /**
     * Adds an element to the back of the list.
     * @param item The element to be added.
     */
    void push_back(T item)
    {
      Node<T>* newNode = createNewNode(item);
      if (tail == nullptr)
      {
        head = newNode;
        tail = newNode;
      }
      else
      {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
      }
      count++;
    }
    /**
     * Adds an element to the back of the list.
     * @param item The element to be added.
     */
    void push_front(T item)
    {
      Node<T>* newNode = createNewNode(item);
      if (head == nullptr)
      {
        head = newNode;
        tail = newNode;
      }
      else
      {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
      }
        count++;
    }

    /**
     * Inserts an element at the specified index in the list.
     * @param index The index at which to insert the element.
     * @param value The value of the element to be inserted.
     * @return True if the insertion is successful, false otherwise.
     */
    bool insert(int index, T value)
    {
      if (index < 0 || index > count)
        return false;
      if (index == 0)
      {
        push_front(value);
      }
      else if (index == count)
      { // If inserting at the end
        push_back(value);
      }
      else
      { // If inserting at a specific position
        Node<T>* current = head;
        for (int i = 0; i < index - 1; ++i)
        { // Traverse to the node before the specified index
          current = current->next;
        }
        insert_after(current, value); // Use insert_after function
        count++;
      }
      return true;
    }
     /**
     * Removes the first element from the list.
     * @param data Reference to store the removed element.
     * @return True if the removal is successful, false if the list is empty.
     */
    bool pop_front(T& data)
    {
      if (isEmpty())
        return false;
      data = head->data;
      Node<T>* temp = head;
      head = head->next;
      if (head)
        head->prev = nullptr;
      delete temp;
      count--;
      return true;
    }

    // Removes the last element and returns the value in data
    /**
     * Removes the last element from the list.
     * @param data Reference to store the removed element.
     * @return True if the removal is successful, false if the list is empty.
     */
    bool pop_back(T& data)
    {
      if (isEmpty())
        return false;
      data = tail->data;
      Node<T>* temp = tail;
      tail = tail->prev;
      if (tail)
        tail->next = nullptr;
      delete temp;
      count--;
      return true;
    }

    // Deliverable 4 modified Delete Node
    /**
     * Deletes the node at the specified index.
     * @param index The index of the node to be deleted.
     * @return True if deletion is successful, false otherwise.
     */
    bool deleteNode(int index)
    {
      if (index < 0 || index >= count)
        return false;
      if (index == 0)
      {
        return pop_front();
      }
      else if(index == (count - 1))
      {
        return pop_back();
      }
      else
      {
        if(index <= count / 2 )// if closer from head
        {
          Node<T>* current = head;
          for (int i = 0; i < index; ++i)
          {
            current = current->next;
          }
          return deleteAfter(current->prev);
        }
        else // if closer from tail
        {
          Node<T>* current = tail;
          for (int i = count - 1; i > index; --i)
          {
            current = current->prev;
          }
          return deleteAfter(current->prev);
        }
      }
    }
     /**
     * Retrieves the value of the element at the specified index.
     * @param index The index of the element to retrieve.
     * @param value Reference to store the retrieved value.
     * @return True if the index is valid, false otherwise.
     */
    bool elementAt(int index, T& value)
    {
      if (index < 0 || index >= count)
        return false;
      Node<T>* current = head;
      for (int i = 0; i < index; ++i)
      {
        current = current->next;
      }
      value = current->data;
      return true;
    }
    /**
     * Displays the elements of the list in  order.
     */
    void displayList()
    {
      Node<T>* current = head;
      if(current == nullptr)
        cout<<"END";
      while (current != nullptr)
      {
        cout << current->data << " " << endl;
        current = current->next;
      }
      cout << endl;
    }

    /**
     * Displays the elements of the list in reverse order.
     */
    void displayListBackward()
    {
      Node<T>* current = tail;
      if(current == nullptr)
        cout<<"BEGIN";
      while (current != nullptr)
      {
        cout << current->data << " ";
        current = current->next;
      }
      cout << endl;
    }
    
    /**
     * Returns the size of the list.
     * @return The number of elements in the list.
     */
    int size() const
    {
      return count;
    }
    /**
     * Checks if the list is empty.
     * @return True if the list is empty, false otherwise.
     */
    bool isEmpty()
    {
      return count == 0;
    }

    // Deliverable 3
    // Delete all instances of a given item from the list
    /**
     * Deletes all instances of a given item from the list.
     * @param item The item to be deleted.
     */
    void deleteItem(const T& item)
    {
      Node<T>* current = head;
      while (current != nullptr)
      {
        if (current->data == item)
        {
          // If the current node contains the item, remove it
          Node<T>* temp = current;
          if (current == head)
          {
            // If current node is the head node
            head = current->next;
            if (head)
            head->prev = nullptr;
          }
          else if (current == tail)
          {
            // If current node is the tail node
            tail = current->prev;
            tail->next = nullptr;
          }
          else
          {
            // If current node is in the middle of the list
            current->prev->next = current->next;
            current->next->prev = current->prev;
          }
          delete temp;
          count--;
          current = current->next; // Move to the next node
        }
        else
        {
          current = current->next; // Move to the next node
        }
      }
    }

    /**
     * Reverses the order of elements in the list.
     */
    void reverse()
    {
      if (isEmpty() || head == tail) // If the list is empty or has only one node, no need to reverse
        return;
      Node<T>* hNode = head;
      Node<T>* tNode = tail;
      while (hNode != tNode && hNode->prev != tNode)
      {
        // Swap the values of hNode and tNode
        T temp = hNode->data;
        hNode->data = tNode->data;
        tNode->data = temp;

        // Move hNode to the next node and tNode to the previous node
        hNode = hNode->next;
        tNode = tNode->prev;
      }
    }
    /**
     * Searches for all occurrences of a given item in the list.
     * @param searchItem The item to search for.
     * @return A vector containing the indexes of the occurrences.
     */
    vector<int> search(const T& searchItem)
    {
      vector<int> indexes; // Vector to store index positions of searchItem
      Node<T>* current = head;
      int index = 0;
      while (current != nullptr)
      {
        if (current->data == searchItem)
        {
        // If current node contains searchItem, add its index to the vector
        indexes.push_back(index);
        }
        current = current->next;
        index++;
      }
      return indexes;
   }
};

// Deliverable 7
/**
 * Represents a student with a name, GPA, and address.
 */
class Student
{
  private:
    string name;
    float gpa;
    string address;
  public:
    /**
     * Default constructor for Student.
     */
    Student()
    {
      name = "";
      gpa = 0.0;
      address = "";
    }
    /**
     * Parameterized constructor for Student.
     * @param n The name of the student.
     * @param g The GPA of the student.
     * @param a The address of the student.
     */
    Student(string n, float g, string a)
    {
      name = n;
      gpa = g;
      address = a;
    }
    // copy constructor
    /**
     * Copy constructor for Student.
     * @param other The student to be copied.
     */
    Student(const Student &other)
    {
        name = other.name;
        gpa = other.gpa;
        address = other.address;
    }

    // converts the value of the instance
    // variables into a formatted string value
    /**
     * Converts the student object into a formatted string.
     * @return The formatted string representation of the student.
     */
    string to_string() const
    {
      string formatted;
      formatted = "Name: " + name + ", GPA: " + std::to_string(gpa) + ", Address: " + address;
      return formatted;
    }
    /**
     * Equality operator for comparing two students.
     * @param other The student to compare with.
     * @return True if the students are equal, false otherwise.
     */
    bool operator==(const Student &other) const
    {
      bool flag = (name == other.name && gpa == other.gpa && address == other.address);
      return flag;
    }
    friend ostream &operator<<(ostream &out, const Student &Studnet);
};

/**
 * Overloaded ostream operator to output the formatted string representation of a student.
 * @param out The output stream.
 * @param student The student to be output.
 * @return The output stream.
 */
ostream &operator<<(ostream &out, const Student &student)
{
    string output = student.to_string();
    out << output;
    return out;
}

// Deliverable 8
int main()
{
  DoublyLinkedList<Student> studVector;

  //Declaring 10 studnets
  for(int i = 0; i < 10; i++)
  {
    string name = "Student " + to_string(i);
    float gpa = 2.5 + i * 0.1;
    string address = "Address: " + to_string(i);
    Student s(name, gpa, address);
    studVector.push_back(s);
  }

  cout << "All Studnet Objects: " << endl;
  studVector.displayList();
  cout << endl;

  DoublyLinkedList<Student> cpStudVector(studVector); // Utilize the copy constructor
  cout << "Copied Student Objects:" << endl;
  cpStudVector.displayList();

  cout << endl;
  studVector.reverse();
  cout << "Reversed Student Objects:" << endl;
  studVector.displayList();

  Student stObj("Student 5", 3.0, "Address: 5");
  cout << "Index positions of Student5 in studVector:" << endl;
  vector<int> indexes = studVector.search(stObj);
    for (int index : indexes)
    {
        cout << index << " ";
    }
  cout << endl << endl;

  cout << "Deleting Student5 from studVector..." << endl;
  studVector.deleteItem(stObj);

  cout << "Remaining Student Objects:" << endl;
  studVector.displayList();

  return 0;
}
