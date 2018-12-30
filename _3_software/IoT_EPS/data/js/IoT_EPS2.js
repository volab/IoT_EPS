class Plug{
    constructor(v_colorPlug){
        this.v_colorPlug     = v_colorPlug;

        //définition des radio 'modeSelector'
        this.modeManuel;
        this.modeMinuterie;
        this.modeCyclique;
        this.modeHedbomadaire;
        this.modeClone;

        //Mode Manuel
        this.manuelDiv;
            //sub div colone 1
        this.manuelDiv_on_off;
        this.manuelON;
        this.manuelOFF;
            //sub div colone 2
        this.manuelDivDiffTypeSelector;
        this.manuelDiffAt;
        this.manuelDiffIn;
            //sub div colone 3 (1/2)
        this.manuelDiv_hFin;
        this.manuel_hFin;
            //sub div colone 3 (2/2)
        this.manuelDiv_dureeOff;
        this.manuel_dureeOff;
            //submit
        this.manuelSubmit;

        //Mode Minuterie
        this.minuterieDiv;
        this.minuterieDureeOn;
        this.minuterieSubmit;

        //Mode Cyclique
        this.cycliqueDiv;
        this.cycliqueDureeOn;
        this.cycliqueDureeOff;
        this.cycliqueSubmit;

        //Mode Hebdomadaire
        this.hebdomadaireDiv;
            //QuerySelectorAll (Liste d'objet)
        this.hebdomadaireQueryAll;
            //weekday
        this.hebdmadaireAllDays;
        this.hebdomadaireLundi;
        this.hebdomadaireMardi;
        this.hebdomadaireMercredi;
        this.hebdomadaireJeudi;
        this.hebdomadaireVendredi;
        this.hebdomadaireSamedi;
        this.hebdomadaireDimanche;
            //Time selector
        this.hebdomadaire_hDebut;
        this.hebdomadaire_hFin;
            //Submit
        this.hebdmadaireSubmit;

        //Mode Clone
        this.cloneDiv;
        this.cloneSelector;
        this.cloneSubmit;

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
    }

    f_plugInit(v_colorPlug){
        this.f_displayNoneAll();
        this.f_setQueryModeSelector(v_colorPlug);
        this.f_setQueryManuel(v_colorPlug);
        this.f_setQueryMinuterie(v_colorPlug);
        this.f_setQueryCyclique(v_colorPlug);
        this.f_setQueryHebdomadaire(v_colorPlug);
        this.f_setQueryClone(v_colorPlug);
    }

    f_displayNoneAll(){
        /* Permet de masquer tous les DIV à l'intérieur des FILDSET */

    }

    f_setQueryModeSelector(v_colorPlug){
        /* Permet d'initialiser les QuerySelector des boutons radio pour le 'modeSelector */
        this.modeManuel = document.querySelector("." + v_colorPlug + " .modeSelector .Manuel");
        this.modeMinuterie = document.querySelector("." + v_colorPlug + " .modeSelector .Minuterie");
        this.modeCyclique = document.querySelector("." + v_colorPlug + " .modeSelector .Cyclique");
        this.modeHedbomadaire = document.querySelector("." + v_colorPlug + " .modeSelector .Hebdomadaire");
        this.modeClone = document.querySelector("." + v_colorPlug + " .modeSelector .Clone");
        console.log("f_setQueryModeSelector");
    }

    f_setQueryManuel(v_colorPlug){
        /* Permet d'initialiser les QerySelector su mode Manuel */
        this.manuelDiv = document.querySelector("." + v_colorPlug + ".Manuel.div_subSummary" );
            //sub div colone 1
        this.manuelDiv_on_off  = document.querySelector("." + v_colorPlug + " .Manuel .on_off" );
        this.manuelON  = document.querySelector("." + v_colorPlug + " .Manuel .ON" );
        this.manuelOFF  = document.querySelector("." + v_colorPlug + " .Manuel .OFF" );
            //sub div colone 2
        this.manuelDivDiffTypeSelector  = document.querySelector("." + v_colorPlug + " .Manuel .div_diffTypeSelector" );
        this.manuelDiffAt  = document.querySelector("." + v_colorPlug + " .Manuel .diffAt" );
        this.manuelDiffIn  = document.querySelector("." + v_colorPlug + " .Manuel .diffIn" );
            //sub div colone 3 (1/2)
        this.manuelDiv_hFin  = document.querySelector("." + v_colorPlug + " .Manuel .div_hFin" );
        this.manuel_hFin  = document.querySelector("." + v_colorPlug + " .Manuel .hFin" );
            //sub div colone 3 (2/2)
        this.manuelDiv_dureeOff  = document.querySelector("." + v_colorPlug + " .Manuel .div_dureeOff" );
        this.manuel_dureeOff  = document.querySelector("." + v_colorPlug + " .Manuel .dureeOff .dureeNoSec" );
        //Submit
        this.manuelSubmit = document.querySelector("." + v_colorPlug + " .Manuel .submit" );
    }

    f_setQueryMinuterie(v_colorPlug){
        /* Permet d'initialiser les QerySelector su mode Minuterie */
        this.minuterieDiv = document.querySelector("." + v_colorPlug +  " .Minuterie .div_subSummary");
        this.minuterieDureeOn = document.querySelector("." + v_colorPlug +  " .Minuterie .dureeOn");
        this.minuterieSubmit = document.querySelector("." + v_colorPlug +  " .Minuterie .submit");
    }

    f_setQueryCyclique(v_colorPlug){
        this.cycliqueDiv = document.querySelector("."+ v_colorPlug +".Cyclique.div_subSummary");
        this.cycliqueDureeOn = document.querySelector("."+ v_colorPlug +".Cyclique.dureeOn");
        this.cycliqueDureeOff = document.querySelector("."+ v_colorPlug +".Cyclique.dureeOff");
        this.cycliquehDebut = document.querySelector("."+ +".Cyclique.hDebut");
        this.cycliqueSubmit = document.querySelector("."+ v_colorPlug +".Cyclique.submit");
    }
    f_setQueryHebdomadaire(v_colorPlug){
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
        this.hebdmadaireSubmit = document.querySelector("."+ v_colorPlug +".Hebdomadaire.submit");
    }

    f_setQueryClone(v_colorPlug){
        this.cloneDiv = document.querySelector("."+ v_colorPlug +".Clone.div_subSummary");
        this.cloneSelector = document.querySelector("."+ v_colorPlug +".Clone.plugSelector");
        this.cloneSubmit = document.querySelector("."+ +".Clone.submitReset");
    }
}

/* Test de Class */
const red = new Plug("redPlug");
red.f_setQueryModeSelector();
console.log(red.modeManuel);
console.log(red.v_regExDuree);
console.log(red.v_colorPlug)

//var l_plug = ["redPlug", "greenPlug", "bluePlug", "yellowPlug"];
//var l_mode = ["Manuel", "Minuterie", "Cyclique", "Hebdomadaire", "Clone"];

//var v_divDiffSelector = document.getElementsByClassName ("redPlug div_DiffSelector");
//var v_divDiffSelector = document.querySelector(".redPlug .Manuel .div_diffTypeSelector" );

// moseSelector Manuel
var v_redManuel = document.querySelector(".redPlug .modeSelector .Manuel");
var manuelDiv = document.querySelector(".redPlug.Manuel.div_subSummary");
// Manuel on_off (1ere Colone)
var v_rRdOn = document.querySelector(".redPlug .Manuel .ON");
var v_rRdOff = document.querySelector(".redPlug .Manuel .OFF");

// Manuel (2eme Colone)
var  manuelDivDiffTypeSelector = document.querySelector(".redPlug .Manuel .div_diffTypeSelector" );
var manuelDiffAt = document.querySelector(".redPlug .Manuel .diffAt" );
var manuelDiffIn = document.querySelector(".redPlug .Manuel .diffIn" );


// Manuel (3eme Colone)
var manuelDiv_hFin = document.querySelector(".redPlug .Manuel .div_hFin" );
var manuelDiv_dureeOff = document.querySelector(".redPlug .Manuel .div_dureeOff" );
// manuel Submit
var v_redSubmit = document.querySelector(".redPlug .Manuel .submit" );

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

f_displayNoneAll();

/************************
* Mode Manuel : onclick *
************************/
//var manuelDiv = document.querySelector(".redPlug .Manuel .div_subSummary");
v_redManuel.onclick = function (){
    f_displayNoneAll();
    manuelDiv.style.display="block";
    }

v_rRdOn.onclick = function(){
    manuelDivDiffTypeSelector.style.display = "block"; 
    console.log("marche");
    }

v_rRdOff.onclick = function(){
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

v_redSubmit.onclick = function(){
    document.getElementById("formMA").submit();
    document.getElementById("formMA").reset();
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
