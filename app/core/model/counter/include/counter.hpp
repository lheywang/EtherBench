#pragma once

#include <QObject>

namespace EtherBench::Core {

/**
 * @class CounterManager
 */
class CounterManager : public QObject {
    Q_OBJECT
  public:
    explicit CounterManager(QObject *parent = nullptr);

    void increment();

    int getCount() const { return m_count; }

  signals:
    void countChanged(int newValue);

  private:
    int m_count;
};

} // namespace EtherBench::Core
