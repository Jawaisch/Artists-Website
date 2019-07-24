USE 19ss_tedk4_kws;
SET NAMES utf8;

INSERT INTO benutzer ( User_ID, Login, Passwd, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon, Reg_Zeitstempel, Reg_IP ) VALUES 
    ( 4231, "brauer21", SHA2("MeinSicheresPassWD", 256), "Herr", NULL , "Martin", "Brauer", 20259, "Hamburg", "Fruchtallee", "27a", "Brauer.Martin@Yahoo.de", "01753539875", "2018-12-09 13:12:13", "112.64.3.122"),
    ( 4232, "Kunst4Ever", SHA2("Willi123", 256), "Frau", "Dr." , "Wilma", "Haschen", 99087, "Erfurt", "Nödaler Weg", "3", "Wilma.Kunstwerke@Gmx.de", "‎0361/24516341", "2018-12-25 23:50:13", "103.124.21.2"),
    ( 4233, "OhseBild", SHA2("Oehsi2018", 256), "Herr", NULL , "Franz", "Ohse", 12739, "Berlin", "Zaunprommenade", "133", "Franz2018@Web.de", "0179-8523564", "2019-02-01 06:11:44", "99.254.13.54"),
    ( 4234, "Gerda", SHA2("13&5Ea2", 256), "Frau", NULL , "Gerda", "Klein", 80539, "München", "Schönfeldstraße", "12", "GerdaKlein@web.de", "0171-2123124", "2019-03-04 12:33:09", "199.100.32.17"),
    ( 4235, "MiraArtist", SHA2("MeineKatzeBella", 256), "Frau", NULL , "Mira", "Bellenbaum", 16816, "Neuruppin", "Dorfaue", "3", "Mira31992@freenet.de", "01764878901", "2019-03-08 17:14:56", "77.103.232.6")
;

INSERT INTO kuenstler ( Kuenstler_ID, Kname, IBAN, BIC, Vita, User_ID ) VALUES 
    ( 4612, "wÖlma", "DE23186219768630147466", "HELADEF1WEM", "Ich lebe für die Kunst! Seit 2002 male ich mit Öl alles was in meiner Fantasie so vor sich geht.", 4232 ),
    ( 4615, "MiraTusche", "DE438710460013003455817", "WELADED1OPR", NULL, 4235 )
;

INSERT INTO bild ( Bild_ID, User_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP ) VALUES 
    ( 4901, 4232, 4612, "Impasto", "Der Schrei des Blauen", 1000, 600, 140.00, "2018-12-26 23:50:13", "83.124.4.144", "2018-12-30 07:51:44", "201.177.12.3"),
    ( 4903, 4232, 4612, "Ölmalerei", "Die Küste der Stadt", 200, 1000, 250.00, "2018-12-28 12:41:16", "15.1.12.56", "2019-01-09 19:31:03", "154.200.15.1"),
    ( 4907, 4232, 4612, "Ölmalerei", "Rain Vader", 610, 1010, 999.99, "2019-01-03 20:15:01", "103.124.21.2", NULL, NULL),
    ( 4929, 4235, 4615, "Lasurtechnik", "Black Circle", 300, 300, 45.50, "2019-03-10 11:30:05", "71.12.222.6", NULL, NULL),
    ( 4944, 4235, 4615, "Tusche", "Dinosaurier Invasion", 400, 400, 99.49, "2019-03-11 12:25:39", "23.122.232.7", "2019-03-20 03:59:10", "166.13.2.9"),
    ( 4959, 4235, 4615, "Schraffur", "Der furchteinflößende Gigant", 300, 420, 12.99, "2019-03-12 07:06:24", "99.214.15.9", NULL, NULL)
;

INSERT INTO eingeordnet ( Bild_ID, Genre_ID ) VALUES 
    ( 4901, 118 ),
    ( 4903, 133 ),
    ( 4907, 118 ),
    ( 4929, 101 ),
    ( 4944, 134 ),
    ( 4959, 105 )
;