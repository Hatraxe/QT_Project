#include "loginform.h"
#include "ui_loginform.h"
#include <QMessageBox>
LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_Login_clicked()
{
    QString login = ui->lineEdit_Login_Email->text();
    QString motDePasse = ui->lineEdit_Mdp->text();

    if(login == "test" && motDePasse == "test2")
    {
        QMessageBox::information(this,"Login", "Login et mot de passe sont correct");
    }
    else
    {
        QMessageBox::information(this,"Login", "Login et mot de passe ne sont pas correct");

    }
}

void LoginForm::on_pushButton_MdpOublie_clicked()
{
    QMessageBox::information(this,"Erreur","Conctactez l'administrateur pour changer de mot de passe");
}
