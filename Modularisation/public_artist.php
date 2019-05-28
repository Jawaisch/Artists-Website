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
					  "		  kuenstler.Kname, ".
					  "		  kuenstler.Vita ".
					  "FROM	  kuenstler ".
			          "WHERE  kuenstler.Kuenstler_ID = ?";
					  

					  /*"	  bild.Bild_ID, ".
					  "		  bild.Mal_Technik, ".
					  "		  bild.Titel, ".
					  "       bild.Hoehe, ".
					  "       bild.Breite, ".
					  "       bild.VK_Preis, ".
					  "       bild.Einstell_Zeitstempel, ".
					  "		  genre.Genre_ID, ".
					  "		  genre.Name ".
					  INNER JOIN bild USING (Kuenstler_ID) ".
					  "				  INNER JOIN eingeordnet USING (Bild_ID) ".
					  "				  INNER JOIN genre USING (Genre_ID) ".
					  " ORDER BY bild.Einstell_Zeitstempel DESC";*/

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

	function DisplayPublicData($PublicData)
	{
	echo "<div class=\"PublicArtistInfo\">"."\n".
			 "<div class=\"PublicProfilPic\">".
			 "<img src=\"art-images/small/752.png\" alt=\"Profilbild\"/>".
			 "</div>".
			 "<div class=\"PublicArtistVita\">".
			 "  <h3>K&uuml;nstler-Profil von ".$PublicData[0]['Kname']."</h3>"."\n".
			 "<p>".$PublicData[0]['Vita']."</p> ".
			 "</div>".
		
		 "</div>"."\n";

	}
	

  
?>

  <div id="content">
  <?php
		ErrorOccurred( );
		$PublicData = GetPublicArtistData($dbconn, $_GET['kid']);
		DisplayPublicData( $PublicData);
		
		

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
