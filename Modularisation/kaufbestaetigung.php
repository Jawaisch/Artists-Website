<?php
  error_reporting( E_ALL );
  define( "MYDEBUG", true );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  // CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/
?>

  <div id="content">
  <?php
    DebugArr($_POST);
    DebugArr($_SESSION);
    echo $_SERVER['REMOTE_ADDR'];
    //echo 'date= ' . date('Y\-m\-d G\:i\:s');

    //$cart = array(1421,1506,1709, 1502);
    //$cartimpl = implode("','",$cart);
    $con = mysqli_connect("localhost","kws_kunde","kws_kunde","19ss_tedk4_kws");
    $sql_abfrage = "UPDATE  bild
                    SET     bild.Kauf_Zeitstempel = CURRENT_TIMESTAMP(),
                            bild.User_ID = 704,
                            bild.Kauf_IP = '".$_SERVER['REMOTE_ADDR']."'
                    
                    WHERE Bild_ID IN ('".$_SESSION['cartimpl']."')";
    // $_SESSION['login']['UID']
    $res = mysqli_query($con,$sql_abfrage);
    if ($res==true)
        echo "kauf Abgeschlossen.";
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
