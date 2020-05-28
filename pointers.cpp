#include <iostream>

using namespace std;

//int main(){
//int a = 5;

//int *b = &a;

//int *b1;

//*b1 = 5;

//int *c = &a;

//int *d = &c;

//int &x = a;
//cout << "a ="  <<   a << endl;
//cout << "*a =" <<  &a << endl;
//cout << "&a =" <<  &a << endl;
//cout << "*b1 ="  <<  *b1 << endl;
//cout << "*c =" <<  *c << endl;
//cout << "&b =" <<  &b << endl;
//cout << "b1 =" <<  b1 << endl;
//cout << "*b1 ="<<  **b1 << endl;
//cout << "&b1 ="<<  &b1 << endl;

//}
//#include <stdlib.h>
//main(){
//	int **mat;			// integer double pointer
//	int row=5,col=5;		// row = no of rows, col= no of columns
	
//	int i;
//	mat = (int**)malloc(row*sizeof(int*));
//	for (i=0;i<row;i++){
//		mat[i]= (int*)malloc(col*sizeof(int));
//		cout << &mat[i] << endl;
//}
	
//}
//#include <iostream> 
//using namespace std; 
  
void swap(int* x, int* y) 
{ 
    int z = *x; 
    *x = *y; 
    *y = z; 
} 
  
int main() 
{ 
    int a = 45, b = 35; 
    cout << "Before Swap\n"; 
    cout << "a = " << a << " b = " << b << "\n"; 
  
    swap(&a, &b); 
  
    cout << "After Swap with pass by pointer\n"; 
    cout << "a = " << a << " b = " << b << "\n"; 
} 
