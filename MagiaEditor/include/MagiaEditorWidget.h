//
// Created by Arthur Motelevicz on 06/12/23.
//

#ifndef TESTSCINTILLACMAKE_MAGIAEDITORWIDGET_H
#define TESTSCINTILLACMAKE_MAGIAEDITORWIDGET_H

#include <QWidget>

class QToolBar;
namespace sol{
    class state;
}

namespace mg {
    class MagiaEditor;
    class ConsoleOutput;

    class MagiaEditorWidget : public QWidget {
        Q_OBJECT
    public:
        MagiaEditorWidget(QWidget* parent = nullptr);
        void resizeEvent(QResizeEvent *event) override;

        MagiaEditor* getEditor();
        QWidget* getCentralWidget();
        std::shared_ptr<sol::state> getLuaState();

    public slots:
        virtual void onStepOver();
        virtual void onContinue();
        virtual void onPlayClicked();
        virtual void onDebugClicked();
        virtual void onStopClicked();
        virtual void onScriptPaused();
        virtual void onScriptFinished();
        virtual void onScriptStarted();

    private:
        void updateActions();
        QAction* _playAction;
        QAction* _debugAction;
        QAction* _stopAction;
        QAction* _stepOverAction;
        QAction* _continueAction;

        void setupActions();
        void connectActions();

        MagiaEditor* _editor{nullptr};
        ConsoleOutput* _console{nullptr};
        QToolBar *_scriptToolBar;
        QToolBar *_debugToolBar;
        QWidget* _centralWidget{nullptr};
    };
}
#endif //TESTSCINTILLACMAKE_MAGIAEDITORWIDGET_H
