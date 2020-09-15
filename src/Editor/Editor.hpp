#pragma once

#include <QWidget>
#include <QString>
#include <QMenu>
#include <QTabWidget>

#include "../Highlighter.hpp"

namespace Ui {
    class Editor;
}

class Editor : public QWidget {
public:
    explicit Editor(QString const& name, QString const& data, QMenu& editMenu, QTabWidget& tabWidget, bool isNew, QWidget* parent = nullptr);
    ~Editor();

    void Save();
    void SaveAs();

    void Undo() const;
    void Redo() const;

    void CopyToClipboard() const;
    void CutToClipboard() const;
    void PasteFromClipboard() const;

    inline QString GetName() const { return m_name; }
    inline bool IsSaved() const { return !m_textEdited; }

private slots:
    void OnEdit();

private:
    Q_OBJECT

    std::unique_ptr<Ui::Editor> m_ui;
    QMenu& m_editMenu;
    QTabWidget& m_tabWidget;
    Highlighter* m_highlighter;

    QString m_name;
    bool m_textEdited;
};
