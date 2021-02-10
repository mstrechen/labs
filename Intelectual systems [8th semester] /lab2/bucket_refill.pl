
solve(Limits, Goal) :- solve_full(Limits, [], Goal, 1).
solve_silent(Limits, Goal):- solve_full_silent(Limits, [], Goal, 1).


write_state([]):- writeln('').
write_state([jar(_, Limit, Volume)|Jars]) 
:- 
    write(Volume),
    write('/'),
    write(Limit),
    write(',\t'),
    write_state(Jars).

write_path([]).
write_path([X|L]) :- write_state(X), write_path(L).


solve_full_silent([], Jars, Goal) :- 
    solve_full_(Jars, jar(_, _, Goal), [], _).
solve_full([], Jars, Goal) :-
    solve_full_(Jars, jar(_, _, Goal), [], Path), write_path(Path).


solve_full([], Jars, Goal, _):- solve_full([], Jars, Goal).
solve_full([Limit|Limits], Jars, Goal, I) :- 
    I_next is I + 1,
    solve_full(
        Limits, [jar(I, Limit, 0)|Jars], Goal, I_next
	).

solve_full_silent([], Jars, Goal, _):- solve_full_silent([], Jars, Goal).
solve_full_silent([Limit|Limits], Jars, Goal, I) :- 
    I_next is I + 1,
    solve_full_silent(
        Limits, [jar(I, Limit, 0)|Jars], Goal, I_next
	).



replace(S, [S|L], X, [X|L]).
replace(S, [T|L], X, [T|Ls]) :- replace(S, L, X, Ls).



solve_full_(State, Goal, _, [State]) :- member(Goal, State).
solve_full_(State, Goal, Backlog, [State|Path]) :-
    member(TargetJar, State),
    full_refill(TargetJar, JarResult),
    replace(TargetJar, State, JarResult, StateNew),
    not(member(StateNew, [State|Backlog])),
    solve_full_(StateNew, Goal, [State|Backlog], Path).

solve_full_(State, Goal, Backlog, [State|Path]) :- 
    member(SourceJar, State),
    member(TargetJar, State),
    SourceJar \= TargetJar, 
    transfer(SourceJar, TargetJar, JarResult1, JarResult2),
    replace(SourceJar, State, JarResult1, StateIntermediate),
    replace(TargetJar, StateIntermediate, JarResult2, StateNew),
    not(member(StateNew, [State|Backlog])), 
    solve_full_(StateNew, Goal, [State|Backlog], Path).


full_refill(jar(Id, Limit, _), jar(Id, Limit, Limit)). 

transfer(
   jar(Id_1, Limit1, Volume1),
   jar(Id_2, Limit2, Volume2), 
   jar(Id_1, Limit1, 0),
   jar(Id_2, Limit2, VolumeRes))
:- 
    Volume1 > 0,
    Volume2 >= 0,
    VolumeRes is Volume1 + Volume2,
    VolumeRes =< Limit2,
    VolumeRes >= 0.

transfer(
   jar(Id1, Limit1, Volume1),
   jar(Id2, Limit2, Volume2), 
   jar(Id1, Limit1, VolumeRes1),
   jar(Id2, Limit2, Limit2)
) :- 
    Volume1 > 0,
    Volume2 >= 0,
    VolumeRes1 is Volume1 + Volume2 - Limit2,
    VolumeRes1 >= 0,
    VolumeRes1 =< Limit1.
