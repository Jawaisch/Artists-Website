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
    'login'     => array( 'mand'  => True, 
                          'type'  => 'string',
                          'label' => 'Login', 
                          'index' => 'login',
                          'fname' => 'htmlentities'),
    'pwd'       => array( 'mand'  => True, 
                          'type'  => 'string',
                          'label' => 'Passwort', 
                          'index' => 'pwd',
                          'fname' => 'htmlentities'),
    'anrede'    => array( 'mand' => True, 
                          'type' => 'string',
                          'label' => 'Anrede', 
                          'index' => 'anrede',
                          'fname' =>'htmlentities'),
    'titel'     => array( 'mand' => False, 
                          'type' => 'string',
                          'label' => 'Titel (optional)', 
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
                          'label' => 'Postleitzahl', 
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
                          'label' => 'Hausnummer', 
                          'index' => 'hnr',
                          'fname' =>'htmlentities'),
    'email'     => array( 'mand' => True, 
                          'type' => 'string',
                          'label' => 'Email Adresse', 
                          'index' => 'email',
                          'fname' =>'htmlentities'),
    'tele'      => array( 'mand' => True, 
                          'type' => 'string',
                          'label' => 'Telefonnummer', 
                          'index' => 'tele',
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

  DebugArr($_SESSION);
  DebugArr($_POST);

  // Wurde ein Fehler übergeben?
  ErrorOccurred( );
  
  // Formular vorbereiten
  $header = "Regestrieren";
  $description= "Bitte füllen Sie dieses Formular aus, um ein Konto als Kunde zu erstellen.";
  $action = "./kunde_reg.php?";

  // Formular ausgeben
  HtmlRegForm( $Data_Reqs, $header, $description, $action );
  
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