//
// Created by Arthur Motelevicz on 05/12/23.
//

#include "MagiaDebugger.h"
#include <lua.hpp>
#include <iostream>
#include <sol/sol.hpp>

namespace mg{

    void luaDebugHook(lua_State *L, lua_Debug *ar) {
        lua_getinfo(L, "nSl", ar);
        int currentLine = ar->currentline;
        std::string currentFunction = ar->name ? ar->name : "unknown";
        std::cout << "Current Line: " << currentLine << std::endl;
        std::cout << "Current function: " << currentFunction << std::endl;

        bool isBreakPoint = MagiaDebugger::breakpoints.find(ar->currentline) != MagiaDebugger::breakpoints.end();
        while(isBreakPoint && MagiaDebugger::state == MagiaDebugger::DebuggerState::Running) {
            std::cout << "waiting!" << std::endl;
        }
    }

    void MagiaDebugger::setHook(const std::shared_ptr<sol::state>& sol){
        lua_sethook(sol->lua_state(),luaDebugHook, LUA_MASKLINE, 0);
    }

    void MagiaDebugger::appendBreakpoint(int line){
        breakpoints.insert(line);
    }

    void MagiaDebugger::removeBreakpoint(int line){
        breakpoints.erase(line);
    }
}
