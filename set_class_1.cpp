/***********************************************************************
* Program:
*    Assignment 01, Set Class
*    Brother Ercanbrack, CS235
* Author:
*    David Pappe
* Summary: 
*    This program  will load set of elements and execute intersection,
*    substraction and union operations between them. It also will
*     display the result of these operation executed from main.
************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
using namespace std;

class SetClass
{
   private:
      int capacity;
      int *setOfElementsPtr;
      int size;

      void sortElements(int *setOfElementsPtr);
      void swapElement (int& element1, int& element2);
      int  indexOfSmallest (int *setOfElementsPtr, int startIndex, int capacity);
      void removeDuplicates (int *setOfElementsPtr);

   public:
      SetClass();
      SetClass (int theCapacity);
      SetClass(const SetClass& setClassObj);
      ~SetClass();

      void addElement(int theElement);
      void displayElements() const;
      int  getCapacity() const   { return capacity; };
      bool ifElementExist (int theElement) const;
      void setCapacity(int theCapacity) { capacity = theCapacity; }

      SetClass& operator =(const SetClass& setClassObj);
      SetClass operator -(const SetClass& setClassObj);
      SetClass operator ||(const SetClass& setClassObj);
      SetClass operator &&(const SetClass& setClassObj);

};

/**********************************************************************
* Constructor  SetClass::SetClass()
* 
***********************************************************************/
SetClass::SetClass()
{
   capacity = 0;
   size = 0;
   setOfElementsPtr = NULL;
}

/**********************************************************************
* Constructor  SetClass::SetClass(int theCapacity)
* 
***********************************************************************/
SetClass::SetClass(int theCapacity)
{
   capacity = theCapacity;
   size = 0;
   setOfElementsPtr = NULL;
}

/**********************************************************************
* Copy Constructor  SetClass::SetClass(const SetClass& setClassObj)
* Input  setClassObj - it contains a copy of the original object
* Output 
***********************************************************************/
 SetClass::SetClass(const SetClass& setClassObj)
 {
   capacity = setClassObj.getCapacity();
   setOfElementsPtr = new int[capacity];

   for (int i = 0; i < capacity; ++i)
   {
      setOfElementsPtr[i] = setClassObj.setOfElementsPtr[i];
   }
 }

/**********************************************************************
* void SetClass::addElement(int theElement)
* 
***********************************************************************/
void SetClass::addElement(int theElement)
{
   if (size == 0)
   {
      setOfElementsPtr = new int[capacity];
   }

   setOfElementsPtr[size]= theElement;
   if (size == capacity - 1)
   {
      sortElements(setOfElementsPtr);
      removeDuplicates(setOfElementsPtr);
   }
   size++;   
}
/**********************************************************************
* Destructor SetClass::~SetClass()
* 
***********************************************************************/
SetClass::~SetClass()
{
   delete [] setOfElementsPtr;
   setOfElementsPtr = NULL;
}

/**********************************************************************
* Display void SetClass::displayElements(SetClass mySetOfElements)
* 
***********************************************************************/
void SetClass::displayElements() const
{
   for (int i = 0; i < capacity; ++i)
   {
      cout << setw(4) << setOfElementsPtr[i];
      if ( ((i + 1) % 10 == 0) && i < capacity)
      {        
         if ((i + 1) != capacity)
         {
            cout << endl;
         }
      }
   }
   cout << endl << endl;
}

/************************************************************************
*  Sort --  void SetClass::sortElements(int *setOfElementsPtr)
*  Desc:    Sorts the elements that are store in the set buffer
*  Inputs:  setOfElementsPtr - unorder array of elements
*  Outputs: setOfElementsPtr - order array of elements
*  return:  none
**************************************************************************/
void SetClass::sortElements(int *setOfElementsPtr)
{
   int indexOfNextSmallest = 0;     // Holds the smallest index
   for (int i = 0; i < capacity; ++i)
   {
      indexOfNextSmallest = indexOfSmallest (setOfElementsPtr, i, capacity);
      swapElement (setOfElementsPtr[i], setOfElementsPtr[indexOfNextSmallest]);
   }
}

/**************************************************************
* Name: Swap Names Function
* Desc: This function only swap elements
* Inputs:  element1         -  A element
* Outputs: element2         -  A element
* Return:  none
**************************************************************/
void SetClass::swapElement (int& element1, int& element2)
{
   int temp;                // Holds a temporal record
   temp    = element1;
   element1 = element2;
   element2 = temp;
}

/********************************************************************
* Name: Index Of Smallest Function
* Desc: This function computes the small index between two elements
* Inputs:  setOfElementsPtr    - The array of all elements.
*          startIndex          - Contains the initial index of a record
*          capacity            - the array size
* Outputs: none
* return:  indexOfMin     - Index of the Smallest
*********************************************************************/
int SetClass::indexOfSmallest (int *setOfElementsPtr, int startIndex, int capacity)
{
   int min     = setOfElementsPtr[startIndex];
   int indexOfMin = startIndex;

   for (int index = startIndex + 1; index < capacity; index++)
   {
      if (setOfElementsPtr[index] < min)
      {
         min = setOfElementsPtr[index];
         indexOfMin = index;
      }
   }
   return indexOfMin;
}

/********************************************************************
* Name: removeDuplicates
* Desc: This function remove dupicates
* Inputs:  studentList    - The array of all records.
*          startIndex     - Contains the initial index of a record
* Outputs: none
* return:  indexOfMin     - Index of the Smallest
*********************************************************************/
void SetClass::removeDuplicates (int *setOfElementsPtr)
{
   int noDups = 0;

   for (int i = 0; i < capacity; i++)
   {
      if (setOfElementsPtr[i] != setOfElementsPtr[noDups])
         setOfElementsPtr[++noDups] = setOfElementsPtr[i];
   }

   capacity = noDups + 1;
   size = capacity;
}

/********************************************************************
* Name: ifElementExist
* Inputs:  studentList    - The array of all records.
* Outputs: none
* return:  indexOfMin     - Index of the Smallest
*********************************************************************/
bool SetClass::ifElementExist ( int theElement) const
{
   for (int i = 0; i < this->capacity; i++)
   {
      if (this->setOfElementsPtr[i] == theElement)
         return true;
   }
   return false;
}

/**********************************************************************
* Asignment Operator
* SetClass& SetClass::operator =(const SetClass& setClassObj)
* Input  setClassObj  - 
***********************************************************************/
SetClass& SetClass::operator =(const SetClass& setClassObj)
{
   if (this == &setClassObj)
   {
      return *this;
   }
   else
   {
      if (setClassObj.capacity > capacity)
      {
         delete [] setOfElementsPtr;
         setOfElementsPtr = new int [setClassObj.capacity];
         capacity = setClassObj.capacity;
      }

      for (int i = 0; i < setClassObj.capacity; i++)
      {
         setOfElementsPtr[i] = setClassObj.setOfElementsPtr[i];
      }
      return *this;
   }
}

/**********************************************************************
* Substraction Operator
* 
***********************************************************************/
SetClass SetClass::operator -(const SetClass& setClassObj)
{
   int macthedElements = 0;

   for (int i = 0; i < this->capacity; i++)
   {
      for (int j = 0; j < setClassObj.capacity; j++)
      {
         if (this->setOfElementsPtr[i] == setClassObj.setOfElementsPtr[j])
         {
            macthedElements++;
         }
       }
    }

   SetClass result(this->capacity - macthedElements);

   for (int i = 0; i < this->capacity; i++)
   {
       if (!(setClassObj.ifElementExist(this->setOfElementsPtr[i])))
         {
            result.addElement(this->setOfElementsPtr[i]);
         }
    }

   return result;
}

/**********************************************************************
* Union Operator 
* SetClass SetClass::operator ||(const SetClass& setClassObj)
***********************************************************************/
SetClass SetClass::operator ||(const SetClass& setClassObj)
{
   SetClass result(this->capacity + setClassObj.capacity);

   for (int i = 0; i < this->capacity; i++)
   {
      result.addElement(this->setOfElementsPtr[i]);
   }

   for (int j = 0; j < setClassObj.capacity; j++)
   {
      result.addElement(setClassObj.setOfElementsPtr[j]);
   }
   return result;
}

/**********************************************************************
* Intersection Operator
* SetClass SetClass::operator &&(const SetClass& setClassObj)
***********************************************************************/
SetClass SetClass::operator &&(const SetClass& setClassObj)
{
   int macthedElements = 0;
   SetClass result;

   for (int i = 0; i < this->capacity; i++)
   {
      for (int j = 0; j < setClassObj.capacity; j++)
      {
         if (this->setOfElementsPtr[i] == setClassObj.setOfElementsPtr[j])
         {
            macthedElements++;
         }
       }
    }

   if ( macthedElements > 0)
   { 
      if (this->capacity == setClassObj.capacity)
      {
         result.setCapacity(capacity);
      }
      else
      {
         result.setCapacity(this->capacity - macthedElements);  
      }

      for (int i = 0; i < this->capacity; i++)
      {
          if ((setClassObj.ifElementExist(this->setOfElementsPtr[i])))
         {
            result.addElement(this->setOfElementsPtr[i]);
         }
      }
         return result;
   }
    return NULL;
 }

/**********************************************************************
* Main Function
* It will read the records from a file, put the in a string array and
* sort all the names. Then, it gets the name to be found and search
* it in the sort it array. Finally, it will print the record found on
* the screen.
***********************************************************************/
int main(int argc, char **argv)
{
   string filename = argv[argc - 1];
   int theElement ; 
   int theCapacity;

  ifstream  inFile (filename.c_str());
   
  // Checks the file if it exist
  if (inFile.fail())
  {
    cout << "Unable to open \""
         << filename << "\"" << endl;
      
    return false;
  }

  inFile >> theCapacity;
  SetClass setA(theCapacity);

  for (int i = 0; i < theCapacity; ++i)
  {
      inFile >> theElement;
      setA.addElement(theElement);
  }

   inFile >> theCapacity;

   SetClass setB(theCapacity);
   for (int i = 0; i < theCapacity; ++i)
   {
      inFile >> theElement;
      setB.addElement(theElement);
   }  

   cout << "Set A:" << endl;
   setA.displayElements();

   cout << "Set B:" << endl;
   setB.displayElements();

   SetClass intersectionSet;
   intersectionSet = setA && setB;
   cout << "Intersection of A and B:" << endl;
   intersectionSet.displayElements();


   SetClass unionSet;
   unionSet = setA || setB;
   cout << "Union of A and B:" << endl;
   unionSet.displayElements();

   SetClass diff;
   diff = setA - setB;
   cout << "Difference of A and B:" << endl;
   diff.displayElements();

   SetClass diff2;
   diff2 = setB - setA;
   cout << "Difference of B and A:" << endl;
   diff2.displayElements();

   return 0;
}