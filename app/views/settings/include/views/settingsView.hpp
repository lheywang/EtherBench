/**
 * @file    settingsView.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the home menu view for the EtherBenchApp project.
 * @version 0.1
 * @date    2026-04-02
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ----------------------------------------------------------------------
// INCLUDES
// ----------------------------------------------------------------------
// Local libraries
#include <views/baseView.hpp>

// Models
#include <models/parameterRegistry.hpp>

// QT
#include <QFormLayout>
#include <QScrollArea>
#include <QSplitter>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------

namespace EtherBench::UI {

class SettingsView : public BaseView {
    Q_OBJECT

  public:
    explicit SettingsView(QWidget *parent = nullptr);

    QString viewTitle() const override;
    void onActivated() override;
    void onDeactivated() override;

    QWidget *
    createEditorWidget(const QString &key, const EtherBench::Models::Parameter &param);

  private slots:
    void onCategorySelected(QTreeWidgetItem *current, QTreeWidgetItem *previous);

  private:
    void setupUI();
    void setupTreeView();
    void setupEditor();
    void populateTree();
    void clearLayout(QLayout *layout);

    QString getCategoryPath(QTreeWidgetItem *item) const;

    QTreeWidget *m_treeWidget;
    QWidget *m_editorContainer;
    QFormLayout *m_editorLayout;
    QSplitter *m_splitter;
    QScrollArea *m_scrollArea;
};

} // namespace EtherBench::UI