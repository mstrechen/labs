# Lab. 1 : HashSet for strings

Simple realisation of HashSet for strings

### Usage

You could test the datastructure by simply running main.cpp.

Tests have to be written as a sequence of `<op> <string>`, where `<op> = + | ? | -` (add string, ask if some string is present in the set, remove string), ending with `#`.
For `?` queries you will receive `YES` if the string is present in the set or `NO` otherwise.

To compile, just run ```make```.

Running `main.out` without any command line args or with first argument equals to `PALINDROMES` will run **palindrome test** - strings will be filtred by palindromicity before inserting into the set. Additionally, the full set will be written in the end of execution. Such a behaviour was required by the task.
Running `main.out` with any other command line arguments will run "regular" test without any additional filtering.


