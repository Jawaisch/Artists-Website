<?php
/*
 @file Diese Datei entählt Funktionen zur Erzeugung von HTML-Elementen.
*/

/* ****************************************************************************************
@funktion PrintHtmlHeader( )

@brief Erzeugt den HTML-Kopf der Seite.
    
@param  -

@return - 
****************************************************************************************** */
function PrintHtmlHeader( )
{
  echo <<<EO_HEADER
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
  <head>
    <title>ART'TICK </title>

    <meta http-equiv="content-type" content="text/html; charset=utf-8" />
    <meta name="Künstlerwebsite" content="STB" />
    <link rel="stylesheet" type="text/css" href="style.css" media="screen" />
  </head>
  <body>
    <div id="header">
      <div id="logo">
        <h1>ART'TICK</h1>
      </div>
    </div>
    <!-- end #header -->

EO_HEADER;
}


/* ****************************************************************************************
@funktion PrintHtmlTopnav( $path, $Session_ID )

@brief Erzeugt die Haupt-Navigations-Leiste und setzt die class="active" in die aktuell
       aufgerufenen Seitenlink, damit dieser in roter Farbe dargestellt wird.
    
@param  - Den Pfad und Namen des aktuellen Dokuments
		  Session_ID

@return - 
****************************************************************************************** */
function PrintHtmlTopnav( $path, $Session_ID )
{
  // zerlegt die Zeichenkette an Stellen mit /
  $keywords = preg_split("*/*", $path);
  // Den Wert des letzten Array Elements auslesen
  $site_name = end($keywords);//$keywords[3];

  $class1 = "";
  $class2 = "";
  $class3 = "";
  $class4 = "";
  $class5 = "";

  switch( $site_name )
    {
      case    "index.php":
              $class1 = "class=\"active\"";
              break;

      case    "galerie.php":
              $class2 = "class=\"active\"";
              break;

      case    "kunstler.php":
              $class3 = "class=\"active\"";
              break;

      case    "ueber.php":
              $class4 = "class=\"active\"";
              break;

      case    "kontakt.php":
              $class5 = "class=\"active\"";
              break;
    }

  $output = ''.
  '    <div class="topnav" >'."\n".
  '      <a href="index.php?'.$Session_ID.'" '.   $class1 .' >Home</a>'."\n".
  '      <a href="galerie.php?'.$Session_ID.'" '. $class2 .' >Galerie</a>'."\n".
  '      <a href="kunstler.php?'.$Session_ID.'" '.$class3 .' >Künstler</a>'."\n".
  '      <a href="ueber.php?'.$Session_ID.'" '.   $class4 .' >Über uns</a>'."\n".
  '      <a href="kontakt.php?'.$Session_ID.'" '. $class5 .' >Kontakt</a>'."\n".
  '    </div>'."\n".
  '    <!-- end #topnav -->'."\n".
  '    <div id="main">'."\n";

  echo $output;
}


/* ****************************************************************************************
@funktion PrintHtmlSidebar( $user_type, $Session_ID )

@brief Erzeugt die Sidebar.
    
@param  - user_type: ein String der die Art des Users repräsentiert z.B. kuenstler
		  Session_ID

@return - 
****************************************************************************************** */
function PrintHtmlSidebar( $user_type, $Session_ID )
{
	//print_r($user_type);
  echo <<<EO_TOP
	  <div id="sidebar">
		<ul>
		  <li>
			<div id="search" >
			  <form method="get" action="">
				<div>
				  <input type="text" name="s" id="search-text" value="Bildname" />
				  <input type="submit" id="search-submit" value="Suchen" />
				</div>
			  </form>
			</div>
			<div class="clearBoth" >&nbsp;</div> 
		  </li>

EO_TOP;

  switch($user_type)
    {

      case    "admin":
              HtmlSidebarAdmin( $Session_ID );
              break;

      case    "bearbeiter":
              HtmlSidebarAdmin( $Session_ID );
              break;

      case    "kuenstler":
              HtmlSidebarKünstler( $Session_ID );
              break;

      case    "kunde":
              HtmlSidebarKunde( $Session_ID );
              break;

      case    "login":
              break;

      case    "reg":
              break;

      default:HtmlSidebarGast( $Session_ID );
    }

  echo <<<EO_END

		</ul>
	  </div>
	  <!-- end #sidebar -->
	  <div class="clearBoth" >&nbsp;</div>
	</div>
	<!-- end #main -->
EO_END;

}

function HtmlSidebarAdmin( $Session_ID )
{
  echo <<<EO_MID
      <li>
        <h2>Administration</h2>
        <p>Hier könnte perspektivisch eine Umgebung zum Verwalten der Webseite implementiert werden.</p>
      </li>
      <li>
        <h2>Gast</h2>
        <ul>
          <li><a href="#">Logout</a></li>
          <li><a href="#">Registrieren</a></li>
        </ul>
      </li>
      <li>
        <h2>Benutzer</h2>
        <ul>
          <li><a href="#">Mein Profil</a></li>
          <li><a href="#">Kaufübersicht</a></li>
          <li><a href="#">Künstler werden</a></li>
        </ul>
      </li>
      <li>
        <h2>Künstler</h2>
        <ul>
          <li><a href="#">Kunst verkaufen</a></li>
          <li><a href="#">Meine Kunst</a></li>
          <li><a href="#">Verkaufsübersicht</a></li>
        </ul>
      </li>
EO_MID;
}

function HtmlSidebarKunde( $Session_ID )
{
  $sname=session_name();
  $sid=session_id();
  echo <<<EO_MID
		  <li>
        <h2>Info</h2>
        <p>Sie müssen sich als Künstler registrieren bevor Sie Kunst verkaufen können.</p>
		  </li>
		  <li>
        <h2>Benutzer</h2>
        <ul>
          <li>
            <form action="logout.php" method="post">
              <input type="hidden" name="$sname" value="$sid" />
              <div class="buttonrow">
                <input type="submit" name="submit" value="Logout" />
              </div>
            </form></li>
          <li><a href="./profil.php?$Session_ID">Mein Profil</a></li>
          <li><a href="#">Kaufübersicht</a></li>
          <li><a href="#">Künstler werden</a></li>
        </ul>
		  </li>
EO_MID;
}

function HtmlSidebarKünstler( $Session_ID )
{
  $sname=session_name();
  $sid=session_id();
  echo <<<EO_MID
		  <li>
			<h2>Info</h2>
			<p>Laden Sie ein Bild Ihrer Kunst hoch um Interessenten zu finden.</p>
		  </li>
		  <li>
        <h2>Benutzer</h2>
        <ul>
          <li>
            <form action="logout.php" method="post">
              <input type="hidden" name="$sname" value="$sid" />
              <div class="buttonrow">
                <input type="submit" name="submit" value="Logout" />
              </div>
            </form></li>
          <li><a href="./profil.php?$Session_ID">Mein Profil</a></li>
          <li><a href="#">Kaufübersicht</a></li>
        </ul>
		  </li>
		  <li>
        <h2>Künstler</h2>
        <ul>
          <li><a href="#">Kunst verkaufen</a></li>
          <li><a href="#">Meine Kunst</a></li>
          <li><a href="#">Verkaufsübersicht</a></li>
        </ul>
		  </li>
EO_MID;
}

function HtmlSidebarGast( $Session_ID )
{
  echo <<<EO_MID
		  <li>
        <h2>Info</h2>
        <p>Sie müssen sich einloggen bevor Sie Kunst kaufen und verkaufen können.</p>
		  </li>
		  <li>
        <h2>Gast</h2>
        <ul>
          <li><a href="./login.php?$Session_ID">Login</a></li>
          <li><a href="./kunde_reg.php?$Session_ID">Als Kunde registrieren</a></li>
          <li><a href="./kuenstler_reg.php?$Session_ID">Als Künstler registrieren</a></li>
        </ul>
		  </li>
EO_MID;
}


/* ****************************************************************************************
@funktion PrintHtmlFooter( $Session_ID )

@brief Erzeugt den HTML-Footer der Seite
    
@param - $Session_ID
@return - 
****************************************************************************************** */
function PrintHtmlFooter( $Session_ID )
{
  echo <<<EO_FOOTER

    <div id="footer">
      <p>     
        <a href="agb.php?$Session_ID">AGBs</a> &mdash; 
        <a href="impressum.php?$Session_ID">Impressum</a> &mdash; 
        <a href="dsrl.php?$Session_ID">Datenschutzrichtlinien</a> &mdash; 
        <a href="admin.php?$Session_ID">Admin</a>
      </p>
    </div>
	<!-- end #footer -->
  </body>
</html>

EO_FOOTER;
}


 /* ****************************************************************************************
@funktion HtmlErrorDiv( $class, $title, $desc )

@brief Erzeugt eine DIV als Fehlermeldung

		
@param - $class Die CSS-Klasse des DIVs 
         $titel Der Fehler-Titel
         $desc  Die Fehlerbeschreibung

@return - Ein gültiges HTML-Div als String
****************************************************************************************** */
  function HtmlErrorDiv( $class, $title, $desc  )
  {
   $HtmlStr=<<<EOT
    <div class="$class">
      <div class="title">$title</div>
      <div class="desc">$desc</div>
    </div>
EOT;
   return $HtmlStr;
  }


/* ****************************************************************************************
@funktion HtmlUserAccount( $daten )

@brief - Erzeugt eine Tabelle für das User Profil
		
@param - User Daten

@return - Ein gültiges HTML-Div als String
****************************************************************************************** */
  function HtmlUserAccount( $daten )
  {
    $table =  "   <table class =\"table\">". // Der Tabellenkopf
              "\n		<thead>".
              "\n			<tr>".
              "\n       <th>Bezeichnung</th> <th>Wert</th>".
              "\n     </tr>".
              "\n		</thead>".
              "\n		<tbody>";

    // Wdh. solange Datensätze vorhanden
    foreach ( $daten AS $user )
    {
      foreach ( $user AS $key => $value )
      {     
        $table .= "<tr> <td>". $key." </td>".
                       "<td>". $value." </td> </tr> ";
      }
    }
    $table .="\n </tbody>\n </table>"; // Der Tabellenfuß

    return $table;
  }


/* ****************************************************************************************
@funktion PrintHtmlCards( $offer, $sold, $Session_ID )

@brief - Erzeugt 2 ancklikbare Karten mit den aktuellen Zahlen
		     der angebotenen und verkauften Bilder
    
@param - Anzahl eingestellter Bilder, Anzahl verkaufter Bilder
@return - Ein gültiges HTML-Div als String
****************************************************************************************** */
function PrintHtmlCards( $offer, $sold, $Session_ID )
{
  echo <<<EO_CARDS

     <div>
      <div class="column">
        <a href="index.php?$Session_ID" >
          <div class="card">
            <h4>$offer</h4>
            <p>Angeboten</p>
          </div>
        </a>
      </div>

      <div class="column">
        <a href="index.php?$Session_ID" >
          <div class="card">
            <h4>$sold</h4>
            <p>Verkauft</p>
          </div>
        </div>
      </a>
    </div>

EO_CARDS;
}