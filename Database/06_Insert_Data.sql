USE 19ss_tedk4_kws;

DELETE FROM eingeordnet WHERE Bild_ID      BETWEEN 1100 AND 1199;
DELETE FROM bild        WHERE Bild_ID      BETWEEN 1100 AND 1199;
DELETE FROM kuenstler   WHERE Kuenstler_ID BETWEEN 1100 AND 1199;
DELETE FROM benutzer    WHERE User_ID      BETWEEN 1100 AND 1199;


INSERT INTO benutzer (User_ID, login, passwd, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon, Reg_Zeitstempel, Reg_Ip) 
       VALUES (1101 ,'Maler' ,SHA2('maler', 256), 'Herr', 'Dr.', 'Franz', 'Maler', '14621', 'Schönwalde-Glien', 'Klecksweg', '42', 'Maler_Klecks@blau.de', '03515 654654', '2019-03-23 20:40:12', '123.154.5.56');

INSERT INTO benutzer 
       VALUES (1102 ,'Pinsel02' ,SHA2('pinsel', 256), 'Herr', NULL, 'Ralf', 'Zuselr', '14612', 'Falkensee', 'Mauerstrasse', '111', 'der_Kringel@bew.de', '03598 8865484', '2019-03-24 13:38:22', '119.205.54.1');

INSERT INTO benutzer 
       VALUES (1103 ,'Master_Painter' ,SHA2('master', 256), 'Herr', 'Prof.', 'Johann', 'Schuessel', '06895', 'Elster', 'Elbstraße', '14', 'Elbe14@mailg.com', '78788 654654', '2019-04-15 05:58:51', '83.144.89.204');

INSERT INTO benutzer 
       VALUES (1104 ,'Faker123' ,SHA2('fake', 256), 'Herr', NULL, 'Frank', 'Acker', '89874', 'Ostmuenchen', 'Busgasse', '14', 'Smurfer666@dmax.de', '03455 445111', '2019-04-30 10:01:22', '101.1.1.99');

INSERT INTO benutzer 
       VALUES (1105 ,'Luisa_Herbst' ,SHA2('luisa', 256), 'Frau', NULL, 'Luisa', 'Herbst', '14612', 'Falkensee', 'Rathausstrasse', '89', 'Luisa_Herbst@web.de', '03321 1244512', '2019-05-01 15:21:55', '3.89.108.166');

INSERT INTO kuenstler (Kuenstler_ID, Kname, IBAN, BIC, Vita, User_ID)
       VALUES (1111 ,'Cipasso', 'DE67805501019124760185', 'HELADE67', 'Ich bin der Cipasso, zeichne seit nunmehr als 25 Jahren Stilleben und erfreue mich immer an neuen Ideen für neue Motive.', 1101);

INSERT INTO kuenstler
       VALUES (1112 ,'Gan Vough', 'DE25467294986157184941', 'KLAUSI99', NULL, 1102);
  
INSERT INTO bild (Bild_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP)
       VALUES (1101 , 1111, 'Ölmalerei', 'Arbeitszimmer', '2300', '2000', '250', '2019-04-01 15:20:42', '23.14.125.77', NULL, NULL);

INSERT INTO bild (Bild_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP)
       VALUES (1104 , 1112, 'Pointilismus', 'Fischer am Morgen', '1200', '800', '75', '2019-04-02 09:45:24', '87.154.15.189', NULL, NULL);

INSERT INTO bild (Bild_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP)
       VALUES (1106 , 1112, 'Pointilismus', 'Unser Marlie', '800', '3000', '870', '2019-04-02 11:01:52', '23.154.15.189', NULL, NULL);

INSERT INTO bild (Bild_ID, User_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP) 
       VALUES (1102 , 1101, 1111, 'Ölmalerei', 'Sack Nüsse', '1600', '1200', '100', '2019-04-01 15:34:02', '23.14.125.77', '2019-06-23 15:01:33', '138.57.156.13');

INSERT INTO bild (Bild_ID, User_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP) 
       VALUES (1103 , 1102, 1111, 'Ölmalerei', 'Heiligen Drei', '4500', '3500', '1500', '2019-04-01 15:55:12', '23.14.125.77', '2019-06-16 23:42:44', '165.125.67.245');

INSERT INTO bild (Bild_ID, User_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP) 
       VALUES (1105 , 1105, 1112, 'Pointilismus', 'Mordor', '1400', '1200', '120', '2019-04-02 10:35:55', '23.154.15.189', '2019-05-22 12:13:14', '45.250.99.02');

INSERT INTO eingeordnet (Bild_ID, Genre_ID)
       VALUES (1101, 103);

INSERT INTO eingeordnet
       VALUES (1102, 103);

INSERT INTO eingeordnet
       VALUES (1103, 103);

INSERT INTO eingeordnet
       VALUES (1104, 109);

INSERT INTO eingeordnet
       VALUES (1105, 109);

INSERT INTO eingeordnet
       VALUES (1106, 109);
