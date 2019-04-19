<?php
  error_reporting( E_ALL );

  include( "./includes/view.inc" );
  include( "./includes/php.inc" );
  // include( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf
  // $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  // CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung

  // $dbconn = KWS_DB_Connect( "gast" ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'] );
?>

  <div id="content">
  
    <!-- Hier kommt euer content rein! -->

	<div class="clearBoth" >&nbsp;</div>
  </div>
  <!-- end #content --> 

<?php
  PrintHtmlSidebar( $_SESSION['login']['user'] );
  PrintHtmlFooter( ); 
?>
