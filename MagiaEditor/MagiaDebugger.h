//
// Created by Arthur Motelevicz on 05/12/23.
//

#ifndef MAGIADEBUGGER_H
#define MAGIADEBUGGER_H

#include <memory>

namespace sol{
    class state;
}

namespace mg{
    class MagiaDebugger {

    enum class DebuggerState {
        Running,
        Paused,
        Step
    };

    public:
        MagiaDebugger();
        ~MagiaDebugger();
        static void setHook(const std::shared_ptr<sol::state>& sol);
    };

}
#endif //MAGIADEBUGGER_H
