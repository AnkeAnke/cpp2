struct Handle // For A1
{
	// Standard ctor
	Handle() : val(-1) {}

	// Copy ctor
	Handle(const Handle& other) : val(other.val) {}

	// Assignment operator
    Handle& operator= (const Handle& other) { val = other.val; return *this; }
    // Normal function
    Handle& copyFrom  (const Handle& other) { val = other.val; return *this; }

    int val;
};


struct Number // For A2 & 3
{
		// Constructs a new number when no further information is given. Hence, standard constructor.
		Number() : val(0) {}

		// Constructs a number when we give it an int.
		Number(int v) : val(v) {} 

		// Constructs a number from another number by copying all data. Hence, copy constructor.
		Number(const Number& other) : val(other.val) {}

		// A glorified function that takes two Numbers (this and other) and adds them together.
		// The result is a new Number that did not exist before, so we can not hand out a reference.
		// Also, we need to leave this (hence this v const) and the other Number (hence const Number&) untouched. See line 90-91.
		Number operator+ (const Number& other) const { return Number(val + other.val); }

		// These two lines do actually change our object, so no const.
		// Both variants are legal. See line 114-115..
		void    operator+= (const Number& other) { somehowChange(other); }
		Number& operator-= (const Number& other) { somehowChangeDifferently(other); return *this; }

		int val;
	};

int main()
{
	//~~~~~~~~~~~~~~~~ A1.1: Is assignment a constructor? ~~~~~~~~~~~~~~~~//

	// Standard construction.
	Handle a, b, c;

	// The operator= should _overwrite_ the data of the left hand object.
	// The following lines do exactly the same thing:
	a = b;			// Syntactic sugar (looks prety, is not special functionality)
	a.operator=(b); // That's the real function name.
	a.copyFrom(b);

	// A constructor creates an object that was not there before. It _initializes_ it.
	Handle aCopy(a);

	// ------------ SIDE NOTES ------------//

	// Sometimes, you need to call the operator by name.
	Handle* aPointer = &a;
	aPointer->operator=(b); // Since = would change the pointer, not the data.

	// When we remember that "ctor initializes a new instance" and "assignment overwrites an existing instance", we understand why this:
	Handle anotherCopy = a; // Does call the copy CTOR. anotherCopy did not exist beforehand, so instead of constructing and directly overwriting it, we can just copy construct it.


	//~~~~~~~~~~~~~~~~ A1.2: Why does the assignment return something? ~~~~~~~~~~~~~~~~//

	// Since operator= has a return type, we can save it in a variable. So line 21 becomes:
	Handle& resultOfAssignment = (a = b); // The parantheses is what the compiler does internally, starting from the rightmost operator=.
	// The result is that a=b, and that resultOfAssignment equals a. You can see that from the operator= function returning *this.
	// So we can now write code like this:
	a = b = c; // Making everything equal to c.


	//~~~~~~~~~~~~~~~~ A2: What constructor is called? ~~~~~~~~~~~~~~~~//

	// The "constructor fucntion" is overloaded, meaning there are several functions with the same name, but different parameters.
	// The compiler will chose the one that fits best.
	Number fromInt(7);					// Ctor, since the function gets an int
	Number b(3);
	Number c(7);
	Number fromOtherNumber(fromInt);	// Copy ctor, since the function gets an object it can copy.

	// Standard ctor, since we did not give any further information.
	Number a;

	// Some equivalent calls again.
	a = b + c;
	a = b.operator+(c);
	// Why the const in the parameters? You woud expect a = 10, b = 3, c = 7. That should be true before and after the call, so put const.

	//~~~~~~~~~~~~~~~~ A3: What about other operators? ~~~~~~~~~~~~~~~~//

	// Operators are specially named functions with syntactic sugar.
	// There are only a few of them, and the parameters are set (you can not have a = without one object on the left and one on the right).
	// There of course is an understanding what they should do: + should add two things together and make a new thing. += should make a thing greater by the amout of the other thing.
	// Anyways, there is no _rule_ forbidding you from writing anything into those operators... = could add things, + could assign, whatever you like. But that makes your code hellish to read!
	// Also, libraries like the standard librard (std::something) will assume that the operator= makes two things equal. If it does not, that's your fault.

	// +=, -=, *=, /=, ^= ... look very similar to the operator=. And if you think about their signature (input and output), that makes sense:
	// They all need a left-hand side object that is changed and a right-hand side object that we use to make that change.
	// Again, they are just functions, thus these are equivalent:
	a -= b;
	a.operator-=(b);  

	// What about return values?
	c = a -= b; // This is allowed. It is the same as:
	c = (a -= b);
	// This is useful, but at the same time, potentially confusing and error-prone.

	// You can omiss the return value. Then you can not chain operators. It is completely your choice whether you want to allow operator chaining!
	c = a -= b; // Allowed, since operator-= returns a.
	c = a += b; // Not allowed, since we return void for operator+=.

}