<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" ); 
  include_once( "./includes/inputCheck.inc" );
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/
  $Data_Reqs = array(
        'title'      => array(  'mand' => True, 
                                'type' => 'string',
                                'label' => 'Titel', 
                                'index' => 'title',
                                'fname'=> 'htmlentities'),

        'hoehe'       => array( 'mand' => True, 
                                'type' => 'int',
                                'label' => 'Höhe in mm', 
                                'index' => 'hoehe',           
                                'fname' =>'htmlentities'),
                                //'regex' => 'check_hoehe'
                  
        'breite'      => array( 'mand' => True, 
                                'type' => 'int',
                                'label' => 'Breite in mm', 
                                'index' => 'breite',
                                'fname' =>'htmlentities'),
                                //'regex' => 'check_breite'),
                  
        'mal_technik' => array( 'mand' => True, 
                                'type' => 'string',
                                'label' => 'Maltechnik', 
                                'index' => 'mal_technik',
                                'fname' =>'htmlentities'),

        'genre_id'   => array(  'mand' => True, 
                                'type' => 'int',
                                'label' => 'Genre', 
                                'index' => 'genre_id',
                                'fname'=> 'abs',                              
                                'select_list' => 'GetGenreArr'),
                                //'regex' => 'check_genre'),
                                
        'preis'      => array(  'mand' => True, 
                                'type' => 'int',
                                'label' => 'Preis in €', 
                                'index' => 'preis',
                                'fname'=> 'abs'),
   );

  echo"    <div id=\"content\">";

  if(isset($_POST['submit']) && $_POST['submit'] == "Absenden")
  { 
    // Überprüfen ob alle Felder ausgefüllt wurden und was eingegeben wurde    
    if( check_input( $_POST['reg_data_arr'], $Data_Reqs , $_SESSION['input_data'] ) )
    {      
      $upload_error  = image_upload();
      if( $upload_error == 0 )
      { // Upload erfolgreich
        $_SESSION['error']['errno'] = 18;
		PrintPicPreview( $_SESSION['bild']['id'] );
      }
    }
    else 
    { // Es fehlen Pflichteingaben
      $_SESSION['error']['errno']=12;
    }
  }

  // Wurde ein Fehler übergeben?
  ErrorOccurred( );
   
  // Formular vorbereiten
  $header = "Bild hochladen";
  $description= "Bitte wählen Sie eine Bilddatei im Format: jpg, png oder gif aus.";
  $action = "./upload.php?";

  // Formular ausgeben
  HtmlRegForm( $Data_Reqs, $header, $description, $action, null, $agbs=false, $upload=true );

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
