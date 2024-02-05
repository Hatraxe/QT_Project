#ifndef DATABASEVIEWER_H
#define DATABASEVIEWER_H

#include <QWidget>
#include <QSqlDatabase>

class DatabaseViewer : public QWidget {
    Q_OBJECT

public:
    explicit DatabaseViewer(QWidget *parent = nullptr);
    ~DatabaseViewer();

    bool connectToDatabase(const QString &databasePath); // Établit une connexion à la base de données
    void refreshData(); // Rafraîchit et affiche les données de la base de données

private:
    QSqlDatabase db; // L'objet de connexion à la base de données
    // Vous pouvez ajouter ici d'autres attributs nécessaires pour la gestion de l'affichage des données

    void setupUi(); // Configure l'interface utilisateur du visualiseur
    void loadData(); // Charge les données de la base de données et les affiche
};

#endif // DATABASEVIEWER_H
