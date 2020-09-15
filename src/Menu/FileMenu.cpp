#include "FileMenu.hpp"
#include <QFileDialog>
#include <QMessageBox>

#include "../Build.hpp"
#include "../Editor/Editor.hpp"
#include "../Utility.hpp"


FileMenu::FileMenu(QTabWidget& tabWidget, QMenuBar& menuBar, QObject* parent /*=nullptr*/)
    :   QObject{ parent },
        m_tabWidget{ tabWidget },
        m_menuBar{ menuBar },
        m_menu{ nullptr }
{
}


FileMenu::~FileMenu() {}


[[nodiscard]] QMenu* FileMenu::CreateNewMenu() {
    m_menu = m_menuBar.addMenu("File");

    QAction* const newAction = m_menu->addAction("New");
    newAction->setShortcut({ Qt::CTRL + Qt::Key_N });

    QAction* const openFileAction = m_menu->addAction("Open file");
    openFileAction->setShortcut({ Qt::CTRL + Qt::Key_O });

    QAction* const openDirAction = m_menu->addAction("Open directory");
    openDirAction->setShortcut({ Qt::CTRL + Qt::SHIFT + Qt::Key_O });

    QAction* const saveAction = m_menu->addAction("Save");
    saveAction->setShortcut({ Qt::CTRL + Qt::Key_S });

    QAction* const saveAsAction = m_menu->addAction("Save As");
    saveAsAction->setShortcut({ Qt::CTRL + Qt::SHIFT + Qt::Key_S });

    m_menu->addSeparator();

    QAction* const closeAction = m_menu->addAction("Close");
    closeAction->setShortcut({ Qt::CTRL + Qt::Key_W });

    QAction* const closeAllAction = m_menu->addAction("Close All");
    closeAllAction->setShortcut({ Qt::CTRL + Qt::SHIFT + Qt::Key_W });

    m_menu->addSeparator();

    QAction* const exitAction = m_menu->addAction("Exit");
    exitAction->setShortcut({ Qt::CTRL + Qt::Key_Q });

    connect(newAction,      &QAction::triggered, this, &FileMenu::OnNew);
    connect(openFileAction, &QAction::triggered, this, &FileMenu::OnOpenFile);
    connect(openDirAction,  &QAction::triggered, this, &FileMenu::OnOpenDir);
    connect(saveAction,     &QAction::triggered, this, &FileMenu::OnSave);
    connect(saveAsAction,   &QAction::triggered, this, &FileMenu::OnSaveAs);
    connect(closeAction,    &QAction::triggered, this, &FileMenu::OnClose);
    connect(closeAllAction, &QAction::triggered, this, &FileMenu::OnCloseAll);
    connect(exitAction,     &QAction::triggered, this, &FileMenu::OnExit);

    return m_menu;
}


void FileMenu::OnNew(bool checked [[maybe_unused]]) {
    static uint8_t s_counter = 1;
    if (m_tabWidget.count() == 0)
        s_counter = 1;

    Editor* newTab = new Editor("", "", *m_menu, m_tabWidget, true);
    m_tabWidget.addTab(newTab, Utility::QFormat("• New File {}", s_counter++));
    m_tabWidget.setCurrentWidget(newTab);
}


void FileMenu::OnOpenFile(bool checked [[maybe_unused]]) {
    QString const path = QFileDialog::getOpenFileName(nullptr, "Open File", 
        Utility::QFormat("{}", Build::Root));

    if (Utility::File::Exists(path.toStdString())) {
        QString const data = Utility::File::ReadFile(path.toStdString());

        Editor* newTab = new Editor(path, data, *m_menu, m_tabWidget, false);
        m_tabWidget.addTab(newTab, QString::fromStdString(path.toStdString().substr(path.lastIndexOf('/') + 1)));
        m_tabWidget.setCurrentWidget(newTab);
    }
}


void FileMenu::OnOpenDir(bool checked [[maybe_unused]]) {
    QString const path = QFileDialog::getExistingDirectory(nullptr, "Select directory", 
        Utility::QFormat("{}", Build::Root), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (Utility::File::DirExists(path.toStdString()))
        emit DirOpened(path.toStdString());
}


void FileMenu::OnSave(bool checked [[maybe_unused]]) {
    if (Editor* const editor = dynamic_cast<Editor*>(m_tabWidget.currentWidget()); editor != nullptr)
        editor->Save();
}


void FileMenu::OnSaveAs(bool checked [[maybe_unused]]) {
    if (Editor* const editor = dynamic_cast<Editor*>(m_tabWidget.currentWidget()); editor != nullptr)
        editor->SaveAs();
}


void FileMenu::OnClose(bool checked [[maybe_unused]]) {
    // If the tab widget contains editors
    if (m_tabWidget.count() > 0) {
        // Grabs the current editor
        if (Editor* const current = dynamic_cast<Editor*>(m_tabWidget.currentWidget()); current != nullptr) {
            // If the file has been opened to a destination before
            if (!current->GetName().isEmpty()) {
                if (!current->IsSaved()) {
                    QMessageBox box{
                        .icon = QMessageBox::Icon::Question,
                        .title = "Save the file?",
                        .text = "The file is unsaved, do you wish to save it before closing it?",
                        .buttons = QMessageBox::Button::Yes
                    };

                    box.addButton(QMessageBox::Button::No);
                    if (box.exec() == QMessageBox::Button::Yes)
                        current->Save();
                }

                m_tabWidget.removeTab(m_tabWidget.currentIndex());
            }
            else {
                QMessageBox box{
                    .icon = QMessageBox::Icon::Question,
                    .title = "Save the file?",
                    .text = "The file is unsaved, do you wish to save it before closing it?",
                    .buttons = QMessageBox::Button::Yes
                };

                box.addButton(QMessageBox::Button::No);
                if (box.exec() == QMessageBox::Button::Yes)
                    current->SaveAs();

                m_tabWidget.removeTab(m_tabWidget.currentIndex());
            }
        }
    }
}


void FileMenu::OnCloseAll(bool checked [[maybe_unused]]) {
    for (int i = m_tabWidget.count() - 1; i >= 0; i--)
        m_tabWidget.removeTab(i);
}


void FileMenu::OnExit(bool checked [[maybe_unused]]) {
    emit Exit();
}
