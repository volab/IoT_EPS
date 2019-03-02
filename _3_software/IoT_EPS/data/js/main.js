$(document).ready( ()=>{
    // start .ready()

    const log           = new C_MyLog();
    const regEx         = new C_RexExPatern();
    const red           = new C_Plug("redPlug");
    const v_jsonFile    = 'config3.json';

    const HOME          = $("div.home");
    const FIELDSET      = $("fieldset");
    // const HELP          = $("div.help");
    // const CFG           = $("div.cfg");

    const menuHome      = $(".home.modeSelector");
    const menuHelp      = $(".help.modeSelector");
    const menuCfg      = $(".cfg.modeSelector");

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
            red.f_displayDiv_hFin("flex")
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

    $(red.manuelForm).on(
        "submit",
        (event)=>{
            event.preventDefault();
            $(this).submit();
            log.f_formLog( red.f_getQueryTarget(event));
            $(red.manuelForm)[0].reset();
        }
    );

    /*
    * Events Minuterie
    */
    $(red.modeMinuterie).on(
        "click", 
        ()=>{
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

    $(red.minuterieForm).on(
        "submit",
        (event)=>{
            event.preventDefault();
            $(this).submit();
            log.f_formLog( red.f_getQueryTarget(event));
            $(red.minuterieForm)[0].reset();
        }
    );

    /*
    * Events Cyclique
    */
    $(red.modeCyclique).on(
        "click", 
        function(){
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

    $(red.cycliqueForm).on(
        "submit",
        (event)=>{
            event.preventDefault();
            $(this).submit();
            log.f_formLog( red.f_getQueryTarget(event));
            if (!red.cycliquePauseBool){
                $(red.cycliqueForm)[0].reset();
            }
        }
    );

    /* 
    * event Hebdomadaire
    */

    $(red.modeHedbomadaire).on(
        "click", 
        ()=>{
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

    $(red.hebdomadaireForm).on(
        "submit",
        (event)=>{
            event.preventDefault();
            $(this).submit();
            log.f_formLog( red.f_getQueryTarget(event));
            if (!red.hebdomadairePauseBool){
                $(red.hebdomadaireForm)[0].reset();
            }
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

    $(red.cloneForm).on(
        "submit",
        (event)=>{
            event.preventDefault();
            console.log("form Submit");
            $(this).submit();
            log.f_formLog( red.f_getQueryTarget(event));
            $(red.cloneForm)[0].reset();
        }
    );

    /*
    * Traitemant Json
    */

    /* 
    * la fonction loadJson à été piqué ici:
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
        $("#autoTitle").text(v_hostname)};

    function f_populateTable( plug ){
        /* rempli le tableau de la page d'accueil avec les informations contenu dans le ficier JSON */
        var v_tbody = $(".home.tBody");
        var v_body = `
            <tr>
                <td>${plug}</td>
            </tr>`
        v_tbody.prepend(v_body);

    }

    f_loadJSON(v_jsonFile, function(response) {
        var jsonresponse = JSON.parse(response);

        /* general */
        var v_hostname = jsonresponse["general"]["hostName"];
        var v_numberOfPlug = jsonresponse["general"]["numberOfPlugs"];
        //document.getElementById("autoTitle").innerHTML=v_hostname;
        //document.getElementById("autoH1").innerHTML=v_hostname;
        //
        //N.B: l'emploi de 'innerHTML' est déconseiller car il représente une faille de sécurité
        //potenciel.
        f_populateTitle(v_hostname);

        switch (v_numberOfPlug){
            case "4": f_populateTable("yellowPlug");
            case "3": f_populateTable("bluePlug");
            case "2": f_populateTable("greenPlug");
            case "1": f_populateTable("redPlug");
        }

        // let rplg = jsonresponse["redPlug"];

        // for (var prop in rplg){
        //     console.log(`${prop}:${rplg[prop]}`);
        //     if ((prop == "hFin") && rplg[prop]){console.log("####")}
        // }

        // f_populatePlug("redPlug");
        // f_populatePlug("greenPlug");
        // f_populatePlug("bluePlug");
        // f_populatePlug("yellowPlug");
    });

// .ready() end
});

/*
 * ## TODO
 *
 * #. Finir les fonction "clear". Les appliquer sur chaque chagement de mode, changement de prise
 *    et entre chaque action du mode manuel
 *
 * ####
 *
 * #. Ajouter un fieldset de résumé de l'état des prises
 *    /!\ tenir compte de l'état du boutons pause dans le JSON lors du chargement
 *        des modes Cyclique et Hebdomadoare
 * 
 * ####
 *  
 * #. Gestion de la transition entre les DIV (jqueryui .effect "drop" et "slide")
 * 
 * ####
 * 
 * #. Ajouter un fieldset ou un div pour l'aide
 *    ==> ne plus utiliser la page "help.html"
 * 
 *  ####
 * 
 * #. Ajouter un fieldset ou un div pour la personnalisation
 *    (toujours sur la même page)
 * 
 * ####
 * 
 * #. Mode responcive, vérfier le bon affichage sur chacun des modes de la prise
 * 
 * ## TODO
 */
