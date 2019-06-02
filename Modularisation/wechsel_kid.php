<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );
  include_once( "./includes/inputCheck.inc" );
  InitSession();  // Nimmt die aktuelle Session wieder auf

  // CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/
    $Data_Reqs = array( 
            'kuenstler' => array( 'mand' => True, 
                                  'type' => 'int',
                                  'fname'=>'abs'),
                       );

		if(isset($_POST['submit']) && $_POST['submit'] == "Auswählen")
    {     
      // Überprüfen ob alle Felder ausgefüllt wurden und was eingegeben wurde
      if( check_input( $_POST['reg_data_arr'], $Data_Reqs, $_SESSION['input_data'] ) )
      {
        $_SESSION['login']['KID'] = $_SESSION['input_data']['kuenstler']['val'];
        unset( $_SESSION['input_data'] );
        if ( !strpos($_SESSION['referer'],'?') === false )
        {
          $str_connect = '&';
        }
        else
        {
          $str_connect = '?';
        }
        header( 'Location: '.$_SESSION['referer'].$str_connect.SID);
        die();
      }
      else 
      { // Es fehlen Pflichteingaben
        $_SESSION['error']['errno']=12;
        header('Location: '.$_SESSION['referer'].'?'.SID);
        die();
      }
    }
  /*#########################################################################
          ENDE DES CONTENTS
    #######################################################################*/

  PrintHtmlSidebar( $_SESSION['login']['user'], SID );
  PrintHtmlFooter( SID ); 
?>
