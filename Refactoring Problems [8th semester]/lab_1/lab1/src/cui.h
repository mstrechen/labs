#ifndef __CUI_H__
#define __CUI_H__

#include <iostream>
using namespace std;


namespace CUI {
    namespace CONSTANTS{
        const string LINE_BEGINNING = "> ";
        const string WELCOME_MESSAGE = 
            "   Welcome to the simple calculator. \n"
            "   Just type some expression and see what's happening ;) \n"
            "   Or use HELP get some help \n"
            "   P.S. You can also use variables! Variable names should start from the @"
        ;
        const string HELP_MESSAGE = "TBD :)";
        const string UNKNOWN_COMMAND_MESSAGE = "Unknown command ";
        const string UNKNOWN_FUNCTION_MESSAGE = "Unknown function ";
        const string BYE = "Bye!";
    }
    template<typename T>
    void print_result(const T & res){
        cout 
            << res.float_val 
            << "\n"
            << CONSTANTS::LINE_BEGINNING;
    }
    void print_welcome_message(){
        cout << CONSTANTS::WELCOME_MESSAGE << "\n" << CONSTANTS::LINE_BEGINNING;
    } 
    void get_help(){
        cout <<  CONSTANTS::HELP_MESSAGE << "\n" << CONSTANTS::LINE_BEGINNING;
    }
    void newline(){
        cout << CONSTANTS::LINE_BEGINNING;
    }
    void print_unknown_command(const string & command_name){
        cout << CONSTANTS::UNKNOWN_COMMAND_MESSAGE + '"' << command_name << '"' << "\n" << CONSTANTS::LINE_BEGINNING;
    }
    void print_uknown_function(const string & func_name){
        cout << CONSTANTS::UNKNOWN_FUNCTION_MESSAGE + '"' << func_name << '"' << "\n" << CONSTANTS::LINE_BEGINNING;
    }
    void print_bye(){
        cout << CONSTANTS::BYE;
    }
    void setup(){
        cout.precision(20);
    }
    void show_error(const string & error){
        cout << "An error occured: \"" << error << "\"";
    }
};

#endif