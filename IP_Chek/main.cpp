#include <QApplication>
#include "IpInfoWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    IpInfoWidget widget;
    widget.show();
    return app.exec();
}
