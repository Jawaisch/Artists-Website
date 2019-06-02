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
  echo '      <div id="content">'."\n";
  
  DebugArr($_SESSION);

  // Wurde ein Fehler übergeben?
  ErrorOccurred( );
 
  $Last3Pics = GetLast3Pics( $dbconn );
  foreach ($Last3Pics as $Pic)
  {
    list($width, $height, $type, $attr) = getimagesize("art-images/small/".$Pic['Bild_ID'].".png");
    $date = preg_split("* *", $Pic['Einstell_Zeitstempel']);

    $output = ''.
  '       <div class="preview">'."\n".
  '         <h2 class="title">'.$Pic['Titel'].'</h2>'."\n".
  '         <p class="meta">Eingestellt von <a href="#">'.$Pic['KName'].'</a> am '.$date[0].' um '.$date[1].' </p>'."\n".
  '         <a href="gross_bild.php?'.SID.'&amp;bid='.$Pic['Bild_ID'].'">'."\n".
  '         <div class="image">'."\n".
  '           <p><img '."\n".
  '             src="art-images/small/'.$Pic['Bild_ID'].'.png"'."\n".
  '             ' .$attr."\n".
  '             alt="'.$Pic['Titel'].'"'."\n".
  '             title="'.$Pic['Titel'].'"'."\n".
  '           /></p>'."\n".
  '         </div>'."\n".
  '         </a>'."\n".
  '         <p class="links"><a href="#top">Seitenanfang</a></p>'."\n".
  '       </div>'."\n";

  echo $output;
  }
  
  echo '    <div class="clearBoth" >&nbsp;</div>'."\n";
  echo '    </div>'."\n";
  echo '    <!-- end #content -->'."\n";

  /*#########################################################################
          ENDE DES CONTENTS
    #######################################################################*/

  PrintHtmlSidebar( $_SESSION['login']['user'], SID );
  PrintHtmlFooter( SID ); 
?>