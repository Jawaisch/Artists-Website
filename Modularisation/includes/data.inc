<?php

function KWS_DB_Connect( $user )
{
    if(!defined("DBServer")) define("DBServer","localhost");
    if(!defined("DBName"))define("DBName","19ss_tedk4_kws");

    switch($user)
    {

      // User-Parameter
      case    "admin":
              $DBUser =      "kws_admin";
              $DBPassword =  "kws_admin";
              break;

      case    "bearbeiter":
              $DBUser =      "kws_bearbeiter";
              $DBPassword =  "kws_bearbeiter";
              break;

      case    "kuenstler":
              $DBUser =      "kws_kuenstler";
              $DBPassword =  "kws_kuenstler";
              break;

      case    "kunde":
              $DBUser =      "kws_kunde";
              $DBPassword =  "kws_kunde";
              break;

      case    "login":
              $DBUser =      "kws_login";
              $DBPassword =  "kws_login";
              break;

      case    "reg":
              $DBUser =      "kws_reg";
              $DBPassword =  "kws_reg";
              break;

      default:
              $DBUser =      "kws_gast";
              $DBPassword =  "kws_gast";


    }

    // Neues Objekt der Klasse mysqli um Datenbankverbindung aufzubauen
    $dbconn = new mysqli(DBServer, $DBUser, $DBPassword, DBName);

    //Ueberpruefen ob Verbindung erfolgreich

    if($dbconn->connect_errno)
    {
      if( MYDEBUG )
      {
      echo "\n <div class=\"error\">".
        "PHP sagt:(".__FILE__.") Zeile : ".__FILE__.
         "\n <b>Verbindung fehlgeschlagen!</b>".
         "\n <div>". $dbconn->connect_errno." : ".$dbconn->connect_error."<\div>".
         "</div>";

      die("Netzwerkproblem - Abbruch");
      $_SESSION['login']['user'] = 'gast';
      }
      else
      {
        if( MYDEBUG )
        {
          echo "\n <div class=\"info\">".
             "\n <b>Verbindung zu ".$dbconn->host_info." aufgebaut</b>".
             "</div>";
        }
      }
    }
  $dbconn->query("SET NAMES utf8");
    return $dbconn;
}

/* ************************************************************************************
  @function CheckLoginFormData()

    @brief: Überprüft, ob alle Formularfelder der Anmeldung ausgefüllt sind

    Diese Funktion erwartet, dass die Formulardaten per POST übermittel wurden.
    Folgende Eingabedaten werden überprüft:
    - $_POST['login']
    - $_POST['passwd']

    @para - Keine

    @return -  bool
************************************************************************************ */
function CheckLoginFormData( )
{
  return ( !empty($_POST['login']) && !empty($_POST['passwd']) );
}


/* ************************************************************************************
      @function GetUidByLogin( $dbconn, $login , $pwd )

      @brief: Holt die User_ID über die Anmeldedaten

      @para - $dbconn      Eine Datenbankverbindung der Klasse mysqli
          - $login(string) Der Login des Users
          - &pwd(string)   Das Passwort des Users

      @return -  (int)uid im Erfolgsfall
             sonst false
************************************************************************************ */
function GetUidByLogin( $dbconn , $login , $pwd )
{
  //1. ein Objekt der Klasse mysqli_stmt anlegen
  $prepstmt = $dbconn->stmt_init();
  //2.Abfrage mit Platzhalter für Daten zusammenbasteln

  $SQLstring =
    " SELECT User_ID AS uid".
    " FROM benutzer".
    " WHERE Login = ?".
    " AND Passwd = SHA2( ? ,256)";
  // Abfrage an den DB-Server abschicken

  // 3. Prepared Statement auf dem DB-Server vorbereiten
  $OK = $prepstmt->prepare( $SQLstring );

  // Abfrage erfolgreich?

  if($OK === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  //4. Daten an die Parameter binden

  $prepstmt->bind_param( "ss" ,$login , $pwd );

  //5. Diese Parameter anwenden

  $prepstmt->execute();

  //6. Ergebnis holen/Rückgabewerte binden
  //a: Rückgabewert binden
  $prepstmt->bind_result( $uid );

  //b: mit dem üblichen mysqli_result
  //$err_handle = $prepstmt->get_result();

  // fetch-en Spezialfall: ein oder kein Datensatz

  $prepstmt->fetch(); // Rückgabewert ist schon in $uid sh. bind_result( $uid )

  if($uid == NULL)
  {
    $uid = false;
  }

  $prepstmt->close(); //abräumen nach getaner Arbeit
  return $uid;
} // end of   function GetUidByLogin( $dbconn , $login , $pwd )


/* ************************************************************************************
      @function GetKindOfUser( $dbconn , $uid)

      @brief: Überprüft ober der anmeldende Benutzer ein Künstler ist

      @para - $dbconn      Eine Datenbankverbindung der Klasse mysqli
          - $uid       Die User_ID des angemeldenden Benutzers


      @return -  "kuenstler" im Erfolgsfall
             sonst "kunde"
************************************************************************************ */
function GetKindOfUser( $dbconn , $uid)
{
  $SQL_String = "SELECT kuenstler.User_ID,
                        kuenstler.Kuenstler_ID AS KID
                  FROM  kuenstler
                 WHERE  kuenstler.User_ID = ".$uid;

  $result_handle = $dbconn->query($SQL_String);

  // Abfrage erfolgreich?

  if($result_handle === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }
  // Abfrage über UID -> 1 oder keinen Datensatz
  $UserArr = $result_handle->fetch_assoc();

  if( $UserArr == NULL)
  {
    $ResultArr[0] = "kunde";
  }
  else
  {
    $ResultArr[0] = "kuenstler";
  $ResultArr[1] = $UserArr['KID'];
  }
  return $ResultArr;
}


/*************************************************************************************
          @function: GetAllArtists( $dbconn )

          @brief: Holt alle User die als Künstler registriert sind aus der DB
                  Sortiert nach Alphabet

          @para: $dbconn - Eine Datenbankverbinung der Klasse myslqi

          @return: Im Erfolg - ein 2-dimensionales Array aller Kuenstler mit KName
                   Im Misserfolg - false Errorcode
*************************************************************************************/
/*************************************************************************************
          @function: GetAllArtists( $dbconn )

          @brief: Holt alle User die als Künstler registriert sind aus der DB
                  Sortiert nach Alphabet

          @para: $dbconn - Eine Datenbankverbinung der Klasse myslqi

          @return: Im Erfolg - ein 2-dimensionales Array aller Kuenstler mit KName
                   Im Misserfolg - false Errorcode
*************************************************************************************/
function GetAllArtists( $dbconn )
{
  // Abfrage ohne Perpared_Statements
  $SQL_String = "SELECT Kuenstler.KName, ".
				"		Kuenstler.Kuenstler_ID ".
                "FROM kuenstler ".
                "ORDER BY KName ASC";

  // Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String);

  // Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }
  else
  {
    $artist_arr = array();  // ein leeres Array initialisieren!

    $ds = $result_handle->fetch_all( MYSQLI_ASSOC);
	if($ds === NULL)
    {
      $artist_arr = false;
    }
	else
	{
		$artist_arr = $ds;
	}
  }

  return $artist_arr;
}


/*************************************************************************************
          @function: GetLast3Pics( $dbconn )
          @brief:  Holt die letzten drei hochgeladenen kleinen Bilder aus dem
                   Ordner small zur Darstellung in der Index
          @para: $dbconn - Eine Datenbankverbinung der Klasse myslqi
          @return: Im Erfolg - Ein 2-dimensionales Array
                   Im Misserfolg - false
*************************************************************************************/
function GetLast3Pics( $dbconn )
{
  $SQL_String = "SELECT bild.Bild_ID,
                        bild.Titel,
                        bild.Hoehe,
                        bild.Breite,
            bild.Einstell_Zeitstempel,
                        Kuenstler.KName
                 FROM bild INNER JOIN Kuenstler USING (Kuenstler_ID)
                 ORDER BY bild.Einstell_Zeitstempel DESC
                 LIMIT 3";

  // Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String);

  // Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }
  else
  {
    $Three_Pics_arr = array();  // ein leeres Array initialisieren!

    while( $ds = $result_handle->fetch_assoc() )
    {
      $Three_Pics_arr[] = $ds;
    }
  }

  return $Three_Pics_arr;

}


/*
************************************************************************************
          @function: GetAllPics( $dbconn )
          @brief: Hole alle Bilder aus dem Ordner Small zur Darstellung in
                  der Galerie
          @para:
          @return:
************************************************************************************
*/
function GetAllPics( $dbconn )
{
  $SQL_String = " SELECT bild.Bild_ID,".
                "        bild.Titel,".
                "        bild.Hoehe,".
                "        bild.Breite,".
                "        bild.VK_Preis,".
                "        Kuenstler.KName,".
                "    Kuenstler.Kuenstler_ID".
                " FROM bild INNER JOIN Kuenstler USING (Kuenstler_ID)".
                " ORDER BY bild.Einstell_Zeitstempel DESC";

  // Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String);

  // Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    ErrorHandling($SQL_String, $dbconn);
   }
   else
   {
     $Pics_arr = array(); // ein leeres Array initialisieren!

     while( $ds = $result_handle->fetch_assoc() )
     {
       $Pics_arr[] = $ds;
     }
    }

    return $Pics_arr;
}

/*************************************************************************************
          @function: GetUserData( $dbconn )
          @brief: Hole alle Bilder aus dem Ordner Small zur Darstellung in
                  der Galerie
          @para:  $dbconn - Eine Datenbankverbinung der Klasse myslqi
          @return:
*************************************************************************************/
function GetUserData( $dbconn )
{
  // Abfrage ohne Perpared_Statements
  $SQL_String = "SELECT Anrede,
                        Titel,
                        Vorname,
                        Nachname,
                        PLZ,
                        Ort,
                        Strasse,
                        HausNr,
                        Email,
                        Telefon,
                        Reg_Zeitstempel AS registriert_am_um
               FROM     benutzer
               WHERE    User_ID = ".$_SESSION['login']['UID'];

  // Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String);

  // Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }
  else
  {
    $user_data_arr = array(); // ein leeres Array initialisieren!

    while( $ds = $result_handle->fetch_assoc() )
    {
      $user_data_arr = $ds;
    }
  }
  return $user_data_arr;
}


/*
************************************************************************************
          @function: GetMorePicInfo( $dbconn , $BID )
          @brief:
          @para:
          @return:
************************************************************************************
*/

function GetMorePicInfo( $dbconn , $BID )
{
  $SQL_String = "SELECT Kuenstler.KName,".
        "   kuenstler.Kuenstler_ID, ".
                "       bild.Titel, ".
                "       bild.Hoehe, ".
                "       bild.Breite, ".
                "       bild.VK_Preis, ".
                "       bild.Mal_Technik, ".
                "       bild.Kauf_Zeitstempel, ".
                "   bild.Resv_Zeitstempel, ".
                "       genre.Genre_ID, ".
                "       genre.Name ".
                " FROM kuenstler INNER JOIN bild USING (Kuenstler_ID) ".
                " INNER JOIN eingeordnet USING (Bild_ID)".
                " INNER JOIN genre USING (Genre_ID) ".
                " WHERE bild.Bild_ID =". $BID;

  // Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String);

  // Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    ErrorHandling($SQL_String, $dbconn);
   }
   else
   {
     $Pic_arr = array();  // ein leeres Array initialisieren!

     while( $ds = $result_handle->fetch_assoc() )
     {
       $Pic_arr = $ds;
     }
    }

    return $Pic_arr;
}


/* ************************************************************************************
      @function InsertNewUser( $dbconn )

      @brief: Fügt einen neuen Benutzer in die DB ein (Neue Anmeldung)

      @para - $dbconn      Eine Datenbankverbindung der Klasse mysqli

      @return - true im Erfolgsfall
                sonst false
************************************************************************************ */
function InsertNewUser( $dbconn )
{
  //1. ein Objekt der Klasse mysqli_stmt anlegen
  $prepstmt = $dbconn->stmt_init();
  //2.Abfrage mit Platzhalter für Daten zusammenbasteln
  $SQLstring =
    " INSERT INTO benutzer (  Login, Passwd, Anrede, Titel, Vorname,
                              Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon,
                              Reg_Zeitstempel, Reg_IP )
              VALUES  ( ?, SHA2( ?, 256), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, CURRENT_TIMESTAMP, ?)";

  // Abfrage an den DB-Server abschicken

  // 3. Prepared Statement auf dem DB-Server vorbereiten
  $OK = $prepstmt->prepare( $SQLstring );

  // Abfrage erfolgreich?

  if($OK === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  //4. Daten an die Parameter binden
  $type = "ssssssissssss";
  $params = array(&$login, &$pwd, &$anrede, &$titel,
                  &$vname, &$nname, &$plz,  &$ort, &$str,
                  &$hnr,  &$email, &$tele,  &$reg_ip );

  call_user_func_array(array($prepstmt, "bind_param"), array_merge(array($type), $params));

  //5. Parameter setzen
  foreach($_SESSION['input_data'] as $item => $value)
  {
    ${$item} = $value[val];
  }

  // IP-Adresse ermitteln
  // Verwendet der Benutzer einen Proxy-Server
  if ( !isset($_SERVER['HTTP_X_FORWARDED_FOR']) )
  {
    $reg_ip = $_SERVER['REMOTE_ADDR'];
  }
  else
  {
    $reg_ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
  }

  //6. Diese Parameter anwenden
  $OK2 = $prepstmt->execute();
  if($OK2 === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  $prepstmt->close(); //abräumen nach getaner Arbeit
  return $OK2;
}


/* ************************************************************************************
      @function UpdateUserData( $dbconn )

      @brief: Ändert die Benutzer Daten in der DB

      @para - $dbconn      Eine Datenbankverbindung der Klasse mysqli

      @return - true im Erfolgsfall
                sonst false
************************************************************************************ */
function UpdateUserData( $dbconn )
{
  //1. ein Objekt der Klasse mysqli_stmt anlegen
  $prepstmt = $dbconn->stmt_init();
  //2.Abfrage mit Platzhalter für Daten zusammenbasteln
  $SQLstring =
    " UPDATE benutzer SET Anrede = ?, Titel = ?, Vorname = ?,
                          Nachname = ?, PLZ = ?, Ort = ?, Strasse = ?,
                          HausNr = ?, Email = ?, Telefon = ?
                   WHERE User_ID = ?";

  // Abfrage an den DB-Server abschicken

  // 3. Prepared Statement auf dem DB-Server vorbereiten
  $OK = $prepstmt->prepare( $SQLstring );

  // Abfrage erfolgreich?
  if($OK === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  //4. Daten an die Parameter binden
  $type = "ssssisssssi";
  $params = array(&$anrede, &$titel, &$vname, &$nname, &$plz, &$ort, &$str,
                  &$hnr,  &$email, &$tele,  &$uid );

  call_user_func_array(array($prepstmt, "bind_param"), array_merge(array($type), $params));

  //5. Parameter setzen
  foreach($_SESSION['input_data'] as $item => $value)
  {
    ${$item} = $value[val];
  }
  $uid = $_SESSION['login']['UID'];

  //6. Diese Parameter anwenden
  $OK2 = $prepstmt->execute();
  if($OK2 === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  $prepstmt->close(); //abräumen nach getaner Arbeit
  return $OK2;
}


/* ************************************************************************************
      @function UpdateArtistData( $dbconn )

      @brief: Ändert die Künstler Daten in der DB

      @para - $dbconn      Eine Datenbankverbindung der Klasse mysqli

      @return - true im Erfolgsfall
                sonst false
************************************************************************************ */
function UpdateArtistData( $dbconn )
{
  //1. ein Objekt der Klasse mysqli_stmt anlegen
  $prepstmt = $dbconn->stmt_init();
  //2.Abfrage mit Platzhalter für Daten zusammenbasteln
  $SQLstring =
    " UPDATE kuenstler SET Kname = ?, IBAN = ?, BIC = ?, Vita = ?
                   WHERE Kuenstler_ID = ?";

  // Abfrage an den DB-Server abschicken

  // 3. Prepared Statement auf dem DB-Server vorbereiten
  $OK = $prepstmt->prepare( $SQLstring );

  // Abfrage erfolgreich?
  if($OK === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  //4. Daten an die Parameter binden
  $type = "ssssi";
  $params = array(&$kname, &$iban, &$bic, &$vita, &$kid );

  call_user_func_array(array($prepstmt, "bind_param"), array_merge(array($type), $params));

  //5. Parameter setzen
  foreach($_SESSION['input_data'] as $item => $value)
  {
    ${$item} = $value[val];
  }
  $kid = $_SESSION['login']['KID'];

  //6. Diese Parameter anwenden
  $OK2 = $prepstmt->execute();
  if($OK2 === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  $prepstmt->close(); //abräumen nach getaner Arbeit
  return $OK2;
}


/* ************************************************************************************
      @function UpdateUserPasswd( $dbconn )

      @brief: Ändert die Benutzer Daten in der DB

      @para - $dbconn      Eine Datenbankverbindung der Klasse mysqli

      @return - true im Erfolgsfall
                sonst false
************************************************************************************ */
function UpdateUserPasswd( $dbconn, $uid, $passwd  )
{
  //1. ein Objekt der Klasse mysqli_stmt anlegen
  $prepstmt = $dbconn->stmt_init();
  //2.Abfrage mit Platzhalter für Daten zusammenbasteln
  $SQLstring =
    " UPDATE benutzer SET Passwd = SHA2( ?, 256)
                   WHERE User_ID = ?";

  // Abfrage an den DB-Server abschicken

  // 3. Prepared Statement auf dem DB-Server vorbereiten
  $OK = $prepstmt->prepare( $SQLstring );

  // Abfrage erfolgreich?
  if($OK === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  //4. Daten an die Parameter binden
  $type = "si";
  $params = array(&$Passwort, &$User_ID);

  call_user_func_array(array($prepstmt, "bind_param"), array_merge(array($type), $params));
  //5. Parameter setzen

  $Passwort = $passwd; // $_SESSION['input_data']['Passwort']['val'];
  $User_ID = $uid; //$_SESSION['login']['UID'];

  //6. Diese Parameter anwenden
  $OK2 = $prepstmt->execute();
  if($OK2 === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  $prepstmt->close(); //abräumen nach getaner Arbeit
  return $OK2;
}


/* ************************************************************************************
      @function InsertNewArtist( $dbconn )

      @brief: Fügt einen neuen Kuenstler in die DB ein

      @para - $dbconn      Eine Datenbankverbindung der Klasse mysqli

      @return - true im Erfolgsfall
                sonst false
************************************************************************************ */
function InsertNewArtist( $dbconn )
{
  //1. ein Objekt der Klasse mysqli_stmt anlegen
  $prepstmt = $dbconn->stmt_init();
  //2.Abfrage mit Platzhalter für Daten zusammenbasteln

  $SQLstring =
    " INSERT INTO kuenstler (  Kname, IBAN, BIC, Vita, User_ID )
          VALUES  ( ?, ?, ?, ?, ?)";

  // Abfrage an den DB-Server abschicken

  // 3. Prepared Statement auf dem DB-Server vorbereiten
  $OK = $prepstmt->prepare( $SQLstring );

  // Abfrage erfolgreich?

  if($OK === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  //4. Daten an die Parameter binden
  $type = "ssssi";
  $params = array(&$kname, &$iban, &$bic, &$vita, &$User_ID);

  call_user_func_array(array($prepstmt, "bind_param"), array_merge(array($type), $params));

  //5. Parameter setzen
  foreach($_SESSION['input_data'] as $item => $value)
  {
    ${$item} = $value[val];
  }

  $User_ID = $_SESSION['login']['UID'];

  //6. Diese Parameter anwenden
  $OK2 = $prepstmt->execute();
  if($OK2 === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  $prepstmt->close(); //abräumen nach getaner Arbeit
  return $OK2;
}


/* ************************************************************************************
      @function getKidByUid( $uid, $dbconn )

      @brief: Gibt die zur UID gehörende Kuenstler_ID zurück

      @para - $uid       User_ID
              $dbconn    Eine Datenbankverbindung der Klasse mysqli

      @return - die Kuenstler_ID
************************************************************************************ */
function getKidByUid( $uid, $dbconn )
{
  $SQL_String = "SELECT kuenstler.Kuenstler_ID AS kid
                   FROM kuenstler
                  WHERE kuenstler.User_ID = ".$uid;

  $result_handle = $dbconn->query($SQL_String);

  // Abfrage erfolgreich?
  if($result_handle === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }

  // Abfrage über UID -> 1 oder keinen Datensatz
  $ds = $result_handle->fetch_assoc();
  return $ds['kid'];
}


/* ************************************************************************************
      @function GetArtCounts( $dbconn )

      @brief: Gibt die Anzahl der angebotenen und verkauften Bilder zurück

      @para - $dbconn    Eine Datenbankverbindung der Klasse mysqli

      @return - ein Arry mit den Zahlen
************************************************************************************ */
function GetArtCounts( $dbconn )
{
  // Abfrage ohne Perpared_Statements
  $SQL_String1 = " SELECT    COUNT(bild.Bild_ID) AS offers
                   FROM      bild JOIN kuenstler using (Kuenstler_ID)
                   WHERE     bild.Kuenstler_ID = ".$_SESSION['login']['KID'];

  $SQL_String2= "  SELECT    COUNT(bild.Bild_ID) AS sold
                   FROM      bild JOIN kuenstler using (Kuenstler_ID)
                   WHERE     bild.Kuenstler_ID = ".$_SESSION['login']['KID']."
                             AND bild.User_ID IS NOT NULL";

  // 1. Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String1);

  // 1. Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }
  else
  {
    $offers_arr = array();  // ein leeres Array initialisieren!

    $ds = $result_handle->fetch_assoc();
    $offers_arr[0] = $ds['offers'];
  }

  // 2. Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String2);

  // 2. Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }
  else
  {
    $ds = $result_handle->fetch_assoc();
    $offers_arr[1] = $ds['sold'];
  }
  return $offers_arr;
}


/* ************************************************************************************
      @function GetUserBuys( $dbconn )

      @brief: Gibt die gekauften Bilder zurück

      @para - $dbconn    Eine Datenbankverbindung der Klasse mysqli

      @return - ein Array mit den Daten der Bilder
************************************************************************************ */
function GetUserBuys( $dbconn )
{
  // Abfrage ohne Perpared_Statements
  $SQL_String = " SELECT    COUNT(bild.Bild_ID) AS Anzahl,
                            bild.Titel,
                            bild.Kauf_Zeitstempel AS `gekauft am`,
                            bild.VK_Preis AS Preis,
                            bild.Hoehe AS Höhe,
                            bild.Breite
                  FROM      bild JOIN benutzer using (User_ID)
                  WHERE     bild.User_ID = ".$_SESSION['login']['UID']."
                  ORDER BY  bild.Titel";

  // Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String);

  // Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }
  else
  {
    $user_buys_arr = array(); // ein leeres Array initialisieren!

    while( $ds = $result_handle->fetch_assoc() )
    {
      $user_buys_arr = $ds;
    }
  }
  return $user_buys_arr;
}


/* ************************************************************************************
      @function GetArtistData( $dbconn )

      @brief: Gibt die Profildaten eines Künstlers zurück

      @para - $dbconn    Eine Datenbankverbindung der Klasse mysqli

      @return - die Daten
************************************************************************************ */
function GetArtistData( $dbconn )
{
  // Abfrage ohne Perpared_Statements
  $SQL_String = " SELECT    kuenstler.Kname AS Künstlername,
                            kuenstler.IBAN,
                            kuenstler.BIC,
                            kuenstler.Vita
                  FROM      kuenstler
                  WHERE     kuenstler.User_ID = ".$_SESSION['login']['UID'];

  // Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String);

  // Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    ErrorHandling($SQL_String, $dbconn);
  }
  else
  {
    $artist_data_arr = array(); // ein leeres Array initialisieren!

    while( $ds = $result_handle->fetch_assoc() )
    {
      $artist_data_arr = $ds;
    }
  }
  return $artist_data_arr;
}


/*
************************************************************************************
          @function:  Clean_Current_Cart( $dbconn , $Cart )
          @brief:   Leert den Warenkorb, wenn
                    1.Fall innerhalb der reservierten Zeit bezahlt wurde
                    2.Fall noch nicht gezahlt wurde und die reservierte Zeitabgelaufen ist
            @para:  $dbconn - Eine Datenbankverbindung
                    $Cart - Inhalt des Warenkorbs (1-dimensionales Array)
          @return:  Ein Mehrdimensionales Array[Bild_ID][ int ]
                    int = 0 - 2
                    0 = Reservierte Zeit ist noch nicht abgelaufen
                    1 = Es wurde innerhalb der reservierten Zeit gezahlt
                    2 = Es wurde zu lange gewartet und es wurde noch nicht gezahlt

************************************************************************************
*/
  function Clean_Current_Cart( $dbconn , $Cart )
  {
      $SQL_String = "SELECT bild.Bild_ID ".
                    "FROM bild ".
                    "WHERE bild.Bild_ID IN (".$Cart.") AND bild.Resv_Zeitstempel IS NOT NULL";

      // Abfrage an DB-Server senden
      $result_handle = $dbconn->query($SQL_String);

      // Abfrage auf Erfolg Ueberpruefen
      if($result_handle === false)
      {
        ErrorHandling($SQL_String, $dbconn);
      }
      else
      {
        $Cart_arr = array(); // ein leeres Array initialisieren!

        while( $ds = $result_handle->fetch_assoc() )
        {
          $Cart_arr[] = $ds['Bild_ID'];
        }
      }
      return $Cart_arr;
  }


  /* ************************************************************************************
      @function image_upload( $uid, $dbconn )

      @brief:

      @para -

      @return -
************************************************************************************ */
function image_upload()
{
  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  $sql_abfrage = "START TRANSACTION";
  mysqli_query($dbconn, $sql_abfrage );

  $sql_abfrage = "INSERT INTO bild (User_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP, Resv_Zeitstempel) VALUES
    (NULL,'".$_SESSION['login']['KID']."','".$_SESSION['input_data']['mal_technik']['val']."','".$_SESSION['input_data']['title']['val']."',".$_SESSION['input_data']['hoehe']['val'].",".$_SESSION['input_data']['breite']['val'].",
    ".$_SESSION['input_data']['preis']['val'].",CURRENT_TIMESTAMP(),'".$_SERVER['REMOTE_ADDR']."',NULL,NULL, NULL)";

  mysqli_query($dbconn, $sql_abfrage );
  DebugArr($dbconn);
  $last_insert_id = mysqli_insert_id($dbconn);
  $sql_abfrage = "INSERT INTO eingeordnet (Bild_ID, Genre_ID) VALUES
                                          ( LAST_INSERT_ID(),'".$_SESSION['input_data']['genre_id']['val']."')";
  mysqli_query($dbconn, $sql_abfrage );
  DebugArr($dbconn);

  $_SESSION['bild']['id']=$last_insert_id;

  // echo 'last insert id ='. $last_insert_id  ;

  /* ersteinmal eine Testausgabe, was kommt an ... */

  //echo "<br>POST";
  DebugArr($_POST);
  //echo "FILES";
  DebugArr($_FILES);
  //echo "SESSION";
  DebugArr($_SESSION);

  // Datei merken
  $orig_file = $_FILES['bild']['tmp_name'];
  if ( $_FILES['bild']['error']!= 0 )
  {
    /*
    $target='./upload.php?'.SID.'&err='.$_FILES['bild']['error'];
    header("Location: $target");
    */
    $_SESSION['error']['errno'] = 21;
    return 1;
  }

  $file_info = getimagesize($orig_file);
  if ( !empty($file_info) )
  {
    DebugArr($file_info);
  }
  else
  {
    //header("Location: ./upload.php?'.SID.'&err=10");
    //die("Fehler: Bitte wählen Sie ein zulässiges Dateiformat<br>Zulässige Dateiformate: .jpg; .png; .gif");
    // besser: Umlenkung auf eine Fehlerseite
    $_SESSION['error']['errno'] = 20;
    return 1;
  }

  /* ersteinmal alle Originaldaten merken und ausgeben */
  // format: landscape oder portrait
  $format = ($file_info[0] > $file_info[1])?"l":"p";

  //haben wir ein akzeptables format?
  // das wäre: jpg, gif oder png

  switch ( $file_info[2] )
  {
    // abhängig vom Dateityp ein image (rohdaten) erstellen
    case 1 : // gif erkannt
            $orig_img = ImageCreateFromGIF($orig_file);
            $file_ok = TRUE;
            break;
    case 2 : // jpg erkannt
            $orig_img = ImageCreateFromJPEG($orig_file);
            $file_ok = TRUE;
            break;
    case 3 : // png erkannt
            $orig_img = ImageCreateFromPNG($orig_file);
            $file_ok = TRUE;
            break;
    default: $file_ok = FALSE;
            //header("Location: ./upload.php?'.SID.'&err=11");
            // falsches Format
            $_SESSION['error']['errno'] = 20;
            return 1;
  }
  if($file_ok === TRUE)  {
    $sql_abfrage = "COMMIT";
    mysqli_query($dbconn, $sql_abfrage );
    // Jetzt gibt es ein image in den originalgrößen
    // echo 'Upload erfolgreich';

    // neue images in den wunschgrößen vorbereiten
    $bildname   = $last_insert_id.".png" ;
    $dest_big   = "./art-images/big/";
    $dest_small = "./art-images/small/";
    define("BIG_SIZE",600);
    define("SMALL_SIZE",300);

    // abhängig vom Format:
    if ($format == "l")
    {
      $new_width_b  = BIG_SIZE ;
      $new_width_s  = SMALL_SIZE;
      $new_height_b = BIG_SIZE*$file_info[1]/$file_info[0];
      $new_height_s = SMALL_SIZE*$file_info[1]/$file_info[0];
    }
    else
    {
      $new_height_b = BIG_SIZE;
      $new_height_s = SMALL_SIZE;
      $new_width_b  = BIG_SIZE*$file_info[0]/$file_info[1];
      $new_width_s  = SMALL_SIZE*$file_info[0]/$file_info[1];
    }
    // neue - leere - images erstellen
    $big_img        = ImageCreateTrueColor($new_width_b, $new_height_b );
    $small_img      = ImageCreateTrueColor($new_width_s, $new_height_s );
    /*
      ImageCopyResized( zielbild                  , quellbild,
                        ziel_x_start, ziel_y_start, quell_x_start, quell_y_start,
                        ziel_width  , ziel_height,  quell_width,   quell_height
                        );
    */
    ImageCopyResized( $big_img, $orig_img,
                      0,0,      0,0,
                      $new_width_b,  $new_height_b,
                      $file_info[0], $file_info[1]  );
    ImageCopyResized( $small_img, $orig_img,
                      0,0,      0,0,
                      $new_width_s,  $new_height_s,
                      $file_info[0], $file_info[1]  );
    // jetzt immer als png abspeichern:
    ImagePNG( $big_img,   $dest_big.$bildname   );
    ImagePNG( $small_img, $dest_small.$bildname );
    // und noch aufräumen
    ImageDestroy($orig_img);
    ImageDestroy($big_img);
    ImageDestroy($small_img);
  /*
    ?>
    <div>
      <h2>Bildvorschau</h2>
      <img src="<?php echo $dest_big.$bildname;?>" alt="grosses bild" />
    </div>
    <?php
  */
    mysqli_close($dbconn);
    $_SESSION['error']['errno'] = 18;
    return 0;
  }
  else
  {
    $sql_abfrage = "ROLLBACK";
    mysqli_query($dbconn, $sql_abfrage );
    mysqli_close($dbconn);
    $_SESSION['error']['errno'] = 19;
    return 1;
  }
}

?>
