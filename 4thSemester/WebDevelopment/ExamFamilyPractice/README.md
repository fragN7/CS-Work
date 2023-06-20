Write a web application in PHP for managing a personal genealogical tree.

The application should use the following 2 tables:
- table Users: id (int), username (string)
- table FamilyRelations: id (int), userid (int), mother (string), father (string)

The user should authenticate prior to using the application. In order

to be successfully authenticated, the user should specify his username
together with his father's or mother's name (from the FamilyRelations table;

if either one is correct, the user is authenticated). The user should

be able to add another user's mother and father as a record in the
FamilyRelations table. He/she should also be able to display his/her own
siblings (a sibling is another person that has the same mother or the same

father or both as the current authenticated user).

The user of the application should be able to find his father descending
family line (display user's father, user's father's father (grand father),
Sie) ans the

user father's father's father (grand-grand father) and so on
same way, the user should be able to find his mother descending family line
. The descending

(user's mother, user's mother's mother and so on..)
family line should stop with the oldest ancestor in the database (i.e.

the one who does not have a mother/father specified in the DB).

Grading scale:
- 1 point by default (oficiu)
- configure web environment, create DB, add a new record in FamilyRelations
- authentication using username + mother + father
- display siblings of the current user
- display the user's father descending line and mother descending line

