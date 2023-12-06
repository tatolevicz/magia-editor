//
// Created by Arthur Motelevicz on 05/12/23.
//

#ifndef TESTSCINTILLACMAKE_CUSTOMPLAINTEXTEDIT_H
#define TESTSCINTILLACMAKE_CUSTOMPLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <QMenu>

class CustomPlainTextEdit : public QPlainTextEdit {
    Q_OBJECT

public:
    CustomPlainTextEdit(QWidget *parent = nullptr) : QPlainTextEdit(parent) {}

protected:
    void contextMenuEvent(QContextMenuEvent *event) override {
        QMenu *menu = createStandardContextMenu();
        menu->addSeparator();

        QAction *clearAction = new QAction("Clear", this);
        connect(clearAction, &QAction::triggered, this, &CustomPlainTextEdit::clear);
        menu->addAction(clearAction);

        menu->exec(event->globalPos());
        delete menu;
    }
};


#endif //TESTSCINTILLACMAKE_CUSTOMPLAINTEXTEDIT_H
