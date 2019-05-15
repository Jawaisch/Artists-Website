<?php

function KWS_DB_Connect( $user )
{
		if(!defined("DBServer")) define("DBServer","localhost");
		if(!defined("DBName"))define("DBName","19ss_tedk4_kws");

		switch($user)
		{

			// User-Parameter
			case		"admin":
							$DBUser	=			 "kws_admin";
							$DBPassword	=	 "kws_admin";
							break;

			case		"bearbeiter":
							$DBUser	=			 "kws_bearbeiter";
							$DBPassword	=	 "kws_bearbeiter";
							break;

			case		"kuenstler":
							$DBUser	=			 "kws_kuenstler";
							$DBPassword	=	 "kws_kuenstler";
							break;

			case		"kunde":
							$DBUser	=			 "kws_kunde";
							$DBPassword	=	 "kws_kunde";
							break;

			case		"login":
							$DBUser	=			 "kws_login";
							$DBPassword	=	 "kws_login";
							break;

			case		"reg":
							$DBUser	=			 "kws_reg";
							$DBPassword	=	 "kws_reg";
							break;

			default:
							$DBUser	=			 "kws_gast";
							$DBPassword	=	 "kws_gast";


		}

		// Neues Objekt	der	Klasse mysqli	um Datenbankverbindung aufzubauen
		$dbconn	=	new	mysqli(DBServer, $DBUser,	$DBPassword, DBName);

		//Ueberpruefen ob	Verbindung erfolgreich

		if($dbconn->connect_errno)
		{
			if(	MYDEBUG	)
			{
			echo "\n <div	class=\"error\">".
				"PHP sagt:(".__FILE__.") Zeile : ".__FILE__.
				 "\n <b>Verbindung fehlgeschlagen!</b>".
				 "\n <div>". $dbconn->connect_errno."	:	".$dbconn->connect_error."<\div>".
				 "</div>";

			die("Netzwerkproblem - Abbruch");
			$_SESSION['login']['user'] = 'gast';
			}
			else
			{

				if(	MYDEBUG	)
				{
				echo "\n <div	class=\"info\">".
					 "\n <b>Verbindung zu	".$dbconn->host_info." aufgebaut</b>".
					 "</div>";
				}
			}
				
		 }
	$dbconn->query("SET	NAMES	utf8");
		return $dbconn;
}

/* ************************************************************************************
	@function	CheckLoginFormData()

		@brief:	Überprüft, ob	alle Formularfelder	der	Anmeldung	ausgefüllt sind

		Diese	Funktion erwartet, dass	die	Formulardaten	per	POST übermittel	wurden.
		Folgende Eingabedaten	werden überprüft:
		-	$_POST['login']
		-	$_POST['passwd']

		@para	-	Keine

		@return	-	 bool	
************************************************************************************ */
function CheckLoginFormData( )
{
	return ( !empty($_POST['login']) &&	!empty($_POST['passwd']) );	
}


/* ************************************************************************************
			@function	GetUidByLogin( $dbconn,	$login , $pwd	)

			@brief:	Holt die User_ID über	die	Anmeldedaten

			@para	-	$dbconn			 Eine	Datenbankverbindung	der	Klasse mysqli
					-	$login(string) Der Login des Users
					-	&pwd(string)	 Das Passwort	des	Users

			@return	-	 (int)uid	im Erfolgsfall
						 sonst false
************************************************************************************ */
function GetUidByLogin(	$dbconn	,	$login , $pwd	)
{
	//1. ein Objekt	der	Klasse mysqli_stmt anlegen
	$prepstmt	=	$dbconn->stmt_init();
	//2.Abfrage	mit	Platzhalter	für	Daten	zusammenbasteln
	
	$SQLstring =
		"	SELECT User_ID AS	uid".
		"	FROM benutzer".
		"	WHERE	Login	=	?".
		"	AND	Passwd = SHA2( ? ,256)";
	// Abfrage an	den	DB-Server	abschicken

	// 3.	Prepared Statement auf dem DB-Server vorbereiten
	$OK	=	$prepstmt->prepare(	$SQLstring );
	
	// Abfrage erfolgreich?
	
	if($OK === false)
	{
		echo "\n <div	class=\"error\">".
			 "\n <b>Abfrage	fehlgeschlagen!</b>".
			 "\n <div>".$SQLstring."</div>".
			 "\n <div>". $prepstmt->errno."	:	".$prepstmt->error."<\div>".
			 "</div>";

		die("DB-Problem	-	Abbruch");
	}

	//4. Daten an	die	Parameter	binden

	$prepstmt->bind_param( "ss"	,$login	,	$pwd );

	//5. Diese Parameter anwenden

	$prepstmt->execute();

	//6. Ergebnis	holen/Rückgabewerte	binden
	//a: Rückgabewert	binden
	$prepstmt->bind_result(	$uid );

	//b: mit dem üblichen	mysqli_result
	//$err_handle	=	$prepstmt->get_result();

	// fetch-en	Spezialfall: ein oder	kein Datensatz

	$prepstmt->fetch();	// rückgabewert	ist	schon	in $uid	sh.	bind_result( $uid	)

	if($uid	== NULL)
	{
		$uid = false;
	}
	
	$prepstmt->close();	//abräumen nach	getaner	Arbeit
	return $uid;
}	// end of		function GetUidByLogin(	$dbconn	,	$login , $pwd	)


/* ************************************************************************************
			@function	GetKindOfUser( $dbconn , $uid)

			@brief:	Überprüft	ober der anmeldende	Benutzer ein Künstler	ist

			@para	-	$dbconn			 Eine	Datenbankverbindung	der	Klasse mysqli
					-	$uid			 Die User_ID des angemeldenden Benutzers


			@return	-	 "kuenstler" im	Erfolgsfall
						 sonst "kunde" 
************************************************************************************ */
function GetKindOfUser(	$dbconn	,	$uid)
{
	$SQL_String	=	"SELECT	kuenstler.User_ID,
						kuenstler.Kuenstler_ID AS	KID
					 FROM	kuenstler
					 WHERE kuenstler.User_ID = ".$uid;
	
	$result_handle = $dbconn->query($SQL_String);

	// Abfrage erfolgreich?
		
	if($result_handle	===	false)
	{
		echo "\n <div	class=\"error\">".
			 "\n <b>Abfrage	fehlgeschlagen!</b>".
			 "\n <div>".$SQLstring."</div>".
			 "\n <div>". $dbconn->errno."	:	".$dbconn->error."<\div>".
			 "</div>";

		die("DB-Problem	-	Abbruch");
	}
	// Abfrage über	UID	-> 1 oder	keinen Datensatz
	$UserArr = $result_handle->fetch_assoc();

	if(	$UserArr ==	NULL)
	{
		$ResultArr[0]	=	"kunde";
	}
	else
	{
		$ResultArr[0]	=	"kuenstler";
	$ResultArr[1]	=	$UserArr['KID'];
	}
	return $ResultArr; 
}


/*************************************************************************************
					@function: GetAllArtists(	$dbconn	)

					@brief:	Holt alle	User die als Künstler	registriert	sind aus der DB
									Sortiert nach	Alphabet

					@para: $dbconn - Eine	Datenbankverbinung der Klasse	myslqi

					@return: Im	Erfolg - ein 2-dimensionales Array aller Kuenstler mit KName
									 Im	Misserfolg - false Errorcode
*************************************************************************************/
function GetAllArtists(	$dbconn	)
{
	// Abfrage ohne	Perpared_Statements
	$SQL_String	=	"SELECT	KName
								 FROM	Kuenstler
								 ORDER BY	KName";

	// Abfrage an	DB-Server	senden
	$result_handle = $dbconn->query($SQL_String);

	// Abfrage auf Erfolg	Ueberpruefen
	if($result_handle	===	false)
	{
		echo "\n <div	class=\"error\">".
				 "\n <b>Abfrage	fehlgeschlagen!</b>".
				 "\n <div>".$SQLstring."</div>".
				 "\n <div>". $dbconn->errno."	:	".$dbconn->error."<\div>".
				 "</div>";

				 die("DB-Problem - Abbruch");
	}
	else
	{
		$artist_arr	=	array();	// ein leeres	Array	initialisieren!

		while( $ds = $result_handle->fetch_assoc() )
		{
			$artist_arr[]	=	$ds;
		}
	}

	return $artist_arr;
}


/*************************************************************************************
					@function: GetLast3Pics( $dbconn )
					@brief:	 Holt	die	letzten	drei hochgeladenen kleinen Bilder	aus	dem
									 Ordner	small	zur	Darstellung	in der Index
					@para: $dbconn - Eine	Datenbankverbinung der Klasse	myslqi
					@return: Im	Erfolg - Ein 2-dimensionales Array
									 Im	Misserfolg - false
*************************************************************************************/
function GetLast3Pics( $dbconn )
{
	$SQL_String	=	"SELECT	bild.Bild_ID,
												bild.Titel,
												bild.Hoehe,
												bild.Breite,
						bild.Einstell_Zeitstempel,
												Kuenstler.KName
								 FROM	bild INNER JOIN	Kuenstler	USING	(Kuenstler_ID)
								 ORDER BY	bild.Einstell_Zeitstempel	DESC
								 LIMIT 3";

	// Abfrage an	DB-Server	senden
	$result_handle = $dbconn->query($SQL_String);

	// Abfrage auf Erfolg	Ueberpruefen
	if($result_handle	===	false)
	{
		echo "\n <div	class=\"error\">".
				 "\n <b>Abfrage	fehlgeschlagen!</b>".
				 "\n <div>".$SQLstring."</div>".
				 "\n <div>". $dbconn->errno."	:	".$dbconn->error."<\div>".
				 "</div>";

				 die("DB-Problem - Abbruch");
	}
	else
	{
		$Three_Pics_arr	=	array();	// ein leeres	Array	initialisieren!

		while( $ds = $result_handle->fetch_assoc() )
		{
			$Three_Pics_arr[]	=	$ds;
		}
	}

	return $Three_Pics_arr;

}


/*
************************************************************************************
					@function: GetAllPics( $dbconn )
					@brief:	Hole alle	Bilder aus dem Ordner	Small	zur	Darstellung	in
									der	Galerie
					@para:
					@return:
************************************************************************************
*/
function GetAllPics( $dbconn )
{
	$SQL_String	=	"	SELECT bild.Bild_ID,".
								"				 bild.Titel,".
								"				 bild.Hoehe,".
								"				 bild.Breite,".
								"				 bild.VK_Preis,".
								"				 Kuenstler.KName,".
				"		 Kuenstler.Kuenstler_ID".
								"	FROM bild	INNER	JOIN Kuenstler USING (Kuenstler_ID)".
								"	ORDER	BY bild.Einstell_Zeitstempel DESC";

	// Abfrage an	DB-Server	senden
	$result_handle = $dbconn->query($SQL_String);

	// Abfrage auf Erfolg	Ueberpruefen
	if($result_handle	===	false)
	{
		echo "\n <div	class=\"error\">".
				 "\n <b>Abfrage	fehlgeschlagen!</b>".
				 "\n <div>".$SQLstring."</div>".
				 "\n <div>". $dbconn->errno."	:	".$dbconn->error."<\div>".
						"</div>";

		die("DB-Problem	-	Abbruch");
	 }
	 else
	 {
		 $Pics_arr = array();	// ein leeres	Array	initialisieren!

		 while(	$ds	=	$result_handle->fetch_assoc()	)
		 {
			 $Pics_arr[] = $ds;
		 }
		}

		return $Pics_arr;
}

/*************************************************************************************
					@function: GetUserData(	$dbconn	)
					@brief:	Hole alle	Bilder aus dem Ordner	Small	zur	Darstellung	in
									der	Galerie
					@para:	$dbconn	-	Eine Datenbankverbinung	der	Klasse myslqi
					@return:
*************************************************************************************/
function GetUserData(	$dbconn	)
{
	// Abfrage ohne	Perpared_Statements
	$SQL_String	=	"SELECT	Anrede,
												Titel,
												Vorname,
												Nachname,
												PLZ,
												Ort,
												Strasse,
												HausNr,
												Email,
												Telefon,
												Reg_Zeitstempel	AS registriert_am_um
							 FROM			benutzer
							 WHERE		User_ID	=	".$_SESSION['login']['UID'];

	// Abfrage an	DB-Server	senden
	$result_handle = $dbconn->query($SQL_String);

	// Abfrage auf Erfolg	Ueberpruefen
	if($result_handle	===	false)
	{
		echo "\n <div	class=\"error\">".
				 "\n	<b>Abfrage fehlgeschlagen!</b>".
				 "\n	<div>".$SQL_String."</div>".
				 "\n	<div>".	$dbconn->errno." : ".$dbconn->error."<\div>".
						"</div>";

		die("DB-Problem	-	Abbruch");
	}
	else
	{
		$user_data_arr = array();	// ein leeres	Array	initialisieren!

		while( $ds = $result_handle->fetch_assoc() )
		{
			$user_data_arr = $ds;
		}
	}
	return $user_data_arr;
}


/*
************************************************************************************
					@function: GetMorePicInfo( $dbconn , $BID	)
					@brief:
					@para:
					@return:
************************************************************************************
*/

function GetMorePicInfo( $dbconn , $BID	)
{
	$SQL_String	=	"SELECT	Kuenstler.KName,
												bild.Titel,
												bild.Hoehe,
												bild.Breite,
												bild.VK_Preis,
												bild.Mal_Technik,
												bild.Kauf_Zeitstempel,
												genre.Name
									 FROM	kuenstler	INNER	JOIN bild	USING	(Kuenstler_ID)
									INNER	JOIN eingeordnet USING (Bild_ID)
									INNER	JOIN genre USING (Genre_ID)
									 WHERE bild.Bild_ID	=".	$BID;

	// Abfrage an	DB-Server	senden
	$result_handle = $dbconn->query($SQL_String);

	// Abfrage auf Erfolg	Ueberpruefen
	if($result_handle	===	false)
	{
		echo "\n <div	class=\"error\">".
				 "\n <b>Abfrage	fehlgeschlagen!</b>".
				 "\n <div>".$SQLstring."</div>".
				 "\n <div>". $dbconn->errno."	:	".$dbconn->error."<\div>".
						"</div>";

		die("DB-Problem	-	Abbruch");
	 }
	 else
	 {
		 $Three_Pics_arr = array();	// ein leeres	Array	initialisieren!

		 while(	$ds	=	$result_handle->fetch_assoc()	)
		 {
			 $Three_Pics_arr = $ds;
		 }
		}

		return $Three_Pics_arr;
}


/* ************************************************************************************
			@function	InsertNewUser( $dbconn )

			@brief:	Fügt einen neuen Benutzer	in die DB	ein	(Neue	Anmeldung)

			@para	-	$dbconn			 Eine	Datenbankverbindung	der	Klasse mysqli

			@return	-	true im	Erfolgsfall
								sonst	false
************************************************************************************ */
function InsertNewUser(	$dbconn	)
{
	//1. ein Objekt	der	Klasse mysqli_stmt anlegen
	$prepstmt	=	$dbconn->stmt_init();
	//2.Abfrage	mit	Platzhalter	für	Daten	zusammenbasteln
	$SQLstring =
		"	INSERT INTO	benutzer (	Login, Passwd, Anrede, Titel,	Vorname,
															Nachname,	PLZ, Ort,	Strasse, HausNr, Email,	Telefon,
															Reg_Zeitstempel, Reg_IP	)	
							VALUES	(	?, SHA2( ?,	256),	?, ?,	?, ?,	?, ?,	?, ?,	?, ?,	CURRENT_TIMESTAMP, ?)";
	
	// Abfrage an	den	DB-Server	abschicken

	// 3.	Prepared Statement auf dem DB-Server vorbereiten
	$OK	=	$prepstmt->prepare(	$SQLstring );
	
	// Abfrage erfolgreich?
	
	if($OK === false)
	{
		echo "\n <div	class=\"error\">".
			 "\n <b>Abfrage	fehlgeschlagen!</b>".
			 "\n <div>".$SQLstring."</div>".
			 "\n <div>". $prepstmt->errno."	:	".$prepstmt->error."<\div>".
			 "</div>";

		die("DB-Problem	-	Abbruch");
	}

	//4. Daten an	die	Parameter	binden
	$type	=	"ssssssissssss";
	$params	=	array(&$login, &$pwd, &$anrede, &$titel,	
									&$vname, &$nname, &$plz,	&$ort, &$str,	
									&$hnr,	&$email, &$tele,	&$reg_ip );

	call_user_func_array(array($prepstmt,	"bind_param"), array_merge(array($type), $params));

	//5. Parameter setzen
	foreach($_SESSION['input_data']	as $item =>	$value)
	{
		${$item} = $value[val];
	}
	
	// IP-Adresse	ermitteln
	// Verwendet der Benutzer	einen	Proxy-Server
	if ( !isset($_SERVER['HTTP_X_FORWARDED_FOR'])	)	
	{
		$reg_ip	=	$_SERVER['REMOTE_ADDR'];
	}
	else 
	{
		$reg_ip	=	$_SERVER['HTTP_X_FORWARDED_FOR'];
	}

	//6. Diese Parameter anwenden
	$OK2 = $prepstmt->execute();
	if($OK2	===	false)
	{
		echo "\n <div	class=\"error\">".
			 "\n <b>Abfrage	fehlgeschlagen!</b>".
			 "\n <div>".$SQLstring."</div>".
			 "\n <div>". $prepstmt->errno."	:	".$prepstmt->error."<\div>".
			 "</div>";

		die("DB-Problem	-	Abbruch");
	}

	$prepstmt->close();	//abräumen nach	getaner	Arbeit
	return $OK2;
}	


/* ************************************************************************************
			@function	UpdateUserData(	$dbconn	)

			@brief:	Ändert die Benutzer	Daten	in der DB

			@para	-	$dbconn			 Eine	Datenbankverbindung	der	Klasse mysqli

			@return	-	true im	Erfolgsfall
								sonst	false
************************************************************************************ */
function UpdateUserData( $dbconn )
{
	//1. ein Objekt	der	Klasse mysqli_stmt anlegen
	$prepstmt	=	$dbconn->stmt_init();
	//2.Abfrage	mit	Platzhalter	für	Daten	zusammenbasteln
	$SQLstring =
		"	UPDATE benutzer	SET	Anrede = ?,	Titel	=	?, Vorname = ?,
													Nachname = ?,	PLZ	=	?, Ort = ?,	Strasse	=	?, 
													HausNr = ?,	Email	=	?, Telefon = ?
									 WHERE User_ID = ?";

	// Abfrage an	den	DB-Server	abschicken

	// 3.	Prepared Statement auf dem DB-Server vorbereiten
	$OK	=	$prepstmt->prepare(	$SQLstring );
	
	// Abfrage erfolgreich?
	if($OK === false)
	{
		echo "\n <div	class=\"error\">".
			 "\n <b>Abfrage	fehlgeschlagen!</b>".
			 "\n <div>".$SQLstring."</div>".
			 "\n <div>". $prepstmt->errno."	:	".$prepstmt->error."<\div>".
			 "</div>";

		die("DB-Problem	-	Abbruch");
	}

	//4. Daten an	die	Parameter	binden
	$type	=	"ssssisssssi";
	$params	=	array(&$anrede, &$titel, &$vname, &$nname, &$plz,	&$ort, &$str,	
									&$hnr,	&$email, &$tele,	&$uid );
  

	call_user_func_array(array($prepstmt,	"bind_param"), array_merge(array($type), $params));
	
	//5. Parameter setzen
	foreach($_SESSION['input_data']	as $item =>	$value)
	{
		${$item} = $value[val];
	}
	$uid = $_SESSION['login']['UID'];

	//6. Diese Parameter anwenden
	$OK2 = $prepstmt->execute();
	if($OK2	===	false)
	{
		echo "\n <div	class=\"error\">".
			 "\n <b>Abfrage	fehlgeschlagen!</b>".
			 "\n <div>".$SQLstring."</div>".
			 "\n <div>". $prepstmt->errno."	:	".$prepstmt->error."<\div>".
			 "</div>";

		die("DB-Problem	-	Abbruch");
	}

	$prepstmt->close();	//abräumen nach	getaner	Arbeit
	return $OK2;
}


/* ************************************************************************************
			@function	UpdateUserPasswd(	$dbconn	)

			@brief:	Ändert die Benutzer	Daten	in der DB

			@para	-	$dbconn			 Eine	Datenbankverbindung	der	Klasse mysqli

			@return	-	true im	Erfolgsfall
								sonst	false
************************************************************************************ */
function UpdateUserPasswd( $dbconn,	$uid,	$passwd	 )
{
	//1. ein Objekt	der	Klasse mysqli_stmt anlegen
	$prepstmt	=	$dbconn->stmt_init();
	//2.Abfrage	mit	Platzhalter	für	Daten	zusammenbasteln
	$SQLstring =
		"	UPDATE benutzer	SET	Passwd = SHA2( ?,	256)
									 WHERE User_ID = ?";

	// Abfrage an	den	DB-Server	abschicken

	// 3.	Prepared Statement auf dem DB-Server vorbereiten
	$OK	=	$prepstmt->prepare(	$SQLstring );
	
	// Abfrage erfolgreich?	
	if($OK === false)
	{
		echo "\n <div	class=\"error\">".
			 "\n <b>Abfrage	fehlgeschlagen!</b>".
			 "\n <div>".$SQLstring."</div>".
			 "\n <div>". $prepstmt->errno."	:	".$prepstmt->error."<\div>".
			 "</div>";

		die("DB-Problem	-	Abbruch");
	}

	//4. Daten an	die	Parameter	binden
	$type	=	"si";
	$params	=	array(&$Passwort,	&$User_ID);

	call_user_func_array(array($prepstmt,	"bind_param"), array_merge(array($type), $params));
	//5. Parameter setzen

	$Passwort	=	$passwd; //	$_SESSION['input_data']['Passwort']['val'];
	$User_ID = $uid; //$_SESSION['login']['UID'];

	//6. Diese Parameter anwenden
	$OK2 = $prepstmt->execute();
	if($OK2	===	false)
	{
		echo "\n <div	class=\"error\">".
			 "\n <b>Abfrage	fehlgeschlagen!</b>".
			 "\n <div>".$SQLstring."</div>".
			 "\n <div>". $prepstmt->errno."	:	".$prepstmt->error."<\div>".
			 "</div>";

		die("DB-Problem	-	Abbruch");
	}

	$prepstmt->close();	//abräumen nach	getaner	Arbeit
	return $OK2;
}	


/* ************************************************************************************
			@function	InsertNewArtist( $dbconn )

			@brief:	Fügt einen neuen Kuenstler in	die	DB ein

			@para	-	$dbconn			 Eine	Datenbankverbindung	der	Klasse mysqli

			@return	-	true im	Erfolgsfall
								sonst	false
************************************************************************************ */
function InsertNewArtist(	$dbconn	)
{
	//1. ein Objekt	der	Klasse mysqli_stmt anlegen
	$prepstmt	=	$dbconn->stmt_init();
	//2.Abfrage	mit	Platzhalter	für	Daten	zusammenbasteln
	
	$SQLstring =
		"	INSERT INTO	kuenstler	(	 Kname,	IBAN,	BIC, Vita, User_ID ) 
					VALUES	(	?, ?,	?, ?,	?)";

	// Abfrage an	den	DB-Server	abschicken

	// 3.	Prepared Statement auf dem DB-Server vorbereiten
	$OK	=	$prepstmt->prepare(	$SQLstring );
	
	// Abfrage erfolgreich?
	
	if($OK === false)
	{
		echo "\n <div	class=\"error\">".
			 "\n <b>Abfrage	fehlgeschlagen!</b>".
			 "\n <div>".$SQLstring."</div>".
			 "\n <div>". $prepstmt->errno."	:	".$prepstmt->error."<\div>".
			 "</div>";

		die("DB-Problem	-	Abbruch");
	}

	//4. Daten an	die	Parameter	binden
	$type	=	"ssssi";
	$params	=	array(&$kname, &$iban, &$bic,	&$vita,	&$User_ID);

	call_user_func_array(array($prepstmt,	"bind_param"), array_merge(array($type), $params));

	//5. Parameter setzen
	foreach($_SESSION['input_data']	as $item =>	$value)
	{
		${$item} = $value[val];
	}
	
	$User_ID = $_SESSION['login']['UID'];

	//6. Diese Parameter anwenden
	$OK2 = $prepstmt->execute();
	if($OK2	===	false)
	{
		echo "\n <div	class=\"error\">".
			 "\n <b>Abfrage	fehlgeschlagen!</b>".
			 "\n <div>".$SQLstring."</div>".
			 "\n <div>". $prepstmt->errno."	:	".$prepstmt->error."<\div>".
			 "</div>";

		die("DB-Problem	-	Abbruch");
	}

	$prepstmt->close();	//abräumen nach	getaner	Arbeit
	return $OK2;
}


/* ************************************************************************************
			@function	getKidByUid( $uid, $dbconn )

			@brief:	Gibt die zur UID gehörende Kuenstler_ID	zurück

			@para	-	$uid			 User_ID
							$dbconn		 Eine	Datenbankverbindung	der	Klasse mysqli

			@return	-	die	Kuenstler_ID
************************************************************************************ */
function getKidByUid(	$uid,	$dbconn	)
{
	$SQL_String	=	"SELECT	kuenstler.Kuenstler_ID AS	kid
									 FROM	kuenstler
									WHERE	kuenstler.User_ID	=	".$uid;
	
	$result_handle = $dbconn->query($SQL_String);

	// Abfrage erfolgreich?	
	if($result_handle	===	false)
	{
		echo "\n <div	class=\"error\">".
			 "\n <b>Abfrage	fehlgeschlagen!</b>".
			 "\n <div>".$SQLstring."</div>".
			 "\n <div>". $dbconn->errno."	:	".$dbconn->error."<\div>".
			 "</div>";

		die("DB-Problem	-	Abbruch");
	}

	// Abfrage über	UID	-> 1 oder	keinen Datensatz
	$ds	=	$result_handle->fetch_assoc();
	return $ds['kid']; 
}


/* ************************************************************************************
			@function	GetArtCounts(	$dbconn	)

			@brief:	Gibt die Anzahl	der	angebotenen	und	verkauften Bilder	zurück

			@para	-	$dbconn		 Eine	Datenbankverbindung	der	Klasse mysqli

			@return	-	ein	Arry mit den Zahlen
************************************************************************************ */
function GetArtCounts( $dbconn )
{
	// Abfrage ohne	Perpared_Statements
	$SQL_String1 = " SELECT		 COUNT(bild.Bild_ID) AS	offers	
									 FROM			 bild	JOIN kuenstler using (Kuenstler_ID)
									 WHERE		 bild.Kuenstler_ID = ".$_SESSION['login']['KID'];

	$SQL_String2=	"	 SELECT		 COUNT(bild.Bild_ID) AS	sold	
									 FROM			 bild	JOIN kuenstler using (Kuenstler_ID)
									 WHERE		 bild.Kuenstler_ID = ".$_SESSION['login']['KID']."
														 AND bild.User_ID	IS NOT NULL";
		
	// 1.	Abfrage	an DB-Server senden
	$result_handle = $dbconn->query($SQL_String1);

	// 1.	Abfrage	auf	Erfolg Ueberpruefen
	if($result_handle	===	false)
	{
		echo "\n <div	class=\"error\">".
			 "\n	<b>Abfrage fehlgeschlagen!</b>".
			 "\n	<div>".$SQL_String1."</div>".
			 "\n	<div>".	$dbconn->errno." : ".$dbconn->error."<\div>".
				"</div>";

		die("DB-Problem	-	Abbruch");
	}
	else
	{
		$offers_arr	=	array();	// ein leeres	Array	initialisieren!

		$ds	=	$result_handle->fetch_assoc();
		$offers_arr[0] = $ds['offers'];
	}

	// 2.	Abfrage	an DB-Server senden
	$result_handle = $dbconn->query($SQL_String2);

	// 2.	Abfrage	auf	Erfolg Ueberpruefen
	if($result_handle	===	false)
	{
		echo "\n <div	class=\"error\">".
			 "\n	<b>Abfrage fehlgeschlagen!</b>".
			 "\n	<div>".$SQL_String2."</div>".
			 "\n	<div>".	$dbconn->errno." : ".$dbconn->error."<\div>".
				"</div>";

		die("DB-Problem	-	Abbruch");
	}
	else
	{
		$ds	=	$result_handle->fetch_assoc();
		$offers_arr[1] = $ds['sold'];
	}
	return $offers_arr;
}


/* ************************************************************************************
			@function	GetUserBuys( $dbconn )

			@brief:	Gibt die gekauften Bilder	zurück

			@para	-	$dbconn		 Eine	Datenbankverbindung	der	Klasse mysqli

			@return	-	ein	Array	mit	den	Daten	der	Bilder
************************************************************************************ */
function GetUserBuys(	$dbconn	)
{
	// Abfrage ohne	Perpared_Statements
	$SQL_String	=	"	SELECT		COUNT(bild.Bild_ID)	AS Anzahl,	
														bild.Titel,
														bild.Kauf_Zeitstempel	AS `gekauft	am`,
														bild.VK_Preis	AS Preis,
														bild.Hoehe AS	Höhe,
														bild.Breite
									FROM			bild JOIN	benutzer using (User_ID)
									WHERE			bild.User_ID = ".$_SESSION['login']['UID']."
									ORDER	BY	bild.Titel";
		
	// Abfrage an	DB-Server	senden
	$result_handle = $dbconn->query($SQL_String);

	// Abfrage auf Erfolg	Ueberpruefen
	if($result_handle	===	false)
	{
		echo "\n <div	class=\"error\">".
				 "\n	<b>Abfrage fehlgeschlagen!</b>".
				 "\n	<div>".$SQL_String."</div>".
				 "\n	<div>".	$dbconn->errno." : ".$dbconn->error."<\div>".
						"</div>";

		die("DB-Problem	-	Abbruch");
	 }
	 else
	 {
		$user_buys_arr = array();	// ein leeres	Array	initialisieren!

		while( $ds = $result_handle->fetch_assoc() )
		{
			$user_buys_arr = $ds;
		}
	}
	return $user_buys_arr;
}


/* ************************************************************************************
			@function	GetArtistData( $dbconn )

			@brief:	Gibt die Profildaten eines Künstlers zurück

			@para	-	$dbconn		 Eine	Datenbankverbindung	der	Klasse mysqli

			@return	-	die	Daten
************************************************************************************ */
function GetArtistData(	$dbconn	)
{
	// Abfrage ohne	Perpared_Statements
	$SQL_String	=	"	SELECT		kuenstler.Kname	AS Künstlername,
														kuenstler.IBAN,
														kuenstler.BIC,
														kuenstler.Vita
									FROM			kuenstler
									WHERE			kuenstler.User_ID	=	".$_SESSION['login']['UID'];
		
	// Abfrage an	DB-Server	senden
	$result_handle = $dbconn->query($SQL_String);

	// Abfrage auf Erfolg	Ueberpruefen
	if($result_handle	===	false)
	{
		echo "\n <div	class=\"error\">".
				 "\n	<b>Abfrage fehlgeschlagen!</b>".
				 "\n	<div>".$SQL_String."</div>".
				 "\n	<div>".	$dbconn->errno." : ".$dbconn->error."<\div>".
						"</div>";

		die("DB-Problem	-	Abbruch");
	 }
	 else
	 {
		$artist_data_arr = array();	// ein leeres	Array	initialisieren!

		while( $ds = $result_handle->fetch_assoc() )
		{
			$artist_data_arr = $ds;
		}
	}
	return $artist_data_arr;
}
?>