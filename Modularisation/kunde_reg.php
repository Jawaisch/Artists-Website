<?php
  error_reporting( E_ALL );
  define( "MYDEBUG", false );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  // CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  // $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/
?>

<?php

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

  function GetMaxUid( $dbconn )
  {
    // Abfrage ohne Perpared_Statements
    $SQL_String1 = " SELECT    MAX(User_ID) AS MaxUid  
                     FROM      benutzer";
      
    // Abfrage an DB-Server senden
    $result_handle = $dbconn->query($SQL_String1);

    // Abfrage auf Erfolg Ueberpruefen
    if($result_handle === false)
    {
      echo "\n <div class=\"error\">".
         "\n  <b>Abfrage fehlgeschlagen!</b>".
         "\n  <div>".$SQL_String1."</div>".
         "\n  <div>". $dbconn->errno." : ".$dbconn->error."<\div>".
          "</div>";

      die("DB-Problem - Abbruch");
    }
    else
    {
      $ds = $result_handle->fetch_assoc();
      $MaxUid = $ds['MaxUid'];
    }
    return $MaxUid;
  }

  function InsertRegData( $dbconn, $max_uid )
  {
    //1. ein Objekt der Klasse mysqli_stmt anlegen
    $prepstmt = $dbconn->stmt_init();
    //2.Abfrage mit Platzhalter für Daten zusammenbasteln
    
    $SQLstring =
      " INSERT INTO benutzer (  User_ID, Login, Passwd, Anrede, Titel, Vorname,
                                Nachname, PLZ, Ort, Strasse, HausNr, Email, Telefon,
                                Reg_Zeitstempel, Reg_IP ) 
                VALUES  ( ?, ?, SHA2( ?, 256), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, CURRENT_TIMESTAMP, ?)";
  
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
    $type = "issssssissssss";
    $params = array(&$User_ID, &$Login, &$Passwort, &$Anrede, &$Titel, 
                    &$Vorname, &$Nachname, &$PLZ, &$Ort, &$Strasse, 
                    &$HausNr, &$Email, &$Telefon, &$Reg_IP );

    $OK1 = call_user_func_array(array($prepstmt, "bind_param"), array_merge(array($type), $params));

    //5. Parameter setzen
    $User_ID = $max_uid+1;
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
  $labels_arr = array("Login", "Passwort", "Anrede", "Titel", 
                      "Vorname", "Nachname", "PLZ", "Ort", "Strasse", 
                      "HausNr", "Email", "Telefon");

  $dbconn = KWS_DB_Connect("bearbeiter"); // Datenbankverbindung
  $max_uid = GetMaxUid( $dbconn );

  if(isset($_POST['submit']) && $_POST['submit'] == "Absenden")
  { 
    // Überprüfen ob alle Felder ausgefüllt wurden und was eingegeben wurde
    if( CheckRegFormData( $labels_arr ) )
    {
      $dbconn = KWS_DB_Connect("reg"); // Datenbankverbindung
      if( InsertRegData( $dbconn, $max_uid ) )
      {
        $_SESSION['error']['errno']=15;
        header('Location: ./index.php?'.SID);
      }
      else
      {
        $_SESSION['error']['errno']=14;
       //header('Location: ./kunde_reg.php?'.SID);
      }
    }
    else
    {
      $_SESSION['error']['errno']=12;
      //header('Location: ./kunde_reg.php?'.SID);
    }
  }

  // Wurde ein Fehler übergeben?
  ErrorOccurred( );
  echo" <form action=\"./kunde_reg.php?'.SID\" method=\"post\">";
 
  ?>
      <div class="form_container">
        <h1>Regestrieren</h1>
        <p>Bitte füllen Sie dieses Formular aus, um ein Konto als Kunde zu erstellen.</p>
        <hr />
  <?php

        foreach($labels_arr as $label)
        {
          echo "\n        <label ><b>".$label."</b></label>";
          if($label == "Passwort" )
          {
            echo "\n        <input type=\"password\" name=\"reg_data_arr[$label]\" value=\"";
          }
          else
          {
            echo "\n        <input type=\"text\" name=\"reg_data_arr[$label]\" value=\"";
          }
          if(isset($_POST['reg_data_arr'][$label])) 
          { 
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