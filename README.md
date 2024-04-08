


# SQLite Database Viewer

SQLite Database Viewer est une application développée en C++ avec le framework Qt. Elle permet de visualiser et d'interagir avec des bases de données SQLite. L'application offre une interface pour se connecter avec des profils d'utilisateurs différents, afficher et modifier les données des bases de données SQLite existantes.

## Fonctionnalités

-   **Gestion des Utilisateurs** : Création d'un nouvel utilisateur lors du premier lancement. Connexion/déconnexion avec mot de passe pour les utilisations suivantes.
-   **Profils Utilisateurs** : Chaque utilisateur peut posséder plusieurs profils.
-   **Gestion des Droits** : Les droits d'accès (visualisation, édition) sont spécifiques à chaque utilisateur.
-   **Super Utilisateur** : Un super utilisateur par défaut (`email: superuser`, `mdp: password`) dispose de tous les droits, permettant une gestion avancée de l'application.
-   **Visualisation et Gestion des Bases de Données** :
    -   Ajout et suppression de bases de données existantes via un `QFileDialog`.
    -   Sélection d'une base de données pour afficher ses tables et leurs contenus.
    -   Exécution de requêtes SQL avec affichage des résultats.
-   **Sécurité et Gestion des Droits** : Restriction des types de requêtes selon les droits de l'utilisateur (seul le super utilisateur peut exécuter toutes les requêtes).

## Installation

Décrivez ici comment compiler et exécuter votre application, y compris les dépendances requises et les étapes de compilation spécifiques à votre projet.

## Utilisation

1.  **Premier Lancement** : Suivez les instructions à l'écran pour créer un nouvel utilisateur.
2.  **Connexion** : Utilisez vos identifiants pour vous connecter. Pour accéder en tant que super utilisateur, utilisez l'email `superuser` et le mot de passe `password`.
3.  **Gestion des Bases de Données** : Utilisez l'interface pour ajouter, supprimer ou sélectionner des bases de données à visualiser.
4.  **Exécution de Requêtes** : Les utilisateurs peuvent exécuter des requêtes `SELECT`. Le super utilisateur a accès à toutes les opérations SQL.

## Développement Futur

-   **Amélioration de la Gestion des Droits** : Permettre au super utilisateur de modifier les droits d'accès des autres utilisateurs.
-   **Extension des Fonctionnalités** : Ajout de fonctionnalités avancées de gestion et d'analyse des données.
