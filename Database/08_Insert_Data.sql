USE 19ss_tedk4_kws;
SET NAMES utf8;

INSERT INTO benutzer ( User_ID, Login, Passwd, Anrede, Titel, Vorname, Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon, Reg_Zeitstempel, Reg_IP ) VALUES 
	(1500,	"Seibold",		SHA2("zaq1zaq1", 256),	"Herr",	NULL,	"Christoph",  "Seibold",		73312,	"Düsseldorf",				        "Offenbergstr.",	"140",	"c.seibold@mail.xyz",			      "73317928077",	'2017-03-24 17:25:23',	"192.168.0.19"),
	(1501,	"a.lehr",		  SHA2("passw0rd", 256),	"Frau",	NULL,	"Anouk",	    "Lehr",			  54552,	"Demerath",					        "Wörthstr.",		  "21",	  "a.lehr@mail.xyz",				      "659288212210",	'2014-12-24 17:35:12',	"50.17.48.176"),
	(1502,	"dragon",		  SHA2("killer", 256),	  "Frau",	"Prof.","Alexandra","Hammond",		55276,	"Dienheim",					        "Im Haubenfeld",	"159",	"a.hammond@mail.xyz",			      "613334437461",	'2007-04-25 15:25:13',	"161.248.102.60"),
	(1503,	"B.B.",			  SHA2("starwars", 256),	"Frau",	NULL,	"Bina",		    "Babel",		  24635,	"Rickling",					        "Rosenplatz",		  "184",	"bina.babel@mail.xyz",			    "432865102467",	'2011-05-04 09:25:14',	"203.52.143.174"),
	(1504,	"Mia",			  SHA2("freedom", 256),	  "Frau",	NULL,	"Mia",		    "Padilla",		33378,	"Rheda-Wiedenbrück",        "Gropiusstr.",		"186",	"mia.padilla@mail.xyz",			    "524255499760",	'2019-03-24 15:25:15',	"120.169.21.73"),
	(1505,	"c.b.",			  SHA2("whatever", 256),	"Frau",	"Dr.","Claudia",	  "Birnenmost",	61348,	"Bad Homburg vor der Höhe",	"Äußere Kanalstr.",	"9",	"c.birnenmost@mail.xyz",		    "617252361376",	'2019-01-03 06:00:16',	"141.56.126.93"),
	(1506,	"Lewin",		  SHA2("qazwsx", 256),	  "Herr",	NULL,	"Lewin",	    "Launisch",		66500,	"Hornbach",					        "Kriegerweg",		  "34",	  "lewin.launisch@mail.xyz",		  "633893573629",	'2017-06-20 10:25:17',	"138.124.101.2"),
	(1507,	"i.stumpf",		SHA2("trustno1", 256),	"Frau",	NULL,	"Isabelle",	  "Stumpf",		  88631,	"Beuron",					          "Weseler Str.",		"177",	"i.stumpf@mail.xyz",			      "746681484669",	'2018-08-15 16:45:01',	"21.222.78.164"),
	(1508,	"Pinsel",		  SHA2("654321", 256),	  "Herr",	NULL,	"Constantin", "Bröcker",		25776,	"Sankt Annen",			        "Lammerbach",		    "4",	"constantin.broecker@mail.xyz",	"488228030553",	'2017-03-17 18:55:19',	"197.170.77.185");


INSERT INTO kuenstler ( Kuenstler_ID, Kname, IBAN, BIC, Vita, User_ID ) VALUES
	(1500, "Seibold", 		  "DE13500105171559422498", "DDEEBB09345", "Christoph Seibold, 1955 in Münster geboren, studierte bei Professor Alexandra Hammond an der Staatlichen Kunstakademie in Düsseldorf. Er hatte bereits zahlreiche Einzel- und Gruppenausstellungen in Europa, Asien und Afrika. Seibold ist zudem als Kurator und Dozent tätig; 2008 erhielt er für seine Arbeit den Rheinischen Kunstpreis. Er lebt und arbeitet in Düsseldorf.", 1500),
	(1503, "B.B.", 			    "DE50500105171816386763", "DFEEBB09345", "Bina Babel, geb. 1940 in Dessau, studierte an der Kunstakademie Düsseldorf - in der Klasse von Constantin Bröcker. Ihre Werke faszinieren Kunstfreunde in der ganzen Welt. BBs Bilder sind konsequent gegenstandslos und klar konturiert, voller Entschiedenheit und Prägnanz. Dabei bleibt das Gedankliche unsichtbar. Es ist das \"Nichtgemalte\", das beim Betrachter Empfindungen erzeugt und der Fantasie keine Grenzen setzt.", 1503),
	(1505, "Mrs. Brainwash","DE45500105172673145852", "DDEEBB09345", "Ihr Weg zur erfolgreichsten Künstlerin der letzten Jahre ist eng verbunden mit dem Namen Banksy und dessen Oscar prämierten Film \"Exit Through the Gift Shop\".", 1505),
	(1508, "Pinselmaier", 	"DE71500105173565424716", "BAEEBB09", 	 "Pinselmaier wurde 1968 in der deutschen Kunstmetropole Sankt Annen geboren. Bereits als Kind erhält er Zeichenunterricht, obwohl sein Vater, ein Goldschmied und Uhrmacher, sich anfänglich sträubt. Er besucht die Handelsschule sowie die Kunstakademie Sankt Annen, an der knapp zehn Jahre vor ihm schon Christoph Seibold Kunstunterricht erhalten hatte. ", 1508);
	
	
INSERT INTO bild ( Bild_ID, User_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP ) VALUES
	(1500, NULL, 1500, "Öl auf Leinwand", 	 "Praxiteles in seiner Werkstatt",		 875, 1260, 2400, '2018-03-24 17:25:41', "192.168.0.19",   NULL, NULL), -- 112
	(1501, NULL, 1500, "Leimfarbe auf Holz", "Christus am Ölberg, Nachbildung",		 630,  800, 3200, '2017-06-14 19:25:11', "192.168.0.19",   NULL, NULL), -- 119
	(1502, NULL, 1500, "Öl auf Holz", 		   "Darbringung im Tempel, Nachbildung",	 800,  105, 4200, '2017-06-14 19:30:14', "192.168.0.19",   NULL, NULL), -- 119
	(1505, NULL, 1505, "C-Print auf Aludibond", 	 		    "Guard 1",			 	1300,  950, 1800, '2018-05-19 15:25:11', "141.56.126.93",  NULL, NULL), -- 115
	(1506, 1507, 1505, "Mischtechnik auf Papier", 	 		  "Captain America",	 	 830,  640, 1200, '2019-01-19 12:15:11', "141.56.126.93",  '2019-02-20 12:15:11', "21.222.78.164"), -- 118
	(1507, NULL, 1505, "Farbsiebdruck auf Pur Coton",		  "Rainbow Soup",	 	 800,  600, 2800, '2019-02-09 15:25:11', "141.56.126.93",  NULL, NULL), -- 118
	(1508, NULL, 1505, "Mischtechnik auf Papier",	 		    "Keep Creating",	 	 970,  970, 2700, '2019-02-09 15:30:11', "141.56.126.93",  NULL, NULL), -- 118
	(1509, NULL, 1508, "Aquatintaradierung auf Bütten",		"Els Gossos IX",	 	1565, 1135,28000, '2000-02-09 12:31:11', "197.170.77.185", NULL, NULL), -- 101
	(1510, 1506, 1508, "Farblithografie",			  		 "Der Singende",	 	 320,  245,  550, '2000-03-09 12:31:41', "197.170.77.185", '2014-03-09 12:31:14', "138.124.101.2"), -- 101
	(1511, NULL, 1508, "Farbradierung", 	 "Der anbrechende Morgen im Mondlicht",	 700,  800, 9500, '2000-04-09 12:31:14', "197.170.77.185", NULL, NULL), -- 101
	(1512, NULL, 1508, "Bleistift und Farbstift auf Papier", "Frau vor der Sonne",	 700,  800, 2500, '2000-05-09 12:31:11', "197.170.77.185", NULL, NULL), -- 101
	(1513, 1508, 1503, "Acryl auf Kunststoff-Folie", 		 "19 Farben 19 Stäbe",	 500,  500,  750, '1995-10-09 15:01:41', "203.52.143.174", '2001-12-09 12:01:11', "197.170.77.185"), -- 101
	(1514, NULL, 1503, "Farbsiebdruck auf Bütten", 		 	 "ohne Titel",	  		1070,  770, 2400, '1995-10-09 15:02:11', "203.52.143.174", NULL, NULL), -- 101
	(1515, NULL, 1503, "Acryl auf Kunststoff-Folie", 		 "Position I",	  		 525,  675,11500, '1995-10-09 15:03:11', "203.52.143.174", NULL, NULL); -- 101
	
	
INSERT INTO eingeordnet ( Bild_ID, Genre_ID ) VALUES
	(1500, 112),
	(1501, 119),
	(1502, 119),
	(1505, 115),
	(1506, 118),
	(1507, 118),
	(1508, 118),
	(1509, 101),
	(1510, 101),
	(1511, 101),
	(1512, 101),
	(1513, 101),
	(1514, 101),
	(1515, 101);
