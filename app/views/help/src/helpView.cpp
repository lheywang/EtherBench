/**
 * @file helpView.cpp
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
#include <views/helpView.hpp>

// Local libraries
#include <views/baseView.hpp>

// Models
#include <models/statusHub.hpp>

// QT
#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QMenuBar>
#include <QString>
#include <QTextBrowser>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------
namespace EtherBench::UI {

HelpView::HelpView(QWidget *parent) : BaseView(parent) {

    /*
     * Configure the UI
     */
    setupUI();
    makeConnections();
}

QString HelpView::viewTitle() const { return "Help"; }

void HelpView::onActivated() { qDebug() << "Welcome to help"; }

void HelpView::onDeactivated() { qDebug() << "Exiting ..."; }

void HelpView::fillMenubar(QMenuBar *menuBar) {

    QMenu *helpMenu = menuBar->addMenu("&Help");
    helpMenu->addAction("Return to homepage");
}

void HelpView::setupUI() {

    m_layout = new QVBoxLayout(this);
    m_browser = new QTextBrowser(this);

    // Loading the stylesheet
    QFile cssFile("qrc:/docs/css/style.css");
    if (cssFile.open(QIODevice::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(cssFile.readAll());
        browser->document()->setDefaultStyleSheet(styleSheet);
    }

    // Configure browser UI
    m_browser->setFrameShape(QFrame::NoFrame);
    m_browser->setSource(QUrl("qrc:/docs/html/main.html"));

    // Finish the layout
    m_layout->addWidget(m_browser);
    m_layout->setContentsMargins(0, 0, 0, 0);
}

void HelpView::makeConnections() {

    connect(m_browser, &QTextBrowser::sourceChanged, [](const QUrl &url) {
        EtherBench::Models::StatusHub::instance().info(
            "Reading documentation: " + url.fileName());
    });
}

} // namespace EtherBench::UI