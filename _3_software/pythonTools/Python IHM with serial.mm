<map version="freeplane 1.9.13">
<!--To view this file, download free mind mapping software Freeplane from https://www.freeplane.org -->
<node TEXT="Python IHM with serial" FOLDED="false" ID="ID_696401721" CREATED="1610381621824" MODIFIED="1656192653727" STYLE="oval" BORDER_WIDTH="3.7 px">
<font SIZE="18"/>
<hook NAME="MapStyle">
    <properties edgeColorConfiguration="#808080ff,#ff0000ff,#0000ffff,#00ff00ff,#ff00ffff,#00ffffff,#7c0000ff,#00007cff,#007c00ff,#7c007cff,#007c7cff,#7c7c00ff" show_icon_for_attributes="true" associatedTemplateLocation="template:/standard-1.6.mm" show_note_icons="true" fit_to_viewport="false"/>

<map_styles>
<stylenode LOCALIZED_TEXT="styles.root_node" STYLE="oval" UNIFORM_SHAPE="true" VGAP_QUANTITY="24 pt">
<font SIZE="24"/>
<stylenode LOCALIZED_TEXT="styles.predefined" POSITION="right" STYLE="bubble">
<stylenode LOCALIZED_TEXT="default" ID="ID_271890427" ICON_SIZE="12 pt" FORMAT_AS_HYPERLINK="false" COLOR="#000000" STYLE="fork" NUMBERED="false" FORMAT="STANDARD_FORMAT" TEXT_ALIGN="DEFAULT" MAX_WIDTH="10 cm" MIN_WIDTH="0 cm" VGAP_QUANTITY="2 pt" BORDER_WIDTH_LIKE_EDGE="false" BORDER_WIDTH="1 px" BORDER_COLOR_LIKE_EDGE="true" BORDER_COLOR="#808080" BORDER_DASH_LIKE_EDGE="false" BORDER_DASH="SOLID">
<arrowlink SHAPE="CUBIC_CURVE" COLOR="#000000" WIDTH="2" TRANSPARENCY="200" DASH="" FONT_SIZE="9" FONT_FAMILY="SansSerif" DESTINATION="ID_271890427" STARTARROW="NONE" ENDARROW="DEFAULT"/>
<font NAME="SansSerif" SIZE="10" BOLD="false" STRIKETHROUGH="false" ITALIC="false"/>
<richcontent CONTENT-TYPE="plain/auto" TYPE="DETAILS"/>
<richcontent TYPE="NOTE" CONTENT-TYPE="plain/auto"/>
<edge STYLE="bezier" COLOR="#808080" WIDTH="1" DASH="SOLID"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.details"/>
<stylenode LOCALIZED_TEXT="defaultstyle.attributes">
<font SIZE="9"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.note" COLOR="#000000" BACKGROUND_COLOR="#ffffff" TEXT_ALIGN="LEFT"/>
<stylenode LOCALIZED_TEXT="defaultstyle.floating">
<edge STYLE="hide_edge"/>
<cloud COLOR="#f0f0f0" SHAPE="ROUND_RECT"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.selection" BACKGROUND_COLOR="#4e85f8" BORDER_COLOR_LIKE_EDGE="false" BORDER_COLOR="#4e85f8"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.user-defined" POSITION="right" STYLE="bubble">
<stylenode LOCALIZED_TEXT="styles.topic" COLOR="#18898b" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subtopic" COLOR="#cc3300" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subsubtopic" COLOR="#669900">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.important" ID="ID_67550811">
<icon BUILTIN="yes"/>
<arrowlink COLOR="#003399" TRANSPARENCY="255" DESTINATION="ID_67550811"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.AutomaticLayout" POSITION="right" STYLE="bubble">
<stylenode LOCALIZED_TEXT="AutomaticLayout.level.root" COLOR="#000000" STYLE="oval" SHAPE_HORIZONTAL_MARGIN="10 pt" SHAPE_VERTICAL_MARGIN="10 pt">
<font SIZE="18"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,1" COLOR="#0033ff">
<font SIZE="16"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,2" COLOR="#00b439">
<font SIZE="14"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,3" COLOR="#990000" MAX_WIDTH="15 cm">
<font SIZE="12"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,4" COLOR="#111111">
<font SIZE="10"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,5"/>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,6"/>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,7"/>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,8"/>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,9"/>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,10"/>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,11"/>
</stylenode>
</stylenode>
</map_styles>
</hook>
<hook NAME="AutomaticEdgeColor" COUNTER="7" RULE="ON_BRANCH_CREATION"/>
<hook NAME="accessories/plugins/AutomaticLayout.properties" VALUE="ALL"/>
<edge STYLE="sharp_bezier"/>
<node TEXT="Récup de l&apos;IHM RDC Capteur" POSITION="right" ID="ID_1793141041" CREATED="1655933009107" MODIFIED="1655933022863">
<edge COLOR="#ff0000"/>
</node>
<node TEXT="arbre des dépendences de classes" POSITION="right" ID="ID_1623956695" CREATED="1655933023302" MODIFIED="1656192685548">
<edge STYLE="sharp_bezier" COLOR="#0000ff" WIDTH="4"/>
<node TEXT="main.py" ID="ID_1293503858" CREATED="1655933079274" MODIFIED="1655933083371">
<node TEXT="CRdcGUI" ID="ID_1021014534" CREATED="1655933126271" MODIFIED="1655933132200">
<node TEXT="Dépendences &quot;system&quot;" ID="ID_1964248327" CREATED="1656191629069" MODIFIED="1656191638386">
<node TEXT="import tkinter as tk" ID="ID_864650357" CREATED="1656191615191" MODIFIED="1656191615191"/>
<node TEXT="from tkinter import ttk" ID="ID_1717890855" CREATED="1656191615191" MODIFIED="1656191615191"/>
<node TEXT="import serial.tools.list_ports" ID="ID_947847343" CREATED="1656191615191" MODIFIED="1656191615191"/>
<node TEXT="from tkinter import messagebox" ID="ID_634434523" CREATED="1656191615191" MODIFIED="1656191615191"/>
<node TEXT="import serial" ID="ID_1556726199" CREATED="1656191615191" MODIFIED="1656191615191"/>
<node TEXT="import os" ID="ID_1898507091" CREATED="1656191615191" MODIFIED="1656191615191"/>
<node TEXT="from time import strftime, localtime" ID="ID_1211016598" CREATED="1656191615191" MODIFIED="1656191615191"/>
<node TEXT="from datetime import datetime #juste pour les milisecondes :-(" ID="ID_1837577273" CREATED="1656191615191" MODIFIED="1656191615191"/>
</node>
<node TEXT="GuiFrameControles" LOCALIZED_STYLE_REF="AutomaticLayout.level,10" ID="ID_1941342954" CREATED="1655933428600" MODIFIED="1655933539402"/>
<node TEXT="GuiFrameDisplay" ID="ID_1482521634" CREATED="1655933560545" MODIFIED="1655933560545"/>
<node TEXT="import GuiFrameControles as FrameControles" ID="ID_1563903352" CREATED="1656191615191" MODIFIED="1656191615191"/>
<node TEXT="import GuiFrameDisplay as FrameDisplay" ID="ID_100574516" CREATED="1656191615191" MODIFIED="1656191615191"/>
<node TEXT="import Trame as Tr" ID="ID_1393425239" CREATED="1656191615191" MODIFIED="1656191615191"/>
<node TEXT="import constantes as CST" ID="ID_1402638729" CREATED="1656191615191" MODIFIED="1656191615191"/>
<node TEXT="from TrameMag import XYZ" ID="ID_1527929332" CREATED="1656191615191" MODIFIED="1656191615191"/>
</node>
<node TEXT="root.after(rdc_gui.RS_HANDLER_PERIOD, rdc_gui.rsHandler)" ID="ID_730830982" CREATED="1656191490594" MODIFIED="1656191490594"/>
</node>
<node TEXT="GuiFrameControles" LOCALIZED_STYLE_REF="AutomaticLayout.level,10" ID="ID_1662997207" CREATED="1655933428600" MODIFIED="1655933539402">
<node TEXT="Dépendences &quot;system&quot;" ID="ID_1589893775" CREATED="1656191629069" MODIFIED="1656191638386">
<node TEXT="import tkinter as tk" ID="ID_1008887239" CREATED="1656192034725" MODIFIED="1656192034725"/>
<node TEXT="from tkinter import ttk" ID="ID_812310129" CREATED="1656192034725" MODIFIED="1656192585193" BORDER_WIDTH="1 px"/>
<node TEXT="import serial" ID="ID_946611995" CREATED="1656192034725" MODIFIED="1656192034725"/>
<node TEXT="import serial.tools.list_ports" ID="ID_601077973" CREATED="1656192034725" MODIFIED="1656192034725"/>
<node TEXT="from tkinter import messagebox" ID="ID_490264417" CREATED="1656192034725" MODIFIED="1656192034725"/>
</node>
<node TEXT="import GuiFrameConfig as FConfig" ID="ID_1493685882" CREATED="1656192034725" MODIFIED="1656192034725"/>
<node TEXT="import GuiFrameRecord as Frec" ID="ID_776738876" CREATED="1656192034725" MODIFIED="1656192034725"/>
<node TEXT="import GuiFrameCalMag as FCalMag" ID="ID_331894917" CREATED="1656192034725" MODIFIED="1656192034725"/>
<node TEXT="from constantes import BAUD_RATE" ID="ID_1968203920" CREATED="1656192034725" MODIFIED="1656192034725"/>
<node TEXT="Les guiControle n&apos;ont pas de classes associée" ID="ID_162986678" CREATED="1656232335910" MODIFIED="1656232443302">
<icon BUILTIN="idea"/>
<node TEXT="Mais ce n&apos;est pas une obligation exemple TrameConf et guiFrameConfig" ID="ID_1550083063" CREATED="1656232450229" MODIFIED="1656232478881"/>
</node>
</node>
<node TEXT="GuiFrameDisplay" ID="ID_932001143" CREATED="1655933560545" MODIFIED="1655933560545">
<node TEXT="import GuiFrameMag as FMag" ID="ID_532190960" CREATED="1656192786884" MODIFIED="1656192786884"/>
<node TEXT="import GuiFrameBaro as FBaro" ID="ID_1492367669" CREATED="1656192786884" MODIFIED="1656192786884"/>
<node TEXT="import GuiFramePitot as FPit" ID="ID_1096832845" CREATED="1656192786884" MODIFIED="1656192786884"/>
<node TEXT="import GuiFrameTlm as FTlm" ID="ID_1247712140" CREATED="1656192786884" MODIFIED="1656192786884"/>
<node TEXT="import GuiFrameAlim as FAlim" ID="ID_259514511" CREATED="1656192786884" MODIFIED="1656192786884"/>
<node TEXT="chacune de ces classe graphique bas niveau fait appel à (instancie) sont homologue non graphique pour les traitements et la mise en forme des données" ID="ID_1915445249" CREATED="1656230602724" MODIFIED="1656231063867" ICON_SIZE="28 pt">
<icon BUILTIN="idea"/>
</node>
<node TEXT="A noter également que chacune des ces classe hérite de tk.LabelFrame" ID="ID_1266021847" CREATED="1656230757021" MODIFIED="1656231054664">
<icon BUILTIN="idea"/>
<node TEXT="mais pour quelle raison ?" ID="ID_1098244347" CREATED="1658598976279" MODIFIED="1658598987729"/>
<node TEXT="Pour disposer d&apos;une zone avec titre et cadre autour pour y mettre des boutons" ID="ID_1945712367" CREATED="1658601645555" MODIFIED="1658601670860"/>
</node>
</node>
</node>
<node TEXT="Construire l&apos;appli graphique avec TK inter" POSITION="right" ID="ID_1232685488" CREATED="1656192269207" MODIFIED="1656192315458" MAX_WIDTH="14.3 cm">
<edge COLOR="#00ff00"/>
<node TEXT="une classe par block d&apos;affichage avec son propre autotest" ID="ID_256136721" CREATED="1656192331926" MODIFIED="1656192715689" MAX_WIDTH="14 cm"/>
<node TEXT="ensuite on remonte d&apos;un cran" ID="ID_494951221" CREATED="1656192350968" MODIFIED="1656192361013">
<node TEXT="GUIdroite" ID="ID_1176887160" CREATED="1656192367525" MODIFIED="1656192372461">
<node TEXT="ici pour la zone d&apos;affichage" ID="ID_1440849892" CREATED="1656192398771" MODIFIED="1656192415529"/>
</node>
<node TEXT="GUIgauche" ID="ID_1105663766" CREATED="1656192373039" MODIFIED="1656192379229">
<node TEXT="ici les controles de l&apos;appli" ID="ID_421113031" CREATED="1656192380682" MODIFIED="1656192394866"/>
</node>
<node TEXT="Cette remontée se fait en instanciant un membre local de chaque gui de niveau inférieur" ID="ID_310094692" CREATED="1656193255531" MODIFIED="1656193309816">
<node TEXT="self.dataBaroFrame" ID="ID_411220198" CREATED="1656193328314" MODIFIED="1656193355029">
<node TEXT="FBaro.GuiFrameBaro( self, 2, 1, self.GEN_PADDING)" ID="ID_1721302389" CREATED="1656193382900" MODIFIED="1656193387097"/>
</node>
</node>
</node>
<node TEXT="on regroupe les gui droites et gauche dans l&apos;UI principal" ID="ID_1533117870" CREATED="1656192361747" MODIFIED="1656799595081" MAX_WIDTH="13.5 cm"/>
<node TEXT="on appelle l&apos;UI principale dans le main" ID="ID_945398279" CREATED="1656192461406" MODIFIED="1656192476449"/>
<node TEXT="la liaison série est gérée sous la forme d&apos;un handler périodique dans l&apos;UI principale mais est initialisée dans le main qui donne en quelques sorte le coup d&apos;envoi." ID="ID_1667158266" CREATED="1656192477121" MODIFIED="1656799638073" MAX_WIDTH="14.8 cm" STYLE="bubble">
<node TEXT="puis le handler s&apos;auto relance" ID="ID_1769387646" CREATED="1656194426997" MODIFIED="1656194439509">
<node TEXT="self.master.after(self.RS_HANDLER_PERIOD, self.rsHandler)" ID="ID_1558877675" CREATED="1656194439509" MODIFIED="1656194443836"/>
</node>
</node>
<node TEXT="gui d&apos;affichage" ID="ID_1771729133" CREATED="1656193577316" MODIFIED="1656193584002"/>
<node TEXT="gui de controle" ID="ID_220650607" CREATED="1656193584518" MODIFIED="1656193594599"/>
<node TEXT="Chaque classe de niveau inférieur peut être testée individuellement" ID="ID_662707078" CREATED="1656193728226" MODIFIED="1656193887217" MAX_WIDTH="16.1 cm" COLOR="#000000" STYLE="bubble">
<edge STYLE="hide_edge" COLOR="#000099" ALPHA="0" WIDTH="thin"/>
<cloud COLOR="#ff6666" SHAPE="ARC"/>
</node>
</node>
<node TEXT="aspect alimentation des GUI d&apos;affichage avec les data" POSITION="right" ID="ID_1457383813" CREATED="1656193066704" MODIFIED="1656193623281" MAX_WIDTH="14.2 cm" STYLE="bubble">
<edge COLOR="#ff00ff"/>
<node TEXT="A chaque GUI est passé une instance d&apos;un objet &quot;trameDecoupee&quot;" ID="ID_1974838563" CREATED="1656193110247" MODIFIED="1656193641094" MAX_WIDTH="16 cm"/>
<node TEXT="chaque GUI chargée d&apos;afficher des données, instancie une méthode displayData qui recoit l&apos;objet trame découpée" ID="ID_1790803281" CREATED="1656193976194" MODIFIED="1656799686070" MAX_WIDTH="15 cm"/>
<node TEXT="trameDecoupee est une classe qui est instanciée par Trame" ID="ID_537014393" CREATED="1656194724357" MODIFIED="1656799686076" MAX_WIDTH="15 cm">
<node TEXT="C&apos;est le handler RS qui crée un objet trame puis qui appelle la méthode frameDisplay.dataUpdate en lui passant trame.trameDecoupee" ID="ID_529129272" CREATED="1656194583761" MODIFIED="1656799686074" MAX_WIDTH="15 cm"/>
</node>
</node>
<node TEXT="aspect gestion RS" POSITION="right" ID="ID_1118635161" CREATED="1656196000285" MODIFIED="1656196006330">
<edge COLOR="#7c0000"/>
<node TEXT="C&apos;est guiCtroles qui en plus d&apos;instancié et de placer guiConfig, record et calMag gère la RS" ID="ID_1858131030" CREATED="1656196157749" MODIFIED="1656799713346" MAX_WIDTH="21.2 cm"/>
<node TEXT="Je pense que cela aurait du être placé dans un sous-bloc mais ne l&apos;a pas été fait car produit en début de projet" ID="ID_1468726984" CREATED="1656196216662" MODIFIED="1656232775988" ICON_SIZE="28 pt" MAX_WIDTH="16.4 cm" STYLE="bubble">
<icon BUILTIN="messagebox_warning"/>
<icon BUILTIN="stop-sign"/>
</node>
</node>
<node TEXT="Archi resumee" POSITION="right" ID="ID_1757654639" CREATED="1656195056785" MODIFIED="1656195064051">
<edge COLOR="#00ffff"/>
<node TEXT="main" ID="ID_55214438" CREATED="1656195066519" MODIFIED="1656195070393">
<node TEXT="Aspect fondamental" ID="ID_1629314400" CREATED="1658599019828" MODIFIED="1658599028071">
<node TEXT="L&apos;architecture avec GUIs et homologues à du sens seulement parceque la trame est fixe et composée de champs bien délimités" ID="ID_812971591" CREATED="1658599030858" MODIFIED="1658599102442" COLOR="#ff0000">
<font SIZE="12"/>
</node>
</node>
<node TEXT="start gui.rshandler" ID="ID_69038417" CREATED="1656195088138" MODIFIED="1656195100763">
<node TEXT="RS_HANDLER_PERIOD = 9 # ms" ID="ID_235575375" CREATED="1656195202158" MODIFIED="1656195207150"/>
</node>
<node TEXT="Gui" ID="ID_1083462459" CREATED="1656195070393" MODIFIED="1656195077829">
<node TEXT="rshandler" ID="ID_513269103" CREATED="1656195102966" MODIFIED="1656195216901">
<node TEXT="" ID="ID_512940286" CREATED="1656801442734" MODIFIED="1656801442734"/>
<node TEXT="si rs open =&gt; trame.recevoirTrame()" ID="ID_543204937" CREATED="1656195220947" MODIFIED="1656195651709"/>
<node TEXT="si rs open =&gt;" ID="ID_1688225022" CREATED="1656195220947" MODIFIED="1656801477616">
<node TEXT="trame initialisé avec self.frameCtrl.serialPort, self.SIZE_OF_FRAME" ID="ID_235765108" CREATED="1656801490777" MODIFIED="1656801563014" MAX_WIDTH="20 cm">
<font SIZE="12"/>
</node>
<node ID="ID_774761175" CREATED="1656801479629" MODIFIED="1656801479629"><richcontent TYPE="NODE">

<html>
  <head>
    
  </head>
  <body>
    <p>
      trame.recevoirTrame()
    </p>
  </body>
</html>
</richcontent>
<node TEXT="construit _trameBrute" ID="ID_1096145106" CREATED="1656195381008" MODIFIED="1656195443374">
<node TEXT="list()" ID="ID_1289751476" CREATED="1656195446058" MODIFIED="1656195450217"/>
</node>
<node TEXT="si pas d&apos;erreur trameDecoupee.populate()" ID="ID_1853429475" CREATED="1656195388803" MODIFIED="1656195579082">
<node TEXT="trameDecoupe instance" ID="ID_775180989" CREATED="1656195482729" MODIFIED="1656195490306"/>
</node>
<node TEXT="frameDisplay.updateData( trameDecoupee )" ID="ID_1475071463" CREATED="1656195664505" MODIFIED="1656800806876" ICON_SIZE="28 pt" COLOR="#ff0000" STYLE="bubble" MAX_WIDTH="17 cm">
<icon BUILTIN="messagebox_warning"/>
<font SIZE="20" BOLD="true"/>
<node TEXT="c&apos;est PRECISEMENT à cet endroit que se fait le couplage fort entre GUI et Trames" ID="ID_1625820176" CREATED="1656800776866" MODIFIED="1656801887840" MAX_WIDTH="13.6 cm">
<font SIZE="14"/>
</node>
<node TEXT="dans le rshandler" ID="ID_375438623" CREATED="1656801904804" MODIFIED="1656801911125"/>
</node>
</node>
</node>
</node>
<node TEXT="guiControle &amp; guiDisplay" ID="ID_406048120" CREATED="1656195717358" MODIFIED="1656230545818" ICON_SIZE="28 pt">
<icon BUILTIN="messagebox_warning"/>
<richcontent CONTENT-TYPE="xml/" TYPE="DETAILS">
<html>
  <head>
    
  </head>
  <body>
    <p>
      Il y a des images ici
    </p>
  </body>
</html></richcontent>
<node TEXT="guiControls" FOLDED="true" ID="ID_976463840" CREATED="1656229967923" MODIFIED="1656230004027">
<node TEXT="" ID="ID_1892429324" CREATED="1656230011733" MODIFIED="1656230019175">
<hook URI="images/guiControls.JPG" SIZE="1.0" NAME="ExternalObject"/>
</node>
</node>
<node TEXT="guiDisplays" FOLDED="true" ID="ID_148807233" CREATED="1656230023849" MODIFIED="1656230029545">
<node TEXT="" ID="ID_1169529501" CREATED="1656230097810" MODIFIED="1656230106739">
<hook URI="images/guiDisplays.JPG" SIZE="1.0" NAME="ExternalObject"/>
</node>
</node>
</node>
<node TEXT="note : c&apos;est lUI frame controles qui instancie le serialPort" ID="ID_365737866" CREATED="1656801257983" MODIFIED="1656801310913" ICON_SIZE="28 pt">
<icon BUILTIN="yes"/>
<font BOLD="true"/>
<node TEXT="Cette UI est chargée d&apos;ouvrir le port, de faire la liste des ports..." ID="ID_852695792" CREATED="1656801351563" MODIFIED="1656801381060"/>
</node>
</node>
<node TEXT="Les classes d&apos;interface graphiques, outres le fait d&apos;afficher les objets graphiques restent en mémoire et au même titre que toute autre classe possèdent des attributs et des méthodes pas nécessairement graphiques !!!" ID="ID_1972319692" CREATED="1656230135657" MODIFIED="1656799884260" ICON_SIZE="28 pt">
<icon BUILTIN="idea"/>
<node TEXT="recordOn de GuiFrameRecord" ID="ID_666791027" CREATED="1656232636481" MODIFIED="1656232651463"/>
<node TEXT="serialPortIsOpen et serialPort de guiFramesControles" ID="ID_1252734176" CREATED="1656232652282" MODIFIED="1656232699330"/>
</node>
<node TEXT="Question : comment affiche-t-on du texte dans la zone de texte" ID="ID_105269676" CREATED="1657396539370" MODIFIED="1657396715222">
<node TEXT="C&apos;est rsHandler qui le fait directement" ID="ID_1473043450" CREATED="1657396715234" MODIFIED="1657396727508"/>
<node TEXT="En effet, CGUI instancie framDsiplay donc à accès à tous ses membre donc zone de texte." ID="ID_1842934970" CREATED="1657396727956" MODIFIED="1657396776985"/>
</node>
</node>
</node>
<node TEXT="De l&apos;appli RDC vers le template" POSITION="right" ID="ID_1537751439" CREATED="1656800043993" MODIFIED="1656800058702">
<edge COLOR="#00007c"/>
<node TEXT="A droite ne garder que 2 champs de date : baro et alim" ID="ID_526136377" CREATED="1656800058708" MODIFIED="1656801720324" MAX_WIDTH="15 cm">
<node TEXT="on vire Pitot tlm et magneto" ID="ID_1165791253" CREATED="1656800088082" MODIFIED="1656800105514"/>
<node TEXT="même pas dans un premier temps pour aller vers un template très simplissime" ID="ID_794876077" CREATED="1656803118789" MODIFIED="1656803141123"/>
<node TEXT="Exercice très difficile tant la classe Trame est liée aux classes graphiques." ID="ID_856825945" CREATED="1656800619415" MODIFIED="1656801715237" MAX_WIDTH="17.5 cm"/>
</node>
<node TEXT="coté controles on ne garde qu&apos;un block" ID="ID_362254322" CREATED="1656800249896" MODIFIED="1656800265072">
<node TEXT="on vire record et cal" ID="ID_1536731375" CREATED="1656800272147" MODIFIED="1656800278891"/>
</node>
<node TEXT="bien que très intéressante comme fonctionnalité, la fonction d&apos;enregistrement n&apos;est pas conservé dans le template" ID="ID_1351237935" CREATED="1656801651795" MODIFIED="1656801706306" MAX_WIDTH="14.3 cm">
<node TEXT="peut-être un template avancé" ID="ID_288971703" CREATED="1656801690130" MODIFIED="1656801701100"/>
</node>
<node TEXT="De même la fonctionnalité qui consiste à découper la trame n&apos;est pas conservé" ID="ID_692403571" CREATED="1656802133463" MODIFIED="1656802164175">
<node TEXT="Cette fonctionnalité est assurée par autant d&apos;objects que nécessaire qui découpe chacun sa partie avec sa propre méthode populate." ID="ID_1303584283" CREATED="1656802166311" MODIFIED="1656802250973"/>
</node>
<node TEXT="Cette version simplifié du template doit" ID="ID_482861398" CREATED="1656802251921" MODIFIED="1656802264019">
<node TEXT="côté controles" ID="ID_632831038" CREATED="1656802264025" MODIFIED="1656802271137">
<node TEXT="permettre d&apos;ouvrir le port COM" ID="ID_966013646" CREATED="1656802271143" MODIFIED="1656802286891">
<node TEXT="(et de recevoir des données :-)" ID="ID_729858579" CREATED="1656802286895" MODIFIED="1656802303761"/>
</node>
</node>
<node TEXT="côté display d&apos;afficher les données reçues" ID="ID_162694852" CREATED="1656802305970" MODIFIED="1656802369825">
<node TEXT="en conséquence suppression des fichiers trame de chaque partie de la trame" ID="ID_1394116195" CREATED="1656803006767" MODIFIED="1656803042371"/>
</node>
</node>
<node TEXT="La trame n&apos;a pas d&apos;entête connue, elle est en asci de longueur variable" ID="ID_712888301" CREATED="1656803045319" MODIFIED="1656803077754">
<node TEXT="caractère de terminaison 0D 0A ?" ID="ID_990622741" CREATED="1656803077758" MODIFIED="1656803096659"/>
<node TEXT="" ID="ID_938444683" CREATED="1656803097419" MODIFIED="1656803097419"/>
</node>
<node TEXT="Faut-il utiliser la librairie Threading ?" ID="ID_1173716017" CREATED="1657737916408" MODIFIED="1657737931629">
<node TEXT="Si oui comment ?" ID="ID_1553634514" CREATED="1657737931638" MODIFIED="1657737938130"/>
<node TEXT="Faire des essais pour bien la comprendre" ID="ID_27540261" CREATED="1657737939175" MODIFIED="1657737978502"/>
</node>
</node>
</node>
</map>
