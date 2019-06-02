<?php
/*****************************************************************************
  Deklaration der Funktion check_input()
*****************************************************************************/
function check_input($input, $DataReqs, &$clean, $dbconn = null)
{
  $result = True;
  /* Jetzt werden die Anforderungen abgearbeitet:
     Sobald eine geforderte Eingabe fehlt wird umgelenkt und abgebrochen
     ansonsten werden die Eingaben ins temporäre Feld aufgenommen und 
     bereinigt */
  foreach ($DataReqs as $name => $Req) # Gehe Alle Anforderungen durch:
  {
    if ( ( $Req['mand'] === true ) && ( empty( $input[$name] ))  )
    { # Eine geforderte Eingabe fehlt: 
      /* Fehler aufheben */
      $clean[$name]['val']  = null;
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

     /* Die in $DataReqs enthaltenen Funktioneb auf die Eingabe anwenden.*/
       if ( isset($Req['fname']) )  # Funktion gesetzt? - dann anwenden
       {
          $clean[$name]['val'] = $Req['fname']($clean[$name]['val']);
       }

	   // Funktion für Eindeutigkeit gesetzt? - dann anwenden
       if ( isset($Req['check_is_unique']) )  # Funktion gesetzt? - dann anwenden
       {
          if( !($Req['check_is_unique']($clean[$name]['val'], $dbconn)) )
         {
            $clean[$name]['err'] = "Bitte einen anderen ".$name." wählen!";
            $result = false;
         }
       }

	   // Funktion für Formatprüfung gesetzt? - dann anwenden
       if ( isset($Req['regex']) )
       {
          if( !($Req['regex']($clean[$name]['val'])) )
         {
            $clean[$name]['err'] = "Nicht zulässiges Format!";
            $result = false;
         }
       }
       /*
       foreach( $Req['fname'] as $fname )
       {
          $clean[$name]['val'] = $fname($clean[$name]['val']);
       }*/
    }
  } # End of: foreach ($DataReqs as $name => $Req)

  /* Sind wir hier angekommen, dan sind alle geforderten Eingaben vorhanden
     und im Array $clean zwangsweise 'typisiert' und die geforderten Funktionen
     auf ihnen angewendet. */
  return $result;
} # End of: function check_input


/* ************************************************************************************
      @function login_unique( $login, $dbconn )

      @brief: Prüft ob der Login schon vergeben ist

      @para - $login       Den zu prüfenden Login
              $dbconn      Eine Datenbankverbindung der Klasse mysqli

      @return - true wenn nicht vergeben
                sonst false
************************************************************************************ */
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
		  ErrorHandling($SQL_String, $dbconn);
    }

    //4. Daten an die Parameter binden
    $prepstmt->bind_param( "s" ,$login );

    //5. Diese Parameter anwenden
    $prepstmt->execute();

    //6. Ergebnis holen/Rückgabewerte binden
    //a: Rückgabewert binden
    $prepstmt->bind_result( $login );
    
    // fetch-en Spezialfall: ein oder kein Datensatz
    $prepstmt->fetch(); // rückgabewert ist schon in $uid sh. bind_result( $uid )

    if($login == NULL)
    {
      $result = true;
    }    
    $prepstmt->close(); //abräumen nach getaner Arbeit
    return $result;  
}


/* ************************************************************************************
      @function kname_unique( $kname, $dbconn )

      @brief: Prüft ob der Künstlername schon vergeben ist

      @para - $kname       Den zu prüfenden Künstlername
              $dbconn      Eine Datenbankverbindung der Klasse mysqli

      @return - true wenn nicht vergeben
                sonst false
************************************************************************************ */
function kname_unique( $kname, $dbconn )
{
  $result = false;

  //1. ein Objekt der Klasse mysqli_stmt anlegen
  $prepstmt = $dbconn->stmt_init();

  //2.Abfrage mit Platzhalter für Daten zusammenbasteln
  $SQLstring =
    " SELECT Kname".
    " FROM kuenstler".
    " WHERE Kname = ?";

    // 3. Prepared Statement auf dem DB-Server vorbereiten
    $OK = $prepstmt->prepare( $SQLstring );
    
    // Abfrage erfolgreich?
    
    if($OK === false)
    {
      ErrorHandling($SQL_String, $dbconn);
    }

    //4. Daten an die Parameter binden
    $prepstmt->bind_param( "s" ,$kname );

    //5. Diese Parameter anwenden
    $prepstmt->execute();

    //6. Ergebnis holen/Rückgabewerte binden
    //a: Rückgabewert binden
    $prepstmt->bind_result( $kname );
    
    // fetch-en Spezialfall: ein oder kein Datensatz
    $prepstmt->fetch(); // rückgabewert ist schon in $uid sh. bind_result( $uid )

    if($kname == NULL)
    {
      $result = true;
    }    
    $prepstmt->close(); //abräumen nach getaner Arbeit
    return $result;  
}


/* ************************************************************************************
      @function check_plz($plz)

      @brief: Prüft ob die PLZ der Domäne entspricht

      @para - $plz       Die zu prüfende PLZ

      @return - true wenn gültig
                sonst false
************************************************************************************ */
function check_plz($plz)
{
  if(preg_match('/^\d{5}$/',$plz)) 
    return true;
  else
    return false;
}


/* ************************************************************************************
      @function check_iban($iban)

      @brief: Prüft ob die IBAN der Domäne entspricht

      @para - $iban       Die zu prüfende IBAN

      @return - true wenn gültig
                sonst false
************************************************************************************ */
function check_iban($iban)
{
  if(preg_match('/^[A-Z]{2}[0-9]{20}$/',$iban)) 
    return true;
  else
    return false;
}


/* ************************************************************************************
      @function check_bic($bic)

      @brief: Prüft ob die BIC der Domäne entspricht

      @para - $bic       Die zu prüfende BIC

      @return - true wenn gültig
                sonst false
************************************************************************************ */
function check_bic($bic)
{
  if(preg_match('/^[A-Z]{6}[0-9A-Z]{2}([0-9A-Z]{3})?$/',$bic)) 
    return true;
  else
    return false;
} 

?>
