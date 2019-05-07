<?php

// Konstanten
 define( "MYDEBUG", true ); 

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
    }
  }


 /* ****************************************************************************************
@funktion GetErrorDiv( )

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

      case 11:$class="warning";
              $title="Sie sind nicht eingeloggt!";
              $desc ="Um userbezogene Seiten aufrufen zu können, müssen Sie sich vorher einloggen.";
              break;

      case 12:$class="warning";
              $title="Es fehlen Pflichteingaben";
              $desc ="Bitte füllen Sie im Anmeldeformular alle Felder aus";
              break;      
              
      case 13:$class="warning";
              $title="Falsche Anmeldedaten";
              $desc ="Diese kombination aus login und passwort ist ungültig! ".
                     "Geben Sie bitte erneut Ihre korrekten Anmeldedaten ein.";
              break;  
        
      case 14:$class="warning";
              $title="Regestrierung fehlgeschlagen";
              $desc ="";
              break;

      case 15:$class="success";
              $title="Glückwunsch!";
              $desc ="Sie haben erfolgreich ein Kundenkonto angelegt. ".
                     "Loggen Sie sich jetzt ein, um Kunst zu erwerben.";
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
?>

