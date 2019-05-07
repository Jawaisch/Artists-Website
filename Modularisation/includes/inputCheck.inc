<?php
/*****************************************************************************
  Deklaration der Funktion check_input()
*****************************************************************************/
function check_input($input, $DataReqs, &$clean, $dbconn, $redirect_URL = null)
{
  $result = True;
  /* Jetzt werden die Anforderungen abgearbeitet:
     Sobald eine geforderte Eingabe fehlt wird umgelenkt und abgebrochen
     ansonsten werden die Eingaben ins temporäre Feld aufgenommen und 
     bereinigt */
  foreach ($DataReqs as $name => $Req) # Gehe Alle Anforderungen durch:
  {
    if ( ( $Req['mand'] === true ) && ( empty( $input[$name] ))  )
    {                   # Eine geforderte Eingabe fehlt: 
      /* Variante A: eine Umlenkung auf eine Fehlerseite
      if ( $redirect_URL )        # Soll jetzt umgelenkt werden?
      { # umlenken - besser natürlich mit fehlermeldung als Parameter
        header('Location: '.$redirect_URL);
      }
      */
      /* Variante B: eine formatierte Fehlerausgabe (VORSICHT!) 
      if (defined (MY_DEBUG) && MY_DEBUG )
      {
        my_error( "Fehlende Eingabe!",
          "Eingabe $Name fehlt und keine Umlenkung angegeben!",
          FALSE );
      }
      */
      /* Variante C: Fehler aufheben */
      $clean[$name]['val']  = null;
      $clean[$name]['mand'] = true;
      $clean[$name]['err']  = "Fehlende Eingabe!";
      $result = False;
    } 
    else
    { /* Es ist bis jetzt kein Fehler aufgetreten.
         Also die Eingabe zum Array $clean hinzufügen */
      
      $clean[$name]['val'] = $input[$name];
      unset($clean[$name]['err']);
  
      /* Den in $Req enthaltenen Typen auf die Eingabe anwenden */
      if ( isset($Req['type']) )    # ist ein Typ gesetzt? - dann anwenden
        settype( $clean[$name]['val'], $Req['type'] );

     /* Die in $Anforderungen enthaltene Funktion auf die Eingabe anwenden.
       Es ist hier natürlich auch möglich eigene Funktionen zu verwenden. 
       Dies ist insbesondere dann nützlich, wenn mehrere Funktionen verwendet
       werden sollen ;-) */
       if ( isset($Req['fname']) )  # Funktion gesetzt? - dann anwenden
       {
			    $clean[$name]['val'] = $Req['fname']($clean[$name]['val']);
       }
       if ( isset($Req['fname_db_check']) )  # Funktion gesetzt? - dann anwenden
       {
			    $OK = $Req['fname_db_check']($clean[$name]['val'], $dbconn); //TODO:
       }
       /*
       foreach( $Req['fname'] as $fname )
       {
			    $clean[$name]['val'] = $fname($clean[$name]['val']);
       }*/
       if ( !$OK )
       {
          $result = false;
       }
    }
  } # End of: foreach ($DataReqs as $name => $Req)

  /* Sind wir hier angekommen, dan sind alle geforderten Eingaben vorhanden
     und im Array $clean zwangsweise 'typisiert' und die geforderten Funktionen
     auf ihnen angewendet. */
  return $result;
} # End of: function check_input

function login_unique( $login, $dbconn )
{
  $result = false;
  //1. ein Objekt der Klasse mysqli_stmt anlegen
  $prepstmt = $dbconn->stmt_init();

  //2.Abfrage mit Platzhalter für Daten zusammenbasteln
  $SQLstring =
    " SELECT Login".
    " FROM benutzer".
    " WHERE Login = ?";

    // 3. Prepared Statement auf dem DB-Server vorbereiten
    $OK = $prepstmt->prepare( $SQLstring );
    
    // Abfrage erfolgreich?
    
    if($OK === false)
    {
      echo "\n <div class=\"error\">".
         "\n <b>Abfrage fehlgeschlagen!</b>".
         "\n <div>".$SQLstring."</div>".
         "\n <div>". $prepstmt->errno." : ".$prepstmt->error."<\div>".
         "</div>";

      die("DB-Problem - Abbruch");
    }

    //4. Daten an die Parameter binden
    $prepstmt->bind_param( "s" ,$login );

    //5. Diese Parameter anwenden
    $prepstmt->execute();

    //6. Ergebnis holen/Rückgabewerte binden
    //a: Rückgabewert binden
    $prepstmt->bind_result( $result );
    
    // fetch-en Spezialfall: ein oder kein Datensatz
    $prepstmt->fetch(); // rückgabewert ist schon in $uid sh. bind_result( $uid )

    if($result == NULL)
    {
      $result = true;
    }
    
    $prepstmt->close(); //abräumen nach getaner Arbeit
    return $result;  
}



/*****************************************************************************
    Beispiel für eine Anforderungsliste
*****************************************************************************/

/* Es folgt ein Beispiel für die Anforderungen. In diesem Beispiel sollen
   folgende Anforderungen gelten:
  1.  Es gibt drei Eingabefelder:
    "anzahl", "art_nr", "farbe"
  2.  "anzahl" und "art_nr" sind Pflichtfelder, "farbe" nicht
  3.  "anzahl" und "art_nr" sind ganze Zahlen, "farbe" ist Text
  4.  Auf 'anzahl' soll die Funktion positive() angewendet werden
  5.  Auf 'art_nr' soll die Funktion Is_ArtID() angewendete werden
  6.  Auf 'farbe'  soll die Funktion check_color() angewendet werden 
  -   die Funktionen positive(), Is_ArtID() und check_color sind
      selbstgeschriebene Funktionen und müssen natürlich zur Verfügung 
      gestellt werden.

   Nun muss ein Array mit den Anforderungen erstellt werden. Für jedes 
   Eingabefeld, welches überprüft werden soll, wird ein Array angelegt,
   mit den möglichen Einträgen: 
     Pflichteingabe: 'mand', 
     Datentyp:       'type',
     Funktionsname:  'fname'.*/
/*
$Data_Reqs = array(
  'anzahl'  => array('mand' => true, 
                     'type' => 'int',
                     'fname'=> 'positive'),
  'art_nr'  => array('mand' => true, 
                     'type' => 'int'),
  'farbe'   => array('mand' => false, 
                     'type' => 'string', 
                     'fname' =>'check_color')
  );
   
*/
/*****************************************************************************
    Nun soll die Eingabeüberprüfung auch durchgeführt werden. 
    Beispielhafter Aufruf der Funktion Eingabeüberprüfung()
*****************************************************************************/
  /* Beispiel 1
  ==============
  1. Parameter : Die Daten wurden mit der GET-Methode übergeben.
  2. Parameter : Wir haben genau obige Bedingungen im Array $Data_Reqs
                 abgelegt.
  3. Parameter : Die bereinigten Werte mit potenziellen Fehlermeldungen 
                 sollen in der Session unter input_data aufgehoben werden.
  4. Parameter : Wenn fehlende Pflichteingaben auftauchen, dann wollen wir
                 zur Fehlerseite: "htdocs/projekt2/error.php". Dabei merken 
                 wir uns den Fehler missing_input.
  */
/*
  check_input( $_GET, $Data_Reqs, $_SESSION['input_data'],  
          "http://$_SERVER['SERVER_NAME]/projekt2/error.php?Grund=Eingabe");
*/
  /* Beispiel 2
  ==============
  1. Parameter : Die Daten wurden mit der POST-Methode übergeben.
  2. Parameter : Wir haben die Bedingungen im Array $Bedingungen (neuer Name?)
                 abgelegt.
  3. Parameter : Die bereinigten Werte mit potenziellen Fehlermeldungen 
                 sollen in einem neuen Array $clean aufgehoben werden.
  4. Parameter : Keine Umlenkung im Fehlerfall
  */
  /*
$Bedingungen = array(
  'login' => array( 'fname'=> 'check_login',
                    'mand' => true          ),
  'passwd'=> array( 'mand' => true, 
                    'type' => 'string', 
                    'fname' =>'check_passwd')
  );
$clean= array();
check_input( $_POST, $Bedingungen, $clean );
*/
?>
