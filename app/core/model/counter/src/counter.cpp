#include "core/CounterManager.hpp"

namespace EtherBench::Core {

CounterManager::CounterManager(QObject *parent) : QObject(parent), m_count(0) {}

void CounterManager::increment() {
    m_count++;
    emit countChanged(m_count);
}

} // namespace EtherBench::Core