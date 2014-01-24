#ifndef ACCKEYS_H
#define ACCKEYS_H

#include <QBitArray>
#include <QString>

// Define accelerate key combination
class AccKeys
{
    friend class AccKeyThread;
protected:
    // Construct with combination data
    AccKeys(QBitArray &d) : m_arrData(d) {}
public:
    AccKeys();
    // Add key to combination
    AccKeys &setKey(int vkey);
    // Is key exist combination
    bool existKey(int vkey);
    // Extract combination to a string separator with specify separator
    QString toString(QString separator = QString("+"));

    // Logical equal compare
    bool operator ==(AccKeys &keys) const;
    // Logical Unequal compare
    bool operator !=(AccKeys &keys) const;

    // Parse string to key type
    static AccKeys fromString(QString keys,QString separator = QString("+"));
    // Convert virtual key code to string
    static QString translateVKey(int vkey,QString nullString = QString("<Invalid>"));

protected:
    QBitArray m_arrData;
};

#endif // ACCKEYS_H
