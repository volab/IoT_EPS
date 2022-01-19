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
- doxygen gen doc pb avec::

    0044-Iot_ESP_PPlug/projet/_3_software/IoT_EPS/doc/logo_alpha2_reduced.png perdu

- treat 5 BUG From Bug_ToDoLst file
    - wrong global table refresh
    - cfgpage / cfgsend : configuration page (see Bug_ToDOList.rst)
    - clone pause
    - untimely switching
    - push button permuted on yellow and green


- treat 6 TODO From Bug_ToDoLst file
    - oled display error
    - change behavior on fatal error
    - Pause display
    - minify javascripts
    - doxy HTML js
    - file names coherence

- Error handling improvement (todo display low error with LED ? Which one : power led ?)
  A lot of work : change behavior on fatal error : do not sabord system but enable debug only 
  with serial

- complete testToBeConduted see :ref:`here<testToBeConducted>`
    - exhaustive test of hebdo mode : **95%**
- write index special page for softAP Mode with local boostrap or other light js.framework **5%**
- Create an infographic that summarize features and needs 
    - choose tool
    - choose Size
    - choose colors
- Write user manual : **1%**
- Write builder manual
    - mechanical parts
    - buy and groups components
    - oder pcb



- UML and classes documentation 10% - web and json **ABORTED**


Don't forget the todo list of the **doxygen documentation** and **git history**:

    - before regen todo list


- Minifier all files if possible of course and reduce the size of the images
    - minifier picture
    - minifier css
    - minifier html

- try gz files

- improve json file managment **2 points need work**
    - write process
        - test **ok**
            - environnement conda test **ok**
            - write python script to log boot sequence to a file: in progress ``projet\_3_software\outilPythonSpecial`` **ok**
            - record some boot sequence **ok**
            - check boots sequence **ok**
    - treat todo (error rise)
        - regen list
        - treat one by one
    - clean the code
    - comit **ok**
    - push **ok**
    - merge **ok**
    - push **ok**


- packaging study
- integration
- replace relais by MOSFET on general power relay to switch them all in one time on power off
    - choose components (irf530 and irf9530, 2x 10k resistor see personal notes public ``hardware/analog``) 
        - IRF9530 : ok buy to mouser on 21 june  **OK**
        - but no irf530 test with 2N7000  **OK**
    - buy or find the components  **OK**
    - store components in safe place : a box
    - prototype this solution
        - cut vero board
        - solder components
        - prepare test
        - conduct the test
    - integrate the solution into the plugs
    - test it
- solve the usb vs main 5v power on esp8266
    - search and eval shottky diode solution (1N5820 has a typical vf of 0.5V its to high)
    - aop and mos solution
        - from the arduino model
            - list component : LM358, FDN340P, 2x 10k
            - buy or find components
                - LM358 ok mouse cde OK
                - FDN340P : **nok** MOSFET canal P 20V 2A SOT23 cdés sur AliExp arrivée prévue **Dec03**
                - 2x 10k ok
            - group and store components
            - prototype it
                - define the solution veroboard/pcb/cnc machining
                - solder components
                - prepare the test
                - conduct the test
            - IF it is the choosen solution add it to the schematic
- new pcb
    - add above solution
    - replace through hole component by cms version every time it's possible
    - brainstorm connector solutions: reduce the number of pins and best placement
    - reroute pcb to reduce the size
    - don't forget to switch D2 and D3 on U1

- add the 3Dprinted or CNC crafted logo


- continue this list ;-)

.. WARNING:: To be completed
   :class: without-title

====================================================================================================
Task done (for memory)
====================================================================================================
- cache files on web browser : see :ref:`here<webBrowserCaching>` **OK**





====================================================================================================
General
====================================================================================================
03/12/2021: connexion to github impossible. Repaired ssh config with git hub. 
But with the help of tortoise git to configure **CORRECTED**

====================================================================================================
PCB equipment
====================================================================================================
Equiped and tested in may/2021

.. ATTENTION::

    Warning for test WD is not connected

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