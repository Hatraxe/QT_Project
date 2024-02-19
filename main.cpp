#include <QApplication>
#include "application.h" // Assurez-vous d'inclure votre classe Application

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Application application; // Crée une instance de votre classe Application
   // LoginForm loginForm;
   // loginForm.show();
    application.show(); // Affiche la fenêtre principale
   // SignInForm sin;
   // sin.show();
    return app.exec();
}
