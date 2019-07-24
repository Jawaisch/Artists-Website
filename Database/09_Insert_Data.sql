USE 19ss_tedk4_kws;
SET NAMES utf8;

/* Erst einmal aufräumen:
   Dubletten vermeiden !    */
DELETE FROM eingeordnet WHERE Bild_ID      BETWEEN 1701 AND 1709;
DELETE FROM genre       WHERE Genre_ID     =135;
DELETE FROM bild        WHERE Bild_ID      BETWEEN 1701 AND 1709;
DELETE FROM kuenstler   WHERE Kuenstler_ID BETWEEN 1701 AND 1704;
DELETE FROM benutzer    WHERE User_ID      BETWEEN 1701 AND 1704;

INSERT INTO benutzer (`User_ID`, `Anrede`, `Vorname`, `Nachname`, `Email`,
                      `Telefon`, `Strasse`, `HausNr`, `Ort`, `PLZ`, 
                      `Login`, `Passwd`, `Reg_IP`, `Reg_Zeitstempel`
 --                     `Geburtsdatum`, `Status`
                     ) VALUES
(1701, 'Herr', 'Fred', 'Pinsel', 'maler1@meister.de', 
       '0151 151 262 373', 'Infoweg', '9', 'Datenhausen', 9999,
       'PiFre', SHA2('PiFre70', 256), '99.102.37.55', '2013-11-06 10:05:30'),
--       '1970-01-01', 'gesperrt'),
(1702, 'Frau', 'Natascha', 'Schulze', 'nasch@gmx.de', 
       '0172 2 88 35 35', 'Gerade Str.', '14', 'Rehburg-Loccum', 31547,
       'NataschaKatze', SHA2('Nasch!', 256), '121.66.103.124', '2013-12-18 06:06:05'),
--       '1985-10-14', 'aktiv'),
(1703, 'Herr', 'Gunnar', 'Schmidt', 'guschmidt@web.de', 
       '030 9 02 99 92', 'Hoepnerstr.', '4b', 'Berlin', 10123, 
       'Aquarellmaler', SHA2('_ganz_geheim_', 256), '217.81.113.1', '2014-01-02 20:22:23'),
--       '1939-01-13', 'aktiv'),
(1704, 'Divers', 'Charles', 'Boyz', 'badboynele@web.de', 
       '030 80 20 28 59', 'Alt-Lankwitz', '98-100', 'Berlin', 12247, 
       'badboynele', SHA2('__6eb80e1590d930cd', 256), '201.88.107.123', '2013-12-29 11:33:54');
--       '1961-05-12', 'aktiv');

INSERT INTO `kuenstler` (`Kuenstler_ID`, `Vita`, 
                         `Kname`, `IBAN`, `BIC`, `User_ID`
                        ) VALUES
(1701, 'Ich bin der Pinselfred und seit 8 Jahren der ungeschlagene King auf allen Berliner Flomärckten. Jetz könnt ihr zum ersten mal meine begerten Bilder auch online kaufen. Aber achtung: was hier nich in 2 wochen weg geht ist dann garantiert auf einem Flohmarkt verkauft. Also zugreifen!', 
       'PinselFred', 'DE25 3601 0043 0988 7766 55', 'PBNKDEFF360', 1701 ),
(1702, 'Ich bin neu hier und weiß nicht so recht, was ich hier schreiben soll, außer meiner Begeisterung fürs Malen. Vielleicht kommt hier später mal mehr.', 
       'Nasch',      'DE58 1001 0010 0022 7864 57', 'PBNKDEFFXXX', 1702 ),
(1703, 'Ich male seit 30 Jahren Aquarelle und bin jetzt neu hier. Ich weiß nicht so recht, was ich schreiben soll. Aber wenn Ihr mehr über mich wissen wollt, besucht doch meine Webseite: "http://www.guensch_aquarelle.berlin"', 
       'Günsch',     'DE18 1209 6597 0101 0101 01', 'GENODEF1S10', 1703 ),
(1704, 'Abschluss an der UdK VIII 2011 - Preise in Holland und Old Britain für innovative Kunst - 12 Ausstellungen in 3 Jahren - Ausgezeichnet in Finnland als "Innovative Artist 2012". Alles weitere und Weiteres unter www.badboynele.art', 
       'badboynele', 'DE21 1209 6597 1234 4170 12', 'GENODEF1S10', 1704 );


INSERT INTO genre VALUES 
(135, "Kindermimikry", 
      "2010 maßgeblich vom innovativen Künstler badboynele geprägte Stilrichtung der Malerei. Durch Übertreibung des Aspektes der kindlichen Malerei wird der handwerkliche Anspruch von Kunst als Voraussetzung für künstlerische Arbeiten, wie es vor allme bis ins Ende des 20. Jahrhunderts von ewig Gestrigen gefordert wird, ad absurdum geführt. Nicht zu verwechseln mit naiver Malerei, ist ein Anspruch an den Kindermimikry, dass Kunstwerke dieser Richtung nicht von Bildern solcher Kinder zu unterscheiden sind, die noch nicht vom verheerenden Einfluss des Kunstunterrichts herkömmlicher sogenannter Kunstlehrer verdorben wurden. In Holland wurde diese Kunstrichtung 2012 mit dem hochdotiertem Kunstpreis 'vernieuwende kunststromingen 2012' ausgezeichnet. Mehr zu diesem Malstil unter: www.badboynele.art/kindermimikry");


INSERT INTO `bild` 
(`Bild_ID`, `Titel`, `VK_Preis`, `Hoehe`, `Breite`,
       `Mal_Technik`,
--       `Beschreibung`, `Jahr`, `Bilddatei`,
       `Einstell_IP`, `Einstell_Zeitstempel`,
       `Kauf_IP`, `Kauf_Zeitstempel`, `User_ID`, `Kuenstler_ID`) VALUES
(1701, 'Walfamilie', '250.00', 1200, 1593, 
       'Gemälde - Ölpastellfarben auf Karton', 
--       'Eine Walfamilie in Ölpastellfarben auf Karton gemalt und auf einen Aquarellhintergrund gesetzt.',        2014, "1701.jpg", 
       '217.84.133.127', '2014-02-28 17:26:15', 
       NULL, NULL, NULL, 1702),
(1702, 'Blumen', '150.00', 420, 594,  
       'Gemälde - Aquarell', 
--       'Blumen - Aquarell',  2014, "1702.jpg", 
       '217.81.33.12', '2014-02-12 11:12:43',
       NULL, NULL, NULL, 1703),
(1703, 'Blumen', '150.00', 594, 420,  
       'Gemälde - Aquarell', 
--       'Blumen am Seeufer - Aquarell', 2014, "1703.jpg", 
       '217.81.43.12', '2014-03-03 11:42:41',
       NULL, NULL, NULL, 1703),
(1704, 'Lietzensee', '150.00', 420, 594,  
       'Gemälde - Aquarell',
--       'Café am Lietzensee, Hinteransicht - Aquarell', 2014, "1704.jpg", 
       '217.81.55.61', '2014-03-28 14:40:05',
       NULL, NULL, NULL, 1703),
(1705, 'Lietzensee', '150.00', 594, 420,  
       'Gemälde - Aquarell', 
--       'Café am Lietzensee - Aquarell', 2014, "1705.jpg", 
       '217.81.12.21', '2014-05-11 13:21:16',
       NULL, NULL, NULL, 1703),
(1706, 'Selbstportrait', '120.00', 210, 297,  
       'Zeichnung - Filzstift/Marker', 
--       'Kindermimikry - Selbstportrait', 2014, "1706.jpg", 
       '201.88.107.123', '2014-01-03 04:21:16',
       NULL, NULL, NULL, 1704),
(1707, 'Spiegelapfel', '120.00', 210, 297,  
       'Zeichnung - Filzstift/Marker', 
--       'Kindermimikry - Baum, Apfel, erste Schreibversuche - nicht alle gelungen', 2014, "1707.jpg", 
       '201.88.107.123', '2014-01-15 03:11:21',
       NULL, NULL, NULL, 1704),
(1708, 'Gummibären', '175.00', 148, 210,  
       'Zeichnung - Filzstift/Marker', 
--       'Kindermimikry - Drei Tüten Gummibären auf einer Unterlage angeordnet', 2014, "1708.jpg", 
       '201.88.107.123', '2014-01-15 03:15:17',
       NULL, NULL, NULL, 1704),
(1709, 'Tieraltar', '175.00', 148, 210,  
       'Zeichnung - Filzstift/Marker', 
--       'Kindermimikry - Tiere als Pentychon - 4 kleine Zeichnungen um eine große angeordnet', 2014, "1709.jpg", 
       '201.88.107.123', '2014-01-15 03:19:08',
       NULL, NULL, NULL, 1704);

INSERT INTO `eingeordnet` VALUES
(1701, 109),
(1702, 109),
(1703, 109),
(1704, 109),
(1705, 109),
(1706, 135),
(1707, 135),
(1708, 135),
(1709, 135);