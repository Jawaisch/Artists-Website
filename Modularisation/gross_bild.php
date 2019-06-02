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
