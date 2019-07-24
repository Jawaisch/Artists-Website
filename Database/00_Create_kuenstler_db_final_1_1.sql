/* SQL-Skript zum Aufbau der kuenstler-Datenbank */
-- erstmal aufraeumen
DROP DATABASE /*! IF EXISTS */ 19ss_tedk4_kws;

-- jetzt neu anlegen
CREATE DATABASE 19ss_tedk4_kws
  DEFAULT CHARACTER SET "utf8";

USE 19ss_tedk4_kws;

CREATE TABLE benutzer (
  User_ID               BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
  Login                 VARCHAR(20) NOT NULL UNIQUE,
  Passwd                CHAR(64) NOT NULL,
  Anrede                ENUM ("Herr", "Frau", "Divers") NOT NULL,
  Titel                 VARCHAR(20) NULL,
  Vorname               VARCHAR(40) NOT NULL,
  Nachname              VARCHAR(60) NOT NULL,
  PLZ                   INT(5) ZEROFILL NOT NULL,
  Ort                   VARCHAR(40) NOT NULL,
  Strasse               VARCHAR(40) NOT NULL,
  HausNr                VARCHAR(15) NOT NULL,
  Email                 VARCHAR(120) NOT NULL,
  Telefon               VARCHAR(20) NOT NULL,
  Reg_Zeitstempel       TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  Reg_IP                VARCHAR(20) NOT NULL
)ENGINE = InnoDB;

CREATE TABLE kuenstler (
  Kuenstler_ID          BIGINT UNSIGNED PRIMARY KEY AUTO_INCREMENT NOT NULL,
  Kname                 VARCHAR(40) NOT NULL UNIQUE,
  IBAN                  CHAR(22) NOT NULL,
  BIC                   VARCHAR(11) NOT NULL,
  -- Leider nicht in MySQL  CONSTRAINT C_BIC  CHECK (REGEXP_LIKE(BIC, '[A-Z]{6}[A-Z0-9]{2}([A-Z0-9]{3})?')),
  Vita                  VARCHAR(1000) NULL,
  User_ID               BIGINT UNSIGNED NOT NULL,
  FOREIGN KEY (User_ID) REFERENCES benutzer (User_ID)
)ENGINE = InnoDB;

CREATE TABLE bild (
  Bild_ID                   BIGINT UNSIGNED PRIMARY KEY AUTO_INCREMENT NOT NULL,
  User_ID                   BIGINT UNSIGNED NULL,  -- angepasst
  FOREIGN KEY (User_ID)     REFERENCES benutzer (User_ID),
  Kuenstler_ID              BIGINT UNSIGNED NOT NULL,
  FOREIGN KEY (Kuenstler_ID)REFERENCES kuenstler (Kuenstler_ID),
  Mal_Technik               VARCHAR(60) NOT NULL,
  Titel                     VARCHAR(60) NOT NULL,
  Hoehe                     INT(4) UNSIGNED NOT NULL,
  Breite                    INT(4) UNSIGNED NOT NULL,
  VK_Preis                  FLOAT (10,2) NOT NULL,
  Einstell_Zeitstempel      TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  Einstell_IP               VARCHAR(20) NOT NULL,
  Kauf_Zeitstempel          DATETIME NULL,
  Kauf_IP                   VARCHAR(20) NULL,
  Resv_Zeitstempel          DATETIME NULL
)ENGINE = InnoDB;

CREATE TABLE genre (
  Genre_ID              SMALLINT(3) UNSIGNED PRIMARY KEY AUTO_INCREMENT NOT NULL,
  Name                  VARCHAR(60) NOT NULL,
  Beschreibung          VARCHAR(2000) NOT NULL
)ENGINE = InnoDB;

CREATE TABLE eingeordnet (
  Bild_ID    BIGINT UNSIGNED NOT NULL,
  Genre_ID   SMALLINT(3) UNSIGNED NOT NULL,
  PRIMARY KEY (Bild_ID, Genre_ID),
  CONSTRAINT  FrKey_Eingeordnet_Bild_ID
              FOREIGN KEY (Bild_ID) REFERENCES bild (Bild_ID),
  CONSTRAINT  FrKey_Eingeordnet_Genre_ID
              FOREIGN KEY (Genre_ID) REFERENCES genre (Genre_ID)
) ENGINE = InnoDB;