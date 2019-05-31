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
  function GetGenreInfo( $dbconn, $gen )
  {
    $prepstmt = $dbconn->stmt_init();

    $SQL_String = " SELECT  genre.Name,".
                  "         genre.Beschreibung".
                  " FROM    genre ".
                  " WHERE   genre.Genre_ID = ? ";

    // Abfrage an DB-Server senden
    $result_handle = $prepstmt->prepare( $SQL_String );

    // Abfrage auf Erfolg Ueberpruefen
    if($result_handle === false)
    {
      ErrorHandling($SQL_String, $dbconn);
    }
    else
    { 
      //4. Daten an die Parameter binden
      $prepstmt->bind_param( "i" ,$gen);

       //5. Diese Parameter anwenden
      $prepstmt->execute();

      $Genre_Note = array();  // ein leeres Array initialisieren!

      $result_handle = $prepstmt->get_result( );

      // fetch-en Spezialfall: ein oder kein Datensatz

      $Genre_Note = $result_handle->fetch_all( MYSQLI_ASSOC );

      if($Genre_Note == NULL)
      {
        $Genre = false;
      }
      else
      {
        $Genre = $Genre_Note;
      }
    }

    $prepstmt->close(); //abräumen nach getaner Arbeit
    
    return $Genre;
  }

  function DisplayGenreInfo($GenreInfo)
  { 
    $Gname = $GenreInfo[0]['Name']; 
    
    // Überprüfen ob bereits eine HTML-Formatierung im String vorliegt
    if ( preg_match('<p>',$GenreInfo[0]['Beschreibung'])  === false ) 
        {
        $Ginfo = "<p>".$GenreInfo[0]['Beschreibung']."</p>";  
        }
        else
        {      
        $Ginfo = $GenreInfo[0]['Beschreibung'];
    }
    echo <<<GENREBOX
       <div class="Genre_Info">
         <h3>$Gname</h3>
          $Ginfo
       </div>
GENREBOX;
  }
  
?>

  <div id="content">
  <?php
  $GenInfo = GetGenreInfo( $dbconn, $_GET['gen'] );
  DisplayGenreInfo($GenInfo);

  ?>

  
    <!-- Hier kommt euer content rein! -->

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
