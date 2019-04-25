<?php
  error_reporting( E_ALL );
  define( "MYDEBUG", false );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  $Session_ID = session_id();
  // CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], $Session_ID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/
?>

  <div id="content">
  
    <form action="<?php echo $_SESSION['referer']?>" method="session">

        <div class="Input">
          <label for="login">Login:</label>
          <input type="text" name="login" id="login"/>
        </div>

        <div class="Input">
          <label for="passwd">Passwort:</label>
          <input type="password" name="passwd" id="passwd"/>
        </div>

        <div class="buttonrow">
          <input type="submit" name="submit" value="Absenden" />
          <input type="reset" value="Zuruecksetzen" />
        </div>

      </form>

  </div>
  <!-- end #content --> 

<?php
  /*#########################################################################
          ENDE DES CONTENTS
    #######################################################################*/

  PrintHtmlSidebar( $_SESSION['login']['user'], $Session_ID );
  PrintHtmlFooter( $Session_ID ); 
?>

