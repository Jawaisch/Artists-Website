<?php

/* ****************************************************************************************
@funktion InitSession()

@brief Initialidiert eine SESSION für die KWS

Session-Name wird gesetzt und COOKIES deaktiviert.
		
@param -

@return - 
****************************************************************************************** */
function InitSession()
{
  session_name( "kws" );					// den session.name in der Local Value setzten
  ini_set ("session.use_cookies", 0);
  ini_set ("session.use_only_cookies", 0);
  session_start();

  //ist noch kein user gesetzt?
  if ( !isset($_SESSION['login']['user']) )
  {// dann setze 'gast'
    $_SESSION['login']['user']='gast';
  }
}


?>