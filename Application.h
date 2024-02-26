#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <memory>
#include "UserStorage.h"
#include "LoginManager.h"

namespace Ui {
class Application;
}

class Application : public QMainWindow {
    Q_OBJECT

public:
    explicit Application(QWidget *parent = nullptr);
    ~Application() override;

private:
    Ui::Application *ui;
    std::shared_ptr<UserStorage> userStorage;  // Utilisez shared_ptr si UserStorage est partagé
    std::unique_ptr<LoginManager> loginManager;  // Utilisez unique_ptr si LoginManager n'est pas partagé

    void initializeApplication();
    bool isFirstLaunch();
    void showUserCreationForm();
    void showLoginPage();
};

#endif // APPLICATION_H
