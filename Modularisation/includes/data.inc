<?php


function KWS_DB_Connect( $user )
{
    define("DBServer","localhost");
    define("DBName","19ss_tedk4_kws");

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
      //$_SESSION['login']['user'] = 'gast';
      }
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
		$dbconn->query("SET NAMES utf8");
		return $dbconn;
}

/*
************************************************************************************
    			@function: GetAllArtists( $dbconn )

    			@brief: Holt alle User die als Künstler registriert sind aus der DB
                  Sortiert nach Alphabet

    			@para: $dbconn - Eine Datenbankverbinung der Klasse myslqi

    			@return: Im Erfolg - ein 2-dimensionales Array aller Kuenstler mit KName
                   Im Misserfolg - false Errorcode
************************************************************************************
*/
function GetAllArtists( $dbconn )
{
  // Abfrage ohne Perpared_Statements
  $SQL_String = "SELECT KName
                 FROM Kuenstler
                 ORDER BY KName";

  // Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String);

  // Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    echo "\n <div class=\"error\">".
         "\n <b>Abfrage fehlgeschlagen!</b>".
         "\n <div>".$SQLstring."</div>".
         "\n <div>". $dbconn->errno." : ".$dbconn->error."<\div>".
         "</div>";

         die("DB-Problem - Abbruch");
  }
  else
  {
    $artist_arr = array();	// ein leeres Array initialisieren!

    while( $ds = $result_handle->fetch_assoc() )
    {
      $artist_arr[] = $ds;
    }
  }

  return $artist_arr;
}


/*
************************************************************************************
    			@function: GetLast3Pics( $dbconn )
    			@brief:  Holt die letzten drei hochgeladenen kleinen Bilder aus dem
                   Ordner small zur Darstellung in der Index
    			@para: $dbconn - Eine Datenbankverbinung der Klasse myslqi
    			@return: Im Erfolg - Ein 2-dimensionales Array
                   Im Misserfolg - false
************************************************************************************
*/
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
    echo "\n <div class=\"error\">".
         "\n <b>Abfrage fehlgeschlagen!</b>".
         "\n <div>".$SQLstring."</div>".
         "\n <div>". $dbconn->errno." : ".$dbconn->error."<\div>".
         "</div>";

         die("DB-Problem - Abbruch");
  }
  else
  {
    $Three_Pics_arr = array();	// ein leeres Array initialisieren!

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
  $SQL_String = "SELECT bild.Bild_ID,
                        bild.Titel,
                        bild.Hoehe,
                        bild.Breite,
                        bild.VK_Preis,
                        Kuenstler.KName
                 FROM bild INNER JOIN Kuenstler USING (Kuenstler_ID)
                 ORDER BY bild.Einstell_Zeitstempel DESC";

  // Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String);

  // Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    echo "\n <div class=\"error\">".
         "\n <b>Abfrage fehlgeschlagen!</b>".
         "\n <div>".$SQLstring."</div>".
         "\n <div>". $dbconn->errno." : ".$dbconn->error."<\div>".
            "</div>";

    die("DB-Problem - Abbruch");
   }
   else
   {
     $Three_Pics_arr = array();	// ein leeres Array initialisieren!

     while( $ds = $result_handle->fetch_assoc() )
     {
       $Three_Pics_arr[] = $ds;
     }
    }

    return $Three_Pics_arr;
}



/*
************************************************************************************
    			@function: GetPic( $dbconn )
    			@brief:
    			@para:
    			@return:
************************************************************************************
*/
/*
function GetPic( $dbconn , $Session_ID['Bild_ID'] )
{
  $SQL_String = "SELECT bild.Bild_ID,
                        bild.Titel,
                        bild.Hoehe,
                        bild.Breite,
                        bild.VK_Preis,
                        Kuenstler.KName
                 FROM bild INNER JOIN Kuenstler USING (Kuenstler_ID)
                 WHERE bild.Bild_ID = $Session_ID['Bild_ID'];

  // Abfrage an DB-Server senden
  $result_handle = $dbconn->query($SQL_String);

  // Abfrage auf Erfolg Ueberpruefen
  if($result_handle === false)
  {
    echo "\n <div class=\"error\">".
         "\n <b>Abfrage fehlgeschlagen!</b>".
         "\n <div>".$SQLstring."</div>".
         "\n <div>". $dbconn->errno." : ".$dbconn->error."<\div>".
            "</div>";

    die("DB-Problem - Abbruch");
   }
   else
   {
     $Three_Pics_arr = array();	// ein leeres Array initialisieren!

     while( $ds = $result_handle->fetch_assoc() )
     {
       $Three_Pics_arr[] = $ds;
     }
    }

    return $Three_Pics_arr;
}
*/

/*
************************************************************************************
    			@function: InsertNewClient( $dbconn )
    			@brief: Fügt neuen Benutzer in die DB ein (Neue Anmeldung)
    			@para:
    			@return:
************************************************************************************
*/

/*
************************************************************************************
    			@function: InsertNewArtist( $dbconn )
    			@brief: Fügt neue
    			@para:
    			@return:
************************************************************************************
*/

/*
************************************************************************************
    			@function: InsertNewPic( $dbconn )
    			@brief: Fügt neue
    			@para:
    			@return:
************************************************************************************
*/

?>