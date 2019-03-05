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
        let v_plug          = jsonresponse[plug];
        let v_nicName       = v_plug["nickName"];
        let v_emplacement   = v_plug["emplacement"];
        let v_state         = v_plug["State"];
        let v_mode          = v_plug["Mode"];
        let v_pause         = v_plug["Pause"];

        let v_modeConed     = "";
        let v_pauseOn       = "";
        let v_tableColor    = "";

        let v_detail        = "";

        switch (plug){
            case "redPlug": {
                v_tableColor = "table-danger";
                break;}
            case "greenPlug": {
                v_tableColor = "table-success";
                break;}
            case "bluePlug": {
                v_tableColor = "table-primary";
                break;}
            case "yellowPlug": {
                v_tableColor = "table-warning";
                break;}
        }

        switch (v_mode){
            case "Manuel": {
                if (v_state=="ON" && v_plug["hFin"]){
                    v_detail = `Heure d'arrêt : ${v_plug["hFin"]}`;
                } else if (v_state=="ON" && v_plug["dureeOff"]) {
                    v_detail = `Durée avant arrêt : ${v_plug["dureeOff"]} min`;
                }
                break;
            };
            case "Minuterie": {
                v_detail = `Durée de fonctionnement : ${v_plug["dureeOn"]} min `;
                break;
            };
            case "Cyclique": {

                let v_cycl_hDebut = v_plug["hDebut"];
                let v_cycl_dureeOn = v_plug["dureeOn"];
                let v_cycl_dureeOff = v_plug["dureeOff"];

                if (v_cycl_hDebut){
                    v_detail = `
                        <ul>
                            <li>Durée 'ON' : ${v_cycl_dureeOn} min</li>
                            <li>Durée 'OFF' : ${v_cycl_dureeOff} min</li>
                            <li>Heure de début : ${v_cycl_hDebut}</li>
                        </ul>`;
                } else {
                    v_detail = `
                        <ul>
                            <li>Durée 'ON' : ${v_cycl_dureeOn} min</li>
                            <li>Durée 'OFF' : ${v_cycl_dureeOff} min</li>
                        </ul>`;
                }
                break;
            };
            case "Hebdomadaire": {
                break;
            };
        }

        if (jsonresponse[plug]["clonedPlug"]){
            let v_clonedPlug = v_plug["clonedPlug"];
            let v_clonePlugName = jsonresponse[v_clonedPlug]["nickName"];
            v_modeConed = `<br>(prise clonée depuis la prise ${v_clonePlugName})`
        }

        if ((v_mode=="Cyclique" || v_mode=="Hebdomadaire") && v_pause=="ON" && v_state=="ON"){
            v_pauseOn = `<br><span class="text-danger">Actuellement en PAUSE</span>`;
        }

        let v_tbody         = $(".home.tBody");
        let v_body = `
            <tr class="${v_tableColor}">
                <td>${v_nicName}<br>
                    (${v_emplacement})
                </td>
                <td>${v_state}${v_pauseOn}</td>
                <td>${v_mode}${v_modeConed}</td>
                <td>${v_detail}</td>
            </tr>`
            ;
        v_tbody.prepend(v_body);

    }

    f_loadJSON(v_jsonFile, function(response) {
        jsonresponse = JSON.parse(response);

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
 *    * /!\ tenir compte de l'état du boutons pause dans le JSON lors du chargement
 *        des modes Cyclique et Hebdomadoare
 *
 *    * Pour le mode hedomadaire utiliser une boucle for ("for (variable of iterable)")
 *      https://developer.mozilla.org/fr/docs/Web/JavaScript/Reference/Instructions/for...of
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
