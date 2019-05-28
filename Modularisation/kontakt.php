<?php
  error_reporting( E_ALL );

  include_once( "./includes/view.inc" );
  include_once( "./includes/php.inc" );
  include_once( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf
  $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  // Keine Loginprüfung, da auch Gäste eine Nachricht schicken können sollen
  //CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung. Nur auf Seiten die nicht von Gästen gesehen werden dürfen!

  $dbconn = KWS_DB_Connect( $_SESSION['login']['user'] ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'], SID );

/*#########################################################################
      BEGINN DES CONTENTS
  #######################################################################*/    
if(!empty($_POST)){
  if(!empty($_POST['name']) && !empty($_POST['topic']) && !empty($_POST['message'])){
    DebugArr($_POST);
    echo "Ihre Nachricht wurde empfangen.\n ",
    "Fragen werden typischerweise nach einem Werktag beantwortet.";
    $contact_log = fopen("contact_msgs.txt", "a") or die("Unable to open file!");
    $txt = 'Name: '.$_POST['name']."\n". 
    'mail: '.$_POST['mail']."\n".
    'topic: '.$_POST['topic']."\n".
    'date: '.date("Y-m-d H:i:s")."\n".
    'message: '.$_POST['message']."\n". 
    "***************************************************************\n" ;
    fwrite($contact_log, $txt);  
    fclose($contact_log);
  }
  else{
    echo "<br>Es fehlen Pflichteingaben.<br>";
  }      
}
?>
<div id="content">
  <br>
  <h1> Kontakt</h1>
  <br>
  <form id="kaufen" action="kontakt.php?'.SID.'" method="post">
    <input type="hidden" name="purchase_reload" value="true" form="kaufen" />
    Haben Sie Fragen zu Kaufabwicklung? Gibt es Probleme mit ihrem Account? Lassen Sie es uns wissen. <br>
    Möchten Sie uns nur eine Nachricht schicken, ist ihre email Adresse nicht erforderlich.<br>    
    <br>				
    Name*:<br>
    <input type="text" name="name"><br>
    Ihre email-Adresse:<br>
    <input type="text" name="mail"><br>
    Thema*:<br>
    <select name="topic" size="1">
        <option value=""></option>
        <option value="kauf">Kauf</option>
        <option value="account">Account</option>
        <option value="rechtliches">Rechtliches</option>
        <option value="meinung">Meinung</option>
    </select>
    <br><br>
    Ihre Nachricht*:
    <br>
    <textarea name="message" required style="width:400px; height:300px;">Nachricht hier eingeben.
    </textarea> 
    <br>
    <button type="submit" style="  	margin: 0em;
                                        padding: .2em .5em;
                                        background-position: .5em center;
                                        background-repeat: no-repeat;
                                        float: right;">
            absenden
    </button>
    * = Pflichtfelder
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
