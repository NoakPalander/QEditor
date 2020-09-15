#pragma once

#include <QObject>
#include <QMenuBar>
#include <QTabWidget>
#include <QMenu>

class HelpMenu final : public QObject {
public:
    explicit HelpMenu(QTabWidget& tabWidget, QMenuBar& menuBar, QObject* parent = nullptr);
    ~HelpMenu();

    [[nodiscard]] QMenu* CreateNewMenu();

signals:
    void ShowAbout();

private slots:
    void OnGit();
    void OnAbout();

private:
    Q_OBJECT

    QTabWidget& m_tabWidget;
    QMenuBar& m_menuBar;
    QMenu* m_menu;
};
