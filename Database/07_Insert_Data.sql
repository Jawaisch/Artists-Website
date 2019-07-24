USE 19ss_tedk4_kws;
SET NAMES utf8;

INSERT INTO benutzer (User_ID, Login, Passwd, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon, Reg_Zeitstempel, Reg_IP) VALUES 
            (1401, 'HanniNanni',SHA2('HanniP0panni', 256), 'Frau', NULL, 'Hannah', 'Uhlig', 14480, 'Potsdam','Lise-Meitner-Str.','3','Hanni@web.de','0331 6005678','2018-06-24 16:23:14','245.201.02.01'),
            (1402, 'YakMe1ster',SHA2('Wazzzuuup', 256), 'Herr', NULL, 'Maik', 'Müller', 10050, 'Berlin','Heideweg','5B','Yakmeister@aol.de','030-77889900','2018-06-24 21:45:09','199.234.10.04'),
            (1403, 'Dr_Schnoesel',SHA2('P1C4550', 256), 'Frau', 'Prof. Dr.', 'Lea', 'Wiedmann', 20097, 'Hamburg','Reiche-Pinkel-Allee','12','DrWiedmann@Uni-Hamburg.de','0190 78912345','2018-06-25 10:12:37','145.101.01.01'),
            (1404, 'Cap10Marvel',SHA2('LanStee', 256), 'Divers', NULL, 'Elliot', 'Schmiel', 28205, 'Bremen','Bahnhofstrasse','2','artsy@web.de','0150/567 698 0','2018-06-29 13:31:03','92.58.12.03'),
            (1405, 'Canvas1983',SHA2('EchtHaarPinsel', 256), 'Herr', NULL, 'Simon', 'Grotzlowski', 04155, 'Leipzig','Am Marktplatz','23a','S.Grotzlowski@gmail.com','0167 111 111 19','2018-07-03 03:06:47','138.212.34.19');
      
INSERT INTO kuenstler (Kuenstler_ID, Kname, IBAN, BIC, Vita, User_ID) VALUES
            (1411,'Kazumi Yoshino','DE02160500001234567890','WELADED1PMB','Sometimes yo just have to close your eyes and enjoy the art...',1401),
            (1412,'Peter Eastman','DE21679900001234567890','HASUIK24','Klassisches Öl auf Leinwand trifft modernen Comic-Stil',1404),
            (1413,'Morty','DE08878700001234567890','DEUBBA14322', NULL, 1405);

INSERT INTO bild (Bild_ID, User_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP) VALUES
            (1421,NULL,1411,'Aquarell','Kirschblüten bei Nacht',540,420,90.00,'2018-06-24 17:08:14','245.201.02.01',NULL,NULL),
            (1422,1403,1411,'Tusche','Teezeremonie',600,800,200.00,'2018-06-24 17:17:23','245.201.02.01','2018-07-12 20:12:24','145.101.01.01'),
            (1423,NULL,1411,'Tusche','Simple Words',600,350,60.00,'2018-06-24 17:08:14','245.201.02.01',NULL,NULL),
            (1424,1401,1412,'Öl auf Leinwand','Infinity War',600,800,350.00,'2018-07-17 10:00:45','92.58.12.03','2018-07-18 15:03:24','245.201.02.01'),
            (1425,1402,1412,'Öl auf Leinwand','Shelltastic',350,250,120.00,'2018-08-29 17:03:36','92.58.12.03','2018-09-03 18:08:46','245.201.02.01'),
            (1426,NULL,1412,'Öl auf Leinwand','World Wide Web',500,500,200.00,'2018-09-22 23:05:02','92.58.12.03',NULL,NULL),
            (1427,NULL,1413,'Acryl auf Leinwand','Das Bild vom Bild',450,560,80.00,'2018-07-13 12:23:44','138.212.34.19',NULL,NULL),
            (1428,NULL,1413,'Zeichenkohle auf Papier','Halte mich',500,700,100.00,'2018-07-24 19:31:18','138.212.34.19',NULL,NULL),
            (1429,1403,1413,'Tusche auf Papier','Fluktuation 8',400,1200,300.00,'2018-08-03 17:52:37','138.212.34.19','2018-09-24 14:18:34','145.101.01.01');

INSERT INTO eingeordnet (Bild_ID, Genre_ID) VALUES
            (1421,130),
            (1422,107),
            (1423,130),
            (1424,111),
            (1425,111),
            (1426,111),
            (1427,124),
            (1428,105),
            (1429,101);