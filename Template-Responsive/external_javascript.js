
/* Wechseln zwischen dem Hinzufügen und Entfernen der Klasse "responsive" zu topnav, wenn der Benutzer auf das Symbol klickt. */
function ResponsiveNav() {
  var x = document.getElementById("menu");
  if (x.className === "topnav") {
	x.className += " responsive";	
  } else {	
	x.className = "topnav";
  }
}
