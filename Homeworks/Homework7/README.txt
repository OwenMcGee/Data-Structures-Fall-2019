HOMEWORK 7: LIBRARY MAPS


NAME:  < Owen McGee >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< None >

Remember: Your implementation for this assignment must be done on your
own, as described in the “Collaboration Policy & Academic Integrity”
handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 5 >



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the library operations and justify
your answer.  Let n be the number of different titles in the library,
m be the maximum number of copies of a given item, p be the number of
patrons using the library, and c be the maximum number of items any
patron has checked out at one time.  (Please be concise!)


add (a): O(logn)


checkout (c): O(logn + logp + c)


return (r): O(mclogn)


lookup (l): O(m)


print (p): O(nm)



YOUR OWN TEST CASES:
describe each test case you created and your motivation for designing
each (why is the test case helpful for debugging and/or interesting)

The first case tests for attempting to return books from a person who hasn't been mentioned yet. This
case wasn't explored by the example inputs, so I made it the same output as a previous person who just has no books.

The next two cases test adding invalid amounts of books, giving some fun messages when no or negative books are
attempted to be added (since it was also undefined territory, I just assumed it was dissalowed).

The next two cases test correct addition of books, and allow me to ensure both versions of the message
syntax are working (singular and plural).

The next case tests attempting to check out a book that is not in stock.

The next two cases test correct checking out of a book, and then attempting to check out a book that
the patron already has (this also checks the priority of errors, as that book is also out of stock).

The next case tests when a patron attempts to check out a book that is not in stock (this time without
the priority issue of also having checked the book out before).

The next two cases test a patron returning books and then being able to once again check out those books
(which the patron was previously not able to do). The print statements simply make it easier to see this,
and verify. They also test typical printing conditions.

The next two cases test printing when all books are present in the library (which simply prints nothing).

The next two cases test looking up books when none have been checked out (which simply doesn't print that
part at all). It tests both the singular and plural cases ("copy" vs "copies").

The next Two test cases test looking up books which have been checked out, but remain in stock. They also
test the singular case of how many have been checked out ("1 copy").

The next two test cases test looking up books which have all been checked out, as well as the plural case
of how many have been checked out ("2 copies").

The next test case tests looking up a non-existent book. Get it, because I never bought my calc textbooks
and as a result have to jump through hoops to find my homework problems, but convince myself it's too
far into the semester now to buy it, which over time gets more and more correct which just makes me more sure?
Yeah like that.

One final print to look everything over as it stands now, along with one checkout to make it look more interesting.




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


Why no capitalization on the error messages, guys? What, did the shift key break? We're programmers not heathens.