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

  // Anforderungsliste und Labels fürs Formular
  $Data_Reqs = array(
           'login'              => array( 'mand'  => True, 
                                          'type'  => 'string',
                                          'label' => 'Login', 
                                          'index' => 'login',
                                          'fname' => 'htmlentities'),
            'pwd'               => array( 'mand'  => True, 
                                          'type'  => 'string',
                                          'label' => 'Passwort', 
                                          'index' => 'pwd',
                                          'fname' => 'htmlentities'),
       'new_pwd'                => array( 'mand'  => True, 
                                          'type'  => 'string',
                                          'label' => 'Neues Passwort', 
                                          'index' => 'new_pwd',
                                          'fname' => 'htmlentities'),
    'new_pwd_re'                => array( 'mand'  => True, 
                                          'type'  => 'string',
                                          'label' => 'Neues Passwort wiederholen', 
                                          'index' => 'new_pwd_re',
                                          'fname' => 'htmlentities'),
    );

  if(isset($_POST['submit']) && $_POST['submit'] == "Absenden")
  { 
    // Überprüfen ob alle Felder ausgefüllt wurden und was eingegeben wurde
    $dbconn = KWS_DB_Connect("kunde"); // Datenbankverbindung
    if( check_input( $_POST['reg_data_arr'], $Data_Reqs, $_SESSION['input_data'], $dbconn ) )
    {
      $dbconn = KWS_DB_Connect("login"); // Datenbankverbindung
      $uid = GetUidByLogin( $dbconn , $_SESSION['input_data']['login']['val'], $_SESSION['input_data']['pwd']['val']);
      $new_pwd    = $_SESSION['input_data']['new_pwd']['val'];
      $new_pwd_re = $_SESSION['input_data']['new_pwd_re']['val'];

      // Überprüfen ob die richtigen Anmeldedaten eingegeben wurden
      if( $_SESSION['login']['UID'] == $uid  )
      {
        // Überprüfen ob das Passwort richtig wiederholt wurden
        if( $new_pwd == $new_pwd_re )
        {
          $dbconn = KWS_DB_Connect("kunde"); // Datenbankverbindung
          if( UpdateUserPasswd( $dbconn, $uid, $new_pwd ) )
          { // Erfolgsfall
            $_SESSION['error']['errno']=17;
            unset( $_SESSION['input_data'] );
            header('Location: ./neues_passwort.php?'.SID);
            die();
          }
          else
          { // Insert fehlgeschlagen
            $_SESSION['error']['errno']=14;
          }
        }
        else
        { // Passwort Wiederholung fehlgeschlagen
          $_SESSION['error']['errno']=10;
        }
      }
      else
      { // Falsche Anmeldedaten
        $_SESSION['error']['errno']=13;
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
  //$labels_arr = array("Login", "Passwort", "Neues Passwort", "Neues Passwort wiederholen");
  $header = "Passwort ändern";
  $description= "Bitte geben Sie Ihr gewünschtes Passwort ein.";
  $action = "./neues_passwort.php?";

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