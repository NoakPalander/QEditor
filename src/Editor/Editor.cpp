#include "Editor.hpp"
#include "ui_Editor.h"
#include "../Utility.hpp"

#include <QMessageBox>
#include <QFileDialog>
#include <QString>



Editor::Editor(QString const& name, QString const& data, QMenu& editMenu, QTabWidget& tabWidget, bool isNew, QWidget* parent /*=nullptr*/)
    :   QWidget(parent),
        m_ui{ std::make_unique<Ui::Editor>() },
        m_editMenu{ editMenu },
        m_tabWidget{ tabWidget },
        m_name{ name },
        m_textEdited{ isNew } {

    m_ui->setupUi(this);
    this->setLayout(m_ui->rootLayout);

    m_highlighter = new Highlighter(m_ui->textEdit->document());
    m_ui->textEdit->setText(data);

    connect(m_ui->textEdit, &QTextEdit::textChanged, this, &Editor::OnEdit);
}


Editor::~Editor() {}


void Editor::Save() {
    if (m_name.isEmpty())
        SaveAs();
    else {
        if (m_textEdited) {
            int const index = m_tabWidget.currentIndex();
            m_tabWidget.setTabText(index, Utility::QFormat("{}", m_tabWidget.tabText(index).toStdString().substr(4)));

            Utility::File::WriteFile(m_name.toStdString(), m_ui->textEdit->toPlainText().toStdString());

            m_textEdited = false;
        }
    }
}


void Editor::SaveAs() {
    m_name = QFileDialog::getSaveFileName(this, "Save File", "/home/");
    Utility::File::WriteFile(m_name.toStdString(), m_ui->textEdit->toPlainText().toStdString());

    if (m_textEdited && !m_name.isEmpty()) {
        int const index = m_tabWidget.currentIndex();
        m_tabWidget.setTabText(index, Utility::QFormat("{}", m_name.toStdString().substr(m_name.lastIndexOf('/') + 1)));

        m_textEdited = false;
    }
}


void Editor::OnEdit() {
    if (!m_textEdited) {
        int const index = m_tabWidget.currentIndex();
        m_tabWidget.setTabText(index, Utility::QFormat("• {}", m_tabWidget.tabText(index).toStdString()));

        m_textEdited = true;
    }
}


void Editor::Undo() const {
    m_ui->textEdit->undo();
}


void Editor::Redo() const {
    m_ui->textEdit->redo();
}


void Editor::CopyToClipboard() const {
    m_ui->textEdit->copy();
}


void Editor::CutToClipboard() const {
    m_ui->textEdit->cut();
}


void Editor::PasteFromClipboard() const {
    m_ui->textEdit->paste();
}