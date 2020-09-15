#include "LinkLabel.hpp"


LinkLabel::LinkLabel(QWidget* parent /*=nullptr*/, Qt::WindowFlags wf /*=Qt::WindowFlags{}*/)
    :   QLabel{ parent }  
{
}

LinkLabel::LinkLabel(QString const& text, QWidget* parent /*=nullptr*/, Qt::WindowFlags wf /*=Qt::WindowFlags{}*/) 
    :   QLabel{ text, parent, wf }
{
}


LinkLabel::~LinkLabel() {}


void LinkLabel::mousePressEvent(QMouseEvent* event [[maybe_unused]]) {
    emit Pressed();
}


void LinkLabel::mouseReleaseEvent(QMouseEvent* event [[maybe_unused]]) {
    emit Released();
}