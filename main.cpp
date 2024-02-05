#include <QApplication>
#include "application.h" // Assurez-vous d'inclure votre classe Application

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Application application; // Crée une instance de votre classe Application
    application.show(); // Affiche la fenêtre principale

    return app.exec();
}
