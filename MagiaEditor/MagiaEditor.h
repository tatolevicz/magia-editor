//
// Created by Arthur Motelevicz on 05/12/23.
//

#ifndef TESTSCINTILLACMAKE_MAGIAEDITOR_H
#define TESTSCINTILLACMAKE_MAGIAEDITOR_H


#include "ScintillaEdit.h"

namespace sol {
    class state;
}

namespace mg{
    class MagiaEditor : public ScintillaEdit{
        Q_OBJECT
    public:
        MagiaEditor(QWidget *parent = 0);
        void setup();
        virtual ~MagiaEditor();
    protected:
//        bool event(QEvent *event) override;
//        void paintEvent(QPaintEvent *event) override;
//        void wheelEvent(QWheelEvent *event) override;
//        void focusInEvent(QFocusEvent *event) override;
//        void focusOutEvent(QFocusEvent *event) override;
//        void resizeEvent(QResizeEvent *event) override;
//        void keyPressEvent(QKeyEvent *event) override;
//        void mousePressEvent(QMouseEvent *event) override;
//        void mouseReleaseEvent(QMouseEvent *event) override;
//        void mouseDoubleClickEvent(QMouseEvent *event) override;
//        void mouseMoveEvent(QMouseEvent *event) override;
//        void contextMenuEvent(QContextMenuEvent *event) override;
//        void dragEnterEvent(QDragEnterEvent *event) override;
//        void dragLeaveEvent(QDragLeaveEvent *event) override;
//        void dragMoveEvent(QDragMoveEvent *event) override;
//        void dropEvent(QDropEvent *event) override;
//        void inputMethodEvent(QInputMethodEvent *event) override;
//        QVariant inputMethodQuery(Qt::InputMethodQuery query) const override;
//        void scrollContentsBy(int, int) override {}

        void syntaxTimerTimeout();
        void onCharAdded(int ch);
        void onNewLine();
        void scriptModified(Scintilla::ModificationFlags type,
                            Scintilla::Position position,
                            Scintilla::Position length,
                            Scintilla::Position linesAdded,
                            const QByteArray &text,
                            Scintilla::Position line,
                            Scintilla::FoldLevel foldNow,
                            Scintilla::FoldLevel foldPrev);

        void onMarginClicked(Scintilla::Position position,
                             Scintilla::KeyMod modifiers,
                             int margin);

        void idleMouseStart(int x, int y);
        void idleMouseEnd(int x, int y);

        void showAutocomplete();
        void updateErrorMaker(int errorLine);
        int extractErrorLine(const std::string& errorMsg);
        int validateLuaScript(const std::string& script);

        bool showErrorIfAny(int x, int line, int pos);
        bool showVariableValueIfAny(int pos);

        std::shared_ptr<sol::state> _lua{nullptr};

        QTimer* _syntaxTimer{nullptr};
        std::string _currentError;
    };
}
#endif //TESTSCINTILLACMAKE_MAGIAEDITOR_H