#ifndef SIGNINFORM_H
#define SIGNINFORM_H

#include <QWidget>

namespace Ui {
class SignInForm;
}

class SignInForm : public QWidget {
    Q_OBJECT

public:
    explicit SignInForm(QWidget *parent = nullptr);
    ~SignInForm();

private slots:
    void on_signInButton_clicked(); // Slot pour gérer le clic sur le bouton d'inscription

private:
    Ui::SignInForm*ui;
};

#endif // SIGNINFORM_H
