#include <iostream>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


// WARNING!!  This test suite does not contain any test cases for accessing elements out-of-bound.
//
// You must deploy exception throwing for all out-of-bound accesses.
int successCount, passCount;
int totalTestCases, totalAssertions;

bool assert_equal(int, int);
bool assert_equal(char, char);
bool assert_equal(string, string);
bool assert_equal(double, double, double);
void tearDown(bool result);

// ******************* //
// Turn this true once you have implemented the Minimum Four Special Member Functions!!
int testReady = true;
// ******************* //




// Test Case 1 - Constructor Tester
// - Will require you to implement getSize() and getElement() methods.
void testConstructor()
{
	printf("\n=== testConstructor() ===\n");
	bool result = true; // true;	

	objPos zeroPos, currentPos;
	objPosArrayList thisList;
	int expectedSize = 0;
	int actualSize = thisList.getSize();
	
	// First check the list size
	result &= assert_equal(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then check all elements in the array are zero-initialized via objPos() default constructor
	for(int i = 0; i < ARRAY_MAX_CAP; i++)
	{
		currentPos = thisList.getElement(i);
		actualCheck = zeroPos.isPosEqual(&currentPos);

		result &= assert_equal(expectedCheck, actualCheck);
	}

	// The destructor will be called automatically for stack-allocated objects

	tearDown(result);
}


// Test Case 2a - insertHead 1 Element 
// - Will require you to implement getHeadElement(), getTailElement(), and getElement() methods.
void testInsertHead_1Element()
{
	printf("\n=== testInsertHead_1Element() ===\n");
	bool result = true; // true;	

	objPos currentPos;
	objPos samplePos(2, 5, 'a');  

	// Insert 1 sample element
	objPosArrayList thisList;
	thisList.insertHead(samplePos);

	int expectedSize = 1;
	int actualSize = thisList.getSize();
		
	// First check the list size is 1
	result &= assert_equal(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then check whether the head element is what we have inserted.
	currentPos = thisList.getHeadElement();
	actualCheck = samplePos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);


	// Next, check whether the tail element is also the head element in a list of 1 element.
	currentPos = thisList.getTailElement();
	actualCheck = samplePos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);


	// Finally, chech whether the element at index = 0 is also the head element in a list of 1 element
	// Then check whether the head element is what we have inserted.
	currentPos = thisList.getElement(0);
	actualCheck = samplePos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);

	// The destructor will be called automatically for stack-allocated objects

	tearDown(result);
}

// Test Case 2b - insertHead 5 Element 
// - Will require you to implement getHeadElement() and getTailElement() method.
void testInsertHead_5Element()
{
	printf("\n=== testInsertHead_5Element() ===\n");
	bool result = true; // true;	

	objPos currentPos;
	objPos bodyPos(2, 5, 'a');  
	objPos headPos(3, 3, 'm');

	// Insert 4 body elements, then 1 unique head element
	objPosArrayList thisList;
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(headPos);

	int expectedSize = 5;
	int actualSize = thisList.getSize();
		
	// Confirm the list size is now 5
	result &= assert_equal(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then, check the head element is the unique element
	currentPos = thisList.getHeadElement();
	actualCheck = headPos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);

	// Next, chech the body elements at index 1, 2, and 3.
	for(int i = 1; i < actualSize - 1; i++)
	{
		currentPos = thisList.getElement(i);
		actualCheck = bodyPos.isPosEqual(&currentPos);

		result &= assert_equal(expectedCheck, actualCheck);	
	}

	// Finally, check the tail element is the body element
	currentPos = thisList.getTailElement();
	actualCheck = bodyPos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);

	// The destructor will be called automatically for stack-allocated objects
	tearDown(result);
}



// Test Case 3a - insertTail 1 Element 
void testInsertTail_1Element()
{
	printf("\n=== testInsertTail_1Element() ===\n");
	bool result = true; // true;	

	objPos currentPos;
	objPos samplePos(2, 5, 'a');  

	// Insert 1 sample element
	objPosArrayList thisList;
	thisList.insertTail(samplePos);

	int expectedSize = 1;
	int actualSize = thisList.getSize();
		
	// First check the list size is 1
	result &= assert_equal(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then check whether the head element is what we have inserted.
	currentPos = thisList.getHeadElement();
	actualCheck = samplePos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);


	// Next, check whether the tail element is also the head element in a list of 1 element.
	currentPos = thisList.getTailElement();
	actualCheck = samplePos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);


	// Finally, chech whether the element at index = 0 is also the head element in a list of 1 element
	// Then check whether the head element is what we have inserted.
	currentPos = thisList.getElement(0);
	actualCheck = samplePos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);

	// The destructor will be called automatically for stack-allocated objects

	tearDown(result);
}

// Test Case 3b - insertTail 5 Element 
void testInsertTail_5Element()
{
	printf("\n=== testInsertTail_5Element() ===\n");
	bool result = true; // true;

	objPos currentPos;
	objPos bodyPos(2, 5, 'a');  
	objPos tailPos(3, 3, 'm');

	// Insert 4 body elements, then 1 unique head element
	objPosArrayList thisList;
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(tailPos);

	int expectedSize = 5;
	int actualSize = thisList.getSize();
		
	// Confirm the list size is now 5
	result &= assert_equal(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then, check the head element is the common body element
	currentPos = thisList.getHeadElement();
	actualCheck = bodyPos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);

	// Next, chech the body elements at index 1, 2, and 3.
	for(int i = 1; i < actualSize - 1; i++)
	{
		currentPos = thisList.getElement(i);
		actualCheck = bodyPos.isPosEqual(&currentPos);

		result &= assert_equal(expectedCheck, actualCheck);	
	}

	// Finally, check the tail element is the body element
	currentPos = thisList.getTailElement();
	actualCheck = tailPos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);

	// The destructor will be called automatically for stack-allocated objects

	tearDown(result);
}


// Test Case 4a - removeHead from 1 Element List
void testRemoveHead_1Element()
{
	printf("\n=== testRemoveHead_1Element() ===\n");
	bool result = true; // true;

	objPos currentPos;
	objPos samplePos(2, 5, 'a');  

	// Insert 1 sample element
	objPosArrayList thisList;
	thisList.insertHead(samplePos);

	thisList.removeHead();

	int expectedSize = 0;
	int actualSize = thisList.getSize();
		
	result &= assert_equal(expectedSize, actualSize);
	// The destructor will be called automatically for stack-allocated objects

	tearDown(result);
}

// Test Case 4b - removeHead from 5 Element list
void testRemoveHead_5Element()
{
	printf("\n=== testRemoveHead_5Element() ===\n");
	bool result = true; // true;

	objPos currentPos;
	objPos bodyPos(2, 5, 'a');  
	objPos headPos(3, 3, 'm');

	// Insert 4 body elements, then 1 unique head element
	objPosArrayList thisList;
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(headPos);

	thisList.removeHead();
	
	int expectedSize = 4;
	int actualSize = thisList.getSize();
		
	// Confirm the list size is now 4
	result &= assert_equal(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then, check the unique element has been removed
	currentPos = thisList.getHeadElement();
	actualCheck = bodyPos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);

	// Next, the rest of the elements are still common elements
	for(int i = 1; i < actualSize; i++)
	{
		currentPos = thisList.getElement(i);
		actualCheck = bodyPos.isPosEqual(&currentPos);

		result &= assert_equal(expectedCheck, actualCheck);	
	}

	// The destructor will be called automatically for stack-allocated objects

	tearDown(result);
}

// Test Case 5a - removeTail 1 Element 
void testRemoveTail_1Element()
{
	printf("\n=== testRemoveTail_1Element() ===\n");
	bool result = true; // true;

	objPos currentPos;
	objPos samplePos(2, 5, 'a');  

	// Insert 1 sample element
	objPosArrayList thisList;
	thisList.insertTail(samplePos);

	thisList.removeTail();

	int expectedSize = 0;
	int actualSize = thisList.getSize();
		
	// First check the list size is 1
	result &= assert_equal(expectedSize, actualSize);

	// The destructor will be called automatically for stack-allocated objects

	tearDown(result);
}

// Test Case 5b - removeTail 5 Element 
void testRemoveTail_5Element()
{
	printf("\n=== testRemoveTail_5Element() ===\n");
	bool result = true; // true;

	objPos currentPos;
	objPos bodyPos(2, 5, 'a');  
	objPos tailPos(3, 3, 'm');

	// Insert 4 body elements, then 1 unique head element
	objPosArrayList thisList;
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(tailPos);

	thisList.removeTail();

	int expectedSize = 4;
	int actualSize = thisList.getSize();
		
	// Confirm the list size is now 4
	result &= assert_equal(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then, check the tail element removed
	currentPos = thisList.getTailElement();
	actualCheck = bodyPos.isPosEqual(&currentPos);

	result &= assert_equal(expectedCheck, actualCheck);

	// Next, chech the body elements at index 1, 2, and 3.
	for(int i = 0; i < actualSize - 1; i++)
	{
		currentPos = thisList.getElement(i);
		actualCheck = bodyPos.isPosEqual(&currentPos);

		result &= assert_equal(expectedCheck, actualCheck);	
	}

	// The destructor will be called automatically for stack-allocated objects

	tearDown(result);
}




//===========================================================
	bool runAllTests(int argc, char const *argv[]) {
		
		testConstructor();

		testInsertHead_1Element();
		testInsertHead_5Element();

		testInsertTail_1Element();
		testInsertTail_5Element();

		testRemoveHead_1Element();
		testRemoveHead_5Element();

		testRemoveTail_1Element();
		testRemoveTail_5Element();
		
		return (successCount == totalAssertions);
	}

int main(int argc, char const *argv[]) {
  		
	bool testResult = false;
	successCount = 0;
	passCount = 0;
    totalAssertions = 0;
    totalTestCases = 0;
    	
	testResult = runAllTests(argc, argv);

	cout << endl << "=== Array List Test Report ===";
	if(testResult)	cout << endl << "Passed All Tests" << endl; 
	else			cout << endl << "Failed Tests, Check Failure" << endl;

	cout << "Test Case Result: " << passCount << " / " << totalTestCases << endl;
	cout << "Assertion Result: " << successCount << " / " << totalAssertions << endl << endl;		

	
	return testResult? EXIT_SUCCESS : EXIT_FAILURE;
}
    
bool assert_equal(int a, int b)
{
	bool result = (a == b);
	if(result)	
		successCount++;
	else
	{
		cout << "\t\t[ASSERTION] Expected: " << a << ", but Actual: " << b << endl;	
	}

    totalAssertions++;
	return result;
}

bool assert_equal(char a, char b)
{
	bool result = (a == b);
	if(result)	
		successCount++;
	else
	{
		cout << "\t\t[ASSERTION] Expected: " << a << ", but Actual: " << b << endl;
	}

    totalAssertions++;
	return result;
}

bool assert_equal(string a, string b)
{
	bool result = (a == b); 
	if(result)	
		successCount++;
	else
	{
		cout << "\t\t[ASSERTION] Expected: " << a << ", but Actual: " << b << endl;
	}

    totalAssertions++;
	return result;
}


bool assert_equal(double a, double b, double tolRange)
{
	bool result = ((a <= (b + tolRange)) && (a >= (b - tolRange)));
	if(result)	
		successCount++;
	else
	{
		cout << "\t\t[ASSERTION] Expected: " << a << ", but Actual: " << b << endl;
	}

    totalAssertions++;
	return result;
}

void tearDown(bool result)
{
    totalTestCases++;
    
    if(result) 
    {
        passCount++;
        cout << "Passed" << endl;
    }
    else
    {
        cout << "!!! FAILED !!!" << endl;
    }
}