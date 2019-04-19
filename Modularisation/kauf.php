<?php
  error_reporting( E_ALL );

  include( "./includes/view.inc" );
  include( "./includes/php.inc" );
  // include( "./includes/data.inc" );   
  InitSession();  // Nimmt die aktuelle Session wieder auf
  // $_SESSION['referer'] = $_SERVER['PHP_SELF'];
  // CheckLogin();   // Überprüft auf eine erfolgreiche Anmeldung

  // $dbconn = KWS_DB_Connect( "gast" ); // Datenbankverbindung

  PrintHtmlHeader( );
  PrintHtmlTopnav( $_SERVER['PHP_SELF'] );
?>

  <div id="content">
  
    <br>
    <h1> Ihr Einkaufswagen</h1>
    <br>
    <form action="/action_page.php">
        <table>
                <style>
                        table {
                            font-family: arial, sans-serif;
                            border-collapse: collapse;
                            width: 100%;
                        }
                        
                        td, th {
                            border: 1px solid #dddddd;
                            text-align: left;
                            padding: 8px;
                        }
                        
                        tr:nth-child(even) {
                            background-color: #dddddd;
                        }
                </style>
                <tr> <th>Position</th><th>Bild_ID</th> <th>Titel</th> <th>Vorschau</th> <th>Künstler</th><th>Preis</th> </tr>
                <tr> <td>1</td> <td>2101</td> <td>Korsika</td> <td><img src="example-images/corsica_s.jpg" alt="corsican coast"width="90" height="60"></td><td>Marian</td><td>19,95€</td> </tr>
                <tr> <td>2</td> <td>2102</td> <td>Tulpen</td> <td><img src="example-images/corsica_s.jpg" alt="corsican coast"width="90" height="60"></td><td>Marian</td><td>19,95€</td> </tr>
                <tr> <td></td> <td></td> <td></td> <td></td><td>Summe</td><td>39,90€</td> </tr>
            </table>
            <br>
            <button type="submit" style="  	margin: 0em;
                                                padding: .2em .5em;
                                                background-position: .5em center;
                                                background-repeat: no-repeat;
                                                float: right;">
                    jetzt kaufen
            </button>
    </form> 			
    <div class="clearBoth" >&nbsp;</div>
  </div>
  <!-- end #content --> 

<?php
  PrintHtmlSidebar( $_SESSION['login']['user'] );
  PrintHtmlFooter( ); 
?>