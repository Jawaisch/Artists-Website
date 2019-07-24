SET GLOBAL event_scheduler = ON;

USE 19ss_tedk4_kws;

DROP EVENT IF EXISTS update_bild_Resv_Zeitstempel;

DELIMITER |

CREATE EVENT update_bild_Resv_Zeitstempel
ON SCHEDULE EVERY 30 SECOND
DO
BEGIN
    UPDATE bild
    SET Resv_Zeitstempel = NULL
    WHERE TIMESTAMPDIFF(MINUTE, Resv_Zeitstempel, NOW() ) > 1;
END |