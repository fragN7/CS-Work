Write a web application in PHP/JSP/ASP which uses the following 3 database tables:
-	table Persoane: id (integer), nume_prenume (String), varsta (integer),
salariu (integer)
titlu (string), editura (string), an_aparitie (integer)
- table Articole: id (integer), idAutor (integer) foreign key in Persoane, titlu (string), nr_pagini (integer), tip (string)
-	table Carti: id (integer), idAutor (integer) foreign key in Persoane

A form should send one or two person names to the server/backend (a person name consists of two strings, a first name and a last name). A javascript code verifies that at least one person name is not empty, prior to submission to the server-side. The server searches the tables Articole and Carti for all the books and articles
having as author one of the two person names received from the client and will return to the client the list of articles and books of the person which has the
largest number of books+articles (from the two person names received from the client; if the server-side receives from the client only one person name, it will return either the books of this person or his/her articles 5MM depending on which is greater, the number of books or the number of articles).
The application should keep a history with the persons names that were input by the user in the current browsing session. At any time the user can display this history by clicking a button or link.
