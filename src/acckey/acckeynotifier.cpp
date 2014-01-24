#include <QMetaType>
#include <QApplication>
#include "acckeynotifier.h"
#include "acckeythread.h"

int typeId = qRegisterMetaType<AccKeys>("AccKeys");

QList<AccKeyNotifier*> AccKeyNotifier::m_instances;

AccKeyNotifier::AccKeyNotifier( AccKeys keys,QObject *reciever,const char *slot )
:QObject(reciever),m_accKeys(keys),m_slotName(slot)
{
    for (int i = 0;i < m_instances.count();i ++)
    {
        if (m_instances[i]->m_slotName == m_slotName)
        {
            disconnect(
                AccKeyThread::inst(),
                SIGNAL(accKeyPressed(AccKeys)),
                m_instances[i],
                SLOT(on_accKeyPressed(AccKeys)));

            disconnect(
                m_instances[i],
                SIGNAL(accPressed()),
                m_instances[i]->parent(),
                slot);

            m_instances[i]->deleteLater();
        }
    }

    this->connect(AccKeyThread::inst(),
        SIGNAL(accKeyPressed(AccKeys)),
        SLOT(on_accKeyPressed(AccKeys)));

    reciever->connect(this,SIGNAL(accPressed()),slot);

    m_instances.append(this);
}


AccKeyNotifier::~AccKeyNotifier()
{
    m_instances.removeOne(this);
}

void AccKeyNotifier::on_accKeyPressed( AccKeys keys )
{
    if (m_accKeys == keys)
    {
        emit accPressed();
    }
}
