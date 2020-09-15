#pragma once

#include <QObject>
#include <QTabWidget>
#include <QMenuBar>
#include <QMenu>

class EditMenu final : public QObject {
public:
    explicit EditMenu(QTabWidget& tabWidget, QMenuBar& menuBar, QObject* parent = nullptr);
    ~EditMenu();

    [[nodiscard]] QMenu* CreateNewMenu();

private slots:
    void OnUndo(bool checked);
    void OnRedo(bool checked);
    void OnCopy(bool checked);
    void OnCut(bool checked);
    void OnPaste(bool checked);

private:
    Q_OBJECT

    QTabWidget& m_tabWidget;
    QMenuBar& m_menuBar;
    QMenu* m_menu;
};
