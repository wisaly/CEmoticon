#ifndef DLGCONFIG_H
#define DLGCONFIG_H

#include <QDialog>

namespace Ui {
class DlgConfig;
}

class DlgConfig : public QDialog
{
    Q_OBJECT

public:
    explicit DlgConfig(QWidget *parent = 0);
    ~DlgConfig();

private:
    Ui::DlgConfig *ui;
};

#endif // DLGCONFIG_H
