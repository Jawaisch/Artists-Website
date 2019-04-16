<?php
  error_reporting( E_ALL );

  include( "./includes/view.inc" );
  include( "./includes/php.inc" );
  // include( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf
  // CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung

  // $dbconn = KWS_DB_Connect( "gast" ); // Datenbankverbindung
  
  PrintHtmlHeader( );
  PrintHtmlTopnav( );
?>
    <div id="content">
      <div class="preview">
        <h2 class="title"><a href="#">STB-Logo</a></h2>
        <p class="meta">Eingestellt von <a href="#">Someone</a> am März 8, 2019 </p>
        <div class="image">
          <p><img 
            src="example-images/stb-squarelogo.jpg" 
            width="250"   
            height="250" 
            alt="STB-Logo" 
            title="STB-Logo" 
          /></p>
          <p class="links"><a href="#top">Seitenanfang</a></p>
        </div>
      </div>
      <div class="preview">
        <h2 class="title"><a href="#">Roberta</a></h2>
        <p class="meta">Eingestellt von <a href="#">Someone</a> am März 8, 2019 </p>
        <div class="image">
          <p><img 
            src="example-images/stb-squarelogo.jpg" 
            width="250"   
            height="250" 
            alt="STB-Logo" 
            title="STB-Logo" 
          /></p>
          <p class="links"><a href="#top">Seitenanfang</a></p>
        </div>
      </div>
    <div class="clearBoth" >&nbsp;</div>
  </div>
  <!-- end #content -->
      
<?php
  PrintHtmlSidebar( $_SESSION['login']['user'] );
  PrintHtmlFooter( ); 
?>
