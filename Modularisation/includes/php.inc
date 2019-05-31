<?php

// Debug-Konstante
 define( "MYDEBUG", false ); 

/* ****************************************************************************************
@funktion InitSession()

@brief Initialidiert eine SESSION für die KWS

Session-Name wird gesetzt und COOKIES deaktiviert.
    
@param -

@return - 
****************************************************************************************** */
  function InitSession()
  {
    session_name( "kws" );          // den session.name in der Local Value setzten
    ini_set ("session.use_cookies", 0);
    ini_set ("session.use_only_cookies", 0);
    session_start();

    //ist noch kein user gesetzt?
    if ( !isset($_SESSION['login']['user']) )
    {// dann setze 'gast'
      $_SESSION['login']['user']='gast';
    }
  }


/* ****************************************************************************************
@funktion CheckLogin()

@brief Überprüft, ob ein User bereits erfolgreich angemeldet ist

Für diese Überprüfung wird in der SESION das Feld
$_SESSION['login']['success'] ausgewertet. Ist diese nicht erfolgreich,
dann wird auf die Anmeldeseite mit einem Fehlercode umgeleitet
    
@param -

@return - 
****************************************************************************************** */
  function CheckLogin()
  {
    if ( !isset($_SESSION['login']['success']) ||
      $_SESSION['login']['success'] !== true )
    {
      $_SESSION['error']['errno']=11;
      header('Location: ./index.php?'.SID);
      die();
    }
  }


 /* ****************************************************************************************
@funktion GetErrorDiv( $errno )

@brief Liefere eine Fehlermeldung, zu einer Fehlernummer

    
@param - Eine Fehlernummer

@return - gültiges HTML-Div als String
****************************************************************************************** */
  function GetErrorDiv( $errno )
  {
    switch( $errno )
    {
      case 1: $class="";
              $title="";
              $desc ="";
              break;

      case 10:$class="warning";
              $title="Passwort Wiederholung fehlgeschlagen!";
              $desc ="Bitte wiederholen Sie Ihr neues Passwort.";
              break;

      case 11:$class="warning";
              $title="Sie sind nicht eingeloggt!";
              $desc ="Um userbezogene Seiten aufrufen zu können, müssen Sie sich vorher einloggen.";
              break;

      case 12:$class="warning";
              $title="Es fehlen Pflichteingaben";
              $desc ="Bitte füllen Sie im Formular alle Felder aus";
              break;      
              
      case 13:$class="warning";
              $title="Falsche Anmeldedaten";
              $desc ="Diese kombination aus Login und Passwort ist ungültig! ".
                     "Geben Sie bitte erneut Ihre korrekten Anmeldedaten ein.";
              break;  
        
      case 14:$class="warning";
              $title="Regestrierung fehlgeschlagen!";
              $desc ="";
              break;

      case 15:$class="success";
              $title="Glückwunsch!";
              $desc ="Sie haben erfolgreich ein Kundenkonto angelegt. ".
                     "Loggen Sie sich jetzt ein, um Kunst zu erwerben.";
              break;

      case 16:$class="success";
              $title="Glückwunsch!";
              $desc ="Sie haben erfolgreich ein Künstlerkonto angelegt. ".
                     "Laden Sie jetzt Bilder hoch um ihre Kunst anzubieten.";
              break;

      case 17:$class="success";
              $title="Bestätigung!";
              $desc ="Ihre Daten wurden erfolgreich angepasst.";
              break;

    // UPLOAD
              
      case 18:$class="success";
              $title="Upload";
              $desc ="Das Bild wurde erfolgreich in unsere Datenbank eingetragen";
              break;
              
      case 19:$class="warning";
              $title="Upload";
              $desc ="Das Bild konnte aus technischen Gründen nicht hochgeladen werden.";
              break;      
              
      case 20:$class="warning";
              $title="falsches Dateiformat";
              $desc ="Fehler: Sie haben eine Bilddatei hochgeladen, jedoch hat es kein zulässiges Dateiformat<br />Zulässige Dateiformate: .jpg; .png; .gif";
              break;
              
      case 21:$class="warning";
              $title="falsches Dateiformat";
              $desc ="Fehler: Bitte wählen Sie ein zulässiges Dateiformat<br />Zulässige Dateiformate: .jpg; .png; .gif";
              break;

      default:$class="error";
              $title="Unbekannter Fehler";
              $desc ="unbekannt";
              break;
    }
    return HtmlErrorDiv( $class, $title, $desc );
  }

 /* ****************************************************************************************
@funktion ErrorOccurred( )

@brief - Prüft ob ein Fehler übergeben wurde. 
         Im Erfolgsfall wird eine Fehlermeldung ausgegeben.

@param - 

@return - 
****************************************************************************************** */
  function ErrorOccurred( )
  {
    $errString = "";                        // Fehlerausgabe mit Leerstring initialisieren

    // Wurde ein Fehler übergeben?
    if ( isset($_SESSION['error']['errno']))
      $errString = GetErrorDiv( $_SESSION['error']['errno']); // Fehler holen
      unset($_SESSION['error']['errno']);
      if ( empty($_SESSION['errno']) )
        unset($_SESSION['errno']);

    echo $errString;
  }


  /* ****************************************************************************************
@funktion DebugArr()

@brief gibt formatiertes Array aus
    
@param -

@return - 
****************************************************************************************** */
  function DebugArr( $arr ) 
  {
    if ( MYDEBUG )
    {
      echo "\n<pre>";
      print_r( $arr );
      echo "</pre>\n";
    }
  }


  /* ****************************************************************************************
@funktion logout( $location )

@brief der User wird ausgeloggt
    
@param - Das Ziel der Umlenkung

@return - 
****************************************************************************************** */
  function logout( $location ) 
  {
    // $errno = $_SESSION['error']['errno'];
    session_destroy();
    $_SESSION = array();
    // $_SESSION['error']['errno'] = $errno;
    header( 'Location: '.$location );
  }


/* ************************************************************************************
      @function ErrorHandling()

      @brief: Gibt eine Fehlermeldung aus wenn MYDEBUG = True sonst wird
              auf Fehlerseite umgelenkt.

      @para - 

      @return - 
************************************************************************************ */
function ErrorHandling($SQL_String, $dbconn)
{
  if( MYDEBUG )
  {
    echo "\n <div class=\"error\">".
         "\n  <b>Abfrage fehlgeschlagen!</b>".
         "\n  <div>".$SQL_String."</div>".
         "\n  <div>". $dbconn->errno." : ".$dbconn->error."<\div>".
            "</div>";
    die("DB-Problem - Abbruch");
  }
  else
  {
    header('Location: ./error.php?'.SID);
    die();
  }
}
?>

