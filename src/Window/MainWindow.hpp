#pragma once

#include "../Highlighter.hpp"
#include <QMainWindow>
#include <QProcess>
#include <unordered_map>
#include <memory>
#include <functional>

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Q_OBJECT

    std::unique_ptr<Ui::MainWindow> m_ui;
    QTabWidget* m_tabWidget;
};
