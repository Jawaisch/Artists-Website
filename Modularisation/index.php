<?php
  error_reporting( E_ALL );

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
  echo '      <div id="content">'."\n";
  
  DebugArr($_SESSION);

  // Wurde ein Fehler übergeben?
  ErrorOccurred( );
 
  $Last3Pics = GetLast3Pics( $dbconn );
  PrintHtmlIndex($Last3Pics);
  
  echo '    <div class="clearBoth" >&nbsp;</div>'."\n";
  echo '    </div>'."\n";
  echo '    <!-- end #content -->'."\n";

  /*#########################################################################
          ENDE DES CONTENTS
    #######################################################################*/

  PrintHtmlSidebar( $_SESSION['login']['user'], SID );
  PrintHtmlFooter( SID ); 
?>