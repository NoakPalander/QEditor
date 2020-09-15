#include "HelpMenu.hpp"

#include <QMessageBox>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>


HelpMenu::HelpMenu(QTabWidget& tabWidget, QMenuBar& menuBar, QObject* parent /*=nullptr*/)
    :   QObject{ parent },
        m_tabWidget{ tabWidget },
        m_menuBar{ menuBar } {
}


HelpMenu::~HelpMenu() {}


[[nodiscard]] QMenu* HelpMenu::CreateNewMenu() {
    m_menu = m_menuBar.addMenu("Help");

    QAction* const gitAction = m_menu->addAction("Github");
    QAction* const aboutAction = m_menu->addAction("About");

    connect(gitAction, &QAction::triggered, this, &HelpMenu::OnGit);
    connect(aboutAction, &QAction::triggered, this, &HelpMenu::OnAbout);

    return m_menu;
}


void HelpMenu::OnGit() {
    QMessageBox box{
        .icon = QMessageBox::Information,
        .title = "Github profile",
        .text = "The source code for the QEditor is available on github\nhttps://github.com/NoakPalander"
    };

    box.addButton("Close", QMessageBox::NoRole);
    QAbstractButton const* const visitBtn = box.addButton("Visit", QMessageBox::NoRole);

    box.exec();
    if (box.clickedButton() == visitBtn)
        QDesktopServices::openUrl(QUrl("https://github.com/NoakPalander"));
}


void HelpMenu::OnAbout() {
    emit ShowAbout();
}
