Tuple
- Definition: An ordered and finite list of elements
- ORDER MATTERS
	- (1, 2) != (2, 1)
	- But {1, 2} == {2, 1}
- Arity -- number of components in a tuple
	- Arity of (1, 2) is 1
		- |(1, 2)| = 1
- Can be used for relational mapping
	- Ex. mother = {(Rose, John), (Rose, Peter), (Mary, Andy)}
	- Sentences in NLP
		- Ex. "This movie suggestion was not good" --> {(this), (movie), (was), (not), (good)}
- Can be functions
	- Each distinct key yields a distinct value
	- mother is not a function


Cartesian Product
- Definition: The set of tuples such that each elements' respective elements are in another set
- Ex.
	- A = {1, 2, 3} -- B = {2, 3, 4}
	- A x B = {(1, 2), (1, 3), (1, 4), (2, 2), (2, 3), (2, 4), (3, 2), (3, 3), (3, 4)}
	- |A x B| = |A| x |B|
- Can be chained, with similar results
- Not commutative, but associative

Binary Relations
- Definition: Set of pairs (tuples w/ arity 2) in a subset of the product of two sets A and B
- Ex.
	- R = A x B
	- A is the domain, B is the range (or co-domain)
- Can represent a directed graph, arrow diagram, matrix / array, etc.
- May or may not be functions
	- If same domain value has multiple ranges, the relation is not a function

Functions
- Partial Functions
	- For every a in A, there is at most 1 b in B such that a is related to b
- Total Functions
	- "For all a in A there exists 1 b in B such that a is related to b"
		- Definition can be written using mathematical notation
- Properties
	- Injections
		- One-to-One
		- "For any element a in A, there is a distinct element b in B such that a and b are related (F(a) = b)"
			- Ex. F(a) = 2a
	- Surjections
		- Onto
		- "For all b in B, there exists at least one a in A such that F(a) = B"
		- Does not require unique domain
	- Bijection
		- One-to-One correspondence
		- For every a in A, there is a distinct element b in B such that F(a) = b
		- For every b in B, there is at least one element a in A such that f(a) = b
		- For no b in B are there two elements a1 and a2 such that f(a1) = b and f(a2) = b
		- Ex.
			- y = x+1 for x, y in Z
			- y = x ^ 2 ONLY for x, y in Z+
				- May or may not be bijective depending on domain
	- Inverse
		- If a function f(a) maps a to b, then the inverse function maps b to a
			- f ^ -1 (b) = a
			- f(a) = 2a, f(b) = 0.5b
	- Composition
		- If function f maps a to b and function g maps b to c then the composition of function f * g maps a to c
	- Identity
		- Given an inversible function f, then the composition of functions f and the inverse of f yields its input across the domain of f
		- f ( f ^ -1 (a)) = a

Binary Relation Properties
- Transitivity
	- A relation R is transitive if for aRb and bRc, aRc exists in the relation for all a, b, c in R
- Reflexivity
	- A relation R is reflexive if aRa exists for all a in R
- Anti-Reflexivity
	- A relation R is anti-reflexive if no aRa exists for any a in R
- Symmetry
	- A relation R is symmetric if for aRb there exists bRa for all a, b in R
- Anti-Symmetry
	- A relation R is anti-symmetric if for all aRb there exists no relation bRa for any a, b in R
- Equivalence
	- A relation is equivalent if it is transitive, reflexive, and symmetric
- Notes
	- A relation may either be transitive or not transitive
	- A relation may either be reflexive, anti-reflexive, or neither
	- A relation may either be symmetric, anti-symmetric, or neither
	- A relation may either be equivalent or not equivalent

Finite Sets
- A set that does not have a **one-to-one** correspondence with any of its **proper subsets**
Infinite Sets
- A set that has a one-to-one correspondence with **at least one** of its proper subsets
Countability
- Equipotent: 2 sets of the same cardinality
- A set is countable if it is equipotent to some subset of the natural numbers
- A set is uncountable if it is not equipotent to some subset of the natural numbers
	- The set of real numbers 'R' is uncountably infinite
	- 

