class Plug{
    constructor(v_colorPlug){
        this.v_colorPlug        = v_colorPlug;

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
        this.minuterieDureeOn           = null;
            //Submit
        this.minuterieForm              = null;
        this.minuterieSubmit            = null;

        /* Mode Cyclique */
            //DIV
        this.cycliqueDiv                = null;
            //Time Selector
        this.cycliqueDureeOn            = null;
        this.cycliqueDureeOff           = null;
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

        // regEx
        this.v_regExDuree       = /^(300|[0-2]{0,1}\d{1,2}|300:00|[0-2]{0,1}\d{0,2}:[0-5]\d{1})$/;
            // /!\Attention/!\:
            //      - les minutes sont comprises entre 0 et 300
            //      - les secondes sont comprises entre 0 et 59
            //          --> si les minutes sont égales à 300, les secondes doivent être égale à 0
        this.v_regExDureeNoSec  = /^(300|[0-2]{0,1}\d{1,2})$/;
            // /!\Attention/!\ 
            // Le format de durée pour le mode Manuel et pour le mode Cyclique est sur 3 digit, pas de secondes
            //      - les minutes sont comprises entre 0 et 300

        this.v_regExHeure       = /^([0-2]{0,1}\d{1}:[0-5]\d{1})$/;
            // /!\Attention/!\:
            //      - Les heures sont comprises entre 0 et 23
            //      - Les minutes sont comprises entre 0 et 59

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
        this.modeCyclique = document.querySelector("." + v_colorPlug + ".modeSelector.Cyclique");
        this.modeHedbomadaire = document.querySelector("." + v_colorPlug + ".modeSelector.Hebdomadaire");
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
        this.manuel_dureeOff  = document.querySelector("." + v_colorPlug + ".Manuel.dureeOff.dureeNoSec" );
        //Submit
        this.manuelForm = document.querySelector("." + v_colorPlug + ".Manuel.formRequest");
        this.manuelSubmit = document.querySelector("." + v_colorPlug + ".Manuel.submit" );
    }

    f_setQueryMinuterie(v_colorPlug){
        /* Permet d'initialiser les QerySelector pour le mode Minuterie */
        v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;
        
        this.minuterieDiv = document.querySelector("." + v_colorPlug +  ".Minuterie.div_subSummary");
        this.minuterieDureeOn = document.querySelector("." + v_colorPlug +  ".Minuterie.dureeOn");
        this.minuterieForm = document.querySelector("." + v_colorPlug +  ".Minuterie.formRequest");
        this.minuterieSubmit = document.querySelector("." + v_colorPlug +  ".Minuterie.submit");
    }

    f_setQueryCyclique(v_colorPlug){
        /* Permet d'intialiser les QuerySelector pour le mode Cyclique */
        v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;

        this.cycliqueDiv = document.querySelector("."+ v_colorPlug +".Cyclique.div_subSummary");
        this.cycliqueDureeOn = document.querySelector("."+ v_colorPlug +".Cyclique.dureeOn");
        this.cycliqueDureeOff = document.querySelector("."+ v_colorPlug +".Cyclique.dureeOff");
        this.cycliquehDebut = document.querySelector("."+ v_colorPlug +".Cyclique.hDebut");
        this.cycliqueForm = document.querySelector("."+ v_colorPlug +".Cyclique.formRequest");
        this.cycliquePause = document.querySelector("."+ v_colorPlug +".Cyclique.pause");
        this.cycliqueSubmit = document.querySelector("."+ v_colorPlug +".Cyclique.submit");
    }
    f_setQueryHebdomadaire(v_colorPlug){
        /* Permet d'intialiser les QuerySelector pour le mode Hebdomadaire */
        v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;
            //DIV
        this.hebdomadaireDiv = document.querySelector("."+ v_colorPlug +".Hebdomadaire.div_subSummary");
            //QuerySelectorAll (liste d'objet)
        this.hebdomadaireQueryAll = document.querySelectorAll("."+ +".Hebdomadaire.daySelector")
            //WeekDay
        this.hebdmadaireAllDays = document.querySelector("."+ v_colorPlug +".Hebdomadaire.AllDays");
        this.hebdomadaireLundi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Lundi");
        this.hebdomadaireMardi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Mardi");
        this.hebdomadaireMercredi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Mercredi");
        this.hebdomadaireJeudi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Jeudi");
        this.hebdomadaireVendredi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Vendredi");
        this.hebdomadaireSamedi = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Samedi");
        this.hebdomadaireDimanche = document.querySelector("."+ v_colorPlug +".Hebdomadaire.Dimanche");
            //Time Selector
        this.hebdomadaire_hDebut = document.querySelector("."+ v_colorPlug +".Hebdomadaire.hDebut");
        this.hebdomadaire_hFin = document.querySelector("."+ v_colorPlug +".Hebdomadaire.hFin");
            //submit
        this.hebdomadaireForm = document.querySelector("."+ v_colorPlug +".Hebdomadaire.formRequest");
        this.hebdomadairePause = document.querySelector("."+ v_colorPlug +".Hebdomadaire.pause");
        this.hebdomadaireSubmit = document.querySelector("."+ v_colorPlug +".Hebdomadaire.submit");
    }

    f_setQueryClone(v_colorPlug){
        /* Permet d'initialiser les QuerySelector pour le mode Clone */
        v_colorPlug = v_colorPlug ? v_colorPlug : this.v_colorPlug;

        this.cloneDiv = document.querySelector("."+ v_colorPlug +".Clone.div_subSummary");
        this.cloneSelector = document.querySelector("."+ v_colorPlug +".Clone.plugSelector");
        this.hebdomadairePause = document.querySelector("."+ v_colorPlug +".Hebdomadaire.pause");
        this.cloneSubmit = document.querySelector("."+ +".Clone.submitReset");
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
        this.cycliqueDiv.style.display="none";
        //masquage des DIV Hebdomadaire
        this.hebdomadaireDiv.style.display="none";
        //masquage des DIV Clone
        this.cloneDiv.style.display="none";

        console.log("displayNone");
    }
}

/* redPlug */
const red = new Plug("redPlug");
red.f_plugInit();

//var l_plug = ["redPlug", "greenPlug", "bluePlug", "yellowPlug"];
//var l_mode = ["Manuel", "Minuterie", "Cyclique", "Hebdomadaire", "Clone"];

// moseSelector Manuel
var modeManuel = document.querySelector(".redPlug.modeSelector.Manuel");
var manuelDiv = document.querySelector(".redPlug.Manuel.div_subSummary");
// Manuel on_off (1ere Colone)
var manuelON = document.querySelector(".redPlug .Manuel .ON");
var manuelOFF = document.querySelector(".redPlug .Manuel .OFF");

// Manuel (2eme Colone)
var manuelDivDiffTypeSelector = document.querySelector(".redPlug .Manuel .div_diffTypeSelector" );
var manuelDiffAt = document.querySelector(".redPlug .Manuel .diffAt" );
var manuelDiffIn = document.querySelector(".redPlug .Manuel .diffIn" );


// Manuel (3eme Colone)
var manuelDiv_hFin = document.querySelector(".redPlug .Manuel .div_hFin" );
var manuelDiv_dureeOff = document.querySelector(".redPlug .Manuel .div_dureeOff" );
// manuel Submit
var manuelForm = document.querySelector(".redPlug.Manuel.formRequest");
var manuelSubmit = document.querySelector(".redPlug .Manuel .submit" );

// Minuterie DIV
var minuterieDiv = document.querySelector(".redPlug.Minuterie.div_subSummary");

//Cyclique
var cycliqueDiv = document.querySelector(".redPlug.Cyclique.div_subSummary");

//Hebdomadaire
var hebdomadaireDiv = document.querySelector(".redPlug.Hebdomadaire.div_subSummary");

//Clone
var cloneDiv = document.querySelector(".redPlug.Clone.div_subSummary");

/* Fonction de masquage de tous les éléments */
function f_displayNoneAll(){
    //mode Manuel
    manuelDiv.style.display="none";
    manuelDivDiffTypeSelector.style.display="none";
    manuelDiv_hFin.style.display="none";
    manuelDiv_dureeOff.style.display="none";
    manuelDiffAt.checked = false;
    manuelDiffIn.checked = false;
    //masquage des DIV Minuterie
    minuterieDiv.style.display="none";
    //masquage des DIV Cyclique
    cycliqueDiv.style.display="none";
    //masquage des DIV Hebdomadaire
    hebdomadaireDiv.style.display="none";
    //masquage des DIV Clone
    cloneDiv.style.display="none";
}

//f_displayNoneAll();

/************************
* Mode Manuel : onclick *
************************/
//var manuelDiv = document.querySelector(".redPlug .Manuel .div_subSummary");
modeManuel.onclick = function (){
    f_displayNoneAll();
    manuelDiv.style.display="block";
    }

manuelON.onclick = function(){
    manuelDivDiffTypeSelector.style.display = "block"; 
    console.log("marche");
    }

manuelOFF.onclick = function(){
    manuelDivDiffTypeSelector.style.display = "none";
    manuelDiv_dureeOff.style.display = "none";
    manuelDiv_hFin.style.display = "none";
    console.log("Arrêt");
    }

manuelDiffAt.onclick = function(){
    manuelDiv_hFin.style.display = "block";
    manuelDiv_dureeOff.style.display = "none";
    manuelDiffIn.checked = false;
}

manuelDiffIn.onclick = function(){
    manuelDiv_dureeOff.style.display = "block";
    manuelDiv_hFin.style.display = "none";
    manuelDiffAt.checked = false;
}

manuelSubmit.onclick = function(){
    manuelForm.submit();
    manuelForm.reset();
    }

/***************** 
* Mode Minuterie *
*****************/
//var v_redMinuterie = document.getElementById("rMinuterie");
var v_redMinuterie = document.querySelector(".redPlug .modeSelector .Minuterie");

v_redMinuterie.onclick = function(){
    f_displayNoneAll();
    document.querySelector(".redPlug .Minuterie .submit").disabled = true;
    document.getElementsByClassName("redPlug Minuterie div_subSummary ")[0].style.display="block";
}

// Code de validation du format pour les durées (pour le mode Minuterie)
var v_regExDuree = /^(300|[0-2]{0,1}\d{1,2}|300:00|[0-2]{0,1}\d{0,2}:[0-5]\d{1})$/;
    // /!\Attention/!\:
    //      - les minutes sont comprises entre 0 et 300
    //      - les secondes sont comprises entre 0 et 59
    //          --> si les minutes sont égales à 300, les secondes doivent être égale à 0

var v_duree = document.querySelector(".redPlug .Minuterie .dureeOn"); 
    // attention il sagit d'un Objet, pas d'un tableau.
    // On ne peut donc pas faire de "foreach" dessus, mais seulement un "for"

v_duree.addEventListener("input", function(event){
    if (v_regExDuree.test(v_duree.value)){
        v_duree.style.border="2px solid green";
        document.querySelector(".redPlug .Minuterie .submit").disabled = false;
    } else {
        v_duree.style.border="2px solid red";
        document.querySelector(".redPlug .Minuterie .submit").disabled = true;
            }
}, false);


/****************
* Mode Cyclique *
****************/
//var v_redCyclique = document.getElementById("rCyclique");
var v_redCyclique = document.querySelector(".redPlug .modeSelector .Cyclique");

v_redCyclique.onclick = function(){
    f_displayNoneAll();
    document.getElementsByClassName("redPlug div_subSummary Cyclique")[0].style.display="block";
}


/********************
* Mode Hebdomadaire *
********************/
//var v_redHebdo = document.getElementById("rHebdomadaire");
var v_redHebdo = document.querySelector(".redPlug .modeSelector .Hebdomadaire");

v_redHebdo.onclick = function(){
    f_displayNoneAll();
    document.getElementsByClassName("redPlug div_subSummary Hebdomadaire")[0].style.display="block";
}

var v_daySelector = document.querySelectorAll(".redPlug .daySelector");
v_daySelector[0].addEventListener("click", function(event){ 
    if (v_daySelector[0].checked){ 
        for (var i=1; i<(v_daySelector.length); i++){
            v_daySelector[i].checked = true;
        }} }, false);


var v_weekDay = document.querySelector(".redPlug .Hebdomadaire .weekDay")
v_weekDay.addEventListener("click", function(event){
    if (!event.target.checked){
        v_daySelector[0].checked = false;
    }
}, false);
        

/*************
* Mode Clone *
*************/
//var v_redClone = document.getElementById("rClone");
var v_redClone = document.querySelector(".redPlug .modeSelector .Clone");

v_redClone.onclick = function(){
    f_displayNoneAll();
    document.getElementsByClassName("redPlug div_subSummary Clone")[0].style.display="block";
}

/////////////////////////////////////////////////////////////
//Code de validation du format pour les durées

/* /!\Attention/!\ */ 
// Le format de durée pour le mode Manuel et pour le mode Cyclique est sur 3 digit, pas de secondes
/*
var regExDureeNoSec = /^(300|[0-2]{0,1}\d{0,2})$/;
    // /!\Attention/!\:
    //      - les minutes sont comprises entre 0 et 300
*/

////////////////////////////////////////////////////////////////
// Code de validation du format pour les heures
/*
var regExHeure = /^([0-2]{0,1}\d{1}:[0-5]\d{1})$/;
    // /!\Attention/!\:
    //      - Les heures sont comprises entre 0 et 23
    //      - Les minutes sont comprises entre 0 et 59
*/

///////////////////////////////////////////////////////////////
// Code du bouton pause, avec 'auto-submit'
/*
var pause = document.querySelector(".redPlug.Cyclique.pause");

var v_dureeOnTest = document.querySelector(".redPlug.Cyclique.dureeOn");
var v_dureeOffTest = document.querySelector(".redPlug.Cyclique.dureeOff");
var v_hDebutTest = document.querySelector(".redPlug.Cyclique.hDebut");


pause.onclick = function(){
if (pause.checked){
  v_dureeOnTest.disabled = true;
  v_dureeOffTest.disabled = true;
  v_hDebutTest.disabled = true;
  console.log("Pause");
  this.form.submit();
} else {
  v_dureeOnTest.disabled = false;
  v_dureeOffTest.disabled = false;
  v_hDebutTest.disabled = false;
  console.log("Travail");
  this.form.submit();
} }
*/

////////////////////////////////////////////////////////

//test pour savoir si un éléments à bien une ou plusieur classe 
/*
var test = document.querySelector(".redPlug.Minuterie.dureeON");
test.classList.contains("patern_duree");
    // retourne un boolean
    */

///////////////////////////////////////////////////////////

//Fonction permettant d'afficher la requete d'un form dans la console
/*
function formLog(){
    var it = new FormData( document.getElementById('formCyclique') ).entries();
       var current = {};
       while ( ! current.done ) {
           current = it.next();
           console.info( current )
    }
}
*/
