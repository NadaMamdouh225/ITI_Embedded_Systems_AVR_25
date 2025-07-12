# Session: Data Modifiers
## Lecture Lab 1
### Problem

<img src="../../assets/s5_lab2.png">

### Solution
```c
#include <stdio.h>

int main()
{
	unsigned int x=-1;
	printf("%u\n",x);
	
	return 0;
}

```

## Lab 1
### Problem
Write a c program to convert from decimal to binary using (functions, arrays, and pointers) 

<img src="../../assets/s5_lab1.png">

### Solution
```c

#include <stdio.h>

void decimal_to_binary(int arr[], long long int num, int* size);

int main(){
	
	long long int num;
	int	size;
	int binary_arr[50];
	
	printf("Enter a decimal number: ");
	scanf("%lld",&num);
	
	decimal_to_binary(binary_arr, num, &size);
	
	// Print binary array in reversed order
	printf("Binary: ");
	for(int i=size-1; i>=0; i--)
	{
		printf("%d ", binary_arr[i]);
	}
	printf("\n");

    return 0;
}

void decimal_to_binary(int arr[], long long int num, int* size)
{
	*size = 0;
	while(num>0)
	{
		// record the remainder
		arr[*size] = num%2;
		
		// divide by 2
		num /= 2;
		(*size)++;
		
	}
}
```
## Lab 2 : const keyword
`unsigned char* ptr = &x;`<br>
*Explaination*<br>
`ptr` is a pointer to `unsigned char`.The value pointed to can be changed, and the pointer itself can point to different addresses.

`unsigned char* const ptr = &x;`<br>
*Explaination* <br>
const pointer (this pointer can't point to another variable. only holding one address) to unsigned char<br>

`const unsigned char* ptr = &x;`<br>
*Explaination* <br>
pointer to a const unsigned char (which means the value of the pointee couldn't be changed, but this pointer could point to different addresses)<br>


`const unsigned char* const ptr = &x;`<br>
*Explaination* <br>
const ptr to const unsigned char (value of x wouldn't be changed nor the pointer would point to another variable)<br>


## Lab 3 : static keyword
### Problem : Notice the problem in the following codes
```c
#include <stdio.h>

int increment(void);

int main(){
	
	increment();
	increment();
	increment();
	
    return 0;
}

int increment(void)
{
	int counter =0;
	counter++;
	printf("%d\n", counter);
}

```

 Both count() and another_counter() access and modify the same global variable counter, so their behaviors are not independent. Also, any function in any file can change `counter`, leading to unpredictable bugs, especially in embedded systems. 

```c
#include <stdio.h>

void count (void);
void another_counter(void);
int counter = 0;

int main() {
	count();
	another_counter();
	count();

    return 0;
}

void count(void)
{
	counter++;
	printf("%d\n",counter);
}

void another_counter(void)
{
	counter++;
	printf("%d\n",counter);
}
```

You can't modify counter through a pointer, the variable itself doesn’t persist between calls. `counter` is a normal local variable, it is reset to 0 every call. 

```c
#include <stdio.h>

int increment(void);

int main() {
    increment();
    increment();
    increment();
    return 0;
}

int increment(void) {
    int counter = 0;         // new each time
    int* ptr = &counter;
    (*ptr)++;
    printf("%d\n", counter);
}

```
### Solution : Fixed version (use static keyword)
```c
#include <stdio.h>

int increment(void);

int main(){
	
	increment();
	increment();
	increment();
	
    return 0;
}

int increment(void)
{
	static int counter =0;
	counter++;
	printf("%d\n", counter);
}

```


## Lab 4
### Problem
```
Write a C program to demonstrates how to use the `extern` keyword to share a global variable (sharedValue) between two source files `file1.c`, which contains the main function and modifies the variable, and `file2.c`, which defines the variable and contains a function (display) that accesses and prints its value.
```

### Solution 
In `file1`

```c
/*  
	This is a source file, there is no main function here
	only one file must contain the main() function. 
	That's the entry point for the entire program.
*/
#include <stdio.h>

int sharedValue = 10;

void display(void)
{
	printf("In src file1.c sharedValue = %d\n",sharedValue);
} 

```
In `file2`

```c
#include <stdio.h>

// Declare the variable that is defined in another file
extern int sharedValue;

void display(void);

int main()
{
	sharedValue = 50;
	// calling this function
	printf("In file2 sharedValue = %d\n", sharedValue);
	display();
	return 0;
}
```
### How to Compile:
`gcc file1.c file2.c -o out`
`out.exe`
