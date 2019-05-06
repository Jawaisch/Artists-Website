<?php
  error_reporting( E_ALL );
  define( "MYDEBUG", false );

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
  
    <h2>Gallery</h2>
      <p>Ändern Sie die Größe des Browserfensters, um den Response-Effekt zu sehen.</p>

      <!-- Gallery Grid -->
      <div class="row">
        <div class="column">
          <div class="content">
            <img src="art-images/small/1428.png" alt="Text" style="width:100%" />
            <h3>My Work</h3>
            <p>Lorem ipsum..</p>
          </div>
        </div>
        <div class="column">
          <div class="content">
            <img src="art-images/small/1425.png" alt="Text" style="width:100%" />
            <h3>My Work</h3>
            <p>Lorem ipsum..</p>
          </div>
        </div>
        <div class="column">
          <div class="content">
            <img src="art-images/small/1515.png" alt="Text" style="width:100%" />
            <h3>My Work</h3>
            <p>Lorem ipsum..</p>
          </div>
        </div>
      </div>
	  <div class="row">
        <div class="column">
          <div class="content">
            <img src="art-images/small/1428.png" alt="Text" style="width:100%" />
            <h3>My Work</h3>
            <p>Lorem ipsum..</p>
          </div>
        </div>
        <div class="column">
          <div class="content">
            <img src="art-images/small/1425.png" alt="Text" style="width:100%" />
            <h3>My Work</h3>
            <p>Lorem ipsum..</p>
          </div>
        </div>
        <div class="column">
          <div class="content">
            <img src="art-images/small/1515.png" alt="Text" style="width:100%" />
            <h3>My Work</h3>
            <p>Lorem ipsum..</p>
          </div>
        </div>
      </div>

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
