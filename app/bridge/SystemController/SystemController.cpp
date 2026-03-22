#include "SystemController.hpp"
#include <QDebug>

SystemController::SystemController(
    QObject* parent
) : QObject(parent), m_clickCount(0), m_currentView(static_cast<int>(ActiveView::Home)) {}

int SystemController::getClickCount() const {
    return m_clickCount;
}

int SystemController::getCurrentView() const {
    return m_currentView;
}

void SystemController::executeAction(
    const QString& actionName
) {
    m_clickCount++;
    
    qInfo() << "[C++] Action reçue du QML :" << actionName << "| Compteur interne :" << m_clickCount;
    
    emit clickCountChanged();
}

void SystemController::setCurrentView(
    int viewId
) {
    if (m_currentView == viewId) {
        return;
    }
    
    m_currentView = viewId;
    qInfo() << "[Système] Basculement vers la vue ID :" << m_currentView;
    emit currentViewChanged();
}