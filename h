* [33mf935cec[m[33m ([m[1;36mHEAD -> [m[1;32mdevFirmware[m[33m)[m on the road to new pcb
* [33m9196e1c[m[33m ([m[1;31morigin/devFirmware[m[33m)[m bug on main power switch corrected
* [33m7a546df[m bug corrected
* [33m9c9786a[m preparation to correct bug dureeon dureeof not reset
* [33m9cda614[m 3D printLogo design
* [33m341b351[m Documetation
* [33m04bc364[m[33m ([m[1;32mnewErrorHandling[m[33m)[m newErrorHandling finished !
* [33mfccc0dc[m New commands B and b : ok
* [33m6113319[m command to rise error is already terminated see SerialCommand.cpp
* [33m6de3d63[m little bug in fatal error count for display corrected
* [33mccda447[m B and b commands added to the help menu
* [33m6a7f990[m new Z command to set WD to 4mn to upload firmware
* [33md54c8e0[m help cmds rearanged
* [33maa879af[m new method isThereFatalError but no tested
* [33m51da8fd[m code ckeaning
* [33m6e3dc1a[m writeToJson in Cpowerplug erased and clean comments
* [33mafaf64c[m writeToJson commented it seems towork fine
* [33mb44ed81[m CJsonIotEps::_hashFile commented
* [33mef68461[m cpowerplug cleanup 2 todo
* [33m926807d[m documentation correction checkJsonOneFileIntegrity
* [33m7698c08[m documentation correction 4 doc errors like pNanoioExp...
* [33m8b217a5[m documentation correction necessaryFileList
* [33m2e946bd[m ajout doc logo_alpha2_reduced.png pour Doxygen fichier perdu !
* [33medc2dcc[m caching file ok
* [33m64596b2[m Documentation process
* [33m5c21d00[m preparation for web catching
* [33m7115c39[m find bug bp2 and 3 permutted on pcb reroute to correct
* [33m38957c7[m on/off count bug corrected
* [33m1fb09f5[m list of test added
* [33m2196e15[m bug restaure physical state correction
* [33m46e5238[m writeDays tuning
* [33m9fc12b9[m correction of the for loop to store days but not tested + list test doc introducted
* [33mb6219c1[m code cleaning and lots of inducted bugs corrections
* [33m94561ad[m bug json plugs not writed corrected but not tested
* [33m12d7f78[m start of code cleaning
* [33md828f9d[m One todo in the code removed
* [33m0fe899c[m Shutdown message added to oled
* [33mad29229[m Watchdog ok, oled display sys state display speed slow down and litle change
* [33m2e80f19[m[33m ([m[1;32moled-display-erro-bug[m[33m)[m oled display error bug corrected
* [33m6f7d1e5[m new oled bug !
* [33m9cad0a4[m some typo corrections
* [33mbb734d1[m bug display wd corrected but new bug see softdev.rst
* [33m362bb02[m add some print on watchdog test function to see 4 returned test values
* [33m71914fa[m CSysStatus::display() changed with sysErrorTable
* [33m5a6952b[m config.h and config_advenced.h added (not the right branch but...)
* [33mac04091[m start of wd bug traitment
* [33mc825f79[m typo correction
* [33mbcf856b[m ssh config ... with github
* [33mb480c43[m[33m ([m[1;32mjson_new[m[33m)[m The end of json_new branch
* [33mb96a389[m add watchdog hex file !
* [33mfa71f52[m Pb with watchdog ATTiny85
* [33m41be291[m[33m ([m[1;31morigin/json_new[m[33m)[m json improvment writed, todo: conduct more test
* [33md81f557[m check integrity ok, read ok, new json with version at the end ok v5.1
* [33md4802c2[m checkJsonFilesIntegrity before new paradigm
* [33mf91cbce[m some litle change before rewrite test in chek integrity of json, write method always in writ in progress
* [33me4b79b7[m strore to json one file write in progress, todo : continue with plugs parameters
* [33m12c78c6[m StoreOneJson write in progress
* [33m3d629e2[m conf page handler rewrited
* [33m0124850[m CServerWeb::handelIOTESPConfPage rewrited end operational
[31m|[m * [33m376165e[m[33m ([m[1;32manalyseFreeMem[m[33m)[m memory analysis end
[31m|[m * [33m6364ee6[m cfgpage handler rewritting wip
[31m|[m * [33m26f2170[m[33m ([m[1;32manalysebis[m[33m)[m En progret dans la boucle loop
[31m|[m * [33mdfbc86f[m Analyze to wevbserver start remove unused function to win 910 bytes
[31m|[m[31m/[m  
* [33m6116a85[m freemem ! dans configParam.cpp
* [33m6c4f352[m Toujours à la recherche du bug
* [33m1bbc65a[m bug de la fonction cfgpage (nécessaire pour mes test)
* [33m315cdae[m Add timig diagram and preparation to write json request (change static CPRAM method to non static)
* [33mc55a732[m Change J debug commande to display one of the 3 json files
* [33mc0198aa[m json load ok but not fully, fully tested
* [33m32d5151[m WIP plugs members updates
* [33mb9f27b7[m WIP read plug param from json start of member update.
* [33m5d6e554[m wip read json plugs param (wrong branch)
* [33md50bd15[m index on json_new: 53447e7 Read config param Ok
[32m|[m * [33m05315d0[m[33m ([m[1;32mmesurePerfBP0_D6[m[33m)[m handleFileRead mes.
[32m|[m * [33m60c0334[m handelPlugHtmlReq mes
[32m|[m * [33m4d43f20[m plugOnOff without Serial Debug
[32m|[m * [33madb414a[m plug on/off mes
[32m|[m * [33m52e8892[m Version mesure du cyle total
[32m|[m * [33me0dd5d6[m ESP8266 D6 pin free
[32m|[m[32m/[m  
* [33m53447e7[m Read config param Ok
* [33md635447[m Json load config in progress...
* [33m1376cd9[m checkFile integrity wrote and checked
* [33m2311af7[m Now it compile but i don't understand the behavior of the compiler !
* [33mb997c89[m Block on jsonFileIntegrity_t enum as a return value of a method
* [33m8cbd803[m Placement of &jsonData in ConfigParam and in CPowerPlug
*   [33m7bc780c[m Merge branch 'json_new' of https://github.com/volab/IoT_EPS into json_new
[34m|[m[35m\[m  
[34m|[m * [33m0845e70[m first run : change config4.json files
[34m|[m * [33md202d51[m ajout graph config4 json
[34m|[m * [33m57df850[m start to write CJsonIotEps
* [35m|[m [33mf399e15[m avant rebase
* [35m|[m [33mc553f03[m Some changes in explanation
* [35m|[m [33m89afb0f[m first run : change config4.json files
* [35m|[m [33m59d3491[m ajout graph config4 json
* [35m|[m [33m64333d5[m start to write CJsonIotEps
* [35m|[m [33md2459d6[m Correction de if ( _oledCptErrToDisplay = 0 )
[35m|[m[35m/[m  
* [33mc983d01[m[33m ([m[1;32mpetiteModifPlugSystem[m[33m)[m UMl Documentation
* [33m40d660b[m web event plugonoff doc
* [33m0e2dcf7[m Documentation de la partie écriture json avec graph uml
* [33m1073479[m Documentation phase of writes to json
* [33m3dcabc6[m some little tuch and documentation graphviz experimentation start
* [33m1fdb9ac[m A lot of files modified but bug, I didn't find the bug! I put IDE in Wifi debug mode and the system return to a normal behavior !
* [33m04b1aa0[m Bug: SoftAP fails after oled creation. Not directly linked to oled features. First code reading without success. Need to run some debug session with hardware.
*   [33m2edf1ee[m Merge branch 'oled' into devFirmware
[36m|[m[1;31m\[m  
[36m|[m * [33m9cad62c[m[33m ([m[1;31morigin/oled[m[33m)[m oled display ended.
[36m|[m * [33m2f26b60[m warning cleaning + oled display error implementation (not complete).
[36m|[m * [33m6a9b0b2[m Oled state in progess : plug name display mode ok
[36m|[m * [33m72e03f9[m oled display ok : todo : decide what to display on the state line !
[36m|[m * [33md90caa3[m Some little change for compil warn and oled loop display prepare
[36m|[m * [33m696ff03[m Supress compil warning stage
[36m|[m * [33m72764ca[m initTimeZone not used in the .ino file and 4 compilation warnig suppresed in CWebserver
[36m|[m * [33mde28ae3[m Somme Doxygen corrections !
[36m|[m * [33m81f9e4e[m Merge fichier CServerWeb.cpp correction bug POST GET
[36m|[m * [33mb6618b3[m find a bug on ChangeCred in html method POST and in CServerWeb method get
[36m|[m * [33m5fa59f1[m 4 oled methods in CSystem Class
[36m|[m * [33m53a0e13[m a lots of jobs
[36m|[m * [33mfb59449[m essais ecran svg
[36m|[m * [33m9087976[m A long time ago...
[36m|[m * [33mdb4e40a[m Grosse update après bien longtemps
[36m|[m * [33mf39fb26[m definition des écran en cours
[36m|[m * [33m36710d8[m merge repertoire source de userDoc !
* [1;31m|[m [33m4fbcd4b[m Correction bug ChangeCred method POST / GET
* [1;31m|[m [33m8e1eb71[m Une bricole To Do : desing oled screen for loop
* [1;31m|[m [33m9e70773[m Merge branch 'oled' into devFirmware
[1;32m|[m[1;31m\[m[1;31m|[m 
[1;32m|[m * [33md64f8db[m Oled premiere grande etape franchie. Fin du boot.
[1;32m|[m * [33m188527e[m mainPowSwitchOk
* [1;33m|[m [33m3a61cab[m Software documentation new organization
[1;33m|[m[1;33m/[m  
* [33m56aff6f[m oled reparation de depot local
* [33m2b3046e[m Remise à 15mn time server Check
*   [33mc927d19[m Merge branch 'devFirmware' of https://github.com/volab/IoT_EPS into devFirmware
[1;34m|[m[1;35m\[m  
[1;34m|[m * [33mc1d7739[m Clean up after CPowerPlug refactoring
* [1;35m|[m [33mc6ce626[m A priori bug corrigé
* [1;35m|[m [33m30c45fe[m Clean up after CPowerPlug refactoring
[1;35m|[m[1;35m/[m  
* [33m8b453c2[m CpowerPlugs refactoring OK
* [33mf288055[m I2C test into CSystem and confParamCheck OK tested
* [33m68fbf5a[m Necessary file check OK
* [33m939e76e[m File system check in CSystem ok : tested
* [33mdbc2832[m Special BP1 action take place ok
* [33m6a42bca[m Some comment cleanup
* [33m3b959bd[m CRtc::update() ok
* [33mb63d380[m timeServerCheck() fonctionnelle, todo : mettre au point displayTime() et update()
* [33m202f47d[m It's compile. One comment and one ,
* [33m205a35f[m all is implemented but not tested
* [33m613c09d[m Nettoyage de commentaires devenu inutiles atomic comit
* [33mfbea8bd[m CWifiLink manque plus que simpleManual modeChaser. Sorti ModelioWks trop le bordel avec git.
* [33m9b23aa2[m CWifiLink.cpp nettoyage des commentaire
* [33m6584413[m CWifiLink en cours d'écriture...
* [33md3cb4e9[m ajout loreOO.mm
* [33m70b7acf[m tentative de passae de wifi par reference (ça compile)
* [33m3322c31[m Sur le long chemin du Wifi begin( *pWifi )
* [33mee2844b[m Début de la construction de la classe CWifiLink afin de nettoyer un peu le setup
* [33mcf35ac7[m début du travail sur l'objet WiFiLink
* [33m08320d7[m Suite rebase on systemObject
* [33mbf0c218[m[33m ([m[1;31morigin/systemObject[m[33m)[m Nettoyage des commentaires
* [33mc7ac262[m /firstBoot : ok fin de la création de la classe webserver
* [33ma5280b4[m /newCred ok + correction bug if "nf"
* [33m83cfb93[m /cfgpage et /cfgpage ok
* [33mdd8e0f7[m Handle index ok + testé à la fois en mode AP et en mode station en même temps
* [33m499ff2e[m /edit delete ok! upload ok creat ok !
* [33m962c412[m /edit creat fonctionnelle
* [33m39ec827[m /edit fonctionnelle
* [33m0a04a59[m Chemin /help fonctionnel
* [33mccf3008[m plugonoff testé + /list?dir=/
* [33m0d7354e[m A compilé mais pas testé : grosse modif intégration plugonoff fonction à webserver
* [33m0db72b9[m /time fonctionnel !
* [33mcb113ba[m toujours pas fonctionnel !
* [33m39f9d41[m En cours non fonctionnel coté web
* [33m9e21ca2[m codeToutCasse
* [33mc58b36f[m start of cleaning  CRtc and DS3231 rtc instances
* [33m1bc8141[m En route vers CSystem mais la route est longue !
* [33m33d65ec[m Début d’écriture de Csystem
* [33mdd7a638[m 9a démarre doucement, utilisation de VisualStudio code
* [33m5bd66a7[m Tentative d'assenaisement
* [33m10e0069[m Création de la branche noSaborde
* [33mc93740d[m Peti maj doc pour forcer commit push sur la nouvelle branche devFirmware
*   [33m61e0e5c[m Merge branch 'dev_Jojo-PC'
[1;36m|[m[31m\[m  
[1;36m|[m * [33m50b6372[m Vers syetm documentaire Sphynx.
[1;36m|[m * [33mf24b3b0[m petite maj doc
* [31m|[m [33mc2f4ec3[m Apres 3 mois d'arret COVID-19
* [31m|[m [33m70be40c[m doc update
* [31m|[m [33mf94e555[m Reprise après le projet Robot Junior
[31m|[m[31m/[m  
* [33m90f935b[m comment and clean the new server function !
* [33me2d47d1[m add a fork for index page in AP mode or in Sta mode in serverFunction.cpp it is the purpose of the function void handleIndex().
*   [33m9dfbd7a[m Merge branch 'STA_AP_mode' into dev_Jojo
[32m|[m[33m\[m  
[32m|[m * [33mfd22ee3[m All is working ! apparently. It is time to merge.
[32m|[m * [33m48b6a32[m Pause to verifiy netError name in json
* [33m|[m [33mc4302a6[m just Execel little correction
* [33m|[m [33m0640c17[m correct ntpErr line 623 .ino
[33m|[m[33m/[m  
* [33m779650c[m restore defConfig.json when firstBoot implemented but not tested
* [33mae66f5d[m return to config page after a configuration to confirm parameters
* [33m5713f3f[m bug one second corrected
* [33maff4b45[m ATtiny85 I2C WatchDog integrated + some code cleanup
* [33m21b1a3e[m watchdog implementation start. Compiled but not tested and a lot of work to do...
* [33m0b2c64b[m defConfig fine tuned
* [33mf1a7daa[m lib Adafruit MCP23017 and Flasher removed and some todo review
* [33m7dbd4f7[m Credentials page ok + todo review with [OPTION] and [NECESSARY] classification
* [33me3501e2[m config set time ok
* [33m3689908[m config page with placeholder from json ok, action is cfgpage
* [33mb8862f3[m configuration ok
* [33m180d71e[m config handler : WIP uri reception ok
* [33mde6bc04[m false config page not versionned
* [33m948185e[m Internet health check ok
* [33m772c1c2[m Documentation and cleanup
* [33m5c0306d[m PB1 special command to repair config4.json file in debug mode
* [33ma5f62e5[m internet test response : WIP a good solution  find, needs to be correctly implemented.
* [33m334337d[m ping : WIP
* [33m38bd884[m pinging : WIP
* [33me422cda[m CBIT of ntp server + necessary files...
* [33m51c2c76[m add DNS server in non DHCP mode
* [33ma09f4b1[m Test DHCP mode off + add gateway in Json
* [33mbb03696[m non DHCP mode coded but not tested + add softAP macc add in json
* [33md23029c[m write station mac add into json
* [33m1cb14a6[m Read number of retry to connect to station from the json file
* [33m6fd495c[m CBIT I2C
* [33m6b88d8a[m WIP time management...
* [33m0cca51d[m WIP : time strategy implementation... compiled but not tested
* [33mb422c25[m Some code cleaning
* [33m6af0889[m A very important improvement of error handling, not completely finished but well advanced. Soma adds to config4.json
* [33mdf8f16b[m WIP on the road of error Handling...
* [33m77cc9fb[m WIP to error handling. Stanby due to change BP and relays pining. Special branch : relayChange
* [33md02fdbe[m sysStatus.fsErr implemented
* [33m3ce4088[m NTP name in IoT_EPS.h file
* [33m8846e6a[m Doc update and STAmaxWifiConnectionRetry to json model
* [33m23f2b78[m LED wifi and power switch ok
* [33m27fde71[m Change pin for main power switch and wifi Led Wip
* [33m9126f80[m Avant chnagement code Main power
* [33md650d5d[m CSysStatus class introduction + power up debug !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
* [33mbc62e02[m firstboot procedure OK, todo a complete test pass. i2c_recovery() active but just one time. Do 2 or 3 try before jump to fatal error mode.
* [33m0a0a29e[m main power switch handling with esp.restart();
* [33m29b3e20[m fisrtBoot : work in progress, AP mode ok. ToDo Station mode + error handling
* [33ma9534ed[m first boot : work in progress
* [33m72622c0[m Main power reflection but not implemented.
* [33mbd5b3fd[m first boot strategy preparation
[33m|[m * [33md2a7f0c[m[33m ([m[1;31morigin/dev_pierre[m[33m)[m Commit apres merdage
[33m|[m * [33m2ca07f8[m UP: config4.json + ADD: config.html
[33m|[m * [33md4e5e95[m sidebar.css: suppression du media 'max-width 768'
[33m|[m * [33m55ce205[m Index + main + table: ajout de la fonction rafraichir accueil
[33m|[m * [33mf812474[m index.html + style.css: mise en place de la navigation responcive
[33m|[m * [33m68377a3[m style.css: suppression des bordures de fieldset
[33m|[m * [33mc8d665f[m index.html: suppression des blocs commentés
[33m|[m * [33m028760e[m firstboot.html + style.css: finalisation de la page firstboot
[33m|[m * [33m2e16c33[m firstboot.html: Creation de la page firstboo.html
[33m|[m * [33mc558d32[m main.js: gestion bouton reset ; plug.js: nettoyage
[33m|[m * [33mc963b81[m main.js + plug.js: modification du comportement du bouton effacer dans le mode Manuel
[33m|[m *   [33m76601b0[m commit après merge de la branch 'dev_jojo'
[33m|[m [35m|[m[33m\[m  
[33m|[m [35m|[m[33m/[m  
[33m|[m[33m/[m[35m|[m   
* [35m|[m [33m05576ad[m return to index page active
* [35m|[m [33m27cceb3[m large modification, config4.json intro. Research about softAP mode.
* [35m|[m [33mac02290[m HTML IHM integration version
* [35m|[m [33m139f4c5[m doc improvement
* [35m|[m [33m7ef6ecc[m some very small corrections
* [35m|[m [33m1c582be[m add a reame for test dir _1-1_
* [35m|[m [33m3bacc69[m switch off ALL led with main power switch
* [35m|[m [33m0933c61[m just some documentations adds
* [35m|[m [33ma6b363e[m main power led managment added (forget)
* [35m|[m [33m4510d35[m display unix local time from RTC
* [35m|[m   [33mdfee098[m Merge branch 'dev_Jojo' of https://github.com/volab/IoT_EPS into dev_Jojo
[1;31m|[m[1;32m\[m [35m\[m  
[1;31m|[m * [35m|[m [33m162a630[m clone mode integration
* [1;32m|[m [35m|[m [33m0754ddc[m short doc change
* [1;32m|[m [35m|[m [33mdbbab55[m clone mode integration
[1;32m|[m[1;32m/[m [35m/[m  
* [35m|[m [33m1cfb4cd[m some little modif
* [35m|[m [33m071ba10[m integration: work in progress, bug with cr/LF in json corrected, bug onTime = 0 or empty corrected
* [35m|[m   [33m925b2a5[m Merge branch 'dev_pierre' of https://github.com/volab/IoT_EPS into dev_Jojo
[1;33m|[m[1;34m\[m [35m\[m  
* [1;34m|[m [35m|[m [33m77bd8d8[m ftp server + BP wakeup + an other step to error handling
* [1;34m|[m [35m|[m [33m9b13937[m main code reorganisation and a steo to better error handling
* [1;34m|[m [35m|[m [33m0ae7e8f[m Led main power ok + start error missing credential handling
* [1;34m|[m [35m|[m [33ma8e5b94[m html main power off response implemented but not tested
* [1;34m|[m [35m|[m [33m81600e2[m bug correction. updateOutputs
[1;34m|[m [1;34m|[m * [33m8fc5c81[m main.js: MAJ des TODO
[1;34m|[m [1;34m|[m * [33m0d6c2be[m table.js: correction de la convertion du temps utc vs local time
[1;34m|[m [1;34m|[m * [33madd84f7[m table.js: convertion nextTimeToSwitch en miliseconde
[1;34m|[m [1;34m|[m * [33mb939964[m index.html + table.s: ajout de l'heure du prochain changement ds le tableau d'accueil
[1;34m|[m [1;34m|[m * [33mbc53a23[m main.js: correction d'un bug d'affichage entre les changement de mode
[1;34m|[m [1;34m|[m * [33mee6afd3[m index.html: Mode Minuterie, ajout du mode de declenchement de l'action
[1;34m|[m [1;34m|[m[1;34m/[m  
[1;34m|[m * [33m279af2b[m index.html + main.js: suppression des fonction submit pour integration avec la partie serveur
[1;34m|[m * [33mb3efc8e[m plug.js: gestion des transitions entre les modes
[1;34m|[m * [33m363c28e[m index.html: Correction de la syntaxe pour compatibilite avec le XHTML
[1;34m|[m * [33m1f3811c[m main.js: mise en place d'AJAX pour le 'post'
[1;34m|[m * [33m4ba215c[m table.js: finalisation de l'affichage du Json dans le tableau de la page d'accueil
[1;34m|[m * [33m66c93ad[m table.js: Creation de la classe C_Table
[1;34m|[m * [33mc907564[m index.html: changement des champs 'action' sur les form + Nettoyage des elements bootstrap et jquerry
[1;34m|[m[1;34m/[m  
* [33m7e0606c[m bug correction bplongclic write state in json
*   [33m520cb8a[m Merge branch 'dev_pierre' of https://github.com/volab/IoT_EPS into dev_Jojo
[1;35m|[m[1;36m\[m  
[1;35m|[m * [33m11ca359[m index.html, main.js: mise en place de la page d'accueil
[1;35m|[m * [33m41a56a4[m Suppression de la class 'redPlug' quand pas necessaire + preparation affichage tableau d'accueil
[1;35m|[m * [33md45bd36[m changemet automatique de class en fonction des prises
[1;35m|[m * [33mb6adf7b[m index.html+main.js+plug.js: Integration du modeSelector dans la sidebar
[1;35m|[m * [33m4c7c6b6[m index.html: Mise en place d'une sidebar
[1;35m|[m * [33m2f7dcf2[m Index.html: suppression du framwork 'Materialize'
[1;35m|[m * [33mbc233b4[m index.html + style.css: correction esthetique
[1;35m|[m * [33m175214e[m style.css: modification du diseign des bouton 'prise'
[1;35m|[m * [33me96818c[m main+plug: Mode Clone, mise en place de l'action au click sur les selecteurs
[1;35m|[m * [33m2f11f57[m index.html: redéfinition du mode clone ; main.js+plug.js: dans le mode clone, suppression de la prise en court d'utilisation
[1;35m|[m * [33m20ddaed[m main.js: correction d'un bug sur les boutons 'pause'
[1;35m|[m * [33mec035eb[m regExPatern.js: Ajout de bandeau d'information pour signaler les erreurs de saisie
[1;35m|[m * [33m39f4cb2[m regExPatern.js: reecriture en JQery + traitemant (en erreur) des heures identiques
[1;35m|[m * [33md6b007c[m main.js: reecriture de tous les event en JQuery
[1;35m|[m * [33mdec68ce[m plug.js: reecriture de tous les selecteur en JQUERY
[1;35m|[m *   [33m2893ca5[m plug + main: ajout du mode Clone ; TODO: dans le mode Clone, desactiver le selecteur de la prise courante
[1;35m|[m [31m|[m[32m\[m  
[1;35m|[m * [32m|[m [33m06c6a80[m plug.js + main.js: ajout du mode Hebdomadaire
[1;35m|[m * [32m|[m [33m2b15882[m interface_Web.rst: ajout de la diffinision des actions sur le mode hebdomadaire
[1;35m|[m * [32m|[m [33m56ac819[m plug.js + main.js: Ajout puis reecriture, en JQuery du mode cyclique
[1;35m|[m * [32m|[m [33m7b70012[m plug.js: Ajout du mode minuterie
[1;35m|[m * [32m|[m [33m8f6ae3a[m Integration de 'Submit' dans C_Plug + Creation de 'interface_Web.rst' et de 'mylog.js'
[1;35m|[m * [32m|[m [33m640870e[m regExPatern.js: gestion des 'submit' en fonction du contenu des 'input'
[1;35m|[m * [32m|[m [33m44ab2c8[m Creation de 'main.js ; plug.js et regExPatern.js
[1;35m|[m * [32m|[m [33m8b6d8a6[m HTML + CSS: Integration de Bootstrap et en plus de materialize
[1;35m|[m * [32m|[m [33macc7795[m Iot_EPS2.js: preparation du mode manuel pour integration dans la class Plug
[1;35m|[m * [32m|[m [33m06fcf9c[m Index.html: suppression des ID (remplaces par des class); IoT_EPS.js: creation de la class Plug + preparation des modes pour intégration dans la class
[1;35m|[m * [32m|[m   [33mdd1ad1f[m Merge branch 'dev_jojo' into dev_pierre
[1;35m|[m [33m|[m[34m\[m [32m\[m  
[1;35m|[m * [34m|[m [32m|[m [33m0a0ec42[m Inex.html: MAJ de la syntax des boutons radios ; IoT_EPS2: gestion de l'action sur les checkbox dans le mode Hebdo
[1;35m|[m * [34m|[m [32m|[m [33mfca5c66[m Index.html: mise en correspodence des noms retournes par les formulaires par rapport a config3.json
[1;35m|[m * [34m|[m [32m|[m   [33m92b00c8[m Merge + correction de conflit depuis la branche dev_jojo
[1;35m|[m [35m|[m[36m\[m [34m\[m [32m\[m  
[1;35m|[m * [36m|[m [34m|[m [32m|[m [33m7da75df[m HTML: Mise en place de la structure pour tous les modes
[1;35m|[m * [36m|[m [34m|[m [32m|[m [33m10d3c7d[m mode manuel, simplification du formulaire pour l'utilisation d'un seul bouton 'Envoyer'
[1;35m|[m * [36m|[m [34m|[m [32m|[m [33md9149de[m ADD: IoT_EPS2.js + simplification de index.html le temps la mise en place
[1;35m|[m * [36m|[m [34m|[m [32m|[m [33m8591829[m IoT_EPS.js: Creation de sous fonction pour le remplissage du résumer des prises
[1;35m|[m * [36m|[m [34m|[m [32m|[m [33m0dd5b50[m Affichage 'Minuterie' redPlug en js
[1;35m|[m * [36m|[m [34m|[m [32m|[m [33ma6402bf[m mise en place d'un script js pour parcourir le fichier 'config2.json'
[1;35m|[m * [36m|[m [34m|[m [32m|[m [33m52c2b05[m ajout des boutons dans les fieldsets
[1;35m|[m * [36m|[m [34m|[m [32m|[m   [33m6b1141f[m refonte d'index.html et mise en place de media dans le CSS
[1;35m|[m [1;31m|[m[1;32m\[m [36m\[m [34m\[m [32m\[m  
[1;35m|[m [1;31m|[m * [36m\[m [34m\[m [32m\[m   [33m39f08a1[m Merge de 'dev_jojo' + Integration du framework materialize
[1;35m|[m [1;31m|[m [1;33m|[m[1;34m\[m [36m\[m [34m\[m [32m\[m  
[1;35m|[m * [1;33m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33me78f903[m Test du framework materialize
[1;35m|[m [1;35m|[m[1;33m\[m[1;33m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m 
[1;35m|[m [1;35m|[m * [1;34m|[m [36m|[m [34m|[m [32m|[m [33m32e1a1e[m Integration du logo dans index.html
[1;35m|[m [1;35m|[m * [1;34m|[m [36m|[m [34m|[m [32m|[m [33ma0d40fb[m Creation et ajout logo
[1;35m|[m [1;35m|[m * [1;34m|[m [36m|[m [34m|[m [32m|[m [33mf7a1d66[m index.html: nettoyage du conflit
[1;35m|[m [1;35m|[m * [1;34m|[m [36m|[m [34m|[m [32m|[m [33mf96aca9[m style.css: petite reorganisation
[1;35m|[m * [1;36m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33mb66ad2e[m test de Bootstrap --> c'est nul !
[1;35m|[m [1;36m|[m[1;36m/[m [1;34m/[m [36m/[m [34m/[m [32m/[m  
[1;35m|[m * [1;34m|[m [36m|[m [34m|[m [32m|[m [33md86963c[m suppression du dossier IoT_EPS de la racine de 'project' suite pb gestion des branch
[1;35m|[m * [1;34m|[m [36m|[m [34m|[m [32m|[m   [33md7ec89a[m commit apres merge depuis la branch dev_jojo
[1;35m|[m [31m|[m[32m\[m [1;34m\[m [36m\[m [34m\[m [32m\[m  
[1;35m|[m * [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33mbbd5451[m UP: index.html et style.css + ADD: Etude_Fonctionnalite.rst
[1;35m|[m * [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33mf319382[m preparation de la page Web
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m798257e[m tempo leds ok and a merge of to for loop in the main loop
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m3c56d53[m add flasher enable
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33ma36adc6[m timed management of leds creat but not tested
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33mcef081b[m some comments cleaning
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33mc1a651e[m FastLed luminosity set from json file : ok + ledsOnTime read from Jsom in cParam but not already used.
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m25384fe[m BP double click action replaced by a special BP. Double clicks are not sure at all. + implementation of html pause request
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33mdc14590[m double clic action work in progress + new json parameters : emplacement, nickName, allLedsOnTime and ledsGlobalLuminosity
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33me83b0cf[m plugs array defined dynamicly ok, set time HH:mm:SS ok and webserver port defined dyna. ok
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m99ada54[m add  /** @todo instnaciate command for set Hours, minutes, seconds separatly */ but not tested
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m6726cd2[m plugs array dynamically defined
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m14f6dba[m to do : /** @todo get server port from config3.json*/ removed but not tested and read numberOfPlug from json
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m8109587[m main power switch ok + handleBPlongClic change write to json
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33mf3b4a81[m CSwitchNano class writted but not tested
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33mc36b125[m Add change SSID in config param and with serial commands + add state restaur @puwer up but not yet tested
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m509339f[m clone mode written, compiled but no tested
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m3c06fe7[m push button long clic ok
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m7b2e556[m BP simple clic pause in hebdo mode ok
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33med83163[m add new feature bp simple clic on cyclic mode
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m779bcd9[m doxy doc little cleanup
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m69c17b3[m Comments about Cmcp class clean up
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33meedabd1[m nanoI2CIOExpander integrated ! And it works !
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [32m|[m [33m2169cb1[m nanoI2C integre et fonctionnel .test() ok alim 5V cablée. ToDo : remplacer le composant MPC...
[32m|[m [32m|[m[32m_[m[32m|[m[32m_[m[1;34m|[m[32m_[m[36m|[m[32m_[m[34m|[m[32m/[m  
[32m|[m[32m/[m[32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m   
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33ma7e76b1[m hebdo mode tested
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33m0e46fcc[m WIP testing and debugging of hebdo mode
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33m0628323[m hebdo mode WIP write to JSON ok, next time to switch computation ok, to do : at time
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33me0ac154[m Hebdo mode work in progress. method that compute nextTime is tested
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33md703da4[m Mode cyclique ok testé.
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33m68ae0c2[m some little corrections : yellow plug bp doesn't work @ start up (call readFromJson !)
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33m333d519[m commit from WDD
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33m95662eb[m set DS3231 manualy with SerialCommand ok <S JJ/MM/AAAA HH:MM:SS>
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33m416658e[m add SerialCommands capability and LED Flasher class to display softAP mode when wifi is not reachable.
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33m39e285a[m some code cleaning but in great deals with wifi connection modes when wifi is not reachable.
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33m9b1e55f[m Utilisation de unixTime2String
* [32m|[m [32m|[m [1;34m|[m [36m|[m [34m|[m [33m92c898e[m work around nexttime to switch and static function to display a unixtime into a humen readable form
[34m|[m [32m|[m[34m_[m[32m|[m[34m_[m[1;34m|[m[34m_[m[36m|[m[34m/[m  
[34m|[m[34m/[m[32m|[m [32m|[m [1;34m|[m [36m|[m   
* [32m|[m [32m|[m [1;34m|[m [36m|[m [33mfd36f8d[m nextTimeToSwitch ok for manual mode, new param in config3.json : nbr of plugs and nextimeToSwitch
* [32m|[m [32m|[m [1;34m|[m [36m|[m [33m1d86160[m Classe CEPSStrTime écrite compilée mais pas testée.
* [32m|[m [32m|[m [1;34m|[m [36m|[m [33m4fa8356[m Classe CEpsStrTime en cours d'écriture
* [32m|[m [32m|[m [1;34m|[m [36m|[m [33m2f292ed[m Implementation du compter onOff dans le json. Correction bug bp acquit au retouren mode manuel.
* [32m|[m [32m|[m [1;34m|[m [36m|[m [33mb6612cf[m bp actif, mode manuel encours de validation, ajouter hfin dureeOff.
* [32m|[m [32m|[m [1;34m|[m [36m|[m [33m9413004[m en chemin vers le décodage des actions. Mode manuel en cous dans la classe CPowerPlug
* [32m|[m [32m|[m [1;34m|[m [36m|[m [33m00a1007[m page écriture correcte dans config3.json ToDO : séparer les paramètres réseau de config3.json
[36m|[m [32m|[m[36m_[m[32m|[m[36m_[m[1;34m|[m[36m/[m  
[36m|[m[36m/[m[32m|[m [32m|[m [1;34m|[m   
* [32m|[m [32m|[m [1;34m|[m [33mdb5a6b7[m enum mode removed to array of String and new static method modeId()
* [32m|[m [32m|[m [1;34m|[m [33ma49201d[m CPowerPlug::readJson() en cours de mise au point. Lectures Ok. Rest à mettre les string lues sous forme de variables membres
* [32m|[m [32m|[m [1;34m|[m [33mbd31e03[m Passage au fichier config3.json (testé et fonctionnel) sur le chemin de la lecture des parametre de chaque plug
* [32m|[m [32m|[m [1;34m|[m [33m2b7f145[m Passage sur le fichier config2.json + somme cleanup of the code
* [32m|[m [32m|[m [1;34m|[m [33m180a9cf[m plug removed from config param class
* [32m|[m [32m|[m [1;34m|[m [33m9d3a8c0[m RGB color LED integration
* [32m|[m [32m|[m [1;34m|[m [33ma190f01[m add display param in handlePlugOnOff + pise en charge des 3 autres plugs et de leur initialisation
* [32m|[m [32m|[m [1;34m|[m [33m355aff4[m plugs sous forme de tableau + doc + premières commande de relais
* [32m|[m [32m|[m [1;34m|[m [33m05acbf1[m nettoyage fichiers
* [32m|[m [32m|[m [1;34m|[m [33m6ba5415[m Test du parametre hidden pour la couleur: fonctionnel
* [32m|[m [32m|[m [1;34m|[m [33m2114b59[m Macro DEFDPROMPT(X) works !
* [32m|[m [32m|[m [1;34m|[m [33mc266a20[m define macro DPROMPT en cours non compilable
* [32m|[m [32m|[m [1;34m|[m [33m62f3ce4[m réception formulaire ok - todo: mettre la fonction dans la class power plug
* [32m|[m [32m|[m [1;34m|[m [33m3c46244[m commit en cours de travail pour recup config2.json new
* [32m|[m [32m|[m [1;34m|[m [33m63993a8[m Merge dossier data from dev_pierre (git checkout dev_pierre data à condition d'être juste au dessus et de le faire dans une fenêtre de commande -pas avec toirtoise)
* [32m|[m [32m|[m [1;34m|[m   [33m14ea1bf[m Merge branch 'dev_Jojo' of https://github.com/volab/IoT_EPS into dev_Jojo
[33m|[m[34m\[m [32m\[m [32m\[m [1;34m\[m  
[33m|[m * [32m|[m [32m|[m [1;34m|[m [33mbd1d859[m Ajout classe mère Cmcp (commune à CPowerPlug et CButton)
* [34m|[m [32m|[m [32m|[m [1;34m|[m [33m1427f4c[m Ajout classe mère Cmcp (commune à CPowerPlug et CButton)
[34m|[m[34m/[m [32m/[m [32m/[m [1;34m/[m  
* [32m|[m [32m|[m [1;34m|[m [33md7bc100[m Création de la classe CPowerPlug avec variable et fonction static. Compilé mias pas testée en cours d'écriture. Il manque notament les méthodes pour gérer le temps.
* [32m|[m [32m|[m [1;34m|[m [33m2ae1667[m un poil de doc pour le choix des relais et la définition des modes de fonctionnement
* [32m|[m [32m|[m [1;34m|[m [33md95738a[m MCP23017 ajouté et fonctionnel
[1;34m|[m [32m|[m[1;34m_[m[32m|[m[1;34m/[m  
[1;34m|[m[1;34m/[m[32m|[m [32m|[m   
* [32m|[m [32m|[m [33mdb8fa1e[m Ajout help to help.htm + favicon
* [32m|[m [32m|[m [33ma76741e[m Gestion du mode client. Connection à volab_iot ok. Edition directe des fichier possible grâce à l'intégration des fonctions de l'exemple FSBrowser.
* [32m|[m [32m|[m [33m1d829bc[m Integration de l'exemple FSBrowser pour la gestion des css et autres fichiers associés à la page html, ajout du fichier .epgz Pencil pour le design des interface graphiques
* [32m|[m [32m|[m [33mceda1c0[m affichage de l'heure du DS3231 dans une page html en dur dans le code ToDO : lire cette page sur SPIFFS et remplacer un texte genre afficher_heure_ici par l'heure avant de l'envoyer
* [32m|[m [32m|[m [33m2416a25[m ajout du fichier config.json aux commits
* [32m|[m [32m|[m [33maf63eb4[m Premier affichage d'une page html, toujours en mode softAP
* [32m|[m [32m|[m [33m732bbd6[m nettoyage d'un commentaire inutile
* [32m|[m [32m|[m [33m0574e00[m mise au point et homogeneisation de la classe creditential
[32m|[m [32m|[m[32m/[m  
[32m|[m[32m/[m[32m|[m   
* [32m|[m [33md1da2ba[m config param complements
* [32m|[m [33m0e3aaf7[m Création de la classe configParam, fonctionnelle mais incomplete
* [32m|[m [33ma7a7bc1[m Ajout des images perdues ;-(
* [32m|[m [33m9c05137[m Ajout des fichiers html et css de la branche de Pierre
* [32m|[m [33m6bb5d3e[m Creation de la class Credential
* [32m|[m [33m638cae5[m credentials read from json file ok
* [32m|[m [33m5584fb2[m un peu de git doxydoc
[32m|[m[32m/[m  
* [33m9f9f421[m Recup softDev.rst de l'autre branche ;-(
* [33m9efd3b0[m premier Commit - nouvelle branche suite à fausse manip credit. et blocage ATOM !
* [33m1b7d5dd[m[33m ([m[1;31morigin/master[m[33m, [m[1;31morigin/HEAD[m[33m, [m[1;32mmaster[m[33m)[m Tentative ajout répertoire _3_ branche master
* [33ma7c9abd[m Premier commit, creation du projet