add_front(L,E,NList) :- NList = node(E,L).add_back(nil, E, NList) :-   NList = node(E,nil).   
add_back(node(Head,Tail), E, NList) :-   add_back(Tail, E, NewTail),   NList = node(Head,NewTail).