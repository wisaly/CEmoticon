#ifndef ACCKEYNOTIFIER_H
#define ACCKEYNOTIFIER_H

#include "acckeys.h"

#include <QObject>

// Define accelerate key notifier
class AccKeyNotifier : public QObject
{
    Q_OBJECT
public:
    AccKeyNotifier(AccKeys keys,QObject *reciever,const char *slot);
    ~AccKeyNotifier();

protected slots:
    void on_accKeyPressed(AccKeys keys);

signals:
    void accPressed();
protected:
    AccKeys m_accKeys;
    QString m_slotName;
    static QList<AccKeyNotifier*> m_instances;
};

#endif // ACCKEYNOTIFIER_H
