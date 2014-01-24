#include <QApplication>
#include <config/appconfig.h>
#include "common/common.h"
#include "common/singleapplication.h"
#include "dlg/dlgconfig.h"

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv, CE_MUTEX);

    if (app.isRunning())
    {
        app.sendMessage("message from other instance.");
        return 0;
    }

    AppConfig::inst()->load();

    DlgConfig w;

    // connect message queue to the main window.
    //QObject::connect(&app, SIGNAL(messageAvailable(QString)), &w, SLOT(receiveMessage(QString)));

    w.show();

    return app.exec();
}
