<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );
  include_once( "./includes/inputCheck.inc" );
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/

  // Anforderungsliste
  $Data_Reqs = array(
    'kname'   => array( 'mand' => True, 
                              'type' => 'string',
                              'label' => 'Künstlername', 
                              'index' => 'kname',
                              'fname'=> 'htmlentities',
                              'check_is_unique' => 'kname_unique'),
      'iban'       => array(  'mand' => True, 
                              'type' => 'string',
                              'label' => 'IBAN', 
                              'index' => 'iban',            
                              'fname' =>'htmlentities',
                              'regex' => 'check_iban'),
      'bic'        => array(  'mand' => True, 
                              'type' => 'string',
                              'label' => 'BIC', 
                              'index' => 'bic',
                              'fname' =>'htmlentities',
                              'regex' => 'check_bic'),
      'vita'       => array(  'mand' => False, 
                              'type' => 'string',
                              'label' => 'Vita', 
                              'index' => 'vita',
                              'fname' =>'htmlentities',
                              'textarea' => True),
    );
  
  if(isset($_POST['submit']) && $_POST['submit'] == "Absenden")
  { 
    // Überprüfen ob alle Felder ausgefüllt wurden und was eingegeben wurde
    $dbconn = KWS_DB_Connect("bearbeiter"); // Datenbankverbindung
    if( check_input( $_POST['reg_data_arr'], $Data_Reqs, $_SESSION['input_data'], $dbconn ) )
    {
      $dbconn = KWS_DB_Connect("reg"); // Datenbankverbindung
      if( InsertNewArtist( $dbconn ) )
      { // Erfolgsfall
        $_SESSION['error']['errno'] = 16;
        $_SESSION['login']['user'] = "kuenstler";
        $_SESSION['login']['KID'] = getKidByUid( $_SESSION['login']['UID'], KWS_DB_Connect("bearbeiter") );
        header('Location: ./profil.php?'.SID);
        die("header?!");
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
  $header = "Künstlerkonto anlegen";
  $description= "Bitte füllen Sie dieses Formular aus, um Ihrem Konto ein Künstlerkonto hinzuzufügen.";
  $action = "./kuenstler_reg.php?";

  // Formular ausgeben
  HtmlRegForm( $Data_Reqs, $header, $description, $action, null, $agbs=True );
  
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