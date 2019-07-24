USE 19ss_tedk4_kws;

DELETE FROM eingeordnet WHERE Bild_ID      BETWEEN 750 AND 758;
DELETE FROM bild        WHERE Bild_ID      BETWEEN 750 AND 758;
DELETE FROM kuenstler   WHERE Kuenstler_ID BETWEEN 760 AND 762;
DELETE FROM benutzer    WHERE User_ID      BETWEEN 700 AND 704;


INSERT INTO benutzer
( User_ID , Login , Passwd , Anrede , Titel , Vorname , Nachname , PLZ , Ort, Strasse , HausNr , Email , Telefon , Reg_Zeitstempel , Reg_IP)
VALUES
(700,'MC_Monte',SHA2('Daheim',256),'Divers','Dr.','Monte','Carlo','85386','Eching','Obere Hauptstrasse','22a','Monte.Carlo@gmail.com','089123456','2019-01-03','130.168.0.10'),
(701,'CC_TOP',SHA2('ZMINGA',256),'Frau','','Claudia','Cram','85375','Neufahrn','Auweg','27','Claudia.Cram@web.com','08165123456','2019-02-13','202.168.0.11'),
(702,'Günni',SHA2('Hartertyp',256),'Herr','','Günther','Gross','85774','Unterföhring','Gernweg','15','KGrasser.Günni@gmail.com','089123457','2019-03-24','150.168.0.12'),
(703,'Faustus',SHA2('Foerster',256),'Herr','','Christoph','Spalter','13187','Berlin','Breite Straße','20','Spalter.Chris@gmail.com','030456789','2019-01-07','22.168.0.13'),
(704,'Freeman',SHA2('klausklausklaus',256),'Frau','Dr.','Morgana','Freimann','13158','Berlin','Kastanienallee','107a','Frei.Geist@gmail.com','030123456','2019-01-03','56.168.0.14');

INSERT INTO kuenstler ( Kuenstler_ID , User_ID , Kname , IBAN , BIC , Vita ) VALUES
(760 , 700 , 'Icinv' ,'DE45123412341234123412','GENBAN12K12','Toller Text'),
(761 , 701 , 'Tenom' ,'DE45123415987234123412','GENBAN12K13','Noch mehr toller Text'),
(762 , 703 , 'Tmilk' ,'DE46582435987234123412','GENBAN12K15','Ich dreh gleich durch so toll ist der Text :DDDDDDDd!!!1111elf');

INSERT INTO bild ( Bild_ID , User_ID , Kuenstler_ID , Mal_Technik , Titel , Hoehe,Breite , Einstell_Zeitstempel , Einstell_IP , VK_Preis , Kauf_Zeitstempel  , Kauf_IP)
VALUES
(750, NULL ,760,'Bundstifte','Die Welt im Wandel',600,600,'2019-01-03','130.168.0.10','50.00',NULL,NULL),
(751, 704 ,760,'Fingerfarben','Sonne',1158,1164,'2019-01-27','130.168.0.10','120.00','2019-02-22','56.168.0.14'),
(752, NULL ,760,'Pinselmalerei','Boot',338,508,'2019-02-14','130.168.0.10','150.00',NULL,NULL),

(753, NULL ,761,'Impasto','Blau',218,170,'2019-05-03','202.168.0.11','12.00',NULL,NULL),
(754, NULL ,761,'Pastell','Katze',565,800,'2019-06-03','202.168.0.11','12.00',NULL,NULL),
(755, 702 ,761,'Pinselmalerei','Fisch',700,700,'2019-07-03','202.168.0.11','12.00','2019-07-22','150.168.0.12'),

(756, 704 ,762,'Pinselmalerei','Einsamkeit',330,660,'2019-01-07','22.168.0.13','12.00','2019-01-09','56.168.0.14'),
(757, NULL ,762,'Bundstifte','Ich rauche nicht ich dampfe',225,225,'2019-02-13','22.168.0.13','12.00',NULL,NULL),
(758, NULL ,762,'Acryl','#Gesund',174,290,'2019-03-22','22.168.0.13','12.00',NULL,NULL);

INSERT INTO eingeordnet(Bild_ID , Genre_ID ) VALUES

(750,101),
(751,101),
(752,130),

(753,101),
(754,130),
(755,107),

(756,131),
(757,134),
(758,113);