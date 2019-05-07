<?php
  error_reporting( E_ALL );
  define( "MYDEBUG", false );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  //CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );
  $SingleInfo=GetMorePicInfo( $dbconn, $_GET['bid'] );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/

 function PrintSinglePic( $SingleInfo, $BID )
 {
	$bid		= $BID;
	$btitle		= $SingleInfo['Titel'];
	$bartist	= $SingleInfo['KName'];
	$bheight	= $SingleInfo['Hoehe'];
	$bwidth		= $SingleInfo['Breite'];
	$bprice		= $SingleInfo['VK_Preis'];
	$bpaint		= $SingleInfo['Mal_Technik'];
	$bgenre		= $SingleInfo['Name'];

	if($SingleInfo['Kauf_Zeitstempel'] === NULL) // Überprüft ob das Bild bereits verkauft wurde 
		$bsold = "Verfügbar";
	else
		$bsold = "Bereits verkauft";

	$SID = session_id();
	$SIN = session_name();
	$Self = $_SERVER['PHP_SELF'];

echo <<<EO_SinglePic
	<div class="single_content">
		<div class="big_image">
			<img src="art-images/big/$bid.png" alt="$btitle"/>
		</div>

		<div class="big_image_notes">
			<h2>$btitle</h2>
			<p><span class="description">Künstler:</span>$bartist</p>
			<p><span class="description">Höhe:</span>$bheight mm</p>
			<p><span class="description">Breite:</span>$bwidth mm</p>
			<p><span class="description">Verkaufspreis:</span>$bprice&euro;</p>
			<p><span class="description">Maltechnik:</span>$bpaint</p>
			<p><span class="description">Genre:</span>$bgenre</p>
			<p><span class="description">Verfügbarkeit:</span>$bsold</p>
		</div>

EO_SinglePic;
		if( $SingleInfo['Kauf_Zeitstempel'] === NULL )
		{
			echo <<<EO_Cart_Form
					<form action="übersicht.php?kws=$SID&amp;bid=$bid" method="post">
						<button name="cart" type="submit" value="Submit">In den Warenkorb</button>
						<input type="hidden" name="$SIN" value="$SID" />
					</form>
				</div>
EO_Cart_Form;
		}
		else
			echo "</div>";
			


 }
?>

  <div id="content">
		
		<?php PrintSinglePic($SingleInfo, $_GET['bid'])?>


		<div class="clearBoth" >&nbsp;</div>
  </div>

<?php
  /*#########################################################################
          ENDE DES CONTENTS
    #######################################################################*/

  PrintHtmlSidebar( $_SESSION['login']['user'], SID );
  PrintHtmlFooter( SID ); 
?>
