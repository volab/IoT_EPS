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
        this.minuterie_dureeOn           = null;
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
        this.cycliqueSubmit             = null;

        /* Mode Hebdomadaire */
        this.hebdomadaireDiv            = null;
            //QuerySelectorAll (Liste d'objet)
        this.hebdomadaireQueryAll       = null;
            //weekday
        this.hebdmadaireAllDays         = null;
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
        this.hebdmadaireSubmit          = null;

        /* Mode Clone */
            //DIV
        this.cloneDiv                   = null;
            //Selector
        this.cloneSelector              = null;
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

    f_setQueryModeSelector(v_colorPlug){
        /* Permet d'initialiser les QuerySelector des boutons radio pour le 'modeSelector */
        v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;

        this.modeManuel = document.querySelector("." + v_colorPlug + ".modeSelector.Manuel");
        this.modeMinuterie = document.querySelector("." + v_colorPlug + ".modeSelector.Minuterie");
        this.modeCyclique = $(`.${v_colorPlug}.modeSelector.Cyclique`);
        // this.modeHedbomadaire = document.querySelector("." + v_colorPlug + ".modeSelector.Hebdomadaire");
        this.modeHedbomadaire = $(`.${v_colorPlug}.modeSelector.Hebdomadaire`);
        this.modeClone = document.querySelector("." + v_colorPlug + ".modeSelector.Clone");
    }

    f_setQueryManuel(v_colorPlug){
        /* Permet d'initialiser les QerySelector pour le mode Manuel */
        v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;

        this.manuelDiv = document.querySelector("." + v_colorPlug + ".Manuel.div_subSummary");
            //sub div colone 1
        this.manuelDiv_on_off  = document.querySelector("." + v_colorPlug + ".Manuel .on_off" );
        this.manuelON  = document.querySelector("." + v_colorPlug + ".Manuel.ON" );
        this.manuelOFF  = document.querySelector("." + v_colorPlug + ".Manuel.OFF" );
            //sub div colone 2
        this.manuelDivDiffTypeSelector  = document.querySelector("." + v_colorPlug + ".Manuel.div_diffTypeSelector" );
        this.manuelDiffAt  = document.querySelector("." + v_colorPlug + ".Manuel.diffAt" );
        this.manuelDiffIn  = document.querySelector("." + v_colorPlug + ".Manuel.diffIn" );
            //sub div colone 3 (1/2)
        this.manuelDiv_hFin  = document.querySelector("." + v_colorPlug + ".Manuel.div_hFin" );
        this.manuel_hFin  = document.querySelector("." + v_colorPlug + ".Manuel.hFin" );
            //sub div colone 3 (2/2)
        this.manuelDiv_dureeOff  = document.querySelector("." + v_colorPlug + ".Manuel.div_dureeOff" );
        this.manuel_dureeOff  = document.querySelector("." + v_colorPlug + ".Manuel.dureeOff" );
        //Submit
        this.manuelForm = document.querySelector("." + v_colorPlug + ".Manuel.formRequest");
        this.manuelSubmit = document.querySelector("." + v_colorPlug + ".Manuel.submit" );
    }

    f_setQueryMinuterie(v_colorPlug){
        /* Permet d'initialiser les QerySelector pour le mode Minuterie */
        v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;
        
        this.minuterieDiv = document.querySelector("." + v_colorPlug +  ".Minuterie.div_subSummary");
        this.minuterie_dureeOn = document.querySelector("." + v_colorPlug +  ".Minuterie.dureeOn");
        this.minuterieForm = document.querySelector("." + v_colorPlug +  ".Minuterie.formRequest");
        this.minuterieSubmit = document.querySelector("." + v_colorPlug +  ".Minuterie.submit");
    }

    f_setQueryCyclique(v_colorPlug){
        /* Permet d'intialiser les QuerySelector pour le mode Cyclique */
        v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;

        this.cycliqueDiv = $(`.${v_colorPlug}.Cyclique.div_subSummary`);
        this.cyclique_dureeOn = $(`.${v_colorPlug}.Cyclique.dureeOn`);
        this.cyclique_dureeOff = $(`.${v_colorPlug}.Cyclique.dureeOff`);
        this.cyclique_hDebut = $(`.${v_colorPlug}.Cyclique.hDebut`);
        this.cycliqueForm = $(`.${v_colorPlug}.Cyclique.formRequest`);
        this.cycliquePause = $(`.${v_colorPlug}.Cyclique.pause`);
        this.cycliqueSubmit = $(`.${v_colorPlug}.Cyclique.submit`);

    }
    f_setQueryHebdomadaire(v_colorPlug){
        /* Permet d'intialiser les QuerySelector pour le mode Hebdomadaire */
        v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;
            //DIV
        // this.hebdomadaireDiv = document.querySelector("."+ v_colorPlug +".Hebdomadaire.div_subSummary");
        this.hebdomadaireDiv = $(`.${v_colorPlug}.Hebdomadaire.div_subSummary`);
            //QuerySelectorAll (liste d'objet)
        // this.hebdomadaireQueryAll = document.querySelectorAll("."+v_colorPlug +".Hebdomadaire.daySelector")
        this.hebdomadaireQueryAll = $(`.${v_colorPlug}.Hebdomadaire.daySelector`);
            //WeekDay
        // this.hebdmadaireAllDays = document.querySelector("."+ v_colorPlug +".Hebdomadaire.AllDays");
        // this.hebdomadaireLundi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Lundi");
        // this.hebdomadaireMardi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Mardi");
        // this.hebdomadaireMercredi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Mercredi");
        // this.hebdomadaireJeudi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Jeudi");
        // this.hebdomadaireVendredi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Vendredi");
        // this.hebdomadaireSamedi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Samedi");
        // this.hebdomadaireDimanche = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Dimanche");

        this.hebdmadaireAllDays = $(`.${v_colorPlug}.Hebdomadaire.AllDays`);
        this.hebdomadaireLundi = $(`.${v_colorPlug}.Hebdomadaire.Lundi`);
        this.hebdomadaireMardi = $(`.${v_colorPlug}.Hebdomadaire.Mardi`);
        this.hebdomadaireMercredi = $(`.${v_colorPlug}.Hebdomadaire.Mercredi`);
        this.hebdomadaireJeudi = $(`.${v_colorPlug}.Hebdomadaire.Jeudi`);
        this.hebdomadaireVendredi = $(`.${v_colorPlug}.Hebdomadaire.Vendredi`);
        this.hebdomadaireSamedi = $(`.${v_colorPlug}.Hebdomadaire.Samedi`);
        this.hebdomadaireDimanche = $(`.${v_colorPlug}.Hebdomadaire.Dimanche`);
            //Time Selector
        // this.hebdomadaire_hDebut = document.querySelector("."+ v_colorPlug +".Hebdomadaire.hDebut");
        // this.hebdomadaire_hFin = document.querySelector("."+ v_colorPlug +".Hebdomadaire.hFin");
        this.hebdomadaire_hDebut = $(`.${v_colorPlug}.Hebdomadaire.hDebut`);
        this.hebdomadaire_hFin = $(`.${v_colorPlug}.Hebdomadaire.hFin`);
            //submit
        // this.hebdomadaireForm = document.querySelector("."+ v_colorPlug +".Hebdomadaire.formRequest");
        // this.hebdomadairePause = document.querySelector("."+ v_colorPlug +".Hebdomadaire.pause");
        // this.hebdomadaireSubmit = document.querySelector("."+ v_colorPlug +".Hebdomadaire.submit");
        this.hebdomadaireForm = $(`.${v_colorPlug}.Hebdomadaire.formRequest`);
        // this.hebdomadairePause = $(`.${v_colorPlug}.Hebdomadaire.pause`);
        this.hebdomadairePause = $(".redPlug.Hebdomadaire.pause");
        this.hebdomadaireSubmit = $(`.${v_colorPlug}.Hebdomadaire.submit`);
    }

    f_setQueryClone(v_colorPlug){
        /* Permet d'initialiser les QuerySelector pour le mode Clone */
        v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;

        this.cloneDiv = document.querySelector("."+ v_colorPlug +".Clone.div_subSummary");
        this.cloneSelector = document.querySelector("."+ v_colorPlug +".Clone.plugSelector");
        this.hebdomadairePause = document.querySelector("."+ v_colorPlug +".Hebdomadaire.pause");
        this.cloneSubmit = document.querySelector("."+ +".Clone.submitReset");
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
        this.manuelDiv.style.display="none";
        this.manuelDivDiffTypeSelector.style.display="none";
        this.manuelDiv_hFin.style.display="none";
        this.manuelDiv_dureeOff.style.display="none";
        this.manuelDiffAt.checked = false;
        this.manuelDiffIn.checked = false;
        //masquage des DIV Minuterie
        this.minuterieDiv.style.display="none";
        //masquage des DIV Cyclique
        // this.cycliqueDiv.style.display="none";
        this.cycliqueDiv.css("display", "none");
        //masquage des DIV Hebdomadaire
        // this.hebdomadaireDiv.style.display="none";
        this.hebdomadaireDiv.css("display", "none");
        //masquage des DIV Clone
        this.cloneDiv.style.display="none";
    }

    f_displayManuelDiv(v_displayStatus){
        /* permet d'afficher ou de masquer le DIV Manuel 
         * Les valeur attendue sont: "none" ou "block"
         */

        if ((v_displayStatus === "block")||(v_displayStatus === "none")){
            this.f_displayNoneAll();
            this.manuelDiv.style.display=v_displayStatus;
        }
    }

    f_displayTypeSelector(v_displayStatus){
        /* permet d'fficher ou de masquer le DIV DiffTypeSelector
         * Les valeur attendue sont: "none" ou "block"
         */
        if ((v_displayStatus === "block")||(v_displayStatus === "none")){
            this.manuelDivDiffTypeSelector.style.display = v_displayStatus;
        }
    }

    f_displayDiv_dureeOff(v_displayStatus){
        /* permet d'fficher ou de masquer le DIV dureeOff
         * Les valeur attendue sont: "none" ou "block"
         */
        if ((v_displayStatus === "block")||(v_displayStatus === "none")){
            if (v_displayStatus === "none"){
                this.manuel_dureeOff.value = "";
                this.manuelDiffIn.checked = false;
            }
            this.manuelDiv_dureeOff.style.display = v_displayStatus;
        }
    }

    f_displayDiv_hFin(v_displayStatus){
        /* permet d'fficher ou de masquer le DIV f_displayDiv_hFin
         * Les valeur attendue sont: "none" ou "block"
         */
        if ((v_displayStatus === "block")||(v_displayStatus === "none")){
            if (v_displayStatus === "none"){
                this.manuel_hFin.value = "";
                this.manuelDiffAt.checked = false;
            }
            this.manuelDiv_hFin.style.display = v_displayStatus;
        }
    }

    f_displayMinuterieDiv(v_displayStatus){
        /* permet d'afficher ou de masquer le DIV Minuterie 
         * Les valeur attendue sont: "none" ou "block"
         */

        if ((v_displayStatus === "block")||(v_displayStatus === "none")){
            this.f_displayNoneAll();
            this.minuterieDiv.style.display=v_displayStatus;
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
}