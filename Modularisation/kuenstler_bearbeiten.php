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
		'kname'		=> array( 'mand' => True, 
                              'type' => 'string',
							  'label' => 'Künstlername', 
                              'index' => 'kname',
                              'fname'=> 'htmlentities'),
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
							  'textarea' => True ),
    );

  $dbconn = KWS_DB_Connect("kuenstler"); // Datenbankverbindung

  if(isset($_POST['submit']) && $_POST['submit'] == "Absenden")
  { 
    // Überprüfen ob alle Felder ausgefüllt wurden und was eingegeben wurde
    if( check_input( $_POST['reg_data_arr'], $Data_Reqs, $_SESSION['input_data'], $dbconn ) )
    {
      if( UpdateArtistData( $dbconn ) )
      { // Erfolgsfall
        $_SESSION['error']['errno']=17;
        unset( $_SESSION['input_data'] );
        header('Location: ./kuenstler_bearbeiten.php?'.SID);
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
  $header = "Künstlerprofil bearbeiten";
  $description= "Bitte ändern Sie hier Ihre gewünschten Profildaten.";
  $action = "./kuenstler_bearbeiten.php?";

  // Formular ausgeben
  $artistData = GetArtistData( $dbconn );
  DebugArr($artistData);
  //DebugArr($_POST);
  HtmlRegForm( $Data_Reqs, $header, $description, $action, GetArtistData( $dbconn ) );

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