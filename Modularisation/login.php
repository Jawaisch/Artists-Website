<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf
  // CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

  /*#########################################################################
        BEGINN DES CONTENTS
    #######################################################################*/
?>

  <div id="content">
	<?php
	DebugArr($_SESSION);
    ErrorOccurred( );

		if(isset($_POST['submit']) && $_POST['submit'] == "Absenden")
		{	
			// Überprüfen ob alle Felder ausgefüllt wurden und was eingegeben wurde
			if( CheckLoginFormData() )
			{
				$dbconn = KWS_DB_Connect("login"); // Datenbankverbindung
				$uid = GetUidByLogin( $dbconn , $_POST['login'] , $_POST['passwd'] );
				
				if( $uid !== false )
				{
					$_SESSION['login']['UID'] = $uid;
					$_SESSION['login']['success'] = true;
					$dbconn = KWS_DB_Connect("kunde");
					$User_Handle = GetKindOfUser( $dbconn , $uid);
					$_SESSION['login']['user'] = $User_Handle[0];
					if($User_Handle[0] == "kuenstler")
						$_SESSION['login']['KID'] = $User_Handle[1];
					header( 'Location: '.$_SESSION['referer'].'?'.SID );
				}
				else
				{
					$_SESSION['error']['errno']=13;
					header('Location: ./login.php?'.SID);
				}
			}
      else
      {
        $_SESSION['error']['errno']=12;
				header('Location: ./login.php?'.SID);
      }
		}
	?>

	
    <form action="<?php echo $_SERVER['PHP_SELF']?>" method="post">
      <div class="form_container">
        <div class="Input">
          <label for="login">Login:</label>
          <input type="text" name="login" id="login"/>
        </div>

        <div class="Input">
          <label for="passwd">Passwort:</label>
          <input type="password" name="passwd" id="passwd"/>
        </div>

        <input type="hidden" name="<?php echo session_name(); ?>" value="<?php echo session_id();?>" />

        <div class="buttonrow">
          <input type="submit" name="submit" value="Absenden" />
          <input type="reset" value="Zurücksetzen" />
        </div>
      </div>
    </form>

  </div>
  <!-- end #content --> 

<?php
  /*#########################################################################
          ENDE DES CONTENTS
    #######################################################################*/

  PrintHtmlSidebar( $_SESSION['login']['user'], SID );
  PrintHtmlFooter( SID ); 
?>
