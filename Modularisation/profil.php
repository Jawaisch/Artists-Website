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
      function GetArtCounts( $dbconn )
      {
        // Abfrage ohne Perpared_Statements
        $SQL_String1 = " SELECT    COUNT(bild.Bild_ID) AS offers  
                         FROM      bild JOIN kuenstler using (Kuenstler_ID)
                         WHERE     bild.Kuenstler_ID = ".$_SESSION['login']['KID'];

        $SQL_String2= "  SELECT    COUNT(bild.Bild_ID) AS sold  
                         FROM      bild JOIN kuenstler using (Kuenstler_ID)
                         WHERE     bild.Kuenstler_ID = ".$_SESSION['login']['KID']."
                                   AND bild.User_ID IS NOT NULL";
          
        // 1. Abfrage an DB-Server senden
        $result_handle = $dbconn->query($SQL_String1);

        // 1. Abfrage auf Erfolg Ueberpruefen
        if($result_handle === false)
        {
          echo "\n <div class=\"error\">".
             "\n  <b>Abfrage fehlgeschlagen!</b>".
             "\n  <div>".$SQL_String1."</div>".
             "\n  <div>". $dbconn->errno." : ".$dbconn->error."<\div>".
              "</div>";

          die("DB-Problem - Abbruch");
        }
        else
        {
          $offers_arr = array();  // ein leeres Array initialisieren!

          $ds = $result_handle->fetch_assoc();
          $offers_arr[0] = $ds['offers'];
        }

        // 2. Abfrage an DB-Server senden
        $result_handle = $dbconn->query($SQL_String2);

        // 2. Abfrage auf Erfolg Ueberpruefen
        if($result_handle === false)
        {
          echo "\n <div class=\"error\">".
             "\n  <b>Abfrage fehlgeschlagen!</b>".
             "\n  <div>".$SQL_String2."</div>".
             "\n  <div>". $dbconn->errno." : ".$dbconn->error."<\div>".
              "</div>";

          die("DB-Problem - Abbruch");
        }
        else
        {
          $ds = $result_handle->fetch_assoc();
          $offers_arr[1] = $ds['sold'];
        }
        return $offers_arr;
      }

      function GetUserBuys( $dbconn )
      {
        // Abfrage ohne Perpared_Statements
        $SQL_String = " SELECT    COUNT(bild.Bild_ID) AS Anzahl,  
                                  bild.Titel,
                                  bild.Kauf_Zeitstempel AS `gekauft am`,
                                  bild.VK_Preis AS Preis,
                                  bild.Hoehe AS Höhe,
                                  bild.Breite
                        FROM      bild JOIN benutzer using (User_ID)
                        WHERE     bild.User_ID = ".$_SESSION['login']['UID']."
                        ORDER BY  bild.Titel";
          
        // Abfrage an DB-Server senden
        $result_handle = $dbconn->query($SQL_String);

        // Abfrage auf Erfolg Ueberpruefen
        if($result_handle === false)
        {
          echo "\n <div class=\"error\">".
               "\n  <b>Abfrage fehlgeschlagen!</b>".
               "\n  <div>".$SQL_String."</div>".
               "\n  <div>". $dbconn->errno." : ".$dbconn->error."<\div>".
                  "</div>";

          die("DB-Problem - Abbruch");
         }
         else
         {
          $user_buys_arr = array(); // ein leeres Array initialisieren!

          while( $ds = $result_handle->fetch_assoc() )
          {
            $user_buys_arr[] = $ds;
          }
        }
        return $user_buys_arr;
      }

      function GetArtistData( $dbconn )
      {
        // Abfrage ohne Perpared_Statements
        $SQL_String = " SELECT    kuenstler.Kname AS Künstlername,
                                  kuenstler.IBAN,
                                  kuenstler.BIC,
                                  kuenstler.Vita
                        FROM      kuenstler
                        WHERE     kuenstler.User_ID = ".$_SESSION['login']['UID'];
          
        // Abfrage an DB-Server senden
        $result_handle = $dbconn->query($SQL_String);

        // Abfrage auf Erfolg Ueberpruefen
        if($result_handle === false)
        {
          echo "\n <div class=\"error\">".
               "\n  <b>Abfrage fehlgeschlagen!</b>".
               "\n  <div>".$SQL_String."</div>".
               "\n  <div>". $dbconn->errno." : ".$dbconn->error."<\div>".
                  "</div>";

          die("DB-Problem - Abbruch");
         }
         else
         {
          $artist_data_arr = array(); // ein leeres Array initialisieren!

          while( $ds = $result_handle->fetch_assoc() )
          {
            $artist_data_arr[] = $ds;
          }
        }
        return $artist_data_arr;
      }

    echo "<div class=\"split left\">";
    echo "  <h3>Ihr User Profil</h3>";
    echo    HtmlUserAccount( GetUserData( $dbconn ) );  
    echo "</div>";

    if ( $_SESSION['login']['user'] == "kuenstler" )
    {
      $ArtCounts = GetArtCounts( $dbconn );
      $offer = $ArtCounts[0];
      $sold  = $ArtCounts[1];
      echo "<div class=\"split right\">";
      echo "  <h3>Ihr Künstler Profil</h3>";
      echo    HtmlUserAccount( GetArtistData( $dbconn ) );
      echo    PrintHtmlCards( $offer, $sold, SID );
      echo "</div>";
    }
    echo "<div class=\"clearBoth\" >&nbsp;</div>";

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
