/**
 * Class permmetant de définir l'objet Plug (Prise)
 * Chaque prise représente une nouvelle instance de cette class.
 *
 * @class C_Plug
 * @param {string} v_colorPlug - Défini la couleur de la prise. Les paramètres attendu sont :
 *  - redPlug
 *  - greenPlug
 *  - bluePlug
 *  - YellowPlug
 */
class C_Plug{
    constructor(v_colorPlug){
        this.v_colorPlug                = v_colorPlug;
        this.targetClassList            = null;

        /* définition des radio 'modeSelector' */
        this.divLeft                    = null;
        this.modeManuel                 = null;
        this.modeMinuterie              = null;
        this.modeCyclique               = null;
        this.modeHedbomadaire           = null;
        this.modeClone                  = null;

        /* Mode Manuel */
            //DIV
        this.manuelDiv                  = null;
            //sub div colone 1
        this.manuelDiv_on_off           = null;
        this.manuelON                   = null;
        this.manuelOFF                  = null;
            //sub div colone 2
        this.manuelDivDiffTypeSelector  = null;
        this.manuelDiffAt               = null;
        this.manuelDiffIn               = null;
            //sub div colone 3 (1/2)
        this.manuelDiv_hFin             = null;
        this.manuel_hFin                = null;
            //sub div colone 3 (2/2)
        this.manuelDiv_dureeOff         = null;
        this.manuel_dureeOff            = null;
            //submit
        this.manuelForm                 = null;
        this.manuelSubmit               = null;

        /* Mode Minuterie */
            //Time Selector
        this.minuterieDiv               = null;
        this.minuterie_dureeOn          = null;
            //Submit
        this.minuterieForm              = null;
        this.minuterieSubmit            = null;

        /* Mode Cyclique */
            //DIV
        this.cycliqueDiv                = null;
            //Time Selector
        this.cyclique_dureeOn           = null;
        this.cyclique_dureeOff          = null;
        this.cyclique_hDebut            = null;
            //Submit
        this.cycliqueForm               = null;
        this.cycliquePause              = null;
        this.cycliquePauseBool          = false;
        this.cycliqueSubmit             = null;

        /* Mode Hebdomadaire */
        this.hebdomadaireDiv            = null;
            //QuerySelectorAll (Liste d'objet)
        this.hebdomadaireQueryAll       = null;
            //weekday
        this.hebdmadaireAllDays         = null;
        this.hebdomadaireWeekDay        = null;
        this.hebdomadaireLundi          = null;
        this.hebdomadaireMardi          = null;
        this.hebdomadaireMercredi       = null;
        this.hebdomadaireJeudi          = null;
        this.hebdomadaireVendredi       = null;
        this.hebdomadaireSamedi         = null;
        this.hebdomadaireDimanche       = null;
            //Time selector
        this.hebdomadaire_hDebut        = null;
        this.hebdomadaire_hFin          = null;
            //Submit
        this.hebdomadaireForm           = null;
        this.hebdomadairePause          = null;
        this.hebdomadairePauseBool      = false;
        this.hebdmadaireSubmit          = null;

        /* Mode Clone */
            //DIV
        this.cloneDiv                   = null;
            //FormHide
        this.cloneInputHide             = null;
            //Selector
        this.cloneToRed                 = null;
        this.cloneToGreen               = null;
        this.cloneToBlue                = null;
        this.cloneToYellow              = null;
            //Submit
        this.cloneForm                  = null;      
        this.cloneSubmit                = null;

        //Init
        this.f_plugInit()

    }

    f_plugInit(v_colorPlug){
        /* Initialisation des différents éléments */
        this.f_setQueryModeSelector(v_colorPlug);
        this.f_setQueryManuel(v_colorPlug);
        this.f_setQueryMinuterie(v_colorPlug);
        this.f_setQueryCyclique(v_colorPlug);
        this.f_setQueryHebdomadaire(v_colorPlug);
        this.f_setQueryClone(v_colorPlug);

        this.f_displayNoneAll();
    }

    f_clean(){
        $("input[type='text']").val("");
    }

    f_setQueryModeSelector(v_colorPlug){
        /* Permet d'initialiser les QuerySelector des boutons radio pour le 'modeSelector */
        // v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;

        this.divLeft            = $(`.div_left`);
        this.modeManuel         = $(`.modeSelector.Manuel`);
        this.modeMinuterie      = $(`.modeSelector.Minuterie`);
        this.modeCyclique       = $(`.modeSelector.Cyclique`);
        this.modeHedbomadaire   = $(`.modeSelector.Hebdomadaire`);
        this.modeClone          = $(`.modeSelector.Clone`);
    }

    f_setQueryManuel(v_colorPlug){
        /* Permet d'initialiser les QerySelector pour le mode Manuel */
        // v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;

        this.manuelDiv = $(`.Manuel.div_subSummary`);
            //sub div colone 1
        this.manuelDiv_on_off  = $(`.Manuel .on_off`);
        this.manuelON  = $(`.Manuel.ON`);
        this.manuelOFF  = $(`.Manuel.OFF`);
            //sub div colone 2
        this.manuelDivDiffTypeSelector  = $(`.Manuel.div_diffTypeSelector`);
        this.manuelDiffAt  = $(`.Manuel.diffAt`);
        this.manuelDiffIn  = $(`.Manuel.diffIn`);
            //sub div colone 3 (1/2)
        this.manuelDiv_hFin  = $(`.Manuel.div_hFin`);
        this.manuel_hFin  = $(`.Manuel.hFin`);
            //sub div colone 3 (2/2)
        this.manuelDiv_dureeOff  = $(`.Manuel.div_dureeOff`);
        this.manuel_dureeOff  = $(`.Manuel.dureeOff`);
        //Submit
        this.manuelForm = $(`.Manuel.formRequest`);
        this.manuelSubmit = $(`.Manuel.submit`);
    }

    f_setQueryMinuterie(v_colorPlug){
        /* Permet d'initialiser les QerySelector pour le mode Minuterie */
        // v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;
        
        this.minuterieDiv = $(`.Minuterie.div_subSummary`);
        this.minuterie_dureeOn = $(`.Minuterie.dureeOn`);
        this.minuterieForm = $(`.Minuterie.formRequest`);
        this.minuterieSubmit = $(`.Minuterie.submit`);
    }

    f_setQueryCyclique(v_colorPlug){
        /* Permet d'intialiser les QuerySelector pour le mode Cyclique */
        // v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;

        this.cycliqueDiv = $(`.Cyclique.div_subSummary`);
        this.cyclique_dureeOn = $(`.Cyclique.dureeOn`);
        this.cyclique_dureeOff = $(`.Cyclique.dureeOff`);
        this.cyclique_hDebut = $(`.Cyclique.hDebut`);
        this.cycliqueForm = $(`.Cyclique.formRequest`);
        this.cycliquePause = $(`.Cyclique.pause`);
        this.cycliqueSubmit = $(`.Cyclique.submit`);

    }

    f_setQueryHebdomadaire(v_colorPlug){
        /* Permet d'intialiser les QuerySelector pour le mode Hebdomadaire */
        // v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;
            //DIV
        this.hebdomadaireDiv = $(`.Hebdomadaire.div_subSummary`);
            //QuerySelectorAll (liste d'objet)
        this.hebdomadaireQueryAll = $(`.Hebdomadaire.daySelector`);
            //WeekDay
        this.hebdmadaireAllDays     = $(`.Hebdomadaire.AllDays`);
        this.hebdomadaireWeekDay    = $(`input:checkbox.Hebdomadaire.daySelector`).not(".AllDays");
        this.hebdomadaireLundi      = $(`.Hebdomadaire.Lundi`);
        this.hebdomadaireMardi      = $(`.Hebdomadaire.Mardi`);
        this.hebdomadaireMercredi   = $(`.Hebdomadaire.Mercredi`);
        this.hebdomadaireJeudi      = $(`.Hebdomadaire.Jeudi`);
        this.hebdomadaireVendredi   = $(`.Hebdomadaire.Vendredi`);
        this.hebdomadaireSamedi     = $(`.Hebdomadaire.Samedi`);
        this.hebdomadaireDimanche   = $(`.Hebdomadaire.Dimanche`);
            //Time Selector
        this.hebdomadaire_hDebut    = $(`.Hebdomadaire.hDebut`);
        this.hebdomadaire_hFin      = $(`.Hebdomadaire.hFin`);
            //submit
        this.hebdomadaireForm       = $(`.Hebdomadaire.formRequest`);
        this.hebdomadairePause      = $(`.Hebdomadaire.pause`);
        this.hebdomadaireSubmit     = $(`.Hebdomadaire.submit`);
    }

    f_setQueryClone(v_colorPlug){
        /* Permet d'initialiser les QuerySelector pour le mode Clone */
        // v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;

        this.cloneDiv               = $(`.Clone.div_subSummary`);
        this.cloneInputHide         = $(`input[name="clonedPlug"]`)
        this.cloneToRed             = $(`.Clone.Red`);
        this.cloneToGreen           = $(`.Clone.Green`);
        this.cloneToBlue             = $(`.Clone.Blue`);
        this.cloneToYellow          = $(`.Clone.Yellow`);
        this.cloneForm              = $(`.Clone.formRequest`);
        this.cloneSubmit            = $(`.Clone.submit`);
    }

    f_getQueryTarget(event){
        let v_targetClassList = (event.target.classList);
        this.targetClassList = (event.target.classList);
        let v_tmp = "";
        for (let i=0; i<v_targetClassList.length; i++){
            v_tmp += "." + v_targetClassList[i];
            }
            return document.querySelector(v_tmp);
    }

    f_displayNoneAll(){
        /* Permet de masquer tous les DIV à l'intérieur des FILDSET */
        //mode Manuel
        this.divLeft.css("display", "none");
        this.manuelDiv.css("display", "none");
        this.manuelDivDiffTypeSelector.css("display", "none");
        this.manuelDiv_hFin.css("display", "none");
        this.manuelDiv_dureeOff.css("display", "none");
        // this.manuelDiffAt.checked = false;
        // this.manuelDiffIn.checked = false;
        //masquage des DIV Minuterie
        this.minuterieDiv.css("display", "none");
        //masquage des DIV Cyclique
        this.cycliqueDiv.css("display", "none");
        //masquage des DIV Hebdomadaire
        this.hebdomadaireDiv.css("display", "none");
        //masquage des DIV Clone
        this.cloneDiv.css("display", "none");
    }

    f_displayManuelDiv(v_displayStatus){
        /* permet d'afficher ou de masquer le DIV Manuel 
         * Les valeur attendue sont: "none" ou "block"
         */
        if ((v_displayStatus === "block")||(v_displayStatus === "none")){
            this.f_displayNoneAll();
            this.manuelDiv.css("display", v_displayStatus);
            this.manuelForm[0].reset();
        }
    }

    f_displayTypeSelector(v_displayStatus){
        /* permet d'afficher ou de masquer le DIV DiffTypeSelector
         * Les valeur attendue sont: "none" ou "block"
         */
        if ((v_displayStatus === "block")||(v_displayStatus === "none")){
            this.manuelDivDiffTypeSelector.css("display", v_displayStatus);
        }
    }

    f_displayDiv_dureeOff(v_displayStatus){
        /* permet d'afficher ou de masquer le DIV dureeOff
         * Les valeur attendue sont: "none", "block" ou "flex"
         */
        if (((v_displayStatus === "block")||(v_displayStatus === "flex"))||(v_displayStatus === "none")){
            if (v_displayStatus === "none"){
                this.manuel_dureeOff.value = "";
                this.manuelDiffIn.checked = false;
            }
            this.manuelDiv_dureeOff.css("display", v_displayStatus);
        }
    }

    f_displayDiv_hFin(v_displayStatus){
        /* permet d'afficher ou de masquer le DIV f_displayDiv_hFin
         * Les valeur attendue sont: "none", "block" ou "flex"
         */
        if (((v_displayStatus === "block")||(v_displayStatus === "flex"))||(v_displayStatus === "none")){
            if (v_displayStatus === "none"){
                this.manuel_hFin.value = "";
                this.manuelDiffAt.checked = false;
            }
            this.manuelDiv_hFin.css("display", v_displayStatus);
        }
    }

    f_displayMinuterieDiv(v_displayStatus){
        /* permet d'afficher ou de masquer le DIV Minuterie 
         * Les valeur attendue sont: "none" ou "block"
         */
        if ((v_displayStatus === "block")||(v_displayStatus === "none")){
            this.f_displayNoneAll();
            this.minuterieDiv.css("display", v_displayStatus);
        }
    }

    f_displayCycliqueDiv(v_displayStatus){
        /* permet d'afficher ou de masquer le DIV Cyclique 
         * Les valeur attendue sont: "none" ou "block"
         */
        if ((v_displayStatus === "block")||(v_displayStatus === "none")){
            this.f_displayNoneAll();
            this.cycliqueDiv.css("display", v_displayStatus);
        }
    }
    
    f_displayHebdomadaireDiv(v_displayStatus){
        /* permet d'afficher ou de masquer le DIV Hebdomadaire 
         * Les valeur attendue sont: "none" ou "block"
         */
        if ((v_displayStatus === "block")||(v_displayStatus === "none")){
            this.f_displayNoneAll();
            this.hebdomadaireDiv.css("display", v_displayStatus);
        }
    }

    f_displayCloneDiv(v_displayStatus){
        /* permet d'afficher ou de masquer le DIV Hebdomadaire 
         * Les valeur attendue sont: "none" ou "block"
         */
        if ((v_displayStatus === "block")||(v_displayStatus === "none")){
            this.f_displayNoneAll();
            this.cloneDiv.css("display", v_displayStatus);
        }
    }

    f_toggleCycliquePauseBool(){
        this.cycliquePauseBool = !this.cycliquePauseBool;
    }

    f_toggleHebdomadairePauseBool(){
        this.hebdomadairePauseBool = !this.hebdomadairePauseBool;
    }

    f_cloneHideCurrentPlug(event){
        /* Permet de masquer la prise en court d'utilisation de la liste des prises à cloner */
        let v_target = $(event.target);
        if (v_target.hasClass("redPlug")){
            $(".div_cloneRed").hide();
            $(".div_cloneGreen").show();
            $(".div_cloneBlue").show();
            $(".div_cloneYellow").show();
        } else if (v_target.hasClass("greenPlug")){
            $(".div_cloneRed").show();
            $(".div_cloneGreen").hide();
            $(".div_cloneBlue").show();
            $(".div_cloneYellow").show();
        } else if (v_target.hasClass("bluePlug")) {
            $(".div_cloneRed").show();
            $(".div_cloneGreen").show();
            $(".div_cloneBlue").hide();
            $(".div_cloneYellow").show();
        } else if (v_target.hasClass("yellowPlug")) {
            $(".div_cloneRed").show();
            $(".div_cloneGreen").show();
            $(".div_cloneBlue").show();
            $(".div_cloneYellow").hide();
        }
    }

    f_switchClass(v_eventTarget){
        /* Permet de permuter les class 'home', 'redPlug', 'greenPlug', 'bluePlug', 'yellowPlug', 'help' et 'cfg' */
        // let HOME        = "home";
        let REDPLUG     = "redPlug";
        let GREENPLUG   = "greenPlug";
        let BLUEPLUG    = "bluePlug";
        let YELLOWPLUG  = "yellowPlug";
        // let HELP        = "help";
        // let CFG         = "cfg";

        let v_target = $(v_eventTarget);
        let v_fieldset = $("fieldset");
        let v_fieldsetClass = v_fieldset.attr("class");

        let v_hiddenInput = $(".hidden")

        // if (v_target.hasClass(HOME)){
        //     v_fieldset.toggleClass(`${v_fieldsetClass} ${HOME}`);
        //     $("h2").text("Résumé")

        //     v_hiddenInput.each( (i)=>{
        //         $(v_hiddenInput[i]).val(HOME);
        //     } );
        // } else
         if (v_target.hasClass(REDPLUG)){
            v_fieldset.toggleClass(`${v_fieldsetClass} ${REDPLUG}`);
            $("h2").text("Prise Rouge");

            v_hiddenInput.each( (i)=>{
                $(v_hiddenInput[i]).val(REDPLUG);
            } );
        } else if (v_target.hasClass(GREENPLUG)){
            v_fieldset.toggleClass(`${v_fieldsetClass} ${GREENPLUG}`);
            $("h2").text("Prise Verte");

            v_hiddenInput.each( (i)=>{
                $(v_hiddenInput[i]).val(GREENPLUG);
            } );
        } else if (v_target.hasClass(BLUEPLUG)){
            v_fieldset.toggleClass(`${v_fieldsetClass} ${BLUEPLUG}`);
            $("h2").text("Prise Bleue");

            v_hiddenInput.each( (i)=>{
                $(v_hiddenInput[i]).val(BLUEPLUG);
            } );
        } else if (v_target.hasClass(YELLOWPLUG)){
            v_fieldset.toggleClass(`${v_fieldsetClass} ${YELLOWPLUG}`);
            $("h2").text("Prise Jaune");

                v_hiddenInput.each( (i)=>{
                $(v_hiddenInput[i]).val(YELLOWPLUG);
            } );
        }
        //  else if (v_target.hasClass(HELP)){
        //     v_fieldset.toggleClass(`${v_fieldsetClass} ${HELP}`);
        //     $("h2").text("Aide");

        //     v_hiddenInput.each( (i)=>{
        //         $(v_hiddenInput[i]).val(HELP);
        //     } );
        // } else if (v_target.hasClass(CFG)){
        //     v_fieldset.toggleClass(`${v_fieldsetClass} ${CFG}`);
        //     $("h2").text("Configuration");

        //     v_hiddenInput.each( (i)=>{
        //         $(v_hiddenInput[i]).val(CFG);
        //     } );
        // }
    }

}