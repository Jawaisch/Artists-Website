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
		
  $AllImages = GetAllPics( KWS_DB_Connect( 'gast' ) );

  function GalleryView( $AllImages )
  {
	  $SID = session_id();
	  foreach( $AllImages AS $ImageNotes )
	  {
		$bid = $ImageNotes['Bild_ID'];
		$btitle =$ImageNotes['Titel'];
		$bheight=$ImageNotes['Hoehe'];
		$bwidth=$ImageNotes['Breite'];
		$bprice=$ImageNotes['VK_Preis'];
		$bartist=$ImageNotes['KName'];
		$kid=$ImageNotes['Kuenstler_ID'];
		

echo <<<EO_TOP
	  <div class="gallery_content">
		<div class="image">
			<img src="art-images/small/$bid.png" alt="$btitle" />
		</div>
		<div class="image_notes">
		<h3>$btitle</h3>
		<p><span class="description">Künstler:</span><a href="#">$bartist</a></p>
		<p><span class="description">Größe:</span>$bheight mm x $bwidth mm</p>		
		<p><span class="description">Kaufspreis:</span>$bprice €</p>
		<p>
		<a href="gross_bild.php?kws=$SID&amp;bid=$bid">Genauer betrachten</a>
		</p>
		</div>
	  </div>

EO_TOP;
	  }


  }

?>

  <div id="content">
  
    <h2>Gallery</h2>
		<?php GalleryView($AllImages) ?>
    <div class="clearBoth" >&nbsp;</div>

  </div>
  <!-- end #content --> 

<?php
  /*#########################################################################
          ENDE DES CONTENTS
    #######################################################################*/

  PrintHtmlSidebar( $_SESSION['login']['user'], SID );
  PrintHtmlFooter( SID);
