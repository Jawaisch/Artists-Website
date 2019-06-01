<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf

  if($_SESSION['login']['user'] == 'gast')
  {
    $_SESSION['referer'] = "gross_bild.php?bid=".$_GET['bid'];
  }
  else
  {
    $_SESSION['referer'] = "gross_bild.php?".SID."&bid=".$_GET['bid'];
  }

  if( $_SESSION['login']['user'] === 'kuenstler' || $_SESSION['login']['user'] === 'kunde')
  {
  CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!
  }
  if( !isset($_SESSION['cart']) )
  {
  $_SESSION['cart'] = array();
  }
  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );
  $SingleInfo=GetMorePicInfo( $dbconn, $_GET['bid'] );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/

 function PrintSinglePic( $SingleInfo, $BID )
 {
  $bid    = $BID;
  $kid    = $SingleInfo['Kuenstler_ID'];
  $btitle   = $SingleInfo['Titel'];
  $bartist  = $SingleInfo['KName'];
  $bheight  = $SingleInfo['Hoehe'];
  $bwidth   = $SingleInfo['Breite'];
  $bprice   = $SingleInfo['VK_Preis'];
  $bpaint   = $SingleInfo['Mal_Technik'];
  $bgenre   = $SingleInfo['Name'];
  $genid    = $SingleInfo['Genre_ID'];

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
      <p><span class="description">Künstler:</span><a href="public_artist.php?kws=$SID&amp;kid=$kid">$bartist</a></p>
      <p><span class="description">Höhe:</span>$bheight mm</p>
      <p><span class="description">Breite:</span>$bwidth mm</p>
      <p><span class="description">Verkaufspreis:</span>$bprice&euro;</p>
      <p><span class="description">Maltechnik:</span>$bpaint</p>
      <p><span class="description">Genre:</span><a href="./genre.php?kws=$SID&amp;gen=$genid">$bgenre</a></p>
      <p><span class="description">Verfügbarkeit:</span>$bsold</p>
    </div>

EO_SinglePic;
    if( $SingleInfo['Kauf_Zeitstempel'] === NULL && $SingleInfo['Resv_Zeitstempel'] === NULL && (empty($_SESSION['Max_Cart']) || $_SESSION['Max_Cart'] <= 2) &&  (isset($_SESSION['login']['success']) && $_SESSION['login']['success'] === true   ))
    {
      echo <<<EO_Cart_Form
          <form action="gross_bild.php?kws=$SID&amp;bid=$bid" method="post">
            <div> 
              <button name="warenkorb" type="submit" value="Submit">In den Warenkorb</button>
            </div>
          </form>
        </div>
EO_Cart_Form;
    }
    else
      echo "</div>";
 };

 function PicReserve( $dbconn,$bid )
 {
   $SQL_String = "UPDATE bild SET Resv_Zeitstempel = NOW() WHERE bild.Bild_ID=".$bid;

   $result_handle = $dbconn->query($SQL_String);

   // Abfrage erfolgreich?
    
   if($result_handle === false)
   {
    echo "\n <div class=\"error\">".
       "\n <b>Abfrage fehlgeschlagen!</b>".
       "\n <div>".$SQL_String."</div>".
       "\n <div>". $dbconn->errno." : ".$dbconn->error."<\div>".
       "</div>";

    die("DB-Problem - Abbruch");  
    }
 }
?>

  <div id="content">
    <?php
      
      if(isset($_POST['warenkorb']) && $_POST['warenkorb'] === "Submit")
      {
        $_SESSION['Max_Cart'] = sizeof($_SESSION['cart']); 
        if( $_SESSION['Max_Cart'] <= 2) // Überprüft ob der Maximale Inhalt eines Warenkorbs vorhanden ist
        { 
          $_SESSION['cart'][] = $_GET['bid'];
          PicReserve( $dbconn,$_GET['bid'], $Max_Cart );
          header('Location: ./gross_bild.php?'.SID.'&bid='.$_GET['bid']);
        }
        else
        {
          header('Location: ./gross_bild.php?'.SID.'&bid='.$_GET['bid']);
        }
        
      }

      if(isset($_SESSION['cart']) && !empty($_SESSION['cart']))
      {
        $Cart = implode(',',$_SESSION['cart']);
        $Cart_arr = Clean_Current_Cart( $dbconn , $Cart );
        $_SESSION['cart'] = $Cart_arr;
        
      }
        $_SESSION['Max_Cart'] = sizeof($_SESSION['cart']);
    ?>
    
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
