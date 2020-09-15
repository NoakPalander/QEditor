#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

#include <QTabWidget>
#include <QMessageBox>
#include <QFileDialog>

#include "About.hpp"

#include "../Menu/FileMenu.hpp"
#include "../Menu/EditMenu.hpp"
#include "../Menu/HelpMenu.hpp"

#include "../Editor/Editor.hpp"
#include "../Build.hpp"
#include "../Utility.hpp"
#include "../LinkLabel.hpp"

MainWindow::MainWindow(QWidget* parent /*=nullptr*/)
    :   QMainWindow{ parent }, 
        m_ui{ std::make_unique<Ui::MainWindow>() } {

    m_ui->setupUi(this);
    m_ui->rootWidget->setLayout(m_ui->rootLayout);
    setWindowTitle(Utility::QFormat("QEditor [{}]", Build::Type));

    m_tabWidget = new QTabWidget(this);
    m_ui->rootLayout->addWidget(m_tabWidget);

    // Constructs and adds a file menu
    FileMenu* fileMenu = new FileMenu(*m_tabWidget, *m_ui->menubar, this);
    m_ui->menubar->addMenu(fileMenu->CreateNewMenu());

    // Constructs and adds a edit menu
    EditMenu* editMenu = new EditMenu(*m_tabWidget, *m_ui->menubar, this);
    m_ui->menubar->addMenu(editMenu->CreateNewMenu());

    HelpMenu* helpMenu = new HelpMenu(*m_tabWidget, *m_ui->menubar, this);
    m_ui->menubar->addMenu(helpMenu->CreateNewMenu());

    // Binds [ File -> Open Directory ] to a lambda
    connect(fileMenu, &FileMenu::DirOpened, [this](std::string_view name) {
        // TODO: Implement explorer
        QMessageBox box;
        box.setText(Utility::QFormat("'{}' was opened!", name));
        box.exec();
    });

    // Binds [ File -> Exit ] to &MainWindow::close
    connect(fileMenu, &FileMenu::Exit, this, &QMainWindow::close);

    // Binds [ Help -> About ] to a lambda
    connect(helpMenu, &HelpMenu::ShowAbout, this, [this]{
        About* about = new About(this);
        about->setModal(true);
        about->show();
    });
}


MainWindow::~MainWindow() {}
