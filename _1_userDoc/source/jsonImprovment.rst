+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
JSON Improvements
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. contents:: Table of Contents
    :backlinks: top


.. |clearer|  raw:: html

    <div class="clearer"></div>

====================================================================================================
Json file improvements : analyze
====================================================================================================
Simple improvements
====================================================================================================
05/07/2021:

CPowerPlug::readFromJson() : move up configFile.close(); at l253 to l189

readFromJson twice defined. Ontime in CPowerPlug and on time in ConfigParam: not the same method. 
One for Plug parameters and one for general parameter

ConfigParam::readFromJsonParam() : move up configFile.close() Too

CpowerPlug::on, off toggle, updateOutputs could be private

JSON structure
====================================================================================================
.. uml:: graphviz/config4json.wsd

JSON structure vs variables
====================================================================================================
.. uml:: graphviz/config4jsonVsVariables.wsd

Lines in green tag differences between json and class members.

emplacement, startInAPMode and ntpError exist in json but not in the ConfigParam class.

_wifiMode exists in ConfigParam class but not in json

In the same maner for plug structures:

hDebut, hFin, dureeOn, dureeOff, clonePlug and onOffCount are in json but not in the class.



22/07/2021: creation of the members of ConfigParam:

- _emplacement
- _startInApMode
- ``_clé à créer 1_`` : becomes wifimode in config4.json

About ntpError json parameter:

- write in the loop at line 396 in cbit.

- and write in CSystem::timeServerCheck

but what is its usage ??? in the system ?

.. WARNING::

    Don't confuse String CPowerPlug::_plugName and nickName

On power plug class side, creation of new members:

String nickName, hDebut, hFin, dureeOn, dureeOff, clonedPlug, onOffCount.


Write to file improvements
====================================================================================================
**First question**: track all json config file access by tracking all usage of CONFIGFILENAME

See GraphViz diagram : IoTEps config4.json access

.. graphviz:: graphviz/config4Access.gv

Conclusion there are 2 places that write to json file : in ConfigParam Class for configuration
parameters and in Cpowerplug class for plugs parameters.

There are 6 methods that write to json file:

- "CPowerPlug::handleBpLongClic()"
- "CPowerPlug::writeToJson(p,v)"
- "ConfigParam::write2Json()"
- "ConfigParam::creatDefaultJson()"
- "CPowerPlug::writeDaysToJson()"
- "CServerWeb::handelIOTESPConfPage()"

**Second question**: after track all usage of write to json methods

**third question**: what are the events that trig writes on json file ?

handleBpLongClic
====================================================================================================
This method is used 3 times in the ino file. One time in the setup and 2 times in the loop.
The purpose of this function is to force plugs modes to manual. After power off switching or
after a long press on the plug's button

.. graphviz:: graphviz/handleBpLongClic.gv


CPowerPlug::writeToJson(p,v) and writeDaysToJson
====================================================================================================

.. graphviz:: graphviz/CPowerPlugWrites.gv


The second one could be a private method

From configParam classe
====================================================================================================
In configParam class there is only 2 methods that directly write to config4.json file.

- writeTOJson( p,v,f ) : the MAIN function
- creatDefaultJson() : to restaure a fresh file when corrupted

Write to json events
====================================================================================================

.. uml:: graphviz/writeEventsGlobal.wsd

----------------------------------------------------------------------------------------------------

.. uml:: graphviz/wrtiteEventsWebdetails.wsd

----------------------------------------------------------------------------------------------------

.. uml:: graphviz/writeEventsTimeToSwitch.wsd

----------------------------------------------------------------------------------------------------

.. uml:: graphviz/writeEventsWebPlugOnOff.wsd

====================================================================================================
JSON improvements : rewriting stage
====================================================================================================

On git branch : json_new : terminated on 2021 november


Strategy : **obsolete** see REX Reflections
====================================================================================================

One json master file : config4.json (no change) and now we introduce 2 copies

Throughout operations, Json data **reside** in RAM : this is the **most important change**.

On web and plug events, write2json methods do not write directly to the file, they change data in RAM
and after all changes, file is store in SPIFFS and 2 copies are made with hash verification.

At startup, hash of the 3 files are checked to determine what file is good and what file is corrupted.
After this check, the good file is loaded or none if all 3 files are corrupted. In this situation a
new system error is risen.

See the figures below.


.. uml:: graphviz/jsonNewStrategyStore.wsd

.. WARNING::

    Pb: in the write procedure, if power is shut down just after first json write, the master file 
    is good but the file has a different hash value of copy1 and copy2

    Pb2: if power is shut down just after the write of copy 1, 3 hash values are different but
    master is good !
    
    To solve this possible bug we decide to had a special field in the json file to check the 
    readability of the data in the file (jsonTag and jsonVersion).

As we can't compute hash directly on the file but only with data in RAM, the file store strategy 
presented here is not feasible.

So finally we made 3 stores, check the 3 hash values if there are not same we retry 3 times. After 
3 tries, we rise a fatal error.

**REX reflections**::

    With json files, we can't compute checksum, crc or hash value and put it directly in the last octets 
    of the file as it is made with binary config files.

    We need json for direct send by the html server to the web browser's client.

    Today we don't have a lib to compute the hash value directly on the SPIFFS file and even if we find
    one where to store the value ? In an other file ? In this case it creates a new pb if power is shut down
    just between the 2 writes. No luck !

    An other reflection where errors came from ? at the write time or at the read time ? We suppose at the 
    write time, just after the function open as write of the file and power is shut down before the real
    write process.

    The technique of the hash in 3 files is not enough robust. Example: if a write error arrives just 
    at the second write, we have 3 different hashes and we can't conclude. In the same way, we have an 
    error on the first write, a right write on the second and just after a power shut down, here we have
    3 different hash values.

    To correct this we add some tags in the file, so if we put a tag at the beginning of the file and one
    at the end, if this 2 tags are good there is great chances that file is correct.

    Finally we decide to write only 2 files and keep the third as a template to restaure a default
    situation if the 2 others files are corrupts. This Third file is only writes when the user 
    change the configuration.

    Another way (but not implemented), would be to store hash value somewhere in a file or in the nano eeprom and in the 
    load process we keep the first couple hash,file that is correct !

----------------------------------------------------------------------------------------------------

|clearer|

.. uml:: graphviz/jsonNewStrategyLoad.wsd
    :align: center

|clearer|

Json data in RAM (obsolete)
====================================================================================================

How to create ? A check at `ArduinoJson documentation`_

Static or Dynamic json Document ?

::

    The memory of theJsonDocument can be either in the stack or in the heap. The location depends on the 
    derived class you choose. If you use a StaticJsonDocument, it will be in the stack; if you use a
    DynamicJsonDocument, it will be in the heap

.. _`ArduinoJson documentation` : https://arduinojson.org/v6/doc/

From my reads, the technique is to keep a simple structure in RAM and to create the json object at
write or load time. Not to keep the json object throughout operations.

**It is not a good idea to keep Json object** in memory see `Arduinojsondoc Why is it wrong to reuse a JsonDocument?`_

.. _`Arduinojsondoc Why is it wrong to reuse a JsonDocument?` : https://arduinojson.org/v6/how-to/reuse-a-json-document/

.. warning::

    More : data are already in ram : in configParam and in plugs[] instances !!!!!!
    
    The new class needs only 2 pointers to access to this data.



Modifications
====================================================================================================

Class CJsonIotEps created. Instance jsonData in .ino file created.

**Question**: new instance in .ino or in class CSystem ? (answer is just below)

@startup stage : how load the json into ConfigParam and in the plugs ? All the above graphics 
don't answer to this question !!!!!

sysIoteps.init -> ConfigParam.begin -> ConfigParam.readFromJson

.ino (setup)::

    if ( mainPowerSwitchState ) sysStatus.plugParamErr.err( !plugs[i].readFromJson( true ) );

This line restaure plug parameters

**Answer**: new instance in the .ino file

**Question**: who need to call new class ? CSystem, ConfigParam, CPowerPlug ?

In others words, who init with what ? New class with a pointer to ConfigParam and CplowerPlug or
this 2 class with a pointer to new class

**Answer elements**: 

- ConfigParam and CPowerPlug need to trig write on json file
- at startup CJsonIotEps needs to populate ConfigParam and CPowerPlug

This 2 classes already have their own readFromJson method.

At startup ConfigParam and CPowerPlug could ask to CJsonIotEps to read their parameters

**Answer**: ConfigParam and CPowerPlug have a new member : a pointer to CJsonIotEps instance.

22/07/2021: creation of the members of ConfigParam:

- _emplacement
- _startInApMode
- ``_clé à créer 1_`` : becomes wifimode in config4.json

About **ntpError** json parameter:

- write in the loop at lign 396 in cbit.

- and write in CSystem::timeServerCheck

but what is its usage ??? in the system ?



Hash lib (obsolete)
====================================================================================================
There is a class example on arduinojson.org to compute CRC32 of json object or array. 
`See arduinojson.org/v5/doc/tricks`_ §Compute hash of JSON output

.. _`See arduinojson.org/v5/doc/tricks` : https://arduinojson.org/v5/doc/tricks/

With this way, we need to load data in RAM !

An other example provided `on Arduino lib github`_

.. _`on Arduino lib github` : https://github.com/esp8266/Arduino/blob/master/libraries/Hash/examples/sha1/sha1.ino

it works on RAM data too !

====================================================================================================
Conclusion
====================================================================================================
A new class **CJsonIotEps**, instance **jsonData** as a global variable in the ino file.

2 classes CJsonIotEps received a pointer to ConfigParam and CPowerPlug and they are friend 
class of CJsonIotEps so that jsonData can access to their members.

2 classes has a _jsonWriteRequest private member accessed by jsonData.

CJsonIotEps has 2 methods : loadJsonConfigParam and loadJsonPlugParam

Only CJsonIotEps read and write the files. At startup, json is red in 2 steps, the class load config
parameters and after some necessary operations, it populates plugs data.

At the end of the main loop  check if a write request is rise by config or by plug classes and 
if yes  jsonData writes the files main copy1 and only if configuration are changed copy2

informations in `Modifications`_ section are right.


ConfigParam and CPowerPlug