<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );
  include_once( "./includes/inputCheck.inc" );
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = "./profil.php";
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/

  // Anforderungsliste
  $Data_Reqs = array(
    'Login'     => array( 'mand' => True, 
                          'type' => 'string',
                          'fname'=> 'htmlentities',
                          'check_is_unique' => 'login_unique'),
    'Passwort'  => array( 'mand' => True, 
                          'type' => 'string',
                          'fname' =>'htmlentities'),
    'Anrede'    => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Titel'     => array( 'mand' => False, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Vorname'   => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Nachname'  => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'PLZ'       => array( 'mand' => True, 
                          'type' => 'int', 
                          'fname' =>'abs',
                          'regex' => 'check_plz'),
    'Ort'       => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Strasse'   => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'HausNr'    => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Email'     => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Telefon'   => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities')
    );
  
  if(isset($_POST['submit']) && $_POST['submit'] == "Absenden")
  { 
    // Überprüfen ob alle Felder ausgefüllt wurden und was eingegeben wurde
    $dbconn = KWS_DB_Connect("bearbeiter"); // Datenbankverbindung
    if( check_input( $_POST['reg_data_arr'], $Data_Reqs, $_SESSION['input_data'], $dbconn ) )
    {
      $dbconn = KWS_DB_Connect("reg"); // Datenbankverbindung
      if( InsertNewUser( $dbconn ) )
      { // Erfolgsfall
        $_SESSION['error']['errno']=15;
        unset( $_SESSION['input_data'] );
        header('Location: ./login.php?'.SID);
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
  $labels_arr = array("Login", "Passwort", "Anrede", "Titel", 
                      "Vorname", "Nachname", "PLZ", "Ort", "Strasse", 
                      "HausNr", "Email", "Telefon");
	$header = "Regestrieren";
  $description= "Bitte füllen Sie dieses Formular aus, um ein Konto als Kunde zu erstellen.";
  $action = "./kunde_reg.php?";

  // Formular ausgeben
  HtmlRegForm( $labels_arr, $header, $description, $action );
  
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