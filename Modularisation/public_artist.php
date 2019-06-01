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

  $kid = $_GET['kid'];

  function GetPublicArtistData($dbconn, $kid)
  { 
     //1. ein Objekt der Klasse mysqli_stmt anlegen
    $prepstmt = $dbconn->stmt_init();

    $SQL_String = "SELECT kuenstler.Kuenstler_ID, ".
                  "       kuenstler.Kname, ".
                  "       kuenstler.Vita ".
                  "FROM   kuenstler ".
                  "WHERE  kuenstler.Kuenstler_ID = ?";

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
      $prepstmt->bind_param( "i" ,$kid);

       //5. Diese Parameter anwenden
      $prepstmt->execute();

      $Public_Artist_Arr = array();  // ein leeres Array initialisieren!

      $result_handle = $prepstmt->get_result( );

      // fetch-en Spezialfall: ein oder kein Datensatz

      $Public_Artist_Arr = $result_handle->fetch_all( MYSQLI_ASSOC );

      if($Public_Artist_Arr == NULL)
      {
        $Public_Artist_Arr = false;
      }         
    }

    $prepstmt->close(); //abräumen nach getaner Arbeit
    
    return $Public_Artist_Arr;
  }

  function GetAllArtistPics( $dbconn, $kid )
  {
    $prepstmt = $dbconn->stmt_init();

    $SQL_String = " SELECT  bild.Bild_ID,".
                  "         bild.Titel".
                  " FROM    bild INNER JOIN Kuenstler USING (Kuenstler_ID)".
                  " WHERE   bild.Kuenstler_ID = ? ".
                  " ORDER BY bild.Einstell_Zeitstempel DESC";

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
      $prepstmt->bind_param( "i" ,$kid);

       //5. Diese Parameter anwenden
      $prepstmt->execute();

      $Public_Artist_Arr = array();  // ein leeres Array initialisieren!

      $result_handle = $prepstmt->get_result( );

      // fetch-en Spezialfall: ein oder kein Datensatz

      $Public_Artist_Arr = $result_handle->fetch_all( MYSQLI_ASSOC );

      if($Public_Artist_Arr == NULL)
      {
        $Public_Artist_Arr = false;
      }         
    }

    $prepstmt->close(); //abräumen nach getaner Arbeit
    
    return $Public_Artist_Arr;
  }


  function DisplayPublicData($PublicData,$PublicPics)
  {
    $SID = session_id();
    $Kname = $PublicData[0]['Kname'];
    $Kvita = $PublicData[0]['Vita'];
    $LastPic = $PublicPics[0]['Bild_ID'];

    echo <<<PUBLIC_CONTENT
        <div class="PublicArtistInfo">
          <div class="PublicProfilPic">
            <img src="art-images/small/$LastPic.png" alt="Profilbild" />
          </div>
          <div class="PublicArtistVita">
            <h3>&Ouml;ffentliches K&uuml;nstler-Profil von $Kname</h3>
            <p>$Kvita</p>
          </div>
        </div>
PUBLIC_CONTENT;


    if(!empty($PublicPics))
    {
      foreach( $PublicPics AS $PicInfo )
      { 
        $bid = $PicInfo['Bild_ID'];
        $btitle = $PicInfo['Titel'];
        
      echo <<<ARTISTPICS
          <div class="gallery_content">
            <div class="image">
              <img src="art-images/small/$bid.png" alt="$btitle"/>
            </div>
            <div class="image_notes">
              <h4>$btitle</h4>
              <p><a href="gross_bild.php?kws=$SID&amp;bid=$bid">Genauer betrachten</a>
              </p>
            </div>
          </div>
ARTISTPICS;
      }
    }

    
  }
    

  
?>

  <div id="content">
  <?php
    ErrorOccurred( );
    $PublicData = GetPublicArtistData($dbconn, $_GET['kid']);
    $PublicPics = GetAllArtistPics($dbconn, $_GET['kid']);
    DisplayPublicData( $PublicData, $PublicPics);
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
