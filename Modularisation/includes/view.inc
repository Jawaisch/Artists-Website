<?php
/*
 @file Diese Datei entählt Funktionen zur Erzeugung von HTML-Elementen.
*/

/* ****************************************************************************************
@funktion PrintHtmlHeader( )

@brief - Erzeugt den HTML-Kopf der Seite.

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

@brief -  Erzeugt die Haupt-Navigations-Leiste und setzt die class="active" in die aktuell
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
  '      <a href="index.php?'.$Session_ID.'" '.       $class1 .' >Home</a>'."\n".
  '      <a href="galerie.php?'.$Session_ID.'" '.     $class2 .' >Galerie</a>'."\n".
  '      <a href="All_Artists.php?'.$Session_ID.'" '. $class3 .' >Künstler</a>'."\n".
  '      <a href="ueber_uns.php?'.$Session_ID.'" '.   $class4 .' >Über uns</a>'."\n".
  '      <a href="kontakt.php?'.$Session_ID.'" '.     $class5 .' >Kontakt</a>'."\n".
  '    </div>'."\n".
  '    <!-- end #topnav -->'."\n".
  '    <div id="main">'."\n";

  echo $output;
}


/* ****************************************************************************************
@funktion PrintHtmlSidebar( $user_type, $Session_ID )

@brief - Erzeugt die Sidebar.

@param  - $user_type: ein String der die Art des Users repräsentiert z.B. kuenstler

@return -
****************************************************************************************** */
function PrintHtmlSidebar( $user_type, $Session_ID )
{
  echo <<<EO_TOP
    <div id="sidebar">
    <ul>
      <li>
      <div id="search" >
        <form method="post" action="./suche.php?$Session_ID">
        <div>
          <input type="text" name="input_arr[wanted]" id="search-text" value="Bildname" />
          <input type="submit" name="submit" id="search-submit" value="Suchen" />
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

// findet aktuell keine Verwendung könnte aber für administrative Zwecke angepasst werden
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
              <div><input type="hidden" name="$sname" value="$sid" /></div>
              <div class="buttonrow">
                <input type="submit" name="submit" value="Logout" />
              </div>
            </form>
          </li>
          <li><a href="./kauf.php?$Session_ID">Einkaufswagen</a></li>
          <li><a href="./profil.php?$Session_ID">Mein Profil</a></li>
          <li><a href="./kaufuebersicht.php?$Session_ID">Kaufübersicht</a></li>
          <li><a href="./kuenstler_reg.php?$Session_ID">Künstler werden</a></li>
        </ul>
      </li>
EO_MID;
}

function HtmlSidebarKünstler( $Session_ID )
{
  $sname=session_name();
  $sid=session_id();
  $kid=$_SESSION['login']['KID'];
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
              <div><input type="hidden" name="$sname" value="$sid" /></div>
              <div class="buttonrow">
                <input type="submit" name="submit" value="Logout" />
              </div>
            </form>
          </li>
          <li><a href="./kauf.php?$Session_ID">Einkaufswagen</a></li>
          <li><a href="./profil.php?$Session_ID">Mein Profil</a></li>
          <li><a href="./kaufuebersicht.php?$Session_ID">Kaufübersicht</a></li>
        </ul>
      </li>
      <li>
        <h2>Künstler</h2>
        <ul>
          <li><a href="./upload.php?$Session_ID">Kunst verkaufen</a></li>
          <li><a href="./public_artist.php?$Session_ID&amp;kid=$kid">Meine Kunst</a></li>
          <li><a href="./Verkaufsuebersicht.php?$Session_ID&amp;kid=$kid">Verkaufsübersicht</a></li>
          <li><a href="./kuenstler_reg.php?$Session_ID">Neues Künstlerkonto</a></li>
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
          <li><a href="./kunde_reg.php?$Session_ID">Registrieren</a></li>
        </ul>
      </li>
EO_MID;
}


/* ****************************************************************************************
@funktion PrintHtmlFooter( $Session_ID )

@brief - Erzeugt den HTML-Footer der Seite

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

@brief - Erzeugt eine DIV als Fehlermeldung


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
    $table =  "\n     <table class =\"table\">". // Der Tabellenkopf
              "\n     <thead>".
              "\n       <tr>".
              "\n         <th>Bezeichnung</th> <th>Wert</th>".
              "\n       </tr>".
              "\n     </thead>".
              "\n     <tbody>";

    // Wdh. solange Datensätze vorhanden

    foreach ( $daten AS $key => $value )
    {
      $table .= "\n       <tr> <td>". $key."</td>".
                " <td>". $value."</td> </tr> ";
    }

    $table .="\n    </tbody>\n </table>\n"; // Der Tabellenfuß

    return $table;
  }


/* ****************************************************************************************
@funktion PrintHtmlCards( $offer, $sold, $Session_ID )

@brief - Erzeugt 2 ancklikbare Karten mit den aktuellen Zahlen
         der angebotenen und verkauften Bilder

@param - Anzahl eingestellter Bilder, Anzahl verkaufter Bilder
@return -
****************************************************************************************** */
function PrintHtmlCards( $offer, $sold, $Session_ID )
{
  $kid=$_SESSION['login']['KID'];
  echo <<<EO_CARDS

     <div>

      <div class="column">
        <a href="public_artist.php?$Session_ID&amp;kid=$kid" class="card" >
          &nbsp;<br />
          $offer<br />
          &nbsp;<br />
          Angeboten
        </a>
      </div>

      <div class="column">
        <a href="index.php?$Session_ID" class="card">
          &nbsp;<br />
          $sold<br />
          &nbsp;<br />
          Verkauft
        </a>
      </div>

      <div class="column">
        <a href="upload.php?$Session_ID" class="card">
          &nbsp;<br />
          neu<br />
          &nbsp;<br />
          Anbieten<br />
        </a>
      </div>

    </div>

EO_CARDS;
}


/* ****************************************************************************************
@funktion HtmlRegForm( $Data_Reqs, $header, $description, $action, [$user_data_arr=null], [$agbs=false], [$upload=false] )

@brief - Erzeugt ein Formular für z.B.: den Regestriervorgang oder die Profil bearbeiten Seite

@param - $Data_Reqs:    Ein Array welches unter anderem die Labels für das Formular enthält
         $description:  Eine Beschreibung für das Formular als String
         $action:       Die Zielseite der Formulardaten
         $user_data_arr:Ein Arry mit Userdaten für die Seite: Profil bearbeiten
         $agbs:         Ein bool der angibt ob der AGB Hinweis ausgegeben werden muss
         $upload:       Ein bool der angibt ob ein Upload Button ausgegeben werden muss

@return -
****************************************************************************************** */
function HtmlRegForm( $Data_Reqs, $header, $description, $action, $user_data_arr=null, $agbs=false, $upload=false )
{
  if($upload)
    echo "\n    <form  action=\"".$action.SID."\" method=\"post\" enctype=\"multipart/form-data\" >\n";
  else
    echo "\n    <form action=\"".$action.SID."\" method=\"post\">\n";

  echo "\n    <div class=\"form_container\">";
  echo "\n       <h1>".$header."</h1>";
  echo "\n       <p>".$description."</p>";
  echo "\n       <hr />";

  // Wird ein Upload-Button benötigt?
  if($upload)
  {
    echo "\n       <p class=\"label\"><span class=\"description\"><label ><b>Bild</b></label></span>&nbsp;</p>";
    echo "\n       <input type=\"file\" name=\"bild\" id=\"bild\" accept=\"image/*\" size=\"80\" />";
  }

  // Eingabe Felder Erzeugen
  foreach($Data_Reqs as $data)
  {
    echo "\n        <p class=\"label\"><span class=\"description\"><label ><b>".$data['label']."</b></label>";
    // Wurde beim input check ein Fehler eingetragen?
    if(isset( $_SESSION['input_data'][$data['index']]['err'] ))
    {
      echo"</span>".$_SESSION['input_data'][$data['index']]['err']."</p>";
    }
    else
    {
      echo"</span>&nbsp;</p>";
    }
    // Handelt es sich um ein Passwort-Feld?
    if(strpos($data['label'], 'Passwort') !== false)
    {
      echo "\n        <input type=\"password\" name=\"reg_data_arr[".$data['index']."]\" value=\"";
    }
    // Handelt es sich um ein Textarea-Feld?
    elseif( isset($data['textarea']) )
    {
      echo "\n        <textarea name=\"reg_data_arr[".$data['index']."]\" rows=\"5\" cols=\"80\" id=\"vita\">";
    }
    // Handelt es sich um ein Select-Feld?
    elseif( isset($data['select_list']) )
    {
      HtmlFormSelect( $data['select_list'](), $data['index'] );
    }
    // Dann ist es ein Text-Feld
    else
    {
      echo "\n        <input type=\"text\" name=\"reg_data_arr[".$data['index']."]\" value=\"";
    }

    // Nur für nicht Select-Felder
    if( !isset($data['select_list']) )
    {
      // Wurden in dieses Feld bereits Daten eingegeben?
      if(isset( $_POST['reg_data_arr'][$data['index']] ))
      { // dann diese Daten übernehmen
        echo $_POST['reg_data_arr'][$data['index']];
      }
      // Wurden dem Funktionsaufruf Daten für dieses Feld übergeben?
      elseif(isset( $user_data_arr[$data['label']] ))
      { // dann diese Daten übernehmen
        echo $user_data_arr[$data['label']];
      }
    }

    // geöffneten Tag schließen
    // Handelt es sich um ein Textarea-Feld?
    if( isset($data['textarea']) )
    {
      echo " </textarea>\n";
    }
    // Handelt es sich um ein Select-Feld?
    elseif( isset($data['select_list']) )
    {
      // nichts zum schließen
    }
    else
    {
      echo "\" />\n";
    }
  }

  echo "\n       <hr />";
  if( $agbs )
  {
    echo "\n       <p>Mit der Erstellung eines Kontos erklären Sie sich mit unseren <a href=\"agb.php?".session_id()."\">AGBs </a>einverstanden.</p>";
  }
  echo "\n        <input type=\"hidden\" name=\"".session_name()."\" value=\"".session_id()."\" />";
  echo "\n        <div class=\"buttonrow\">";
  echo "\n          <input type=\"submit\" name=\"submit\" value=\"Absenden\" />";
  echo "\n          <input type=\"reset\" value=\"Zurücksetzen\" />";
  echo "\n        </div>";
  echo "\n      </div>";
  echo "\n    </form>";
}


/* ****************************************************************************************
@funktion HtmlFormSelect( $select_list , $name )

@brief - Erzeugt ein gültiges HTML-Div für eine Dropdown-Liste

@param - $select_list: Liste der Auswahlmöglichkeiten
         $name: der Name des Auswahlfeldes

@return -
****************************************************************************************** */
function HtmlFormSelect( $select_list, $name )
{
 echo "\n         <select id=\"genre\" name=\"reg_data_arr[$name]\">";
 echo "\n           <option value=\"\" selected=\"selected\">bitte wählen</option>";

  foreach ( $select_list as $item )
  {
    echo "\n           <option value=\"".$item['Value']."\">".$item['Name']."</option>";
  }
 echo "\n         </select>";
}


/* ****************************************************************************************
@funktion PrintHtmlGallery( $AllImages )

@brief - Erzeugt ein gültiges HTML-Div für die Bilder-Galerie

@param - Ein Array mit den auszugebenden Bilder + Informationen

@return -
****************************************************************************************** */
function PrintHtmlGallery( $AllImages )
{
  $SID = session_id();
  foreach( $AllImages AS $ImageNotes )
  {
  $bid = $ImageNotes['Bild_ID'];
  $btitle =$ImageNotes['Titel'];
  $bheight=$ImageNotes['Hoehe'];
  $bwidth=$ImageNotes['Breite'];
  $bprice=$ImageNotes['VK_Preis'];
  $bartist=$ImageNotes['KName'];
  $kid=$ImageNotes['Kuenstler_ID'];

  //Sollte der Titel mehr als 23 zeichen beinhalten werden für die Gallerieansicht der Titel geschnitten
  // und Punkte angefügt
  $lenght = 23;

      if(strlen($btitle) > $lenght) {

          $btitle = substr($btitle,0,$lenght)."...";

          $string_ende = strrchr($btitle, " ");

          $btitle = str_replace($string_ende," ...", $btitle);
      }


echo <<<EO_TOP
    <div class="gallery_content">
    <div class="image">
      <img src="art-images/small/$bid.png" alt="$btitle" />
    </div>
    <div class="image_notes">
    <h3>$btitle</h3>
    <p><span class="description">Künstler:</span><a href="public_artist.php?kws=$SID&amp;kid=$kid">$bartist</a></p>
    <p><span class="description">Größe:</span>$bheight mm x $bwidth mm</p>
    <p><span class="description">Kaufspreis:</span>$bprice €</p>
    <p>
    <a href="gross_bild.php?kws=$SID&amp;bid=$bid">Genauer betrachten</a>
    </p>
    </div>
    </div>

EO_TOP;
    }

  }


/* ****************************************************************************************
@funktion PrintPicPreview( $pic_id )

@brief - Erzeugt ein gültiges HTML-Div für ein hochgeladenen Bild

@param - $pic_id die Bild_ID des gerade hochgeladenen Bildes

@return -
****************************************************************************************** */
function PrintPicPreview( $pic_id )
{
  $SID = session_id();
  list($width, $height, $type, $attr) = getimagesize("art-images/small/".$pic_id.".png");

  echo <<<EO_PIC
           <div>
             <h3>Bildvorschau</h3>
             <a href="gross_bild.php?kws=$SID&amp;bid=$pic_id">
              <img
                 src="art-images/small/$pic_id.png"
                 $attr
                 alt="Bildvorschau"
                 title="Bildvorschau"
               />
             </a>
           </div>
EO_PIC;
}


/* ****************************************************************************************
@funktion PrintHtmlIndex($Pics)

@brief - Erzeugt ein gültiges HTML-Div für den Index

@param - $Pics ein Arry mit Bildern und Informationen zu diesen

@return -
****************************************************************************************** */
function PrintHtmlIndex($Pics)
{
  foreach ($Pics as $Pic)
  {
    list($width, $height, $type, $attr) = getimagesize("art-images/small/".$Pic['Bild_ID'].".png");
    $date = preg_split("* *", $Pic['Einstell_Zeitstempel']);

    $output = ''.
  '       <div class="preview">'."\n".
  '         <h2 class="title">'.$Pic['Titel'].'</h2>'."\n".
  '         <p class="meta">Eingestellt von <a href="public_artist.php?'.SID.'&amp;kid='.$Pic['Kuenstler_ID'].'">'.$Pic['KName'].'</a> am '.$date[0].' um '.$date[1].' </p>'."\n".
  '         <a href="gross_bild.php?'.SID.'&amp;bid='.$Pic['Bild_ID'].'">'."\n".
  '          <img '."\n".
  '             src="art-images/small/'.$Pic['Bild_ID'].'.png"'."\n".
  '             ' .$attr."\n".
  '             alt="'.$Pic['Titel'].'"'."\n".
  '             title="'.$Pic['Titel'].'"'."\n".
  '           />'."\n".
  '         </a>'."\n".
  '         <p class="links"><a href="#top">Seitenanfang</a></p>'."\n".
  '       </div>'."\n";

  echo $output;
  }
}


 /* ****************************************************************************************
@funktion HtmlPrintPaymentRequest( )

@brief - Gibt eine DIV für die Zahlungsaufforderung aus

@param -

@return -
****************************************************************************************** */
function HtmlPrintPaymentRequest( )
{
  $sum = $_POST['purchase_sum'];
  $art_nr = $_SESSION['cart'][0];

  $HtmlStr=<<<EOT
  <div id="content">
    <div class="success">
      <div class="title">Kauf abgeschlossen</div>
    </div>
    <p>
      Bitte überweisen Sie den Betrag von $sum € auf das folgende Konto:<br />
      <pre>
        Zahlungsempfänger: Art Tick GmbH, Musterstr. 5 in 10243 Musterhausen
        Bank: MusterFinance
        IBAN: CH82 0900 0000 6035 9126 4
        Verwendungszweck: art_nr $art_nr
      </pre>
      <br />
    </p>
    <div class="clearBoth" >&nbsp;</div>
  </div>
EOT;
  echo $HtmlStr;
}


/* ****************************************************************************************
@funktion HtmlPrintPaymentRequest( )

@brief - Gibt eine DIV für die Zahlungsaufforderung aus

@param -

@return -
****************************************************************************************** */
function DisplayAllArtists($Artist_Arr)
{
  echo "<div class=\"table\">".
    "<table>".
      "<tr><th>Unsere K&uuml;nstler</th></tr>";

  foreach ( $Artist_Arr AS $Artists )
    {

     echo "<tr><td><a href=\"public_artist.php?".SID."&amp;kid=".$Artists['Kuenstler_ID']."\">".$Artists['KName']."</a></td></tr>\n";
    }

  echo	"</table></div>";

}


/* ****************************************************************************************
@funktion HtmlPrintPaymentRequest( )

@brief - Gibt eine DIV für die Zahlungsaufforderung aus

@param -

@return -
****************************************************************************************** */
function DisplayPublicData($PublicData,$PublicPics)
{
  $SID = session_id();
  $Kname = $PublicData[0]['Kname'];
  $Kvita = $PublicData[0]['Vita'];
  $LastPic = $PublicPics[0]['Bild_ID'];

  echo <<<PUBLIC_CONTENT
      <div class="PublicArtistInfo">
        <div class="PublicProfilPic">
          <img src="art-images/small/$LastPic.png" alt="Profilbild" />
        </div>
        <div class="PublicArtistVita">
          <h3>&Ouml;ffentliches K&uuml;nstler-Profil von $Kname</h3>
          <p>$Kvita</p>
        </div>
      </div>
PUBLIC_CONTENT;


  if(!empty($PublicPics))
  {
    foreach( $PublicPics AS $PicInfo )
    {
      $bid = $PicInfo['Bild_ID'];
      $btitle = $PicInfo['Titel'];

    echo <<<ARTISTPICS
        <div class="gallery_content">
          <div class="image">
            <img src="art-images/small/$bid.png" alt="$btitle"/>
          </div>
          <div class="image_notes">
            <h4>$btitle</h4>
            <p><a href="gross_bild.php?kws=$SID&amp;bid=$bid">Genauer betrachten</a>
            </p>
          </div>
        </div>
ARTISTPICS;
    }
  }
}


/* ****************************************************************************************
@funktion HtmlPrintPaymentRequest( )

@brief - Gibt eine DIV für die Zahlungsaufforderung aus

@param -

@return -
****************************************************************************************** */

function PrintSinglePic( $SingleInfo, $BID )
{
 $bid      = $BID;
 $kid      = $SingleInfo['Kuenstler_ID'];
 $btitle   = $SingleInfo['Titel'];
 $bartist  = $SingleInfo['KName'];
 $bheight  = $SingleInfo['Hoehe'];
 $bwidth   = $SingleInfo['Breite'];
 $bprice   = $SingleInfo['VK_Preis'];
 $bpaint   = $SingleInfo['Mal_Technik'];
 $bgenre   = $SingleInfo['Name'];
 $genid    = $SingleInfo['Genre_ID'];

 if($SingleInfo['Kauf_Zeitstempel'] === NULL) // Überprüft ob das Bild bereits verkauft wurde
   $bsold = "Verfügbar";
 else
   $bsold = "Bereits verkauft";

 $SID = session_id();
 $SIN = session_name();
 $Self = $_SERVER['PHP_SELF'];

echo <<<EO_SinglePic
 <div class="single_content">
   <div class="big_image">
     <img src="art-images/big/$bid.png" alt="$btitle"/>
   </div>

   <div class="big_image_notes">
     <h2>$btitle</h2>
     <p><span class="description">Künstler:</span><a href="public_artist.php?kws=$SID&amp;kid=$kid">$bartist</a></p>
     <p><span class="description">Höhe:</span>$bheight mm</p>
     <p><span class="description">Breite:</span>$bwidth mm</p>
     <p><span class="description">Verkaufspreis:</span>$bprice&euro;</p>
     <p><span class="description">Maltechnik:</span>$bpaint</p>
     <p><span class="description">Genre:</span><a href="./genre.php?kws=$SID&amp;gen=$genid">$bgenre</a></p>
     <p><span class="description">Verfügbarkeit:</span>$bsold</p>
   </div>

EO_SinglePic;
   if( $SingleInfo['Kauf_Zeitstempel'] === NULL && $SingleInfo['Resv_Zeitstempel'] === NULL && (empty($_SESSION['Max_Cart']) || $_SESSION['Max_Cart'] <= 2) &&  (isset($_SESSION['login']['success']) && $_SESSION['login']['success'] === true   ))
   {
     echo <<<EO_Cart_Form
         <form action="gross_bild.php?kws=$SID&amp;bid=$bid" method="post">
           <div>
             <button name="warenkorb" type="submit" value="Submit">In den Warenkorb</button>
           </div>
         </form>
       </div>
EO_Cart_Form;
   }
   else
     echo "</div>";
}


/* ****************************************************************************************
@funktion HtmlPrintPaymentRequest( )

@brief - Gibt eine DIV für die Zahlungsaufforderung aus

@param -

@return -
****************************************************************************************** */

function DisplayGenreInfo($GenreInfo)
{
  $Gname = $GenreInfo[0]['Name'];

  // Überprüfen ob bereits eine HTML-Formatierung im String vorliegt
  if ( preg_match('<p>',$GenreInfo[0]['Beschreibung'])  === false )
  {
    $Ginfo = "<p>".$GenreInfo[0]['Beschreibung']."</p>";
  }
  else
  {
    $Ginfo = $GenreInfo[0]['Beschreibung'];
  }
  echo <<<GENREBOX
     <div class="Genre_Info">
       <h3>$Gname</h3>
        $Ginfo
     </div>
GENREBOX;

}


/* ****************************************************************************************
@funktion HtmlPrintPaymentRequest( )

@brief - Gibt eine DIV für die Zahlungsaufforderung aus

@param -

@return -
****************************************************************************************** */

function DisplaySoldPics($SoldPics)
{
  foreach( $SoldPics AS $PicInfo )
  {
    $SID = session_id();
    $bid = $PicInfo['Bild_ID'];
    $btitle = $PicInfo['Titel'];
    $uaddress =$PicInfo['Anrede'];
    if($PicInfo['uTitel'] !== NULL)
    {
      $utitle = $PicInfo['uTitel'];
    }
    else
    {
      $utitle = "";
    }
    $uvname = $PicInfo['Vorname'];
    $unname = $PicInfo['Nachname'];
    $kaufZt = $PicInfo['Kauf_Zeitstempel'];

    $lenght = 23;

        if(strlen($btitle) > $lenght)
        {

            $btitle = substr($btitle,0,$lenght)."...";

            $string_ende = strrchr($btitle, " ");

            $btitle = str_replace($string_ende," ...", $btitle);
        }

  echo <<<SOLD
  <div class="gallery_content">
    <div class="image">
      <img src="art-images/small/$bid.png" alt="$btitle" />
    </div>
    <div class="image_notes">
      <h3>$btitle</h3>
      <p><span class="description">Käufer</span> $uaddress $utitle $uvname $unname</p>
      <p><span class="description">Kaufdatum</span> $kaufZt</p>
    </div>
  </div>
SOLD;
  }
}
