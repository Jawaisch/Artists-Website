<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );
  include_once( "./includes/inputCheck.inc" );
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!
  if( $_SESSION['login']['user'] === "kunde")
  {
    header( 'Location: index.php?'.SID);
  }
  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung

  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/
?>

  <div id="content">

    <?php
      $SoldPics = GetAllSoldPics($dbconn, $_SESSION['login']['KID']);
      DisplaySoldPics($SoldPics);
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
