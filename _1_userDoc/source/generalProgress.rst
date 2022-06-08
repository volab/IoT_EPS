++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
General progress of IOT Electrical Power Strip
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date: 04/2021
:last update: 18/07/2021
:Societe: VoRoBoTics
:Entity: VoLAB

.. contents::
    :backlinks: top

.. _mainTodoList:

====================================================================================================
Task list (merged todo list hard and soft : preferred order)
====================================================================================================
Don't forget the todo list of the **doxygen documentation** and **git history**:

    - for a new plug : buy plugs



Doc
----------------------------------------------------------------------------------------------------
- active github pages for the project
    - upload documentation on github pages
    - create page on the volab wiki

- Create an infographic that summarize features and needs 
    - choose tool
    - choose Size
    - choose colors
- Write user manual : **1%**
- Write builder manual
    - mechanical parts
    - buy and groups components
    - oder pcb
    - ARDUINO NANO programming
        - write where to find the precious code ! from github
        - choose ARDUINO NANO old boot, set com port and download

bugs and todos
----------------------------------------------------------------------------------------------------
- Tracking bug ``untimely switching``
    - reset all counter **OK**
    - activate red and bleu cycle and manual off on yellow and green (never switch this 2 plugs) **OK**
    - Check after long period of time if yellow and green counter stay at 0
    - prepare only 2 220V tracker for not in used plugs ( yellow and green for example)
        - it is possible to connect them outside the box directly on power plugs
        - group components
            - list components see here :ref:`here<refDetect220VPres>`
        - build it
        - test it
        - connect to the plugs
        
    - switch to a **special software git branch**
        - perhaps remove some debug messages...
        - add function to read the 2 surveyed analog inputs from io expander
            - test it
        - add a new survey functionality in main loop
        - if this 2 plugs switch to ON 
            - send on serial debug ALERT message
            - display this 2 plugs states variables
            - display json file content
    - conduct long test
        - place the 2 unused plugs in manual off states
        - place the 2 others plugs in cycle mode
            - one with 1 mn on 2 mn off : 3mn total cycle
            - the others with 4 mn on 3 mn off : 7 mn total cycle
        - record debug serial line
        - find the right serial tool to do this job
    - find the cause
        - possible i2c wrong command to io expander
        - io expander bug
        - json file corruption : check json file content in the logs
        - wrong data write in json file : check plug states in th logs




- treat 5 BUG From Bug_ToDoLst file
    - wrong global table refresh
    - cfgpage / cfgsend : configuration page (see Bug_ToDOList.rst)
    - clone pause
    - untimely switching **10%**
    - push button permuted on yellow and green (hardware) **OK**


- treat 6 TODO From Bug_ToDoLst file
    - Pause display
    - minify javascripts
    - doxy HTML js
    - file names coherence

Others task
----------------------------------------------------------------------------------------------------
- complete testToBeConduted see :ref:`here<testToBeConducted>`
    - exhaustive test of hebdo mode : **95%**
- write index special page for softAP Mode with local boostrap or other light js.framework **5%**


- Minifier all files if possible of course and reduce the size of the images
    - minifier picture
    - minifier css
    - minifier html

- try gz files

- improve json file management **2 points need work**
    - write process **OK**
        - test **ok**
            - environnement conda test **ok**
            - write python script to log boot sequence to a file: in progress ``projet\_3_software\outilPythonSpecial`` **ok**
            - record some boot sequence **ok**
            - check boots sequence **ok**
    - treat todo (error rise) 
        - regen list
        - treat one by one
    - clean the code **OK**
    - comit **ok**
    - push **ok**
    - merge **ok**
    - push **ok**


- packaging study
- integration

- continue this list ;-)

.. WARNING:: To be completed
   :class: without-title

====================================================================================================
Task done (for memory)
====================================================================================================
- cache files on web browser : see :ref:`here<webBrowserCaching>` **OK**

- before regen todo list **OK**
    - 5 parameters not documented on csystem.cpp **CORRECTED**
    - count software todo 32 NECESSARY and 11 options **OK**
        - from doxy export docboock and on web docbook to txt **OK**
    - try to ordre them **OK**
        - Excel file created **OK**
        - Check if there are all uptodate rest 22 of 32 **OK**

- doxygen gen doc pb avec **REPAIRED**::

    0044-Iot_ESP_PPlug/projet/_3_software/IoT_EPS/doc/logo_alpha2_reduced.png perdu !

- UML and classes documentation 10% - web and json **ABORTED**

- two of the 6 todo From Bug_ToDoLst file **CLOSED**
    - change behavior on fatal error **CLOSED**
        - analyze :  :ref:`see sofDev.rst<newErrorHandling2022>`
        
    - oled display error **CLOSED**


- Error handling improvement (todo display low error with LED ? Which one : power led ?)
  A lot of work : change behavior on fatal error : do not sabord system but enable debug only with serial
  - switch to special branch : newErrorHandling **OK**

New pcb
----------------------------------------------------------------------------------------------------

- print schematic from easyEda site **OK**
- edit BOM **OK**
- group components **OK**
- solder components **OK**
- Programme watch dog component
    - solder a new one on adaptator board with small pin **OK**
    - programm it with avrdude commands see :ref:`here<refWatchdogProg>` **OK**
    - test it
- use ESP, watchdog and nano from old pcb **NO**
    - reprogram attiny 85 WD **OK**
        - and test it **OK**
    - reprogram new esp8266
        - upload data **OK**
    - reprogram new arduino nano **OK**
    - test it
        - I2C acces to reg(9) of nano IO expander !
        - I2C pull-up ? Probably on DS3231 board
        - I2C scan return the right adress 0X58 ! **OK**
        - try with rtc connected **OK**
            - returned add are ok **OK**
    - write a special program to test specifically communication with the nano
        - working dir  ``\_3_software\etudeDeCode\specialPcbV2\testDirectEspNano`` **OK**
        - not versionned on git, github **OK**
        - ``testDirectEspNano.ino``
- solve the usb vs main 5v power on esp8266 **OK**
    - search and eval shottky diode solution (1N5820 has a typical vf of 0.5V its to high) SS26 Solution **OK**
    - aop and mos solution **ABORTED**
        - from the arduino model
            - list component : LM358, FDN340P, 2x 10k
            - buy or find components
                - LM358 **OK** Mouser cde **OK**
                - FDN340P : MOSFET canal P 20V 2A SOT23 cdés sur AliExp arrivée prévue **OK**
                    - store near the prototype on 13/02/2022 **OK**
                - 2x 10k ok
            - group and store components
            - prototype it **OK**
                - define the solution veroboard/pcb/cnc machining **OK**
                - solder components **OK**
                - prepare the test **OK**
                - conduct the test **OK**
            - IF it is the choosen solution add it to the schematic

- replace relais by MOSFET on general power relay to switch them all in one time on power off **OK**                                                                                              
    - choose components (irf530 and irf9530, 2x 10k resistor see personal notes public ``hardware/analog``) **OK**
        - IRF9530 : ok buy to Mouser on 21 june  **OK**
        - but no irf530 test with 2N7000  **OK**
        - 2N7000 in SOT-23 to buy from RS **OK**
            -  due to the end test and verification ther is no need but already asked from Radiospares **OK**
    - buy or find the components **OK**
        - buy 2N7000 from RS in sot23 package **OK**
    - store components in safe place : a box  **OK**
    - prototype this solution see :ref:`here<refRelayMainPowerSwitch>`  **OK**
        - cut vero board **OK**
        - solder components **OK**
        - prepare test **OK**
        - conduct the test **OK**
    - integrate the solution into the plugs **OK**
    - test it **OK**

- new pcb **OK**

    - in the schematics **OK**
        - add above solutions **OK**
            - SS26 **OK**
            - FDN30P **OK**
        - replace through hole component by cms version every time it's possible **OK**
            - Q1 to Q4 2N7000 in SOT-23 **OK**
            - R1 to R12 in R0805 **OK**
            - move R5 to R8 on hot wire to reduce pin count **OK**
            - J1 remove 6 pins **OK**
            - P5 LED remove 3 pins **OK**
        - don't forget to switch D4 and D3 on U1 **OK**
        - rtc connector reduce 2 pin **OK**
        - group wifi led and power led on same connector and place R on signal and a common gnd **OK**
  
    - On the place and route stage **OK**
        - brainstorm connector solutions: reduce the number of pins and best placement **OK**
            - no connector near the lower edge of the board (minimum distance 10mm) **OK**
            - no connector near the upper edge of the board (minimum 8mm min) **OK**
            - prefered position for connector on right edge **OK**
            - at left edge no connector and no other hight components below main switch (on a 16mm 
              place of the pcb) **OK**
            - rtc connector on upper right **OK**
            - P7 mainpowswitch connector : on left side **OK**
            - P6 special PB : on upper side **OK**
            - J1 relays commands connector : on right side **OK**
            - perhaps turn right side connector in horizontal position **NO**
            - keep ARDUINO and ESP @ same place.  **OK**
            - no hight component near the edges of the PCB **OK**
            - double check the size of the footprint of SS26 **OK**
            - check the size of the footprint of FDN340P Q5 **OK**
            - check pinout of FDN340P **OK**
            - check footprint of the 2N7002 same size as Q5 **OK**
            - One unrouted 5V on 5V Transistor corrected **OK**

    - reroute pcb to reduce the size **OK**

- test it **OK**
    - P2 : 5V power **OK**
    - Screen oled **OK**
    - DS3231 RTC **OK**
    - watch dog **OK**
    - WIFI connection **OK**
    - not tested : led and bp and relay cde... **OK**
- integrate in the plug **OK**
    - question a new plug or the old one adapted ? old not enought time for a new plug **OK**
    - make modification to pass from old pcb to new pcb **OK**
        - remove serial resistor with LED on the wire (hide by heat shrink tube)


Logo
----------------------------------------------------------------------------------------------------
- add the 3Dprinted or CNC crafted logo see :ref:`here<3dLogoDesign>`
    - design **OK**
    - print V2 logo004.stl **OK**
        - x130% in Chitubox **OK**
        - 6.18ml of resin 0h48 to print **OK**
    - paint **OK**
        - fill cavities with paint **OK**
        - scratch excess of paint **OK**
    - glue in place **OK**

====================================================================================================
General
====================================================================================================
03/12/2021: connexion to github impossible. Repaired ssh config with git hub. 
But with the help of tortoise git to configure **CORRECTED**

====================================================================================================
PCB equipment
====================================================================================================
Version 1 : Equipped and tested in may/2021

.. ATTENTION::

    Warning for test WD is not connected

Version 2: equiped on 18/04/2022

====================================================================================================
IHM
====================================================================================================
- Pierre's version : on special github branch (not allways updated in the dev)
- A minimal one from Pierre (a very old one)

.. index::
    pair: Documentation; UML
    pais Documentation; plantUML

====================================================================================================
UML story
====================================================================================================
Just to try it on webserver (dir : ``_1_userDoc\UML`` ) + Modelio (i did not find the 
workspace ! ): it is on modelio_wks_isolACauseDeGit in the project folder because of git

Juin 2021: UML the return: after the discovert of `Graphviz`_ and `plantUML`_ !!!

.. _`plantUML` : https://plantuml.com/fr/ 

.. _`Graphviz` : https://graphviz.org/ 

:download:`Doc plantUML<fichiersJoints/PlantUML_Language_Reference_Guide_fr.pdf>`

`Doc officelle Graphviz`_

.. _`Doc officelle Graphviz` : https://graphviz.org/documentation/

====================================================================================================
Hardware
====================================================================================================
See :ref:`Hardware pogress<hardProgress>`

====================================================================================================
software
====================================================================================================
See :ref:`Software progress page<devProgress>`


====================================================================================================
Weblinks
====================================================================================================

.. target-notes::