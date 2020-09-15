#pragma once

#include <QObject>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTabWidget>
#include <string_view>

class FileMenu final : public QObject {
public:
    explicit FileMenu(QTabWidget& tabWidget, QMenuBar& menuBar, QObject* parent = nullptr);
    ~FileMenu();

    [[nodiscard]] QMenu* CreateNewMenu();

signals:
    void DirOpened(std::string_view directory);
    void Exit();

private slots:
    void OnNew(bool checked);
    void OnOpenFile(bool checked);
    void OnOpenDir(bool checked);
    void OnSave(bool checked);
    void OnSaveAs(bool checked);
    void OnClose(bool checked);
    void OnCloseAll(bool checked);
    void OnExit(bool checked);

private:
    Q_OBJECT

    QTabWidget& m_tabWidget;
    QMenuBar& m_menuBar;
    QMenu* m_menu;
};
