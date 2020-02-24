#include<iostream>
#include "includes/hashset.h"

using namespace std;

using HashBasedDS::HashPair;
using HashBasedDS::HashSet;

void regular_test(){
    HashSet HS;
    char operation;
    string s;
    while(cin >> operation){
        if(operation == '#') break;
        cin >> s;
        switch (operation)
        {
            case '+': HS.insert(s); break;
            case '?': cout << (HS.count(s)? "YES\n" : "NO\n"); break;
            case '-': HS.insert(s); break;
        }
    }
}

bool is_palindrome(const string & s){
    // Function is not effective, but task requires to use hashes :( 
    // (definetly should not use hashes to check if string is palindrome
    // - in the end you have to check it anyway in a regular way)
    HashPair hp_straightforward(s, false), hp_reverse(s, true);
    if(hp_straightforward != hp_reverse) return false;
    for(size_t i = 0; i < s.size() / 2; i++){
        if(s[i] != s[s.size() - i - 1]) return false;
    }
    return true;
}

void palindromes_test(){
    HashSet HS;
    char operation;
    string s;
    while(cin >> operation){
        if(operation == '#') break;
        cin >> s;
        switch (operation)
        {
            case '+': 
                if(is_palindrome(s))
                    HS.insert(s);
                break;
            case '?': cout << (HS.count(s)? "YES\n" : "NO\n"); break;
            break;
            case '-': HS.insert(s); break;
        }
    }
    for(auto i: HS){
        cout << i << '\n';
    }
}

const string PALINDROMES_TEST_CASE = "PALINDROMES";

int main(int argc, char ** argv){
    if(argc == 1 || argv[1] == PALINDROMES_TEST_CASE){
        palindromes_test();
    } else {
        regular_test();
    }
}