#include "application.h"
#include "qapplication.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Application application;
    application.show(); // Affiche la fenêtre principale
    return app.exec();
}
