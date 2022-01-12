++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Liste of tests to be conducted
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date de création: 01/2022
:Date dernière maj: 08/01/2022
:Societe: VoRoBoTics
:Entity: VoLAB

.. contents::
    :backlinks: top

====================================================================================================
Presentation
====================================================================================================
The idea is to write a copy of this section each time a complete test is made.

====================================================================================================
The list
====================================================================================================
- ap mode
    - change ssid
    - change password
    - plug test

- station mode
    - ...

    - only on one plug (plug test)
        - manual mode on / off /on /off
        - manual mode with hfin
        - manual mode with on duration
        - timer mode
        - timer mode restart with bp
        - timer mode differed start with button
        - cycle mode
        - cycle mode with diff start HH:Memory
        - cycle mode pause from web interface
        - cycle mode pause with push button
        - hebdo mode few days (first and last day)
        - hebdo all days
        - hebdo pause from web interface
        - hebdo pause with push button

- power loosing / restaure state


- with push Button
    - basic on/offs
    - push button to force manual mode

- special push button test

- power switch off 
- power switch on

- master json corruption

- ... TBC

----------------------------------------------------------------------------------------------------

.. WARNING::

    hebdo modes are difficult to test cause we need to wait few days to check the result !!!
    We need to find a solution


====================================================================================================
08/01/2022 test
====================================================================================================
Basic test in ap mode from web interface only conducted on green plug only

- station mode
    - ...

    - only on one plug (plug test)
        - manual mode on / off /on /off **OK**
        - manual mode with hfin **OK**
        - manual mode with on duration
        - timer mode stay in mode and keep time after elapsed time **OK**
        - timer mode restart with bp on green plug **OK**
        - timer mode differed start with button
        - cycle mode
        - cycle mode with diff start HH:Memory
        - cycle mode pause from web interface
        - cycle mode pause with push button
        - hebdo mode few days (first and last day)
        - hebdo all days
        - hebdo pause from web interface
        - hebdo pause with push button

- power loosing / restaure state

- with push Button
    - basic on/offs
        - green **OK**
        - red **NOT WORK**
        -yelow and bleu **PERMUTED**
    - push button to force manual mode


====================================================================================================
Weblinks
====================================================================================================

.. target-notes::