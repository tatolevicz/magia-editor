//
// Created by Arthur Motelevicz on 05/12/23.
//

#include "MagiaDebugger.h"
#include <lua.hpp>
#include <iostream>
#include <sol/sol.hpp>

namespace mg{
    void luaDebugHook(lua_State *L, lua_Debug *ar){
        lua_getinfo(L, "nSl", ar);
        int currentLine = ar->currentline;
        std::string currentFunction = ar->name ? ar->name : "unknown";
        std::cout << "Current Line: " << currentLine << std::endl;
        std::cout << "Current function: " << currentFunction << std::endl;
    }

    MagiaDebugger::MagiaDebugger(){

    }
    MagiaDebugger::~MagiaDebugger(){

    }
    void MagiaDebugger::setHook(const std::shared_ptr<sol::state>& sol){
        lua_sethook(sol->lua_state(),luaDebugHook, LUA_MASKLINE, 0);
    }
}
