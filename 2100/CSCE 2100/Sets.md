Sets, Set Properties, and Set Operations

Definition:
- Collection of objects or elements.
	- Objects do not need to be of the same type

Ex.
- { ☺,  2, f(x), 1.3}

Equality:
- Sets are considered equivalent if they have their distinct contents are equal
	- Ex.
		- {1, 2, 3} == {1, 2, 2, 3, 3, 3}
		- {1, 2, 3} == {3, 2, 1} --> sets are unordered
		- {1, 2, 3} != {1, 2, 2}

Properties:
- All elements in a set are unique
	 - Duplicate elements do not change the state of a set
- Cardinality
	- Number of elements in a set
		 - Ex. Set A = {1, 2, 3} has a cardinality of 3 --> |A| == 3
- May or may not be finite
	- All real numbers (R)
- May or may not be countable
	- R is not countable, N (Natural numbers) are
- Sets can contain other sets
	- Ex.
		- Q2 = { {3, 2}, {6, {7, 1}, 9}, {-5}, {empty_set}}
		- |Q2| == 4

Notation:
- Sets are represented with curly braces ( { } ) where their contents are separated by commas ( , )
	- Roster notation
- Membership
	- num E Set
- Empty Set (O with a strike-through)
	- Cardinality of 0
	- The Empty Set does not contain any elements, no element is contained by the Empty Set

Sets in Math
- C
	- Complex Numbers (numbers of the form a + bi)
- R
	- Real Numbers
- Q
	- Rational Numbers (numbers of the form a / b where a, b are integers)
- Z
	- Integers
- N
	- Natural numbers

Power Sets
- Represent the set that contains all subsets of Set S
	- Represented by P(S)
	- |P(S)| = 2^|S|
- Ex.
	- If S = {A, B} , P(S) = {empty_set, {A}, {B}, {A, B}}
	- If S = {3}, P(S) = {empty_set, {3}}
	- If S = empty_set, P(S) = {empty_set}

Atoms
- Elements not in a set
- Indivisible

Set Builder Notation
- Abstraction of a set
- Ex.
	- S = {x | 0 <= x < 10}
		- Above defines the set of all digits, from 0 (inclusive) to 10 (exclusive)
		- Read: S equals the set of all 'x' such that x is greater than or equal to 0 and less than 10
	- S = {x | 0 <= x < 10 and x % 2 == 0}
		- Condition contains a predicate --> now, S only contains the even digits
	- S = {x E R : |x| < 1}
		- Equivalent to {x | x E R and |x| < 1}

Example Problem:
- Using the set of employees 'M' create a set 'S' that contains employees older than 60
- Ans:
	- S = { (first_name, last_name, age) | (first_name, last_name, age) E M and age > 60}

Set Operations
- Union (A U B)
	- Set that contains all elements of A and B
	- Ex.
		- A = {1, 2, 3} -- B = {2, 3, 4}
		- C = A u B;
		- C = {1, 2, 3, 4}
	- Commutative
- Intersection (A ∩ B)
	- Set that contains all elements in both A and B
	- Ex.
		- A = {1, 2, 3} -- B = {2, 3, 4}
		- C = A ∩ B
		- C = {2, 3}
	- Commutative
- Difference (A - B)
	- Set that contains all elements in A not in B
	- Ex.
		- A = {1, 2, 3} -- B= {2, 3, 4}
		- C = A - B = {1}
		- D = B - A = {4}
	- Not commutative
- Symmetric Difference (A Δ B)
	- Set that contains all elements in either A or B, but not both
	- A Δ B = A U B - A ∩ B
	- A Δ B = (A - B) U (B - A)
	- Ex.
		- A = {1, 2, 3} -- B= {2, 3, 4}
		- C = A Δ B = {1, 4}
	- Commutative
- Complement (A')
	- Assumes there exist some universal set (Let S be the universal set) of either finite or infinite cardinality that contains all pertinent value
	- A' = S - A
	- A = S - A'
	- A U A' = S
	- A ∩ A' = {}


Properties
- Commutative Property of Union
	- A u B == B u A
- Commutative Property of Intersection
	- A ∩ B == B ∩ A

Sequences
- U (i = 0 -> n)
	- S = Ai u A(i+1) ... An
- ∩ (i = 0 -> n)
	- S = Ai ∩ A(i+1) ... An


   