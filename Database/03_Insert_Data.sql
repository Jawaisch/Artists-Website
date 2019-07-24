USE 19ss_tedk4_kws;
SET NAMES utf8;
/* Erst einmal aufräumen:
   Dubletten vermeiden !    */
DELETE FROM eingeordnet WHERE Bild_ID      BETWEEN 0221 AND 0229;
DELETE FROM bild        WHERE Bild_ID      BETWEEN 0221 AND 0229;
DELETE FROM kuenstler   WHERE Kuenstler_ID BETWEEN 0211 AND 0219;
DELETE FROM benutzer    WHERE User_ID      BETWEEN 0201 AND 0209;

INSERT INTO benutzer (User_ID, Login, Passwd, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon, Reg_Zeitstempel, Reg_IP) VALUES 
            (0201, 'Hans Müller',SHA2('beatifullittlecloud', 256), 'Herr', NULL, 'Hans', 'Müller', 32114, 'Daytona','Beach str.','3','mueller@web.de','0331 6004678','2015-06-24 16:23:13','245.231.02.01'),
            (0202, 'Bob',SHA2('476ghl2', 256), 'Herr', NULL, 'Bob', 'Ross', 13156, 'Berlin','Okarinastr.','89','bob@yahoo.com','030-54279902','2018-06-23 20:45:09','199.233.10.14'),
            (0203, 'Ulrike',SHA2('jtzkw4r', 256), 'Frau', NULL, 'Ulrike', 'Koch', 95448, 'Bayreuth','Stuckbergstr','12','koch@web.de','0190 78912345','2017-06-25 10:12:37','145.131.01.01'),
            (0204, 'Tom',SHA2('wawfff', 256), 'Herr', 'Prof. Dr.' , 'Tom', 'Fröhlich', 28205, 'Hannover','Rolandstr.','2','tom@web.de','0150/567 6987','2018-04-29 13:31:03','72.58.12.02'),
            (0205, 'Hui Buh',SHA2('wafwffwe', 256), 'Divers', NULL, 'Hui', 'Buh', 04155, 'Gruselschlosshausen','Brunnenweg','2','buh@gruselschloss.de','0167 111 111 19','2011-07-03 03:06:47','132.212.34.18');
      
INSERT INTO kuenstler (Kuenstler_ID, Kname, IBAN, BIC, Vita, User_ID) VALUES
            (0211,'Bob Ross','DE02160500341234567890','rosstheboss','Lets draw a beautiful little cloud.',0202),
            (0212,'Hans','DE21679900568234567890','moechtegern0815','',0201),
            (0213,'Giger','DE08878727001234567890','giger_ch', NULL, 0205);

INSERT INTO bild (Bild_ID, User_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP) VALUES
            (0221,NULL,0212,'Fotografie','Korsika',540,420,90.00,'2018-06-24 17:08:14','245.201.02.01',NULL,NULL),
            (0222,0203,0211,'Fotografie','Brandenburger Tor',600,800,200.00,'2018-06-24 17:17:23','245.201.02.01','2018-07-12 20:12:24','145.101.01.01'),
            (0223,NULL,0211,'Fotografie','Tür im Herbst',600,350,60.00,'2018-06-24 17:08:14','245.201.02.01',NULL,NULL),
            (0224,0201,0212,'Digitale Zeichnung','Metallic',600,800,350.00,'2018-07-17 10:00:45','92.58.12.03','2018-07-18 15:03:24','245.201.02.01'),
            (0225,0202,0212,'Fotografie','Seerose',350,250,120.00,'2018-08-29 17:03:36','92.58.12.03','2018-09-03 18:08:46','245.201.22.01'),
            (0226,NULL,0213,'Emblem','Raumanzug',500,500,200.00,'2018-09-22 23:05:02','92.58.12.03',NULL,NULL),
            (0227,NULL,0213,'Poster','Das unheimliche Wesen aus einer fremden Welt',450,560,80.00,'2018-07-13 12:23:44','138.212.34.19',NULL,NULL),
            (0228,NULL,0211,'Digitale Zeichnung','paintskill lvl 99',500,700,100.00,'2018-07-24 19:31:18','118.212.34.19',NULL,NULL),
            (0229,0203,0213,'Öl auf Leinwand','Gogh',400,1200,300.00,'2018-08-03 17:52:37','128.212.34.19','2018-09-24 14:18:34','145.121.01.01');

INSERT INTO eingeordnet (Bild_ID, Genre_ID) VALUES
            (0221,130),
            (0222,107),
            (0223,130),
            (0224,111),
            (0225,111),
            (0226,111),
            (0227,124),
            (0228,105),
            (0229,101);