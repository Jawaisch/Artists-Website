SET NAMES utf8;
USE mysql;

/* Benutzer löschen, wenn bereits existent */
/* Original war:
DELETE FROM `user` WHERE `User` = 'kws_bearbeiter' OR `User` = 'kws_kuenstler' OR `User` = 'kws_kunde' OR `User` = 'kws_gast' OR `User` = 'kws_login' OR `User` = 'kws_reg' OR `User` = 'kws_admin';


Diese Alternative nur bei konsequenten Namenskonventionen
*/
DELETE FROM `user`          WHERE `User` LIKE 'kws_%';
DELETE FROM `db`            WHERE `User` LIKE 'kws_%';
DELETE FROM `columns_priv`  WHERE `User` LIKE 'kws_%';
DELETE FROM `proxies_priv`  WHERE `User` LIKE 'kws_%';
DELETE FROM `tables_priv`   WHERE `User` LIKE 'kws_%';

/*Benutzerrechte bereinigen*/
FLUSH PRIVILEGES;

/* Benutzer erstellen */


CREATE USER 'kws_admin'@'%'         IDENTIFIED BY 'test';
CREATE USER 'kws_bearbeiter'@'%'    IDENTIFIED BY 'kws_bearbeiter';
CREATE USER 'kws_kunde'@'%'         IDENTIFIED BY 'kws_kunde';
CREATE USER 'kws_gast'@'%'          IDENTIFIED BY 'kws_gast';
CREATE USER 'kws_login'@'%'         IDENTIFIED BY 'kws_login';
CREATE USER 'kws_reg'@'%'           IDENTIFIED BY 'kws_reg';
CREATE USER 'kws_kuenstler'@'%'     IDENTIFIED BY 'kws_kuenstler';
# und noch mal für localhost
CREATE USER 'kws_admin'@'localhost'         IDENTIFIED BY 'test';
CREATE USER 'kws_bearbeiter'@'localhost'    IDENTIFIED BY 'kws_bearbeiter';
CREATE USER 'kws_kunde'@'localhost'         IDENTIFIED BY 'kws_kunde';
CREATE USER 'kws_gast'@'localhost'          IDENTIFIED BY 'kws_gast';
CREATE USER 'kws_login'@'localhost'         IDENTIFIED BY 'kws_login';
CREATE USER 'kws_reg'@'localhost'           IDENTIFIED BY 'kws_reg';
CREATE USER 'kws_kuenstler'@'localhost'     IDENTIFIED BY 'kws_kuenstler';


/*Benutzerrechte bereinigen*/
FLUSH PRIVILEGES;


/*ab hier Rechtevergabe*/
USE 19ss_tedk4_kws;

# Privileges for `kws_bearbeiter`@`%`

GRANT SELECT ON 19ss_tedk4_kws.bild TO 'kws_bearbeiter'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (Bild_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, User_ID, Kauf_Zeitstempel, Kauf_IP, Resv_Zeitstempel ) ON 19ss_tedk4_kws.bild TO 'kws_bearbeiter'@'%' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT (User_ID, Login, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon, Reg_Zeitstempel) ON 19ss_tedk4_kws.benutzer TO 'kws_bearbeiter'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (Login, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon) ON 19ss_tedk4_kws.benutzer TO 'kws_bearbeiter'@'%' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT ON 19ss_tedk4_kws.kuenstler TO 'kws_bearbeiter'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE ON 19ss_tedk4_kws.kuenstler TO 'kws_bearbeiter'@'%' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT, UPDATE, INSERT ON 19ss_tedk4_kws.Genre TO 'kws_bearbeiter'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT SELECT, INSERT, DELETE ON 19ss_tedk4_kws.eingeordnet TO 'kws_bearbeiter'@'%' with MAX_QUERIES_PER_HOUR 360000000;



# Privileges for `kws_kuenstler`@`%`

GRANT SELECT (Bild_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Kuenstler_ID, Einstell_Zeitstempel, User_ID, Kauf_Zeitstempel, Resv_Zeitstempel) ON 19ss_tedk4_kws.bild TO 'kws_kuenstler'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Resv_Zeitstempel) ON 19ss_tedk4_kws.bild TO 'kws_kuenstler'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT INSERT, DELETE ON 19ss_tedk4_kws.bild TO 'kws_kuenstler'@'%' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT (User_ID, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon, Reg_Zeitstempel) ON 19ss_tedk4_kws.benutzer TO 'kws_kuenstler'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (Passwd, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon) ON 19ss_tedk4_kws.benutzer TO 'kws_kuenstler'@'%' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT, UPDATE ON 19ss_tedk4_kws.kuenstler TO 'kws_kuenstler'@'%' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT ON 19ss_tedk4_kws.Genre TO 'kws_kuenstler'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT SELECT, INSERT, DELETE ON 19ss_tedk4_kws.eingeordnet TO 'kws_kuenstler'@'%' with MAX_QUERIES_PER_HOUR 360000000;




# Privileges for `kws_kunde`@`%`

GRANT SELECT (Bild_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Kuenstler_ID, Einstell_Zeitstempel, User_ID, Kauf_Zeitstempel, Resv_Zeitstempel) ON 19ss_tedk4_kws.bild TO 'kws_kunde'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (User_ID, Kauf_Zeitstempel, Kauf_IP, Resv_Zeitstempel) ON 19ss_tedk4_kws.bild TO 'kws_kunde'@'%' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT (User_ID, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon, Reg_Zeitstempel) ON 19ss_tedk4_kws.benutzer TO 'kws_kunde'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (Passwd, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon) ON 19ss_tedk4_kws.benutzer TO 'kws_kunde'@'%' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT (Kuenstler_ID, User_ID, Kname, Vita) ON 19ss_tedk4_kws.kuenstler TO 'kws_kunde'@'%' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT ON 19ss_tedk4_kws.Genre TO 'kws_kunde'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT SELECT ON 19ss_tedk4_kws.eingeordnet TO 'kws_kunde'@'%' with MAX_QUERIES_PER_HOUR 360000000;



# Privileges for `kws_gast`@`%`

GRANT SELECT (Bild_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Kuenstler_ID, Einstell_Zeitstempel, Kauf_Zeitstempel,Resv_Zeitstempel) ON 19ss_tedk4_kws.bild TO 'kws_gast'@'%' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT (Kuenstler_ID, Kname, Vita) ON 19ss_tedk4_kws.kuenstler TO 'kws_gast'@'%' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT ON 19ss_tedk4_kws.Genre TO 'kws_gast'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT SELECT ON 19ss_tedk4_kws.eingeordnet TO 'kws_gast'@'%' with MAX_QUERIES_PER_HOUR 360000000;



# Privileges for `kws_login`@`%`

GRANT SELECT (User_ID, Login, Passwd) ON 19ss_tedk4_kws.benutzer TO 'kws_login'@'%' with MAX_QUERIES_PER_HOUR 360000000;



# Privileges for `kws_reg`@`%`
GRANT SELECT (User_ID, login) ON 19ss_tedk4_kws.benutzer TO 'kws_kunde'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT INSERT ON 19ss_tedk4_kws.benutzer TO 'kws_reg'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT SELECT (Kuenstler_ID, User_ID) ON 19ss_tedk4_kws.kuenstler TO 'kws_kunde'@'%' with MAX_QUERIES_PER_HOUR 360000000;
GRANT INSERT ON 19ss_tedk4_kws.kuenstler TO 'kws_reg'@'%' with MAX_QUERIES_PER_HOUR 360000000;



# Privileges for `kws_admin`@`%`

GRANT ALL 
   ON 19ss_tedk4_kws.* 
   TO 'kws_admin'@'%'
   WITH GRANT OPTION;



# Privileges for `kws_bearbeiter`@`localhost`

GRANT SELECT ON 19ss_tedk4_kws.bild TO 'kws_bearbeiter'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (Bild_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, User_ID, Kauf_Zeitstempel, Kauf_IP ) ON 19ss_tedk4_kws.bild TO 'kws_bearbeiter'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT (User_ID, Login, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon, Reg_Zeitstempel) ON 19ss_tedk4_kws.benutzer TO 'kws_bearbeiter'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (Login, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon) ON 19ss_tedk4_kws.benutzer TO 'kws_bearbeiter'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT ON 19ss_tedk4_kws.kuenstler TO 'kws_bearbeiter'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE ON 19ss_tedk4_kws.kuenstler TO 'kws_bearbeiter'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT, UPDATE, INSERT ON 19ss_tedk4_kws.Genre TO 'kws_bearbeiter'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT SELECT, INSERT, DELETE ON 19ss_tedk4_kws.eingeordnet TO 'kws_bearbeiter'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;



# Privileges for `kws_kuenstler`@`localhost`

GRANT SELECT (Bild_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Kuenstler_ID, Einstell_Zeitstempel, User_ID, Kauf_Zeitstempel, Resv_Zeitstempel) ON 19ss_tedk4_kws.bild TO 'kws_kuenstler'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Resv_Zeitstempel) ON 19ss_tedk4_kws.bild TO 'kws_kuenstler'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT INSERT, DELETE ON 19ss_tedk4_kws.bild TO 'kws_kuenstler'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT (User_ID, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon, Reg_Zeitstempel) ON 19ss_tedk4_kws.benutzer TO 'kws_kuenstler'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (Passwd, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon) ON 19ss_tedk4_kws.benutzer TO 'kws_kuenstler'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT, UPDATE ON 19ss_tedk4_kws.kuenstler TO 'kws_kuenstler'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT ON 19ss_tedk4_kws.Genre TO 'kws_kuenstler'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT SELECT, INSERT, DELETE ON 19ss_tedk4_kws.eingeordnet TO 'kws_kuenstler'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;



# Privileges for `kws_kunde`@`localhost`

GRANT SELECT (Bild_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Kuenstler_ID, Einstell_Zeitstempel, User_ID, Kauf_Zeitstempel,Resv_Zeitstempel) ON 19ss_tedk4_kws.bild TO 'kws_kunde'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (User_ID, Kauf_Zeitstempel, Kauf_IP,Resv_Zeitstempel) ON 19ss_tedk4_kws.bild TO 'kws_kunde'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT (User_ID, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon, Reg_Zeitstempel) ON 19ss_tedk4_kws.benutzer TO 'kws_kunde'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT UPDATE (Passwd, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon) ON 19ss_tedk4_kws.benutzer TO 'kws_kunde'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT (Kuenstler_ID, User_ID, Kname, Vita) ON 19ss_tedk4_kws.kuenstler TO 'kws_kunde'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT ON 19ss_tedk4_kws.Genre TO 'kws_kunde'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT SELECT ON 19ss_tedk4_kws.eingeordnet TO 'kws_kunde'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;



# Privileges for `kws_gast`@`localhost`

GRANT SELECT (Bild_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Kuenstler_ID, Einstell_Zeitstempel, Kauf_Zeitstempel,Resv_Zeitstempel) ON 19ss_tedk4_kws.bild TO 'kws_gast'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT (Kuenstler_ID, Kname, Vita) ON 19ss_tedk4_kws.kuenstler TO 'kws_gast'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;

GRANT SELECT ON 19ss_tedk4_kws.Genre TO 'kws_gast'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT SELECT ON 19ss_tedk4_kws.eingeordnet TO 'kws_gast'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;



# Privileges for `kws_login`@`localhost`

GRANT SELECT (User_ID, Login, Passwd) ON 19ss_tedk4_kws.benutzer TO 'kws_login'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;



# Privileges for `kws_reg`@`localhost`
GRANT SELECT (User_ID, login) ON 19ss_tedk4_kws.benutzer TO 'kws_kunde'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT INSERT ON 19ss_tedk4_kws.benutzer TO 'kws_reg'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT SELECT (Kuenstler_ID, User_ID) ON 19ss_tedk4_kws.kuenstler TO 'kws_kunde'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;
GRANT INSERT ON 19ss_tedk4_kws.kuenstler TO 'kws_reg'@'localhost' with MAX_QUERIES_PER_HOUR 360000000;



# Privileges for `kws_admin`@`localhost`

GRANT ALL 
    ON 19ss_tedk4_kws.*
    TO 'kws_admin'@'localhost'
    WITH GRANT OPTION;

