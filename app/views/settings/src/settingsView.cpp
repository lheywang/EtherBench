/**
 * @file settingsView.cpp
 * @author lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date 2026-04-02
 *
 * @copyright Copyright (c) 2026
 *
 */

// ----------------------------------------------------------------------
// INCLUDES
// ----------------------------------------------------------------------
// Header
#include <views/settingsView.hpp>

// Local libraries
#include <views/baseView.hpp>

// QT
#include <QCheckBox>
#include <QDebug>
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QSplitter>
#include <QString>
#include <QTreeView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------
namespace EtherBench::UI {

SettingsView::SettingsView(QWidget *parent) : BaseView(parent) { setupUI(); }

QString SettingsView::viewTitle() const { return "Settings"; }

void SettingsView::onActivated() { qDebug() << "Welcome to settings"; }

void SettingsView::onDeactivated() { qDebug() << "Exiting ..."; }

void SettingsView::populateTree() {
    m_treeWidget->clear();

    /*
     * TESTING ONLY. SHALL BE DELETED
     */
    QStringList keys = {
        "Network/Ethernet/IP Address",
        "Network/Ethernet/Gateway",
        "Network/WiFi/SSID",
        "Display/Brightness",
        "Display/Language",
        "System/Logging/Enabled"};

    for (const QString &key : keys) {
        QStringList parts = key.split('/');
        QTreeWidgetItem *parent = nullptr;

        for (int i = 0; i < parts.size() - 1; ++i) {
            QString categoryName = parts[i];

            bool found = false;
            int count =
                (parent) ? parent->childCount() : m_treeWidget->topLevelItemCount();

            for (int j = 0; j < count; ++j) {
                QTreeWidgetItem *item =
                    (parent) ? parent->child(j) : m_treeWidget->topLevelItem(j);
                if (item->text(0) == categoryName) {
                    parent = item;
                    found = true;
                    break;
                }
            }

            if (!found) {
                auto *newItem = new QTreeWidgetItem();
                newItem->setText(0, categoryName);
                if (parent)
                    parent->addChild(newItem);
                else
                    m_treeWidget->addTopLevelItem(newItem);
                parent = newItem;
            }
        }
    }
    m_treeWidget->expandAll();
}

void SettingsView::setupUI() {

    // Configure the main view
    auto mainLayout = new QVBoxLayout(this);
    auto m_splitter = new QSplitter(Qt::Horizontal, this);

    // Setup views
    setupTreeView();
    setupEditor();

    // Place them
    m_splitter->addWidget(m_treeWidget);
    m_splitter->addWidget(m_scrollArea);
    m_splitter->setStretchFactor(1, 1);

    // Fill the view
    mainLayout->addWidget(m_splitter);

    // Connect signals
    connect(
        m_treeWidget,
        &QTreeWidget::currentItemChanged,
        this,
        &SettingsView::onCategorySelected);

    // Finally, fill the tree
    populateTree();
}

void SettingsView::setupTreeView() {

    // Create the instances
    m_treeWidget = new QTreeWidget(this);
    m_treeWidget->setHeaderLabel("Parameters");
    m_treeWidget->header()->setStretchLastSection(true);
}

void SettingsView::setupEditor() {

    m_scrollArea = new QScrollArea(this);
    m_editorContainer = new QWidget();
    m_editorLayout = new QFormLayout(m_editorContainer);

    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_editorContainer);
}

void SettingsView::onCategorySelected(QTreeWidgetItem *current, QTreeWidgetItem *) {
    if (!current)
        return;

    QLayoutItem *child;
    while ((child = m_editorLayout->takeAt(0)) != nullptr) {
        if (child->widget())
            delete child->widget();
        delete child;
    }

    QString fullPath = getCategoryPath(current);

    m_editorLayout->addRow(new QLabel("Settings for .... : " + fullPath));
    m_editorLayout->addRow("Value :", new QLineEdit());
    m_editorLayout->addRow("Active :", new QCheckBox());
}

QString SettingsView::getCategoryPath(QTreeWidgetItem *item) const {
    QString path = item->text(0);
    while (item->parent()) {
        item = item->parent();
        path = item->text(0) + "/" + path;
    }
    return path;
}

} // namespace EtherBench::UI