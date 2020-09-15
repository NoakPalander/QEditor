#pragma once

#include <QWidget>
#include <QLabel>

class LinkLabel final : public QLabel {
public:
    explicit LinkLabel(QWidget* parent = nullptr, Qt::WindowFlags wf = Qt::WindowFlags{});
    explicit LinkLabel(QString const& text, QWidget* parent = nullptr, Qt::WindowFlags wf = Qt::WindowFlags{});

    ~LinkLabel();

signals:
    void Pressed();
    void Released();

private:
    Q_OBJECT

    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
};
