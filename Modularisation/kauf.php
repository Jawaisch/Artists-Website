<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  if( !isset($_SESSION['cart']) )
  {
    $_SESSION['cart'] = array();
  }

  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung

  if(isset($_SESSION['cart']) && !empty($_SESSION['cart']))
  {
    $Cart = implode(',',$_SESSION['cart']);
    $Cart_arr = Clean_Current_Cart( $dbconn , $Cart );
    $_SESSION['cart'] = $Cart_arr;

  }
    $_SESSION['Max_Cart'] = sizeof($_SESSION['cart']);
    
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/
?>

  <div id="content">
  <?php
    if(empty($_POST['purchase_reload'])){   // prüfen ob schon hier gewesen
    //$cart = array(1421,1506,1709, 1502);    //  TO_DO:  Schutz vor SQL Injection:  $cart vor fremdem Imput schützen
    if(!empty($_POST['remove']))
      unset($_SESSION['cart'][array_search($_POST['remove'], $_SESSION['cart'])]);
    echo
      '<br>' .
      '<h1> Ihr Einkaufswagen</h1>' .
      '<br>' .
      '<form id="kaufen" action="kaufbestaetigung.php?'.SID.'" method="post" >';

                  DebugArr($_POST);
                  DebugArr($_SESSION);
                  echo '<br>';

                  $_SESSION['cartimpl'] = implode("','",$_SESSION['cart']);
                  $con = mysqli_connect("localhost","kws_kunde","kws_kunde","19ss_tedk4_kws");

                  mysqli_query($con, "SET NAMES 'utf8'");
                  $sql_abfrage = "SELECT  bild.Titel,
                                          bild.Bild_ID,
                                          bild.VK_Preis,
                                          kuenstler.Kname
                                  FROM bild LEFT OUTER JOIN kuenstler USING (Kuenstler_ID)
                                  WHERE Bild_ID IN ('".$_SESSION['cartimpl']."')";
                  $res = mysqli_query($con,$sql_abfrage);
                  //echo "<b>".$sql_abfrage."</b>";

                  echo '<table  class ="table">';
                  echo '<tr>
                              <th>Position</th>
                              <th>Titel</th>
                              <th>Künstler</th>
                              <th>Bild_ID</th>
                              <th>Vorschau</th>
                              <th>Preis</th>
                              <th>Artikel entfernen</th>
                    </tr>';
                    $img_index = 1;
                    $sum = 0;

                        while ($dsatz = mysqli_fetch_assoc($res))
                      {
                        echo "<tr>";
                        echo "<td>" . $img_index . "</td>";
                        echo "<td>" . $dsatz["Titel"] . "</td>";
                        echo "<td>" . $dsatz["Kname"] . "</td>";
                        echo "<td>" . $dsatz["Bild_ID"] . "</td>";
                        //echo  '<option value="'. $i .'">'. $i .'</option>';
                        echo '<td><img src="art-images/small/' . $dsatz["Bild_ID"] . '.png" alt="missing image ' . $dsatz["Titel"] . '"width="90" height="60"> </td>';
                        echo  "<td>" . $dsatz["VK_Preis"] . ' €' . "</td>";
                        echo '<td>' . '<div style="">' .
                        //'<input type="submit" name="remove_' . $dsatz["Bild_ID"] . '" value="entfernen" form_id="remove">' .
                        '<button name="remove" value="' . $dsatz["Bild_ID"] . '" form="remove">entfernen</button>' .
                        '</div>' . "</td>";
                        echo "</tr>";
                        $img_index++;
                        $sum += $dsatz["VK_Preis"];
                      }
                      echo "<tr><td></td><td></td><td></td><td></td><td></td><td>Summe: $sum €</td><td></td></tr>";
                  echo "</table>";
                  mysqli_close($con);
                  echo '<input type="hidden" name="purchase_reload" value="true" form="kaufen" />'.
                       '<input type="hidden" name="$sname" value='.SID.' />'.
                       '<input type="hidden" name="purchase_sum" value='.$sum.' />'.


              '<br>' .
              '<button type="submit" style="    margin: 0em;
                                                  padding: .2em .5em;
                                                  background-position: .5em center;
                                                  background-repeat: no-repeat;
                                                  float: right;">
                      jetzt kaufen
              </button>'.
      '</form>' .
      '<form id="remove" action="kauf.php?'.SID.'" method="post">'.
      '</form>';
    }
    else{
      header('"Location: kaufbestaetigung.php?'.SID.'"');
    }
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
