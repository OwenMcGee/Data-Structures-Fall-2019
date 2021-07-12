HOMEWORK 10: CONSTELLATION HASH TABLES


NAME:  < Owen McGee >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< None >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 8 >



PROGRAM DESIGN, DATA STRUCTURE & ALGORITHMS CHOICES:
	The program compares a list of Star objects (created using the data in
	the input file) to potentially multiple Constellation objects (which are
	essentially also lists of Star objects, with added functionality that helps
	out later when printing lines).

	The program runs through every combination of three stars from the input file to find
	three stars with matching (within a degree of error) relative distances and angles
	between them, and without conflicting names or brightnesses already recorded.

	The program then holds onto the first two confirmed stars, and for every subsequent
	star in the constellation being searched for, when checking triplets of input file stars
	it must only run through the list of stars at most one time, as the first two are already
	confirmed. Also, because they are compared using relative distance not absolute distance,
	this ensures that the stars are all correct in reference to one another.

	If every star within the constellation is found, the program finishes by printing the
	new star assignments and updating the output file. If not, it will repeat the process with
	the next constellation in the list, until there are no constellations left, at which point
	it will output that a match could not be found.



EXTRA CREDIT: HANDLING IMAGE SCALING
	Rather than use absolute distance between stars, I use the relative distance
	of the star being checked, away from two other stars that have already been
	confirmed. Seeing as the distance being used is relative, it should stay the
	same regardless of image scale.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


