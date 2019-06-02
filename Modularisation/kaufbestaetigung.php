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
    
    $con = mysqli_connect("localhost","kws_kunde","kws_kunde","19ss_tedk4_kws");
    $sql_abfrage = "UPDATE  bild
                    SET     bild.Kauf_Zeitstempel = CURRENT_TIMESTAMP(),
                            bild.User_ID = '".$_SESSION['login']['UID']."',
                            bild.Kauf_IP = '".$_SERVER['REMOTE_ADDR']."'
                    
                    WHERE Bild_ID IN ('".$_SESSION['cartimpl']."')";
    // $_SESSION['login']['UID']
    $res = mysqli_query($con,$sql_abfrage);
    if ($res==true)    
    ?>

    <div class="success">
      <br />Kauf abgeschlossen<br /><br />
    </div>

    Bitte überweisen Sie den Betrag von <?php echo $_POST['purchase_sum'] ?>€ auf das folgende Konto:<br />
    <pre>
    Zahlungsempfänger: Art Tick GmbH, Musterstr. 5 in 10243 Musterhausen    
    Bank: MusterFinance
    IBAN: CH82 0900 0000 6035 9126 4    
    Verwendungszweck: art_nr <?php echo $_SESSION['cart'][0] ?>
    </pre>
    <br />
    <?php $_SESSION['cart'] = NULL;  $_SESSION['cartimpl'] = NULL ; ?>   

	<div class="clearBoth" >&nbsp;</div>
  </div> 
<?php
  /*#########################################################################
          ENDE DES CONTENTS
    #######################################################################*/

  PrintHtmlSidebar( $_SESSION['login']['user'], SID );
  PrintHtmlFooter( SID ); 
?>
