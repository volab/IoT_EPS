+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Bug et ToDo-list
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


====================================================================================================
Déscription
====================================================================================================

    Dans ce fichier sont renseignés les bugs identifiés et la liste des choses à faire.
    
    #. Bugs identifiés
    
        A chaque fois qu'un bug est identifés, il doit être renseigner ici si il ne fait
        pas l'objet d'un traitemant immédiat.
        
    #. ToDo-list
    
        Ici doivent être renseigner la liste des tâches à faire. Il s'agit souvent de
        petites choses à fort potentiel d'oublie ou des tâches qui ne peuvent pas faire
        l'objet d'un traitemant immédiat.
        
.. WARNING::
    Cette liste est renseignée manuellement. Ne pas oublier le To do list du code source C++
    `<codeDoc\\html\\index.html>`_

====================================================================================================
Model Type
====================================================================================================

    :Date de saisie:        Date à laquelle la problématique à été identifiée
    :Date de traitemant:    Date du traitement de la probélmatique
    :Cible:                 [userDoc, modelisation, software, PCB, autre]
    :Status:                [NONE, WIP, DONE]
    :Problematique:         Déscriptif de la problématique
    :Traitement:            Déscriptif du traitement de la probélmatique

----------------------------------------------------------------------------------------------------

====================================================================================================
Open bugs
====================================================================================================

**BUG** : push button permutted on yellow and green
====================================================================================================

    :Date de saisie:    08/01/2022    
    :Date de traitemant:    
    :Cible:             firmware
    :Status:            **OPEN**    
    :Problematique:     cabling is good !

    :Traitement:        
                        
----------------------------------------------------------------------------------------------------

**BUG** : corrupted value of on/off counter
====================================================================================================

    :Date de saisie:    08/01/2022    
    :Date de traitemant:    
    :Cible:             firmware
    :Status:            **OPEN**    
    :Problematique:     after somme tests values of all counter are very stranges. only those in the configFile3
                        seams to be right. I don't know exactly when.
    :Traitement:        
                        

------------------------------------------------------------------------------------------

**BUG** : wrong global table refresh
====================================================================================================

    :Date de saisie:    191225    
    :Date de traitemant:    
    :Cible:             software / IHM
    :Status:            **OPEN**    
    :Problematique:     le tableau de synthèse ne se met pas à jour quand il y a un changement d'état d'une prise    
    :Traitement:        Le touche F5 n'est pas une solution, renvoie également la dernière commande !
                        

------------------------------------------------------------------------------------------

**BUG** : Allumage intempestif 
====================================================================================================

    :Date de saisie:        191225     
    :Date de traitemant:    
    :Cible:                 firmware
    :Status:                **OPEN**
    :Problematique:         Au cours des essais 2 prises bleu et jaune se sont retrouvé allumées alors
                            que dans le json elles étaient off !
    :Traitement:            



------------------------------------------------------------------------------------------



**BUG** : cfgpage / cfgsend
====================================================================================================

    :Detection date:   23/10/21
    :Resolution date:  
    :Target:           firmware
    :Status:           **OPEN**
    :Problem:         /cfgpage after cfgpage send the link in browser turn to /cfgsend du to usage 
                      of send button. This behavior is normal. But we refresh the page with new
                      values and if user use the resend button from the browser he resend the same
                      page. Not realy a bug but not very clean.
                      **More** Add to this page, there is no return to home button
    :Traitement:
    


----------------------------------------------------------------------------------------------------

**BUG** : clone pause
====================================================================================================

    :Date de saisie:        210718
    :Date de traitemant:    
    :Cible:                 firmware
    :Status:                **OPEN**
    :Problematique:         Bug not confirmed but in CPowerPlug::handleHtmlReq in mode cloned
    :Traitement:
    
    ::

        test pause before to call on or off method (about line 601) write
        if (_state && !_pause) but move line ``_pause = clonedPlug.getPause();``
        before

----------------------------------------------------------------------------------------------------



====================================================================================================
Open todo
====================================================================================================

ToDo : Pause display
===========================

    :Date de saisie:        08/01/2022
    :Date de traitemant:    
    :Cible:                 firmware
    :Status:                **OPEN**
    :Problematique:         display pause on oled screen. 
    :Traitement:            
            

------------------------------------------------------------------------------------------

ToDo : minify javascripts
===========================

    :Date de saisie:        210821
    :Date de traitemant:    
    :Cible:                 Data/javascript
    :Status:                **OPEN**
    :Problematique:         reduce the size of the web files. Reduce the size of the logo.
    :Traitement:            
            

------------------------------------------------------------------------------------------

ToDo : doxy HTML js
======================

    :Date de saisie:        181214
    :Date de traitemant:    
    :Cible:                 software
    :Status:                **OPEN**
    :Problematique:         Use Doxigen on HTML et JS codes.
    :Traitement:            

------------------------------------------------------------------------------------------

ToDo : file names coherence
==============================

    :Date de saisie:        181214
    :Date de traitemant:    
    :Cible:                 software
    :Status:                **OPEN**
    :Problematique:         Faire correspondre dans index.html, style.css et dans IoT_EPS2.js les
                            noms utilisés avec ceux définis dans configFile3.json.
    :Traitement:            

------------------------------------------------------------------------------------------

Todo : change behavior on fatal error
==========================================

    :creation date:         11/12/2021
    :Date of treatment:    
    :Cible:                 [software]
    :Status:                **OPEN**
    :Problem:               System sabord on fatal error and only blink led. This behavior prevent
                            us to diagnose problem.
    :Traitement:            Change this to only permit serial diag on fatal error.


----------------------------------------------------------------------------------------------------

====================================================================================================
Closed bug
====================================================================================================

**BUG** : cfgpage
====================================================================================================

    :Date de saisie:        21/08/21
    :Date de traitemant:    16/10/21
    :Cible:                 firmware
    :Status:                closed
    :Problematique:         /cfgpage : faile to load json param!
    :Traitement:
    
    ::

        Free memory analyse was conducted. memory managment improvement was introduced.

----------------------------------------------------------------------------------------------------

**BUG** soft AP fail
====================================================================================================

    :Date de saisie:        210627      
    :Date de traitemant:    210630
    :Cible:                 firmware
    :Status:                closed
    :Problematique:         Soft AP fails
    :Traitement:            Set Arduino IDE/ESP in Wifi debug mode has correct the problem !!!


------------------------------------------------------------------------------------------

**BUG** : oled do not display system error
====================================================================================================

    :Detection date:   11/12/21
    :Resolution date:  18/12/2021
    :Target:           firmware
    :Status:           [closed]
    :Problem:         When system error oled display blank line
                      
    :Traitement:      local branch oled-display-error-bug

----------------------------------------------------------------------------------------------------

**BUG** : watchdog ok
====================================================================================================

    :Detection date:   05/12/21
    :Resolution date:  15/12/2021
    :Target:           firmware
    :Status:           [closed]
    :Problem:         There is no  watchdog component in the system and system always displays 
                      watchdog ok !!!
                      
    :Traitement:        Watch dog display ok on oled cause  normaly wd error is a fatal error that
                        sabord the system and it does not reach the line where it is displayed but
                        with the no_sabord option system reach the line.
                        insert a new parameter NBR_OF_SYSTEM_ERROR and a new table of error

----------------------------------------------------------------------------------------------------


====================================================================================================
Closed todo
====================================================================================================

ToDo : online gh-page
========================

    :Date de saisie:        181214
    :Date de traitemant:    
    :Cible:                 autre
    :Status:                closed
    :Problematique:         Créer la Branch 'gh-pages' pour y intégrer la documentation générer par
                            Sphinx et par Doxigen.
    :Traitement:            

------------------------------------------------------------------------------------------

.. _todocreateconfigfile:


ToDo : config.h
================

    :Date de saisie:        200703        
    :Date de traitemant:    11/12/2021
    :Cible:                 firmware
    :Status:                closed
    :Problematique:         Create config.h file with only #define
    :Traitement:            To separate from include files. To day there is only one file IoT_EPS.h
                            2 file created config and config_advanced 

----------------------------------------------------------------------------------------------------

Todo : Complete the CSystem class
==========================================

    :Date de saisie:        11/09/2020
    :Date de traitemant:    10/02/2021
    :Cible:                 [software]
    :Status:                [closed]
    :Problematique:         Add all system servitude in this class
    :Traitement:            Move code froom .ino to this code


----------------------------------------------------------------------------------------------------



ToDo-list
=========

    :Date de saisie:        
    :Date de traitemant:    
    :Cible:                 [userDoc, modelisation, software, PCB, autre]
    :Status:                
    :Problematique:         
    :Traitement:            


