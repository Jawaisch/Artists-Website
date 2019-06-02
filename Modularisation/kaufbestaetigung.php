<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/

		// Datenbankverbindung
		$dbconn = KWS_DB_Connect( "kunde" ); 

		// gekaufte Bilder mit dem Kunden verknüpfen
		UpdateImageState( $dbconn );
		
		// Zahlungsaufforderung
		HtmlPrintPaymentRequest( );

		// den Warenkorb löschen
		$_SESSION['cart'] = NULL;  $_SESSION['cartimpl'] = NULL ;

  /*#########################################################################
          ENDE DES CONTENTS
    #######################################################################*/

  PrintHtmlSidebar( $_SESSION['login']['user'], SID );
  PrintHtmlFooter( SID ); 
?>
