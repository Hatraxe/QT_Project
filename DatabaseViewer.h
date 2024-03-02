/*!
 * \file DatabaseViewer.h
 * \brief Définition de la classe DatabaseViewer pour visualiser les données d'une base de données SQLite.
 *
 * DatabaseViewer fournit une interface pour afficher et interagir avec les données d'une base de données SQLite.
 */

#ifndef DATABASEVIEWER_H
#define DATABASEVIEWER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVBoxLayout>
#include <QTableView>
#include <QSqlTableModel>

/*!
 * \class DatabaseViewer
 * \brief La classe DatabaseViewer est utilisée pour afficher les données d'une base de données SQLite dans une interface graphique.
 *
 * Cette classe crée une connexion à une base de données SQLite spécifiée et affiche ses données dans un QTableView.
 */
class DatabaseViewer : public QWidget {
    Q_OBJECT

public:
    /*!
     * \brief Constructeur de DatabaseViewer.
     * \param parent Le widget parent de ce widget.
     */
    explicit DatabaseViewer(QWidget *parent = nullptr);

    /*!
     * \brief Destructeur de DatabaseViewer.
     */
    ~DatabaseViewer();

    /*!
     * \brief Établit une connexion à la base de données SQLite spécifiée.
     * \param databasePath Le chemin d'accès au fichier de la base de données SQLite.
     * \return true si la connexion est établie avec succès, false sinon.
     */
    bool connectToDatabase(const QString &databasePath);

    /*!
     * \brief Rafraîchit les données affichées dans le QTableView.
     *
     * Cette méthode recharge les données depuis la base de données et met à jour l'affichage.
     */
    void refreshData();

private:
    QSqlDatabase db; ///< L'objet de connexion à la base de données.

    /*!
     * \brief Configure l'interface utilisateur du visualiseur.
     *
     * Cette méthode initialise le QTableView et d'autres widgets nécessaires pour afficher les données.
     */
    void setupUi();

    /*!
     * \brief Charge les données de la base de données et les affiche dans le QTableView.
     *
     * Cette méthode utilise un QSqlTableModel pour lier les données de la base de données au QTableView.
     */
    void loadData();
};

#endif // DATABASEVIEWER_H
