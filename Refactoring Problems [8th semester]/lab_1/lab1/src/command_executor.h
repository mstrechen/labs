#ifndef __COMMAND_EXECUTOR_H__
#define __COMMAND_EXECUTOR_H__

#include "universal_type.h"
#include "cui.h"

struct CommandExecutor{
    static void execute(const string & command_name){
        if(command_name == "EXIT"){
            CUI::print_bye();
            exit(0);
        }
        CUI::print_unknown_command(command_name);
    }
};

#endif