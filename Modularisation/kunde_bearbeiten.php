<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );
  include_once( "./includes/inputCheck.inc" );
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = "./profil.php";
  CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/

  // Anforderungsliste
  $Data_Reqs = array(
    'anrede'    => array( 'mand' => True, 
                          'type' => 'string',
                          'label' => 'Anrede', 
                          'index' => 'anrede',
                          'fname' =>'htmlentities'),
    'titel'     => array( 'mand' => False, 
                          'type' => 'string',
                          'label' => 'Titel', 
                          'index' => 'titel',
                          'fname' =>'htmlentities'),
    'vname'     => array( 'mand' => True, 
                          'type' => 'string',
                          'label' => 'Vorname', 
                          'index' => 'vname',
                          'fname' =>'htmlentities'),
    'nname'     => array( 'mand' => True, 
                          'type' => 'string',
                          'label' => 'Nachname', 
                          'index' => 'nname',
                          'fname' =>'htmlentities'),
    'plz'       => array( 'mand' => True, 
                          'type' => 'int',
                          'label' => 'PLZ', 
                          'index' => 'plz',
                          'fname' =>'abs',
                          'regex' => 'check_plz'),
    'ort'       => array( 'mand' => True, 
                          'type' => 'string',
                          'label' => 'Ort', 
                          'index' => 'ort',
                          'fname' =>'htmlentities'),
    'str'       => array( 'mand' => True, 
                          'type' => 'string',
                          'label' => 'Strasse', 
                          'index' => 'str',
                          'fname' =>'htmlentities'),
    'hnr'       => array( 'mand' => True, 
                          'type' => 'string',
                          'label' => 'HausNr', 
                          'index' => 'hnr',
                          'fname' =>'htmlentities'),
    'email'     => array( 'mand' => True, 
                          'type' => 'string',
                          'label' => 'Email', 
                          'index' => 'email',
                          'fname' =>'htmlentities'),
    'tele'      => array( 'mand' => True, 
                          'type' => 'string',
                          'label' => 'Telefon', 
                          'index' => 'tele',
                          'fname' =>'htmlentities')
    );
  
  if(isset($_POST['submit']) && $_POST['submit'] == "Absenden")
  { 
    // Überprüfen ob alle Felder ausgefüllt wurden und was eingegeben wurde
    $dbconn = KWS_DB_Connect("kunde"); // Datenbankverbindung
    if( check_input( $_POST['reg_data_arr'], $Data_Reqs, $_SESSION['input_data'], $dbconn ) )
    {
      $dbconn = KWS_DB_Connect("kunde"); // Datenbankverbindung

      // wurde ein neues Passwort eingegeben?
      if( !empty($_SESSION['input_data']['Passwort']['val']) )
      { 
        UpdateUserPasswd( $dbconn ); // TODO Passwort wiederholen
        unset($_SESSION['input_data']['Passwort']);
      }
      if( UpdateUserData( $dbconn ) )
      { // Erfolgsfall
        $_SESSION['error']['errno']=17;
        unset( $_SESSION['input_data'] );
        header('Location: ./kunde_bearbeiten.php?'.SID);
        die();
      }
      else
      { // Insert fehlgeschlagen
        $_SESSION['error']['errno']=14;
      }
    }
    else 
    { // Es fehlen Pflichteingaben
      $_SESSION['error']['errno']=12;
    }
  }

  echo"    <div id=\"content\">";

  // Wurde ein Fehler übergeben?
  ErrorOccurred( );
  
  // Formular vorbereiten
  $header = "Profil bearbeiten";
  $description= "Bitte ändern Sie hier Ihre gewünschten Profildaten.";
  $action = "./kunde_bearbeiten.php?";

  // Formular ausgeben
  $dbconn = KWS_DB_Connect("kunde"); // Datenbankverbindung
  $userData = GetUserData( $dbconn);
  HtmlRegForm( $Data_Reqs, $header, $description, $action, GetUserData( $dbconn ) );

  echo "  <p class=\"links\"><a href=\"./neues_passwort.php?".SID."\">Passwort ändern</a></p>"."\n";
  
  ?>
    <div class="clearBoth" >&nbsp;</div>
  </div>

  <!-- end #content --> 

<?php
  /*#########################################################################
          ENDE DES CONTENTS
    #######################################################################*/

  PrintHtmlSidebar( $_SESSION['login']['user'], SID );
  PrintHtmlFooter( SID ); 
?>