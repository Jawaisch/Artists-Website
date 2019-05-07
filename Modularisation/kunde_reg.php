<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );
  include_once( "./includes/inputCheck.inc" );
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = "./profil.php";
  // CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  // $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/
?>

<?php

/*****************************************************************************
    Anforderungsliste
*****************************************************************************/
  $Data_Reqs = array(
    'Login'     => array( 'mand' => True, 
                          'type' => 'string',
                          'fname'=> 'htmlentities',
                          'check_is_unique' => 'login_unique'),
    'Passwort'  => array( 'mand' => True, 
                          'type' => 'string'),
    'Anrede'    => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Titel'     => array( 'mand' => False, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Vorname'   => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Nachname'  => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'PLZ'       => array( 'mand' => True, 
                          'type' => 'int', 
                          'fname' =>'abs',
                          'regex' => 'check_plz'),
    'Ort'       => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Strasse'   => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'HausNr'    => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Email'     => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities'),
    'Telefon'   => array( 'mand' => True, 
                          'type' => 'string', 
                          'fname' =>'htmlentities')
    );

  function CheckRegFormData( $labels_arr )
  {
    $result = True;
    foreach($labels_arr as $label)
    {
      if (empty($_POST['reg_data_arr'][$label]))
        $result = False;
    }
      return $result;
  }

/* ************************************************************************************
			@function InsertNewUser( $dbconn )

			@brief: Fügt neuen Benutzer in die DB ein (Neue Anmeldung)

			@para - $dbconn		   Eine Datenbankverbindung der Klasse mysqli

			@return - true im Erfolgsfall
					      sonst false
************************************************************************************ */
  function InsertNewUser( $dbconn )
  {
    //1. ein Objekt der Klasse mysqli_stmt anlegen
    $prepstmt = $dbconn->stmt_init();
    //2.Abfrage mit Platzhalter für Daten zusammenbasteln
    
    $SQLstring =
      " INSERT INTO benutzer (  Login, Passwd, Anrede, Titel, Vorname,
                                Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon,
                                Reg_Zeitstempel, Reg_IP ) 
                VALUES  ( ?, SHA2( ?, 256), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, CURRENT_TIMESTAMP, ?)";
  
    // Abfrage an den DB-Server abschicken

    // 3. Prepared Statement auf dem DB-Server vorbereiten
    $OK = $prepstmt->prepare( $SQLstring );
    
    // Abfrage erfolgreich?
    
    if($OK === false)
    {
      echo "\n <div class=\"error\">".
         "\n <b>Abfrage fehlgeschlagen!</b>".
         "\n <div>".$SQLstring."</div>".
         "\n <div>". $prepstmt->errno." : ".$prepstmt->error."<\div>".
         "</div>";

      die("DB-Problem - Abbruch");
    }

    //4. Daten an die Parameter binden
    $type = "ssssssissssss";
    $params = array(&$Login, &$Passwort, &$Anrede, &$Titel, 
                    &$Vorname, &$Nachname, &$PLZ, &$Ort, &$Strasse, 
                    &$HausNr, &$Email, &$Telefon, &$Reg_IP );

    $OK1 = call_user_func_array(array($prepstmt, "bind_param"), array_merge(array($type), $params));

    //5. Parameter setzen
    foreach($_POST['reg_data_arr'] as $item => $value)
    {
      ${$item} = $value;
    }
    
    // IP-Adresse ermitteln
    // Verwendet der Benutzer einen Proxy-Server
    if ( !isset($_SERVER['HTTP_X_FORWARDED_FOR']) ) 
    {
      $Reg_IP = $_SERVER['REMOTE_ADDR'];
    }
    else 
    {
      $Reg_IP = $_SERVER['HTTP_X_FORWARDED_FOR'];
    }
 
    //5. Diese Parameter anwenden
    $OK2 = $prepstmt->execute();
    if($OK2 === false)
    {
      echo "\n <div class=\"error\">".
         "\n <b>Abfrage fehlgeschlagen!</b>".
         "\n <div>".$SQLstring."</div>".
         "\n <div>". $prepstmt->errno." : ".$prepstmt->error."<\div>".
         "</div>";

      die("DB-Problem - Abbruch");
    }

    $prepstmt->close(); //abräumen nach getaner Arbeit
    return $OK2;
  } 

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/
    
  echo"<div id=\"content\">";
  
  if(isset($_POST['submit']) && $_POST['submit'] == "Absenden")
  { 
    // Überprüfen ob alle Felder ausgefüllt wurden und was eingegeben wurde
    $dbconn = KWS_DB_Connect("bearbeiter"); // Datenbankverbindung
    if( check_input( $_POST['reg_data_arr'], $Data_Reqs, $_SESSION['input_data'], $dbconn ) )
    {
      $dbconn = KWS_DB_Connect("reg"); // Datenbankverbindung
      if( InsertNewUser( $dbconn ) )
      { // Erfolgsfall
        $_SESSION['error']['errno']=15;
        header('Location: ./login.php?'.SID);
        die("header?!");
      }
      else
      { // Insert fehlgeschlagen
        $_SESSION['error']['errno']=14;
      }
    }
    else 
    { // Es fehlen Pflichteingaben
      $_SESSION['error']['errno']=12;
    }
  }

  DebugArr( $_SESSION );
  DebugArr( $_POST );
  $dbconn = KWS_DB_Connect("bearbeiter");
  var_dump( login_unique( "Pinsel", $dbconn ) );
  //$_SESSION['input_data'][$label]['err']

  // Wurde ein Fehler übergeben?
  ErrorOccurred( );
  echo "\n    <form action=\"./kunde_reg.php?".SID."\" method=\"post\">\n";
 
  ?>
      <div class="form_container">
        <h1>Regestrieren</h1>
        <p>Bitte füllen Sie dieses Formular aus, um ein Konto als Kunde zu erstellen.</p>
        <hr />
  <?php

        $labels_arr = array("Login", "Passwort", "Anrede", "Titel", 
                    "Vorname", "Nachname", "PLZ", "Ort", "Strasse", 
                    "HausNr", "Email", "Telefon");

        foreach($labels_arr as $label)
        {
          //echo "\n        <label ><b>".$label."</b></label>";
          echo "\n        <p class=\"label\"><span class=\"description\"><label ><b>".$label."</b></label>";
          if(isset( $_SESSION['input_data'][$label]['err'] ))
          {
            echo"</span>".$_SESSION['input_data'][$label]['err']."</p>";
          }
          else
          {
            echo"</span>&nbsp;</p>";
          }
          if($label == "Passwort" )
          {
            echo "\n        <input type=\"password\" name=\"reg_data_arr[$label]\" value=\"";
          }
          else
          {
            echo "\n        <input type=\"text\" name=\"reg_data_arr[$label]\" value=\"";
          }
          if(isset( $_POST['reg_data_arr'][$label] )) 
          { 
            //echo $_SESSION['input_data'][$label]['err'];
            echo $_POST['reg_data_arr'][$label]; 
          }
          echo "\" />\n";      
        }
        /*
        <label ><b>Login</b></label>
        <input type="text" name="reg_data_arr[Login]" value="<?php if(isset($_POST['reg_data_arr']['Login'])) { echo $_POST['reg_data_arr']['Login']; } ?>" />

        <label ><b>Passwort</b></label>
        <input type="password" name="reg_data_arr[Passwd]" />

        <label ><b>Anrede</b></label>
        <input type="text" name="Anrede" />

        <label ><b>Titel</b></label>
        <input type="text" name="Titel" />

        <label ><b>Vorname</b></label>
        <input type="text" name="Vorname" />

        <label ><b>Nachname</b></label>
        <input type="text" name="Nachnamet" />

        <label ><b>PLZ</b></label>
        <input type="text" name="PLZ" />

        <label ><b>Ort</b></label>
        <input type="text" name="Ort" />

        <label ><b>Strasse</b></label>
        <input type="text" name="Strasse" />

        <label ><b>HausNr.</b></label>
        <input type="text" name="HausNr." />

        <label ><b>Email</b></label>
        <input type="text" name="Email" />

        <label ><b>Telefon</b></label>
        <input type="text" name="Telefon" />
        */
        ?>
        <hr />
        <p>Mit der Erstellung eines Kontos erklären Sie sich mit unseren <a href="agb.php?<?php echo session_id();?>">AGBs </a>einverstanden.</p>
  
        <input type="hidden" name="<?php echo session_name(); ?>" value="<?php echo session_id();?>" />

        <div class="buttonrow">
          <input type="submit" name="submit" value="Absenden" />
          <input type="reset" value="Zurücksetzen" />
        </div>
      </div>
    </form>

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