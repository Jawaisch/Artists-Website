<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );
  include_once( "./includes/inputCheck.inc" );
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  // CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/

  // Anforderungsliste
  $Data_Reqs = array(
            'wanted'    => array( 'mand' => True, 
                                  'type' => 'string',
                                  'fname'=> 'htmlentities'),
                                );

  echo"    <div id=\"content\">";

  if(isset($_POST['submit']) && $_POST['submit'] == "Suchen")
  { 
    if( $_POST['input_arr']['wanted'] != "Bildname" )
    {
      // Überprüfen ob das Feld ausgefüllt wurden und was eingegeben wurde
      if( check_input( $_POST['input_arr'], $Data_Reqs, $_SESSION['input_data'] ) )
      {
        if( $reslut = GetImageByName( $dbconn, $_SESSION['input_data']['wanted']['val'] ) )
        { // Erfolgsfall
          echo "      <h3>Ihr Suchergebnis</h3>";
          PrintHtmlGallery($reslut);
          unset( $_SESSION['input_data'] );   
        }
        else
        { // Nichts gefunden
          $_SESSION['error']['errno']=22;
        }
      }
      else 
      { // Es fehlen Pflichteingaben
        $_SESSION['error']['errno']=23;
      }
    }
    else
    { // Keine Eingabe
      $_SESSION['error']['errno']=24;
    }
  }

  // Wurde ein Fehler übergeben?
  ErrorOccurred( );

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
