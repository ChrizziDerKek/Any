
# Any

Simple boxed data type for C++. It's similar to the object type from Java or C# but worse.

## How it works

This library implements an IGeneric class which contains all overloadable operators and some virtual methods that can be reimplemented by the actual data types. A pointer to this class is our Any data type. In that case I decided to use shared pointers. It also introduces a lot of basic data types like Int, String, etc. which all inherit the IGeneric class. They also define their supported methods for the operators (A table that shows which type supports which methods and operators can be found below) and store their value. This value can be retrieved by the IGeneric / Any class by using the Serialize method that returns the value as a void pointer. Each of these classes also implements a GetType method so that we know which type we stored in an Any object.

## How to use
Simple, just include the any.hpp file and you're done!

It will introduce a new type called Any that can contain the following data types (Their boxed types are in brackets):
- integers (Long, ULong, Int, UInt, Short, UShort, SByte, Byte)
- floats (Double, Float)
- strings and characters (String, Char, WString, WChar)
- booleans (Bool)
- raw pointers (PVoid)
- functions (Function)

Each of these types inherits the Any type, so they are all compatible and can be represented in a single type.

With the construct method, you can create such a type, like this:

```cpp
Any number = construct<Int>(1337);
```

You can get the actual type of the Any-Object with GetType which returns a value from the eType enum:

```cpp
Any number = construct<Int>(1337);
std::cout << number->GetType() << std::endl;
```

The value can be retrieved by one of many get-Methods:

```cpp
Any number = construct<Int>(1337);
std::cout << number->GetInt() << std::endl;
//Output: 1337

Any str = construct<String>("Hello World!");
std::cout << str->GetString() << std::endl;
//Output: Hello World!
```

Also there are many different methods and operators that can be used to modify the values:

```cpp
Any first = construct<Int>(1300);
Any second = construct<Int>(30);
Any third = construct<Int>(6);
second += third;
++second;
Any result = first + second;
std::cout << result->GetInt() << std::endl;
//Output: 1337
```

Below you can see a table of operators which shows which datatype supports which ones.

## General Method overview
These methods can be used by every type (except the Call method, which can only be used by a Function) and can be accessed publicly:
- ``eType GetType()``: Gets the type of the Any object
- ``std::string ToString()``: Returns the value of the Any object as a string
- ``Any Clone()``: Creates a copy of the Any object
- ``void* Call(void* arg)``: Calls the stored function with an arg and a return value

## Operator overview

| Function (Operator) / Datatype | Long | ULong | Int | UInt | Short | UShort | SByte | Byte | Double | Float | PVoid | Bool | String | Char | WString | WChar | Function |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Add (x + y) | x | x | x | x | x | x | x | x | x | x |  |  | x |  | x |  |  |
| Sub (x - y) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |
| Mul (x * y) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |
| Di (x / y) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |
| Mod (x % y) | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |  |  |
| Xor (x ^ y) | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |  |  |
| And (x & y) | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |  |  |
| Or (x \| y) | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |  |  |
| Neg (~x) | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |  |  |
| Not (!x) | x | x | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |
| Inc (++x) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |
| Inc (x++) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |
| Dec (--x) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |
| Dec (x--) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |
| EAdd (x += y) | x | x | x | x | x | x | x | x | x | x |  |  | x |  | x |  |  |
| ESub (x -= y) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |
| EMul (x *= y) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |
| EDiv (x /= y) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |
| EMod (x %= y) | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |  |  |
| EXor (x ^= y) | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |  |  |
| EAnd(x &= y) | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |  |  |
| EOr (x \|= y) | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |  |  |
| Compare (x == y) | x | x | x | x | x | x | x | x | x | x | x | x | x | x | x | x | x |
| Compare (x != y) | x | x | x | x | x | x | x | x | x | x | x | x | x | x | x | x | x |
| Compare (x > y) | x | x | x | x | x | x | x | x | x | x |  | x |  |  |  |  |  |
| Compare (x < y) | x | x | x | x | x | x | x | x | x | x |  | x |  |  |  |  |  |
| Compare (x >= y) | x | x | x | x | x | x | x | x | x | x |  | x |  |  |  |  |  |
| Compare (x <= y) | x | x | x | x | x | x | x | x | x | x |  | x |  |  |  |  |  |
| UAdd (+x) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |
| USub (-x) | x | x | x | x | x | x | x | x | x | x |  |  |  |  |  |  |  |

## Adding your own types
1) Add a new entry to the eType enum
2) Define a class for your type that inherits IGeneric
3) Add a variable to your class that stores the value (I always called them m_Value)
4) Implement the Serialize method and return your value as a void pointer
5) Implement the GetType method and return your type defined in eType
6) Add a constructor that sets your value
7) Optional: Define the methods from the table above if you plan to use them or their operators with your type
8) Optional: Add a Get method to IGeneric for easier access to your type

Example type:
```cpp
//1) eType::IntPtr was already defined

class IntPtr : public IGeneric //2)
{
protected:
	int* m_Value; //3)
    
    void* Serialize() override { return (void*)m_Value; } //4)
    eType GetType() override { return eType::IntPtr; } //5)
    
    int Compare(Any that) override { ... } //6)
    Any Clone() { ... } //6)
    //...
    
public:
	IntPtr(int* val) : m_Value(val) { } //6)
}

//8) Method is defined in IGeneric class
int* GetIntPtr() { return (int*)Serialize(); }
```

## More Examples
```cpp
#include "any.hpp"
#include <iostream>

//Example function that will be used as an Any object
void* HelloWorld(void* a) {
	std::cout << ((IGeneric*)a)->GetString() << std::endl << std::endl;
	return nullptr;
}

//Program entrypoint
int Main() {
	//Create a string that we can pass to the method
	Any msg = construct<String>("Hello World!");
	//Create an object for the function we want to call
	Any func = construct<Function>(HelloWorld);
	//Call the function
	func->Call((void*)msg.get());
	//Output: Hello World!

	//Create two floats
	Any v1 = construct<Float>(0.1f);
	Any v2 = construct<Float>(0.2f);
	//Add them together
	Any result = v1 + v2;
	std::cout << result->GetFloat() << std::endl << std::endl;
	//Output: 0.3

	//Create a counter variable
	Any i = construct<Int>(0);
	//Count to 69
	Any limit = construct<Int>(69);
	while (i < limit)
		++i;
	std::cout << i->GetInt() << std::endl;
	//Output: 69
	std::cout << (i == limit) << std::endl << std::endl;
	//Output: 1

	//Count from 10 to 0
	for (Any j = construct<Int>(10); j >= construct<Int>(0); j--)
		std::cout << j->GetInt() << std::endl;
	std::cout << std::endl;
	//Output:
	//10
	//9
	//8
	//7
	//6
	//5
	//4
	//3
	//2
	//1
	//0
	
	return 0;
}
```