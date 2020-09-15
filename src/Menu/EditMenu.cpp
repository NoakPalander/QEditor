#include "EditMenu.hpp"
#include "../Editor/Editor.hpp"


EditMenu::EditMenu(QTabWidget& tabWidget, QMenuBar& menuBar, QObject* parent /*=nullptr*/)
    :   QObject{ parent },
        m_tabWidget{ tabWidget },
        m_menuBar{ menuBar }
{
}


EditMenu::~EditMenu() {}


[[nodiscard]] QMenu* EditMenu::CreateNewMenu() {
    m_menu = m_menuBar.addMenu("Edit");

    QAction* const undoAction = m_menu->addAction("Undo");
    undoAction->setShortcut({ Qt::CTRL + Qt::Key_Z });

    QAction* const redoAction = m_menu->addAction("Redo");
    redoAction->setShortcut({ Qt::CTRL + Qt::SHIFT + Qt::Key_Z });

    m_menu->addSeparator();

    QAction* const copyAction = m_menu->addAction("Copy");
    copyAction->setShortcut({ Qt::CTRL + Qt::Key_C });

    QAction* const cutAction = m_menu->addAction("Cut");
    cutAction->setShortcut({ Qt::CTRL + Qt::Key_X });

    QAction* const pasteAction = m_menu->addAction("Paste");
    pasteAction->setShortcut({ Qt::CTRL + Qt::Key_V });

    connect(undoAction, &QAction::triggered, this, &EditMenu::OnUndo);
    connect(redoAction, &QAction::triggered, this, &EditMenu::OnRedo);

    connect(copyAction,  &QAction::triggered, this, &EditMenu::OnCopy);
    connect(cutAction,   &QAction::triggered, this, &EditMenu::OnCut);
    connect(pasteAction, &QAction::triggered, this, &EditMenu::OnPaste);

    return m_menu;
}


void EditMenu::OnUndo(bool checked [[maybe_unused]]) {
    if (Editor* const current = dynamic_cast<Editor*>(m_tabWidget.currentWidget()); current != nullptr)
        current->Undo();
}


void EditMenu::OnRedo(bool checked [[maybe_unused]]) {
    if (Editor* const current = dynamic_cast<Editor*>(m_tabWidget.currentWidget()); current != nullptr)
        current->Redo();
}


void EditMenu::OnCopy(bool checked [[maybe_unused]]) {
    if (Editor* const current = dynamic_cast<Editor*>(m_tabWidget.currentWidget()); current != nullptr)
        current->CopyToClipboard();
}


void EditMenu::OnCut(bool checked [[maybe_unused]]) {
    if (Editor* const current = dynamic_cast<Editor*>(m_tabWidget.currentWidget()); current != nullptr)
        current->CutToClipboard();
}


void EditMenu::OnPaste(bool checked [[maybe_unused]]) {
    if (Editor* const current = dynamic_cast<Editor*>(m_tabWidget.currentWidget()); current != nullptr)
        current->PasteFromClipboard();
}