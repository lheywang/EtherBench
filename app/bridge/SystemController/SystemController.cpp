#include "SystemController.hpp"

SystemController::SystemController(QObject *parent)
    : QObject(parent), m_currentView(Home) {}

SystemController::ViewId SystemController::getCurrentView() const {
  return m_currentView;
}

void SystemController::setCurrentView(ViewId view) {
  if (m_currentView != view) {
    m_currentView = view;
    emit currentViewChanged();
  }
}