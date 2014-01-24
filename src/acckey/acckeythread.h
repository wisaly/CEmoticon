#ifndef ACCKEYTHREAD_H
#define ACCKEYTHREAD_H

#include "acckeys.h"

#include <QThread>

// Define accelerate key detect thread
class AccKeyThread : public QThread
{
    Q_OBJECT
public:
    // Interval indicate detect frequency
    AccKeyThread(uint interval = 300);
    ~AccKeyThread(void);

    // Indicate virtual key code limit
    enum {COUNT_VK = 256};

    // Singleton pattern instance function
    static AccKeyThread *inst();

signals:
    // Key press signal
    void accKeyPressed(AccKeys keys);

public slots:
    // Stop thread
    void stop();

protected:
    // Thread main function
    void run();
protected:
    bool m_stop;				// Indicate is thread should stop
    uint m_interval;			// Indicate thread detect frequency
    QBitArray m_caredKeys;	// Indicate which key code is cared
};

#endif // ACCKEYTHREAD_H
