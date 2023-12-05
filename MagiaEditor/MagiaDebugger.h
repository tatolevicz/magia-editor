//
// Created by Arthur Motelevicz on 05/12/23.
//

#ifndef MAGIADEBUGGER_H
#define MAGIADEBUGGER_H

#include <memory>
#include <unordered_set>

namespace sol{
    class state;
}

namespace mg{

    class MagiaDebugger {
    public:
        enum class DebuggerState {
            Running,
            Paused,
            Step
        };

        inline static std::unordered_set<int> breakpoints;
        static void setHook(const std::shared_ptr<sol::state>& sol);
        static void appendBreakpoint(int line);
        static void removeBreakpoint(int line);
        inline static DebuggerState state = DebuggerState::Running;

    private:

    };

}
#endif //MAGIADEBUGGER_H
