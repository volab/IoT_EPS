++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Configuration and parameters
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date: October 2020
:Societe: VoRoBoTics
:Entity: VoLAB

.. contents::
    :backlinks: top


.. index::
    single: Configuration

===================================
Configuration parameter
===================================
 - add IP of AP mode
 - EPS name (host name)
 - Plugs names
 - Station SSID
 - Station mode passwd
 - Soft AP SSID and password

All json general section parameter without:
 - numberOfPlugs
 - rtcValidity
 
set time in AP mode and perhaps for station mode summer and winter time.

As for plugonof, we decide to build one configuration page for station mode and one configuration
page for AP mode because in station mode we can use CDN( bootstrap and jquery) functionality but 
not in AP mode because the embeded version of this :ref:`content delivery network (CDN)<refCdn>` are too 
big >3Mo.  


Action name : cfgsend (all in lowercase)
Action name to get json value updated page : cfgpage

Set time and date parameter names
----------------------------------------------------------------------------------------------------
setTime, setDate


.. index::
    single: Wemos; Config

=========================
ARDUINO Configuration
=========================

WEMOS D1 MIN ARDUINO configurattion:

.. image:: ./image/wemosD1Mini_configArduino.png


====================================
To be added to config json file
====================================

To be added 30/30/2019
 - firstBoot ON/OFF                                                                         DONE
 - Power led behavior versus economy mode (include or exclude) ON/OFF  powerLedEconomyMode  DONE
 - change/separate wifi Station param and soft app                                          DONE
 - add wifiSoftApSsid, wifiSoftApPass SSid are in credentials                               DONE
 - for C code, if wifiSoftApSsid or wifiSoftApPass are empty : creatIt (see @firstBoot)     
 - startInApMode : ON/OFF                                                                   DONE
 - remove wifimode                                                                          DONE
 - change IP in softAP_IP and Port in softAP_port                                           DONE
 - change name of the file to config4.json                                                  DONE
 
To be added 09/05/2019
 - IP add in soft AP mode to display it (what the utility ? to configure it)                DONE
 - mac add to display it                                                                    DONE
 - add ip in mode Station : to configure it if we are not in DHCP mode                      DONE
 - DHCP_mode : On or OFF                                                                    DONE
 - gateway add                                                                              DONE

 To be added 9/7/2019:
  - time zone

====================================================================================================
Weblinks
====================================================================================================

.. target-notes::