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
  
    <h2>Gallery</h2>
      <p>Ändern Sie die Größe des Browserfensters, um den Response-Effekt zu sehen.</p>

      <!-- Gallery Grid -->
      <div class="row">
        <div class="column">
          <div class="content">
            <img src="small/1107_Pop Art Kunst.png" alt="Text" style="width:100%" />
            <h3>My Work</h3>
            <p>Lorem ipsum..</p>
          </div>
        </div>
        <div class="column">
          <div class="content">
            <img src="small/pic_0150.png" alt="Text" style="width:100%" />
            <h3>My Work</h3>
            <p>Lorem ipsum..</p>
          </div>
        </div>
        <div class="column">
          <div class="content">
            <img src="small/pic_0152.png" alt="Text" style="width:100%" />
            <h3>My Work</h3>
            <p>Lorem ipsum..</p>
          </div>
        </div>
        <div class="column">
          <div class="content">
            <img src="small/pic_0153_1.png" alt="Text" style="width:100%" />
            <h3>My Work</h3>
            <p>Lorem ipsum..</p>
          </div>
        </div>
      </div>

    <div class="clearBoth" >&nbsp;</div>
  </div>
  <!-- end #content --> 

<?php
  PrintHtmlSidebar( $_SESSION['login']['user'] );
  PrintHtmlFooter( ); 
?>
