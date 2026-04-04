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

// Models
#include <models/parameterRegistry.hpp>

// QT
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QSpinBox>
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
     * Fetch the key list :
     */
    auto &reg = EtherBench::Models::ParameterRegistry::instance();
    QStringList keys = reg.allKeys();

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
    m_treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void SettingsView::setupEditor() {

    m_scrollArea = new QScrollArea(this);
    m_editorContainer = new QWidget();
    m_editorLayout = new QFormLayout(m_editorContainer);

    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_editorContainer);
}

void SettingsView::onCategorySelected(QTreeWidgetItem *current, QTreeWidgetItem *) {
    // Check if we're not already good
    if (!current)
        return;

    // If not, clean the current editor
    clearLayout(m_editorLayout);

    // Then, fill all the new keys
    QString categoryPath = getCategoryPath(current);
    auto &reg = EtherBench::Models::ParameterRegistry::instance();
    QStringList allKeys = reg.allKeys();

    for (const QString &key : reg.allKeys()) {
        QString paramParentPath = key.section('/', 0, -2);

        if (paramParentPath == categoryPath) {
            const auto &param = reg.get(key);
            m_editorLayout->addRow(param.label + " :", createEditorWidget(key, param));
        }
    }
}

QWidget *SettingsView::createEditorWidget(
    const QString &key, const EtherBench::Models::Parameter &param) {
    auto &reg = EtherBench::Models::ParameterRegistry::instance();

    switch (param.type) {
    case Models::ParamType::Bool: {
        QCheckBox *cb = new QCheckBox();
        cb->setChecked(param.value.toBool());
        // Binding : Quand on coche, on met à jour le registre
        connect(cb, &QCheckBox::toggled, [key, &reg](bool checked) {
            reg.setValue(key, checked);
        });
        return cb;
    }

    case Models::ParamType::Number: {
        QSpinBox *sb = new QSpinBox();
        sb->setRange(param.minValue.toInt(), param.maxValue.toInt());
        sb->setValue(param.value.toInt());

        connect(sb, &QSpinBox::valueChanged, [key, &reg](int val) {
            reg.setValue(key, val);
        });
        return sb;
    }

    case Models::ParamType::Selection: {
        // Menu déroulant pour les Enums
        QComboBox *combo = new QComboBox();
        combo->addItems(param.options);
        combo->setCurrentText(param.value.toString());

        connect(combo, &QComboBox::currentTextChanged, [key, &reg](const QString &text) {
            reg.setValue(key, text);
        });
        return combo;
    }

    case Models::ParamType::Text:
    default: {
        QLineEdit *le = new QLineEdit();
        le->setText(param.value.toString());

        connect(le, &QLineEdit::textChanged, [key, &reg](const QString &text) {
            reg.setValue(key, text);
        });
        return le;
    }
    }
}

QString SettingsView::getCategoryPath(QTreeWidgetItem *item) const {
    QString path = item->text(0);
    while (item->parent()) {
        item = item->parent();
        path = item->text(0) + "/" + path;
    }
    return path;
}

void SettingsView::clearLayout(QLayout *layout) {
    if (!layout)
        return;

    while (m_editorLayout->count() > 0) {
        QLayoutItem *item = m_editorLayout->takeAt(0);
        if (QWidget *w = item->widget()) {
            w->deleteLater();
        }
        delete item;
    }
}

} // namespace EtherBench::UI