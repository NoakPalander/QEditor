#include "About.hpp"
#include "ui_About.h"
#include "../LinkLabel.hpp"
#include "../Utility.hpp"

#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>
#include <QPoint>


About::About(QWidget* parent /*=nullptr*/)
    :   QDialog{ parent },
        m_ui{ std::make_unique<Ui::About>() } {

    m_ui->setupUi(this);
    setLayout(m_ui->rootLayout);

    QString const style = Utility::QFormat("{}", R"(
        QLabel {
            font-style: underline;
            color: #3366BB;
        }
    )");

    m_githubUrl = new LinkLabel("https://github.com/NoakPalander", this);
    m_ui->rootLayout->addWidget(m_githubUrl);
    m_githubUrl->setStyleSheet(style);

    m_fmtUrl = new LinkLabel("https://github.com/fmtlib/fmt", this);
    m_fmtUrl->setStyleSheet(style);
    m_ui->rootLayout->addWidget(m_fmtUrl);

    connect(m_githubUrl, &LinkLabel::Pressed, this, [this]{
        QDesktopServices::openUrl(QUrl{ m_githubUrl->text() });
    });

    connect(m_fmtUrl, &LinkLabel::Pressed, this, [this]{
        QDesktopServices::openUrl(QUrl{ m_fmtUrl->text() });
    });
}


About::~About() {}


void About::mouseMoveEvent(QMouseEvent* event) {
    emit Moved(); 
}