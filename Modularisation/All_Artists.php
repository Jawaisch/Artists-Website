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
  function DisplayAllArtists($Artist_Arr)
  {
    echo "<div class=\"table\">". 
         "\n      <table>".
         "\n        <tr><th>Unsere K&uuml;nstler</th></tr>\n";
        
    foreach ( $Artist_Arr AS $Artists )
      {  
      
       echo "         <tr><td><a href=\"public_artist.php?".SID."&amp;kid=".$Artists['Kuenstler_ID']."\">".$Artists['KName']."</a></td></tr>\n";   
      }
    
    echo  "       </table></div>";
  }

?>

  <div id="content">
  
    <?php
    $Artists = GetAllArtists($dbconn);
    DebugArr($Artists);
    DisplayAllArtists($Artists);
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
