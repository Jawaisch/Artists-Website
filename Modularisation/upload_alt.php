<?php
  error_reporting( E_ALL );


  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );   
  //include_once( "./includes/bild.inc");
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS upload.php
    #######################################################################*/
?>
  <h1>Upload eines Bildes</h1>
  <?php
    DebugArr($_SESSION);
  ?>
    <?php echo '<form  action="./upload.php?'.SID.'" method="post" enctype="multipart/form-data" >'; ?>
		<div id="Eingabe">  
			<label for="bild" >Bild:</label>
			<input type="file" name="bild" id="bild" 
			       accept="image/*" size="80" /><br>
      Titel: <input type="text" name="title"><br>
      Höhe: <input type="text" name="hoehe"><br> cm
      Breite: <input type="text" name="breite"><br>
      Maltechnik: <input type="text" name="mal_technik"><br>
      Genre: 
      <select id="genre" name="genre_id">
        <option value="" selected="selected">bitte wählen</option>

        <option value="101">Abstrakte Malerei</option>
        <option value="102">Amerikanische Malerei</option>
        <option value="103">Barock Malerei</option>
        <option value="104">Biedermeier</option>
        <option value="105">Dadaismus</option>

        <option value="106">Digitale Kunstbilder</option>
        <option value="107">Expressionismus</option>
        <option value="108">Futurismus</option>
        <option value="109">Barock Malerei</option>
        <option value="110">Futurismus</option>

        <option value="111">Klassische Moderne</option>
        <option value="112">Klassizismus</option>
        <option value="113">Kubismus</option>
        <option value="114">Manierismus</option>
        <option value="115">Moderne Kunst</option>

        <option value="116">Naive Malerei</option>
        <option value="117">Pointillismus</option>
        <option value="118">Pop Art Kunst</option>
        <option value="119">Realismus</option>
        <option value="120">Renaissance</option>

        <option value="121">Rokoko</option>
        <option value="122">Romantik</option>
        <option value="123">Suprematismus</option>
        <option value="124">Surrealismus</option>
        <option value="125">Symbolismus</option>

        <option value="126">Viktorianische Malerei</option>
        <!--<option value="127">Fotorealismus</option>
        <option value="128">Tonalismus</option>
        <option value="129">Intimismus</option>-->
        <option value="130">Fotorealismus</option>

        <option value="131">Tonalismus</option>
        <option value="132">Intimismus</option>
        <option value="133">Paysage intime</option>
        <option value="134">Fauvismus</option>
        <option value="135">Kindermimikry</option>
      </select><br>
      Preis: <input type="text" name="price" value="bspw.: 29.29">  €<br>

		</div>
    <input type="submit" name="submit" value="Submit" />
    <input type="reset" value="Reset" />
  </form>

  
<?php 
//Fehler?
if ( isset($_POST['submit']) )
{
  $con = mysqli_connect("localhost","kws_kuenstler","kws_kuenstler","19ss_tedk4_kws");
  $sql_abfrage = "START TRANSACTION";
  mysqli_query($con, $sql_abfrage );
  $sql_abfrage = "INSERT INTO bild (User_ID, Kuenstler_ID, Mal_Technik, Titel, Hoehe, Breite, VK_Preis, Einstell_Zeitstempel, Einstell_IP, Kauf_Zeitstempel, Kauf_IP, Resv_Zeitstempel) VALUES
                              (NULL,'".$_SESSION['login']['KID']."','".$_POST['mal_technik']."','".$_POST['title']."',".$_POST['hoehe'].",".$_POST['breite'].",".$_POST['price'].",CURRENT_TIMESTAMP(),'".$_SERVER['REMOTE_ADDR']."',NULL,NULL, NULL)";
  mysqli_query($con, $sql_abfrage );
  DebugArr($con);
  $last_insert_id = mysqli_insert_id($con);
  $sql_abfrage = "INSERT INTO eingeordnet (Bild_ID, Genre_ID) VALUES
                                          ( LAST_INSERT_ID(),'".$_POST['genre_id']."')";
  mysqli_query($con, $sql_abfrage );
  DebugArr($con);
  
  echo 'last insert id ='. $last_insert_id  ;

  /* ersteinmal eine Testausgabe, was kommt an ... */
  
  echo "<br>POST";
  DebugArr($_POST);
  echo "FILES";
  DebugArr($_FILES);
  echo "SESSION";
  DebugArr($_SESSION); 

	// Datei merken
	$orig_file = $_FILES['bild']['tmp_name'];
	if ( $_FILES['bild']['error']!= 0 )
	{
    $target='./upload.php?'.SID.'&err='.$_FILES['bild']['error'];
    header("Location: $target");
	}

	$file_info = getimagesize($orig_file);
  if ( !empty($file_info) )
  {      
    DebugArr($file_info);
  }	
	else
	{    
    //header("Location: ./upload.php?'.SID.'&err=10");		
    die("Fehler: Bitte wählen Sie ein zulässiges Dateiformat<br>Zulässige Dateiformate: .jpg; .png; .gif");
		// besser: Umlenkung auf eine Fehlerseite
	}

	/* ersteinmal alle Originaldaten merken und ausgeben */
	// format: landscape oder portrait
	$format = ($file_info[0] > $file_info[1])?"l":"p";

	//haben wir ein akzeptables format?
  // das wäre: jpg, gif oder png
  
	switch ( $file_info[2] )
	{
		// abhängig vom Dateityp ein image (rohdaten) erstellen
    case 1 : // gif erkannt
             $orig_img = ImageCreateFromGIF($orig_file);
             $file_ok = TRUE;
             break;
		case 2 : // jpg erkannt
             $orig_img = ImageCreateFromJPEG($orig_file);
             $file_ok = TRUE;
             break;
		case 3 : // png erkannt
             $orig_img = ImageCreateFromPNG($orig_file);
             $file_ok = TRUE;
             break;
    default: $file_ok = FALSE;
             //header("Location: ./upload.php?'.SID.'&err=11"); 
             echo "\n<div><b>falsches Format</b> ".
			            "Bitte nur gif, jpg oder png </div>";
						 
  }
  if($file_ok === TRUE)
  {
    $sql_abfrage = "COMMIT";
    mysqli_query($con, $sql_abfrage ); 
    // Jetzt gibt es ein image in den originalgrößen

    // neue images in den wunschgrößen vorbereiten
    $bildname   = $last_insert_id.".png" ;
    $dest_big   = "./art-images/big/";
    $dest_small = "./art-images/small/";
    define("BIG_SIZE",600);
    define("SMALL_SIZE",300);

    // abhängig vom Format:
    if ($format == "l")
    {
      $new_width_b  = BIG_SIZE ;
      $new_width_s  = SMALL_SIZE;
      $new_height_b = BIG_SIZE*$file_info[1]/$file_info[0];
      $new_height_s = SMALL_SIZE*$file_info[1]/$file_info[0];
    }
    else
    {
      $new_height_b = BIG_SIZE;
      $new_height_s = SMALL_SIZE;
      $new_width_b  = BIG_SIZE*$file_info[0]/$file_info[1];
      $new_width_s  = SMALL_SIZE*$file_info[0]/$file_info[1];
    }
    // neue - leere - images erstellen
    $big_img        = ImageCreateTrueColor($new_width_b, $new_height_b );
    $small_img      = ImageCreateTrueColor($new_width_s, $new_height_s );    
    /*
      ImageCopyResized( zielbild                  , quellbild,
                        ziel_x_start, ziel_y_start, quell_x_start, quell_y_start,
                        ziel_width  , ziel_height,  quell_width,   quell_height
                        );
    */
    ImageCopyResized( $big_img, $orig_img,
                      0,0,      0,0,
                      $new_width_b,  $new_height_b,
                      $file_info[0], $file_info[1]  );
    ImageCopyResized( $small_img, $orig_img,
                      0,0,      0,0,
                      $new_width_s,  $new_height_s,
                      $file_info[0], $file_info[1]  );   
    // jetzt immer als png abspeichern:
    ImagePNG( $big_img,   $dest_big.$bildname   );
    ImagePNG( $small_img, $dest_small.$bildname );    
    // und noch aufräumen
    ImageDestroy($orig_img); 
    ImageDestroy($big_img); 
    ImageDestroy($small_img);     
    ?>
    <div>
      <h2>Bilder <i>resized</i></h2>
      <!--<img src="<?php echo $dest_big.$bildname;?>" alt="grosses bild" />-->
      <img src="<?php echo $dest_small.$bildname;?>" alt="kleines bild" />
    </div>
    <!--
    <div>
      <h2>Bilder <i>resampled</i></h2>
      <img src="<?php echo $dest_big."smp_".$bildname;?>" alt="grosses bild" />
    </div>
    -->
    <?php    
  }
  else
  {
    $sql_abfrage = "ROLLBACK";
    mysqli_query($con, $sql_abfrage );  
  }
  mysqli_close($con);  
}
  /*#########################################################################
          ENDE DES CONTENTS upload.php
    #######################################################################*/

  PrintHtmlSidebar( $_SESSION['login']['user'], SID );
  PrintHtmlFooter( SID ); 
?>
