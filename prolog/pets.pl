likes(john, dog).
likes(sarah, cat).
likes(mike, fish).
likes(sarah, rabbit).

animal_lover(Person) :-
    likes(Person, _).
