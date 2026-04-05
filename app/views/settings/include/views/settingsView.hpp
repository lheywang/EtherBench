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
#include <QMenu>
#include <QMenuBar>
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
    /*
     * Constructors and destructors
     */
    explicit SettingsView(QWidget *parent = nullptr);

    /*
     * Overrides
     */
    QString viewTitle() const override;
    void onActivated() override;
    void onDeactivated() override;
    void fillMenubar(QMenuBar *menuBar) override;

    /*
     * Editor changes
     */
    QWidget *
    createEditorWidget(const QString &key, const EtherBench::Models::Parameter &param);

  private slots:
    void onCategorySelected(QTreeWidgetItem *current, QTreeWidgetItem *previous);

  private:
    /*
     * Utility functions, to setup the view
     */
    void setupUI();
    void setupTreeView();
    void setupEditor();
    void populateTree();
    void clearLayout(QLayout *layout);

    /*
     * Settings import and export
     */
    void settingsExport();
    void settingsImport();
    void resetSettings();

    /*
     * Utility called when building the treeview
     */
    QString getCategoryPath(QTreeWidgetItem *item) const;

    /*
     * Variables
     */
    QSplitter *m_splitter;

    QTreeWidget *m_treeWidget;
    QWidget *m_editorContainer;
    QFormLayout *m_editorLayout;
    QScrollArea *m_scrollArea;

    QMenu *m_settingsMenu;
};

} // namespace EtherBench::UI