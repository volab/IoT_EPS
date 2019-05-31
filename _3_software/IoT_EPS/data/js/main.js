$(document).ready( ()=>{
    // start .ready()

    // const log                   = new C_MyLog();
    const regEx                 = new C_RexExPatern();
    const red                   = new C_Plug("redPlug");
    const table                 = new C_Table();
    const v_jsonFile            = 'config4.json';

    const HOME                  = $("div.home");
    const FIELDSET              = $("fieldset");
    // const HELP               = $("div.help");
    // const CFG                = $("div.cfg");

    const BTN_RST_NOT_MANUEL    = $(".reset:not(:first)");
    const FORM_NOT_MANUEL       = $(".formRequest:not(:first)");

    const menuHome              = $(".home.modeSelector");
    const menuHelp              = $(".help.modeSelector");
    const menuCfg               = $(".cfg.modeSelector");

    /*
    * Nettoyage avant usage
    */
    function f_hideAll(){
        /* Permet de masquer tous les élémets ('home', 'fieldset', 'help' et 'cfg') */
        HOME.hide();
        FIELDSET.hide();
        // HELP.hide();
        // CFG.hide();
    }

    function f_showOne(v_target){
        /* permet d'afficher un éléments parmi : HOME, FIELDSET, HELP et CFG */
        v_target.show();
    }

    regEx.f_clean();
    red.f_clean();

    f_hideAll();
    f_showOne(HOME);

    // /*
    //  * Centrage du titre
    //  */
    // function f_resize(){
    //     let winWidth = $(window).width();
    //     let v_jimbotron = $(".jimbotron");
    //     let v_headerTitle = $(".headerTitle");
    //     let v_headerTitleWidth = v_headerTitle.width();

    //     let v_offsetTitleTop = v_headerTitle.offset().top;
    //     let v_offsetTitleLeft = (winWidth-v_headerTitleWidth)/2;


    //     v_jimbotron.width(winWidth);
    //     v_jimbotron.css({
    //     "margin": "0 1.5% 0 1.5%"
    //     });

    //     v_headerTitle.css({
    //     "position": "fixed",
    //     "top": v_offsetTitleTop,
    //     "left": v_offsetTitleLeft
    //     });
    // }

    // f_resize();

    // /*
    //  * Responcive
    //  */
    // $(window).resize(
    //     ()=>{
    //         f_resize();
    //     }
    // )

    /*
    * Menu (Hamberger + Sidebar)
    */
    var v_sidebar = $('#sidebar');

    var toggleSidebar = ()=>{ 
        v_sidebar.toggleClass('active');
    };

    toggleSidebar()

    $('#sidebarCollapse').on('click', () => {
        toggleSidebar();
    });

    /*
     * Selecteurs sidebar != des prises
     */
    menuHome.on(
        "click",
        ()=>{
            regEx.f_clean();
            f_hideAll();
            f_showOne(HOME);
            toggleSidebar();
        });

    menuHelp.on(
        "click",
        ()=>{
            regEx.f_clean();
            f_hideAll();
            f_showOne(HELP);
        });

    menuCfg.on(
        "click",
        ()=>{
            regEx.f_clean();
            f_hideAll();
            f_showOne(CFG);
    });

    /*
     *  Common Events
     */
    BTN_RST_NOT_MANUEL.on(
        "click", 
        (event)=>{
            regEx.f_clean();
            BTN_RST_NOT_MANUEL.each(
                (i)=>{
                    FORM_NOT_MANUEL[i].reset();
                }
            );
        }
    );

    /*
    * Events Manuel
    */
    $(red.modeManuel).on(
        "click", 
        (event)=>{
            regEx.f_clean();
            f_hideAll();
            f_showOne(FIELDSET);
            red.f_displayManuelDiv("block");
            toggleSidebar();
            red.f_switchClass(event.target);
        }
    );

    $(red.manuelON).on(
        "click",
        ()=>{
            red.f_displayTypeSelector("block"); 
        }
    );

    $(red.manuelOFF).on(
        "click",
        ()=>{
            red.f_displayTypeSelector("none"); 
            red.f_displayDiv_dureeOff("none");
            red.f_displayDiv_hFin("none");
        }
    );

    $(red.manuelDiffAt).on(
        "click",
        ()=>{
            red.f_displayDiv_hFin("flex");
            red.f_displayDiv_dureeOff("none");
        }
    );    

    $(red.manuelDiffIn).on(
        "click",
        ()=>{
            red.f_displayDiv_hFin("none");
            red.f_displayDiv_dureeOff("flex");
        }
    );

    $(red.manuel_hFin).on(
        "input",
        (event)=>{
            regEx.f_callbackRegEx(event)
        }
    );

    $(red.manuel_dureeOff).on(
        "input",
        (event)=>{
            regEx.f_callbackRegEx(event)
        }
    );

    red.manuelReset.on(
        "click",
        (event)=>{
            red.f_displayDiv_dureeOff("none");
            red.f_displayDiv_hFin("none");
            red.f_displayTypeSelector("none");
            regEx.f_clean();
            // INFO : JQuery n'a pas de methode native 'reset()'. Il faut utiliser la methode Javascript
            red.manuelForm[0].reset();
        }
    );

    /*
    * Events Minuterie
    */
    $(red.modeMinuterie).on(
        "click", 
        (event)=>{
            regEx.f_clean();
            f_hideAll();
            f_showOne(FIELDSET);
            red.f_displayMinuterieDiv("block");
            toggleSidebar();
            red.f_switchClass(event.target);
        });

    $(red.minuterie_dureeOn).on(
        "input",
        (event)=>{
            regEx.f_callbackRegEx(event)
        });

    /*
    * Events Cyclique
    */
    $(red.modeCyclique).on(
        "click", 
        function(event){
            regEx.f_clean();
            f_hideAll();
            f_showOne(FIELDSET);
            red.f_displayCycliqueDiv("block");
            toggleSidebar();
            red.f_switchClass(event.target);
        });

    $(red.cyclique_dureeOn).on(
        "input",
        function(event){
            regEx.f_callbackRegEx(event);
        });

    $(red.cyclique_dureeOff).on(
        "input",
        function(event){
            regEx.f_callbackRegEx(event);
        });
            
    $(red.cyclique_hDebut).on(
        "input",
        function(event){
            regEx.f_callbackRegEx(event);
        });

    $(red.cycliquePause).on(
        "click",
        (event)=>{
            let inputJQSelector = $("input.redPlug.Cyclique").not(".pause").not($(red.modeCyclique));
            if ($(red.cycliquePause).is(":checked")){
                red.f_toggleCycliquePauseBool();
                inputJQSelector.each((i)=>{
                    inputJQSelector[i].disabled=true;
                });
            } else {
                red.f_toggleCycliquePauseBool();
                inputJQSelector.each((i)=>{
                    inputJQSelector[i].disabled=false;
                });
            }
            red.cycliqueForm.submit();
        }
    );    

    /* 
    * event Hebdomadaire
    */
    $(red.modeHedbomadaire).on(
        "click", 
        (event)=>{
            regEx.f_clean();
            f_hideAll();
            f_showOne(FIELDSET);
                red.f_displayHebdomadaireDiv("block");
                toggleSidebar();
                red.f_switchClass(event.target);
        });

    $(red.hebdmadaireAllDays).on(
        "click",
        (event)=>{
            let inputJQSelector = $("input.redPlug.daySelector").not(".AllDays");
            if ($(red.hebdmadaireAllDays).is(":checked")){
                inputJQSelector.each((i)=>{
                    inputJQSelector[i].checked=true;
                });
            }
        }
    );

    $(red.hebdomadaireWeekDay).on(
        "click",
        (event)=>{
            if ($(red.hebdomadaireWeekDay).is(":checked")){
                red.hebdmadaireAllDays[0].checked=false;
            }
    });

    $(red.hebdomadaire_hDebut).on(
        "input",
        function(event){
            regEx.f_callbackRegEx(event);
        });

    $(red.hebdomadaire_hFin).on(
        "input",
        function(event){
            regEx.f_callbackRegEx(event);
    });

    $(red.hebdomadairePause).on(
        "click",
        (event)=>{
            let inputJQSelector = $("input.redPlug.Hebdomadaire").not(".pause").not($(red.modeHedbomadaire));
            if ($(red.hebdomadairePause).is(":checked")){
                red.f_toggleHebdomadairePauseBool();
                inputJQSelector.each((i)=>{
                    inputJQSelector[i].disabled=true;
                });
            } else {
                red.f_toggleHebdomadairePauseBool();
                inputJQSelector.each((i)=>{
                    inputJQSelector[i].disabled=false;
                });
            }
            red.hebdomadaireForm.submit();
        }
    );    

    /* 
    * event Clone
    */
    $(red.modeClone).on(
        "click", 
        (event)=>{
            regEx.f_clean();
            f_hideAll();
            f_showOne(FIELDSET);
            red.f_cloneHideCurrentPlug(event);
            red.f_displayCloneDiv("block");
            toggleSidebar();
            red.f_switchClass(event.target);
        });

    $(red.cloneToRed).on(
        "click",
        (event)=>{
        event.preventDefault();
        $(red.cloneInputHide).val("redPlug");
        $(red.cloneForm).submit();
        }
    )

    $(red.cloneToGreen).on(
        "click",
        (event)=>{
        event.preventDefault();
        $(red.cloneInputHide).val("greenPlug");
        $(red.cloneForm).submit();
        }
    )

    $(red.cloneToBlue).on(
        "click",
        (event)=>{
        event.preventDefault();
        $(red.cloneInputHide).val("bluePlug");
        $(red.cloneForm).submit();
        }
    )

    $(red.cloneToYellow).on(
        "click",
        (event)=>{
        event.preventDefault();
        $(red.cloneInputHide).val("yellowPlug");
        $(red.cloneForm).submit();
        }
    )

    /*
    * Traitemant Json
    */

    /* 
    * la fonction loadJson à été piquée ici:
    * http://www.askyb.com/javascript/load-json-file-locally-by-js-without-jquery/comment-page-1/#comment-4130
    */
    function f_loadJSON(v_file, callback) { 
        var xobj = new XMLHttpRequest();
        xobj.overrideMimeType("application/json");
        xobj.open('GET', v_file, true);
        xobj.onreadystatechange = function () {
        if (xobj.readyState == 4 && xobj.status == "200") {
            callback(xobj.responseText);
        }
        }
        xobj.send(null);
    }

    function f_populateTitle( v_hostname ){
        /* permet de modifier le titre de la page (Onglet) */
        $("#autoTitle").text(v_hostname)
    };

    function f_callbackJSON(response) {
        let jsonresponse = JSON.parse(response);

        /* general */
        var v_hostname = jsonresponse["general"]["hostName"];
        var v_numberOfPlug = jsonresponse["general"]["numberOfPlugs"];
        f_populateTitle(v_hostname);

        switch (v_numberOfPlug){
            case "4": {
                let v_plug = "yellowPlug";
                table.f_refresh(jsonresponse, v_plug);
                table.f_populateTable();
            };
            case "3": {
                let v_plug = "bluePlug";
                table.f_refresh(jsonresponse, v_plug);
                table.f_populateTable();
            };
            case "2": {
                let v_plug = "greenPlug";
                table.f_refresh(jsonresponse, v_plug);
                table.f_populateTable();
            };
            case "1": {
                let v_plug = "redPlug";
                table.f_refresh(jsonresponse, v_plug);
                table.f_populateTable();
            };
        }
    }

    f_loadJSON(v_jsonFile, f_callbackJSON);

    $(table.btnUPD).on(
        "click",
        (event)=>{
            table.f_removeTbody();
            f_loadJSON(v_jsonFile, f_callbackJSON);
        }
    );

// .ready() end
});

/*
 * ## TODO
 *
 * #. Ajouter un fieldset ou un div pour l'aide
 *    ==> ne plus utiliser la page "help.html"
 * 
 *  ####
 * 
 * #. Création d'une page de configuration
 * 
 *    - Ajouter un tableau de résumer de la configuration à l'accueil de la page de configuration
 *    - Nom des prises
 *    - Le mot clef de l'action Interface / serveur : "cfgsend"
 *    - Emplacemet des prises
 *    - Les informations de config4.json sont à traiter.
 *      "general": {
 *          "hostName": "PowerStrip01",         --> Nom de l'EPS
 *          "startInAPMode": "OFF",             --> Pour choisir de démarrer en mode AP en mode réseau
 *                                                  (attaché à un accès wifi)
 *          "firstBoot": "OFF",                 --> Si ON, on fait un reset usine
 *          "numberOfPlugs": "4",               --> Ne pas afficher car non configurable
 *          "rtcValidity": "true",              --> Ne pas afficher car non configurable
 *          "softAP_IP": "192.168.95.42",       --> IP en mode AP
 *                                                  Prévoir une IP Fixe pour le mode réseau
 *          "softAP_port": "80",                --> port de connexion en http pour le mode AP
 *          "allLedsOnTime": "30",              --> Délais avant exctinction des LEDs
 *          "ledsGlobalLuminosity": "5",        --> Réglages de l'intensité lumineuse des LEDs (valeur de 0 à 255)
 *          "powerLedEconomyMode": "OFF",       --> Alumer ou eteindre le témoin de mise sous tension
 *          "STAmaxWifiConnexionRetry": "30"    --> Nombre maximum de tentative de connexion avant passage en mode AP
 *          },
 * 
 *      "redPlug": {
 *          "nickName": "Aquarium",             --> Correspond au nom de l'équipement branché
 *          "emplacement": "salon",             --> Défini l'emplacement de la prise 
 * 
 *      - Les informations de credential.json sont à traiter
 *        "general": {
            "ssid" : "VoLab",
            "pass" : "V0L@b42net",
            "softApSsid" : "powerStrip01_mac",
            "softApPass" : "plusDe8c"
            }
 * 
 * ####
 * 
 * #. Générer la documentation automatique du code
 * 
 *      * voir JSDOC
 *      * Sphinx-js
 * 
 * ## TODO
 */
