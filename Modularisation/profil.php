<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/
?>

  <div id="content">
  
    <?php
      // Wurde ein Fehler übergeben?
      ErrorOccurred( );

    echo "<div class=\"split left\">"."\n";
    echo "  <h3>Ihr User Profil</h3>"."\n";
    echo    HtmlUserAccount( GetUserData( $dbconn ) );  
    echo "</div>"."\n";

    if ( $_SESSION['login']['user'] == "kuenstler" )
    {
      $ArtCounts = GetArtCounts( $dbconn );
      $offer = $ArtCounts[0];
      $sold  = $ArtCounts[1];
      echo "<div class=\"split right\">"."\n";
      echo "  <h3>Ihr Künstler Profil</h3>"."\n";
      echo    HtmlUserAccount( GetArtistData( $dbconn ) );
      echo    PrintHtmlCards( $offer, $sold, SID );
      echo "</div>"."\n";
    }
    echo "<div class=\"clearBoth\" >&nbsp;</div>"."\n";
	echo "	<p class=\"links\"><a href=\"./kunde_bearbeiten.php?".SID."\">Profil bearbeiten</a></p>"."\n";

    echo "<h2>Ihre Einkäufe</h2>";
    echo HtmlUserAccount( GetUserBuys( $dbconn ) );

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
