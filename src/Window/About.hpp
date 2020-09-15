#pragma once

#include "../LinkLabel.hpp"
#include <QWidget>
#include <QDialog>
#include <memory>
#include <QMouseEvent>

namespace Ui {
    class About;
}

class About : public QDialog {
public:
    explicit About(QWidget* parent = nullptr);
    ~About();

signals:
    void Moved();

protected:
    // DOESNT WORK
    virtual void mouseMoveEvent(QMouseEvent* event) override;

private:
    Q_OBJECT
    std::unique_ptr<Ui::About> m_ui;

    LinkLabel* m_githubUrl;
    LinkLabel* m_fmtUrl;
};