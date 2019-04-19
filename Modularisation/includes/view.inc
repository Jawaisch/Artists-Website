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
        <h1><a href="#">ART'TICK</a></h1>
      </div>
    </div>
    <!-- end #header -->

EO_HEADER;
}


/* ****************************************************************************************
@funktion PrintHtmlTopnav( $path )

@brief Erzeugt die Haupt-Navigations-Leiste und setzt die class="active" in die aktuell
       aufgerufenen Seitenlink, damit dieser in roter Farbe dargestellt wird.
    
@param  - Den Pfad und Namen des aktuellen Dokuments

@return - 
****************************************************************************************** */
function PrintHtmlTopnav( $path )
{
  // zerlegt die Zeichenkette an Stellen /
  $keywords = preg_split("*/*", $path);
  $site_name = $keywords[2];

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
  '   <div class="topnav" >'."\n".
  '     <a href="index.php" '.   $class1 .' >Home</a>'."\n".
  '     <a href="galerie.php" '. $class2 .' >Galerie</a>'."\n".
  '     <a href="kunstler.php" '.$class3 .' >Künstler</a>'."\n".
  '     <a href="ueber.php" '.   $class4 .' >Über uns</a>'."\n".
  '     <a href="kontakt.php" '. $class5 .' >Kontakt</a>'."\n".
  '   </div>'."\n".
  '   <!-- end #topnav -->'."\n".
  '   <div id="main">'."\n";

  echo $output;
}


/* ****************************************************************************************
@funktion PrintHtmlSidebar( $user_type )

@brief Erzeugt die Sidebar.
    
@param  - $user_type

@return - 
****************************************************************************************** */
function PrintHtmlSidebar( $user_type )
{
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
              HtmlSidebarAdmin();
              break;

      case    "bearbeiter":
              HtmlSidebarAdmin();
              break;

      case    "kuenstler":
              HtmlSidebarKünstler();
              break;

      case    "kunde":
              HtmlSidebarKunde();
              break;

      case    "login":
              break;

      case    "reg":
              break;

      default:HtmlSidebarGast();
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

function HtmlSidebarAdmin()
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

function HtmlSidebarKunde()
{
  echo <<<EO_MID
      <li>
        <h2>Info</h2>
        <p>Sie müssen sich als Künstler registrieren bevor Sie Kunst verkaufen können.</p>
      </li>
      <li>
        <h2>Benutzer</h2>
        <ul>
          <li><a href="#">Logout</a></li>
          <li><a href="#">Mein Profil</a></li>
          <li><a href="#">Kaufübersicht</a></li>
          <li><a href="#">Künstler werden</a></li>
        </ul>
      </li>
EO_MID;
}

function HtmlSidebarKünstler()
{
  echo <<<EO_MID
      <li>
        <h2>Info</h2>
        <p>Laden Sie ein Bild Ihrer Kunst hoch um Interessenten zu finden.</p>
      </li>
      <li>
        <h2>Benutzer</h2>
        <ul>
          <li><a href="#">Logout</a></li>
          <li><a href="#">Mein Profil</a></li>
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

function HtmlSidebarGast()
{
  echo <<<EO_MID
      <li>
        <h2>Info</h2>
        <p>Sie müssen sich einloggen bevor Sie Kunst kaufen und verkaufen können.</p>
      </li>
      <li>
        <h2>Gast</h2>
        <ul>
          <li><a href="#">Login</a></li>
          <li><a href="#">Als Kunde registrieren</a></li>
          <li><a href="#">Als Künstler registrieren</a></li>
        </ul>
      </li>
EO_MID;
}


/* ****************************************************************************************
@funktion PrintHtmlFooter( )

@brief Erzeugt den HTML-Footer der Seite
    
@param - 
@return - 
****************************************************************************************** */
function PrintHtmlFooter( )
{
  echo <<<EO_FOOTER

    <div id="footer">
      <p>     
        <a href="agb.php">AGBs</a> &mdash; 
        <a href="impressum.php">Impressum</a> &mdash; 
        <a href="dsrl.php">Datenschutzrichtlinien</a> &mdash; 
        <a href="admin.php">Admin</a>
      </p>
    </div>
  <!-- end #footer -->
  </body>
</html>

EO_FOOTER;
}